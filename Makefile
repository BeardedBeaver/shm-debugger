.PHONY: all clean venv install_dependencies release debug

VENV_NAME := .venv
CONAN_VERSION := 1.60.2
CONAN_PROFILE := VisualStudioProfile
BUILD_DIR := cmake-build

all: venv

venv:
	python -m venv $(VENV_NAME)

install_dependencies: venv
	$(VENV_NAME)\Scripts\pip install conan==$(CONAN_VERSION)

release: install_dependencies
	$(VENV_NAME)\Scripts\conan install . -if $(BUILD_DIR)/dependencies/conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Release

debug: install_dependencies
	$(VENV_NAME)\Scripts\conan install . -if $(BUILD_DIR)/dependencies/conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Debug

clean:
	rm -rf $(VENV_NAME) $(BUILD_DIR)
