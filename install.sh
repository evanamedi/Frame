#!/bin/bash

set -e

INSTALL_DIR="$HOME/.local/bin"
EXECUTABLE_NAME="frame"

check_requirements() {
	echo "Checking system requirements..."

	if ! command -v gcc &> /dev/null; then
		echo "Error: gcc not found. Please install GCC and try again."
		exit 1
	fi

	if ! command -v make &> /dev/null; then
		echo "Error: make not found. Please install Make and try again"
		exit 1
	fi

	echo "All requirements met"
}

clone_repository() {
	REPO_URL="https://github.com/evanamedi/Frame.git"
	LOCAL_REPO_DIR="$HOME/frame"

	if [ -d "$LOCAL_REPO_DIR" ]; then
		echo "Removing existing directory: $LOCAL_REPO_DIR"
		rm rf "$LOCAL_REPO_DIR"
	fi

	echo "Cloning repository to $LOCAL_REPO_DIR..."
	git clone $REPO_URL $LOCAL_REPO_DIR
	cd $LOCAL_REPO_DIR || exit
}

build_project() {
	echo "building project..."
	make clean
	make
}

install_executable() {
	echo "Installing executable to $INSTALL_DIR"

	mkdir -p $INSTALL_DIR

	cp frame $INSTALL_DIR/$EXECUTABLE_NAME

	echo "Installation complete. You may need to restart you terminal. Run 'frame help' to get started"
}

update_path() {
	if ! echo "$PATH" | grep -q "$HOME/.local/bin"; then
		echo "Adding $INSTALL_DIR to your PATH..."
		SHELL_PROFILE=""
		if [ -n "$BASH_VERSION" ]; then
			SHELL_PROFILE="$HOME/.bashrc"
		elif [ -n "$ZSH_VERSION" ]; then
			SHELL_PROFILE="$HOME/.zshrc"
		fi

		if [ -n "$SHELL_PROFILE" ]; then
			echo 'export PATH="$HOME/.local/bin:$PATH"' >> "$SHELL_PROFILE"
			echo "Please restart your terminal or run 'source $SHELL_PROFILE' to update your PATH."
		else
			echo "Couldn't detect shell profile. Add the following line to your shell configuration file:"
			echo 'export PATH="$HOME/.local/bin:$PATH"'
		fi
	else
		echo "$INSTALL_DIR is already in your PATH."
	fi
}

check_requirements
clone_repository
build_project
install_executable
update_path
