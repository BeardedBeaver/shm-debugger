.PHONY: all clean venv release debug

SHELL=cmd

VENV_DIR := venv
VENV_BIN_DIR := $(VENV_DIR)\Scripts
CONAN_VERSION := 1.60.2
CONAN_PROFILE := VisualStudioProfile
BUILD_DIR := cmake-build

all: venv

venv:
	python -m venv $(VENV_DIR)
	$(VENV_BIN_DIR)\pip install conan==$(CONAN_VERSION)

release: venv
	$(VENV_BIN_DIR)\conan install . -if $(BUILD_DIR)\dependencies\conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Release

debug: venv
	$(VENV_BIN_DIR)\conan install . -if $(BUILD_DIR)\dependencies\conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Debug

clean:
	rmdir /S /Q $(VENV_DIR) & rmdir /S /Q $(BUILD_DIR)
