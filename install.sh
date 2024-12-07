#!/bin/bash

RED='\033[0;31m'
BOLD_RED='\033[1;31m'
GREEN='\033[0;32m'
BOLD_GREEN='\033[1;32m'
NC='\033[0m'
YELLOW='\033[0;33m'
BOLD_YELLOW='\033[1;33m'

check_exit_status() {
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}$1${NC}"
        return 0
    else
        echo -e "${BOLD_RED}$2${NC}"
        return 1
    fi
}

check_wabt() {
	if which wasm2wat &> /dev/null; then
		echo -e "${GREEN}Wabt is installed${NC}"
		return 0
	else
		echo -e "${YELLOW}Installing Wabt...${NC}"
		brew install wabt
		check_exit_status "Wabt installed" "Failed to install Wabt"
	fi
}

check_rust() {
	rustc --version &> /dev/null
	check_exit_status "$1" "$2"
	if [ $? -eq 1 ]; then
		rust_install
	fi
}

rust_install() {
	echo -e "${YELLOW}Installing Rust...${NC}"
	brew install rust
	check_exit_status "Rust and cargo installed" "Failed to install Rust and cargo"
	cargo install cargo-stylus
	check_exit_status "cargo-stylus downloaded" "Failed to download cargo-stylus"
}

check_wasmld() {
	wasm-ld --version &> /dev/null
	check_exit_status "$1" "$2"
}

llvm_install(){
	echo -e "${GREEN}Installing LLVM...${NC}"
	brew install llvm@15
	check_exit_status "$1" "$2"
	echo -e "${YELLOW}Setting up LLVM...${NC}"
    echo -e 'export PATH="$HOME/.brew/opt/llvm@15/bin:$PATH"' >> $HOME/.${SHELL##*/}rc
	echo -e "${GREEN}LLVM installed${NC}"
}

check_llvm() { 
	llvm-config --version &> /dev/null;
	check_exit_status "$1" "$2"
	if [ $? -eq 1 ]; then
		llvm_install
	fi
}

check_docker_desktop() {
	if [ -d "/Applications/Docker.app" ]; then
		echo -e "${GREEN}Docker Desktop is installed${NC}"
		return 0
	else
		echo -e "Installing Docker Desktop..."
		brew install --cask docker
		if [ $? -eq 0 ]; then
			echo -e "Docker Desktop installed"
			return 0
		else
			echo -e "Failed to install Docker Desktop"
			return 1
		fi
	fi
}

check_brew() {
	if ! command -v brew &> /dev/null; then
		return 1
	else
		return 0
	fi
}

macos_install() {
	echo -e "${YELLOW}Installing dependencies. for macOS...${NC}"
	check_brew
	if [ $? -eq 0 ]; then
		echo -e "${GREEN}Brew is installed${NC}"
	else
		echo -e "${YELLOW}Installing Brew...${NC}"
		/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
	check_docker_desktop
	check_llvm "LLVM is installed" "LLVM not installed"
	check_wasmld "Wasm-ld is installed\ncheck PATH or try manually 'brew reinstall llvm'" "Installed Wasm-ld..."
	check_rust "Rust is installed" "Rust not installed"
	check_wabt
	echo -e "${BOLD_GREEN}Installation complete${NC}"
	echo -e "${BOLD_YELLOW}Please restart your terminal\nIf in any case you're facing any troubles try to reinstall llvm@15 and rust manually!!$\n\t Use:\n\t\t'brew reinstall llvm@15'\n\t\t\n\t\t'brew reinstall rust${NC}"
}

linux_install() {
	echo -e "${BOLD_RED}Installation for Linux pending${NC}"
}

check_os() {
	if [[ $OSTYPE == darwin* ]]; then
		macos_install
	elif [[ $OSTYPE == linux* ]]; then
		echo -e "Linux"
	else
		echo -e "${BOLD_RED}Unsupported OS${NC}"
		exit 1
	fi
}

echo -e "${YELLOW}Installing...${NC}"
check_os
