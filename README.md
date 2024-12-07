# Loan System with Arbitrum Stylus

## What Aimed to Create and our Result
- We wanted to do a Loan system which took a collateral deposit for the gas used, requested the loan and once accepted payed it.
- We also added an extra part to make the installation of all the dependencies and lets you execute a basic program adding your information

- The final result was not as expected, it ended up not working hence we kept the initial version which created the contract with the ping-pong and Hello World and the bash scripting `install.sh` to install everything 

## Instalation

To install and configure all the necessary environment, simply run the `install.sh` script included in this repository. This script takes care of installing all the dependencies and configuring the project.

### Steps:

1. **Clone the repo:**

    ```bash
    git clone --recurseshttps://github.com/erikgonk/Hackathon-Lemon.git Arbitrum_Stylus_Project
    cd Arbitrum_Stylus_Project
    git submodule update --init --recursive
    ```

2. **Run the installation script:**

    ```bash
    bash install.sh
    ```

3. **Add your Wallet:**
   
        ```bash
   Change line 18 and insert your Contact Address ```
   Change Line 26 and insert your Account
      ```
   
5. **Execute the program:**
    ```bash
    make
    cargo stylus deploy --wasm-file ./contract.wasm -e https://sepolia-rollup.arbitrum.io/rpc --cargo-stylus-version 0.5.3 --private-key INSERT_YOUR_PRIVATE_KEY
    ```

This script performs the following:
- Verifies the installation of Node.js, Docker, Rust and the Arbitrum Stylus CLI.
- Downloads and installs the necessary dependencies.
- Configures a local Arbitrum node using Docker.
- Compile and deploy Stylus contracts to the local node.

## Repo Structure

#### The repository contains the following files and directories:

- `install.sh`: Installation script that configures the environment, dependencies and the local Arbitrum node.

- `frontend/`: Contains the user interface for interacting with the Arbitrum node and Stylus contracts.

- `contracts/`: Stores smart contracts written in WASM or Stylus-compatible languages for deployment.

- `playground/`: A test environment for interacting with contracts and validating their operation.

- `stylus-sdk-c/`: SDK to interact with Stylus using C and facilitate the development of compatible applications.

- `include/`: Contains header files needed for the SDK and other components.

- `Cargo.toml, Cargo.lock, rust-toolchain.toml`: Configurations needed for the Rust environment.

- `Makefile`: Contains the necessary instructions to automate compilation and configuration tasks.

- `package.json`: Configuration file for JavaScript dependencies and frontend tasks.

- `build.rs & entry.rs`: Scripts related to building and configuring Stylus contracts and other components.
