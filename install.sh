#!/bin/bash

check_wabt() {
	brew install wabt > /dev/null
	if [ $? -eq 0 ]; then
		echo "Wabt installed"
		return 0
	else
		echo "Failed to install Wabt"
		return 1
	fi
	wasm-strip --version
}

rust_install() {
	echo "Installing Rust..."
	brew install rust > /dev/null
	check_exit_status "Rust installed" "Failed to install Rust"
    # export PATH="$HOME/.cargo/bin:$PATH"
	# source ~/.${SHELL##*/}rc
	rustc --version && cargo --version
	check_exit_status "Rust and cargo installed" "Failed to install Rust and cargo"
}

check_wasmld() {
	wasm-ld --version
	check_exit_status "$1" "$2"
}

llvm_install(){
	brew install llvm@15
	check_exit_status "$1" "$2"
	echo "Setting up LLVM..."
    echo 'export PATH="$HOME/.brew/opt/llvm@15/bin:$PATH"' >> $HOME/.${SHELL##*/}rc
	# source ~/.${SHELL##*/}rc
}

check_llvm() { 
	llvm-config --version &> /dev/null;
	check_exit_status "$1" "$2"
}

check_docker_desktop() {
	if [ -d "/Applications/Docker.app" ]; then
		echo "Docker Desktop is installed"
		return 0
	else
		echo "Installing Docker Desktop..."
		brew install --cask docker
		if [ $? -eq 0 ]; then
			echo "Docker Desktop installed"
			return 0
		else
			echo "Failed to install Docker Desktop"
			return 1
		fi
	fi
}

check_exit_status() {
    if [ $? -eq 0 ]; then
        echo -e "$1"
        return 0
    else
        echo -e "$2"
        return 1
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
	echo "Installing dependencies..."
	check_brew
	if [ $? -eq 0 ]; then
		echo "Brew is installed"
	else
		echo "Installing Brew..."
		/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
	check_docker_desktop
	check_llvm "LLVM is installed" "LLVM not installed"
	llvm_install "LLVM installed" "Failed to install LLVM"
	# check_wasmld "Wasm-ld is installed\ncheck PATH or try manually 'brew reinstall llvm'" "Installed Wasm-ld..."
	rust_install
	check_wabt
	echo
}

linux_install() {
	echo "Installing for Linux"
}

check_os() {
	if [[ $OSTYPE == darwin* ]]; then
		macos_install
	elif [[ $OSTYPE == linux* ]]; then
		echo "Linux"
	else
		echo "Unsupported OS"
		exit 1
	fi
}

echo "Installing..."
check_os

# # curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# brew install llvm
# export PATH="/usr/local/opt/llvm/bin:$PATH"
# export LDFLAGS="-L/usr/local/opt/llvm/lib"
# export CPPFLAGS="-I/usr/local/opt/llvm/include"
# export CXX=clang++
# export CC=clang
# source $SHELL
# source ~/.bashrc
