#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"

#define STORAGE_SLOT__collateral 0x0 // Define la dirección base para almacenar colateral
#define COLLATERALIZATION_RATIO 1.5  // Define el ratio de colateralización requerido

// Buffer utilizado para devolver datos sin usar malloc
uint8_t buf_out[32];

// Estructura para usuarios en almacenamiento persistente
typedef struct {
    uint8_t address[32]; // Dirección del usuario (padded)
    double collateral;   // Cantidad de colateral depositado
    double debt;         // Monto total del préstamo actual
} User;

// Validación de direcciones válidas
bool inline is_valid_address(uint8_t *input, size_t len) {
    return len == 32 && bebi32_is_u160(input);
}

// Almacena el colateral en un slot de almacenamiento persistente
ArbResult set_collateral(uint8_t *input, size_t len) {
    if (len != 32) {
        // Revertir si la longitud de entrada no es válida
        return _return_short_string(Failure, "InvalidLength");
    }

    uint8_t address[32];
    msg_sender_padded(address); // Obtiene la dirección del remitente

    uint8_t slot_address[32];
    storage_key_from_buffer(address, 32, slot_address); // Genera clave única basada en la dirección

    User user;
    if (!storage_exists(slot_address)) {
        user.collateral = 0;
        user.debt = 0;
        memcpy(user.address, address, 32);
    } else {
        storage_get(slot_address, &user, sizeof(User)); // Recupera datos existentes
    }

    user.collateral += bebi32_to_double(input); // Agrega el colateral

    storage_set(slot_address, &user, sizeof(User)); // Persiste los datos
    storage_flush_cache(false); // Flushea para persistir el almacenamiento

    return _return_success_bebi32(input);
}

// Recupera el colateral almacenado
ArbResult get_collateral(uint8_t *input, size_t len) {
    uint8_t address[32];
    msg_sender_padded(address); // Obtiene la dirección del remitente

    uint8_t slot_address[32];
    storage_key_from_buffer(address, 32, slot_address); // Genera clave única

    if (!storage_exists(slot_address)) {
        return _return_short_string(Failure, "NoCollateral");
    }

    User user;
    storage_get(slot_address, &user, sizeof(User)); // Recupera datos del usuario

    bebi32_set_double(buf_out, user.collateral); // Escribe el colateral en buf_out
    return _return_success_bebi32(buf_out);
}

// Función para calcular el máximo préstamo permitido basado en el colateral
double calculate_max_loan(double collateral) {
    return collateral / COLLATERALIZATION_RATIO;
}

// Solicitar préstamo basado en colateral
ArbResult request_loan(uint8_t *input, size_t len) {
    if (len != 32) {
        return _return_short_string(Failure, "InvalidLength");
    }

    uint8_t address[32];
    msg_sender_padded(address); // Obtiene la dirección del remitente

    uint8_t slot_address[32];
    storage_key_from_buffer(address, 32, slot_address); // Genera clave única

    if (!storage_exists(slot_address)) {
        return _return_short_string(Failure, "UserNotFound");
    }

    User user;
    storage_get(slot_address, &user, sizeof(User)); // Carga los datos del usuario

    double loan_amount = bebi32_to_double(input); // Convierte input a double
    double max_loan = calculate_max_loan(user.collateral);

    if (loan_amount > max_loan) {
        return _return_short_string(Failure, "ExceedsMaxLoan");
    }

    user.debt += loan_amount;
    storage_set(slot_address, &user, sizeof(User)); // Actualiza los datos del usuario

    bebi32_set_double(buf_out, loan_amount); // Escribe el monto del préstamo en buf_out
    return _return_success_bebi32(buf_out);
}

// Maneja la ejecución de funciones según los selectores
int handler(size_t argc) {
    uint8_t argv[argc];
    read_args(argv);

    FunctionRegistry registry[] = {
        {to_function_selector("set_collateral(uint256)"), set_collateral},
        {to_function_selector("get_collateral()"), get_collateral},
        {to_function_selector("request_loan(uint256)"), request_loan},
    };

    uint32_t signature = *((uint32_t *)argv);

    ArbResult res = call_function(
        registry,
        sizeof(registry) / sizeof(registry[0]),
        signature,
        argv + 4, // Excluye selector
        argc - 4
    );

    return (write_result(res.output, res.output_len), res.status);
}

ENTRYPOINT(handler)