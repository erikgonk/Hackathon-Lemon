# Arbitrum Stylus Project

Este repositorio contiene un proyecto de ejemplo desarrollado con Arbitrum Stylus, una herramienta para la creación de contratos inteligentes de alto rendimiento con soporte para WebAssembly.

## Instalación

Para instalar y configurar todo el entorno necesario, simplemente ejecuta el script `install.sh` incluido en este repositorio. Este script se encarga de instalar todas las dependencias y configurar el proyecto.

### Pasos:

1. **Clona este repositorio:**

    ```bash
    git clone https://github.com/erikgonk/Hackathon-Lemon.git Hackaton_Lemon
    cd Hackaton_Lemon
    ```

2. **Ejecuta el script de instalación:**

    ```bash
    bash install.sh
    ```

Este script realiza lo siguiente:
- Verifica la instalación de Node.js, Docker, Rust y el CLI de Arbitrum Stylus.
- Descarga e instala las dependencias necesarias.
- Configura un nodo local de Arbitrum utilizando Docker.
- Compila y despliega los contratos Stylus en el nodo local.

## Estructura del repositorio

- El repositorio contiene los siguientes archivos y directorios:

`install.sh`: Script de instalación que configura el entorno, las dependencias y el nodo local de Arbitrum.

`frontend/`: Contiene la interfaz de usuario para interactuar con el nodo de Arbitrum y los contratos Stylus.

`contracts/`: Almacena los contratos inteligentes escritos en WASM o lenguajes compatibles con Stylus para su despliegue.

`playground/`: Un entorno de pruebas para interactuar con los contratos y validar su funcionamiento.

`stylus-sdk-c/`: SDK para interactuar con Stylus utilizando C y facilitar el desarrollo de aplicaciones compatibles.

`include/`: Contiene archivos de encabezado necesarios para el SDK y otros componentes.

`Cargo.toml, Cargo.lock, rust-toolchain.toml`: Configuraciones necesarias para el entorno Rust.

`Makefile`: Contiene las instrucciones necesarias para automatizar tareas de compilación y configuración.

`package.json`: Archivo de configuración para dependencias de JavaScript y tareas de frontend.

`build.rs & entry.rs`: Scripts relacionados con la construcción y configuración de los contratos Stylus y otros componentes.
