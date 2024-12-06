#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"

/**
 * General utils/helpers
 */

// buffer used to write output, avoiding malloc
uint8_t buf_out[32];

// succeed and return a bebi32
ArbResult inline _return_success_bebi32(bebi32 const retval) {
  ArbResult res = {Success, retval, 32};
  return res;
}

// Validate if input is a valid address (padded to 32 bytes)
bool inline is_valid_address(uint8_t *input, size_t len) {
  if (len != 32)
    return false;

  if (!bebi32_is_u160(input))
    return false;

  return true;
}

ArbResult calldata_len(uint8_t *input, size_t len) {
  bebi32_set_u32(buf_out, len);
  return _return_success_bebi32(buf_out);
}

// Function to retrieve the caller's padded address
ArbResult mi_balance(uint8_t *input, size_t len) {
	msg_sender_padded(buf_out);
	return _return_success_bebi32(buf_out);
}

// Main handler to route calls to the appropriate function
int handler(size_t argc) {
  uint8_t argv[argc];
  read_args(argv); // Read function selector and calldata

  // Registry of functions
  FunctionRegistry registry[] = {
      {to_function_selector("calldata_len()"), calldata_len},
      {to_function_selector("mi_balance()"), mi_balance},
  };

  uint32_t signature = *((uint32_t *)argv); // Take function selector

  // Call the function based on the signature
  ArbResult res = call_function(registry,
                                sizeof(registry) / sizeof(registry[0]),
                                signature, argv + 4, argc - 4 // Exclude the selector from calldata
  );
  // Write the result and return the status
  return (write_result(res.output, res.output_len), res.status);
}

ENTRYPOINT(handler)
