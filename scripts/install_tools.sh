#!/bin/bash
set -e 

ARM_TOOLCHAIN_INSTALL_DIR=${HOME}/arm
ARM_TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu/12.3.rel1/binrel/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz?rev=dccb66bb394240a98b87f0f24e70e87d&hash=B788763BE143D9396B59AA91DBA056B6"
ARM_TOOLCHAIN_FILENAME=arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz
ARM_TOOLCHAIN_EXTRACT_DIR_NAME="${ARM_TOOLCHAIN_FILENAME%.tar.xz}"

OPENOCD_INSTALL_DIR=${HOME}/openocd
OPENOCD_URL="https://github.com/xpack-dev-tools/openocd-xpack/releases/download/v0.12.0-1/xpack-openocd-0.12.0-1-linux-x64.tar.gz"
OPENOCD_FILENAME="xpack-openocd-0.12.0-1-linux-x64.tar.gz"
OPENOCD_EXTRACT_DIR_NAME="${OPENOCD_FILENAME%.tar.gz}"

function install_arm_toolchain()
{
    echo "Installing ARM Toolchain..."
    echo "Cleaning pre-existent logical links..."
    rm -rf ${HOME}/bin/arm-none-eabi-* ${HOME}/.local/bin/arm-none-eabi-*

    echo "Cleaning pre-existing arm toolchain install dir..."
    rm -rf ${ARM_TOOLCHAIN_INSTALL_DIR}

    echo "Downloading ARM toolchain from ${ARM_TOOLCHAIN_URL} to ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME}..."
    curl -L ${ARM_TOOLCHAIN_URL} --create-dirs -C - \
        -o ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME}

    echo "Untaring arm toolchain in ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}..."
    tar -xf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME} -C ${ARM_TOOLCHAIN_INSTALL_DIR}

    echo "Making logical links..."
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-gcc      ${HOME}/.local/bin/arm-none-eabi-gcc
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-ld       ${HOME}/.local/bin/arm-none-eabi-ld
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-objdump  ${HOME}/.local/bin/arm-none-eabi-objdump
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-objcopy  ${HOME}/.local/bin/arm-none-eabi-objcopy
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-size     ${HOME}/.local/bin/arm-none-eabi-size
    ln -sf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-gdb      ${HOME}/.local/bin/arm-none-eabi-gdb

    if grep -Fxq 'PATH=${HOME}/.local/bin:${PATH}' ${HOME}/.bashrc
    then
        echo "${HOME}/.local/bin already exists in ${HOME}/.bashrc!"
    else
        echo "Adding \${HOME}/.local/bin to PATH..."
        echo 'PATH=${HOME}/.local/bin:${PATH}' >> ${HOME}/.bashrc
        export PATH=${HOME}/.local/bin:${PATH}
    fi

    echo "ARM Toolchain installed succesfully!"
}

function install_openocd()
{
    echo "Installing OpenOCD..."
    echo "Cleaning pre-existent logical links..."
    rm -rf ${HOME}/bin/openocd ${HOME}/.local/bin/openocd

    echo "Cleaning pre-existing openocd install dir..."
    rm -rf ${OPENOCD_INSTALL_DIR}

    echo "Downloading openocd from ${OPENOCD_URL} to ${OPENOCD_INSTALL_DIR}/${OPENOCD_FILENAME}..."
    curl -L ${OPENOCD_URL} --create-dirs -C - \
        -o ${OPENOCD_INSTALL_DIR}/${OPENOCD_FILENAME}

    echo "Untaring openocd in ${OPENOCD_INSTALL_DIR}/${OPENOCD_EXTRACT_DIR_NAME}..."
    tar -xf ${OPENOCD_INSTALL_DIR}/${OPENOCD_FILENAME} \
        --one-top-level=${OPENOCD_EXTRACT_DIR_NAME} \
        --strip-components 1 \
        -C ${OPENOCD_INSTALL_DIR}

    echo "Making logical links: ${OPENOCD_INSTALL_DIR}/${OPENOCD_EXTRACT_DIR_NAME}/bin/openocd -> ${HOME}/.local/bin/openocd"
    ln -sf ${OPENOCD_INSTALL_DIR}/${OPENOCD_EXTRACT_DIR_NAME}/bin/openocd     ${HOME}/.local/bin/openocd

    if grep -Fxq 'PATH=${HOME}/.local/bin:${PATH}' ${HOME}/.bashrc
    then
        echo "${HOME}/.local/bin already exists in ${HOME}/.bashrc!"
    else
        echo "Adding \${HOME}/.local/bin to PATH..."
        echo 'PATH=${HOME}/.local/bin:${PATH}' >> ${HOME}/.bashrc
        export PATH=${HOME}/.local/bin:${PATH}
    fi

    echo "OpenOCD installed succesfully!"
}

mkdir -p ${HOME}/.local/bin
install_arm_toolchain
install_openocd