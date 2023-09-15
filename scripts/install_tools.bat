@set CHOCO_COMMON_FLAGS=-y 

@echo "Uninstalling previous versions..."
choco uninstall make openocd-xpack gcc-arm-embedded --yes --no-color

@echo "Installing Make..."
choco install make %CHOCO_COMMON_FLAGS%^
    --version=4.4.1

@echo "Installing OpenOCD..."
choco install openocd-xpack %CHOCO_COMMON_FLAGS%^
    --version=0.11.0.4

@echo "Installing ARM Toolchain..."
choco install gcc-arm-embedded %CHOCO_COMMON_FLAGS%^
    --version=10.3.1