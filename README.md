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

- `src/contratos/`: Contiene los códigos fuente de los contratos inteligentes escritos en WASM o lenguajes compatibles.
- `build/`: Contiene los artefactos generados después de la compilación.
- `scripts/`: Scripts útiles para implementar o interactuar con los contratos.
