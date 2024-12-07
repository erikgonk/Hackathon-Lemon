# Arbitrum Stylus Project

This repository contains a sample project developed with Arbitrum Stylus, a high-performance smart contract creation tool with support for WebAssembly.

## Instalation

To install and configure all the necessary environment, simply run the `install.sh` script included in this repository. This script takes care of installing all the dependencies and configuring the project.

### Steps:

1. **Clone the repo:**

    ```bash
    git clone https://github.com/erikgonk/Hackathon-Lemon.git Arbitrum_Stylus_Project
    cd Arbitrum_Stylus_Project
    git submodule update --init --recursive
    ```

2. **Run the installation script:**

    ```bash
    bash install.sh
    ```

3. **Add your Wallet:**
        ```bash
   Change line 18 and insert your Contact Address
   Change Line 26 and insert your Account
       ```
   
5. **Execute the program:**
    ```bash
    make
    cargo stylus deploy --wasm-file ./contract.wasm -e https://sepolia-rollup.arbitrum.io/rpc --cargo-stylus-version 0.5.3 --private-key INSERT_YOUR_PRIVATE_KEY
    ```

Este script realiza lo siguiente:
- Verifica la instalación de Node.js, Docker, Rust y el CLI de Arbitrum Stylus.
- Descarga e instala las dependencias necesarias.
- Configura un nodo local de Arbitrum utilizando Docker.
- Compila y despliega los contratos Stylus en el nodo local.

## Estructura del repositorio

#### El repositorio contiene los siguientes archivos y directorios:

- `install.sh`: Script de instalación que configura el entorno, las dependencias y el nodo local de Arbitrum.

- `frontend/`: Contiene la interfaz de usuario para interactuar con el nodo de Arbitrum y los contratos Stylus.

- `contracts/`: Almacena los contratos inteligentes escritos en WASM o lenguajes compatibles con Stylus para su despliegue.

- `playground/`: Un entorno de pruebas para interactuar con los contratos y validar su funcionamiento.

- `stylus-sdk-c/`: SDK para interactuar con Stylus utilizando C y facilitar el desarrollo de aplicaciones compatibles.

- `include/`: Contiene archivos de encabezado necesarios para el SDK y otros componentes.

- `Cargo.toml, Cargo.lock, rust-toolchain.toml`: Configuraciones necesarias para el entorno Rust.

- `Makefile`: Contiene las instrucciones necesarias para automatizar tareas de compilación y configuración.

- `package.json`: Archivo de configuración para dependencias de JavaScript y tareas de frontend.

- `build.rs & entry.rs`: Scripts relacionados con la construcción y configuración de los contratos Stylus y otros componentes.
