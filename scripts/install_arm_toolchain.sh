#!/bin/bash

ARM_TOOLCHAIN_INSTALL_DIR=${HOME}/arm
ARM_TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu/12.3.rel1/binrel/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz?rev=dccb66bb394240a98b87f0f24e70e87d&hash=B788763BE143D9396B59AA91DBA056B6"
ARM_TOOLCHAIN_FILENAME=arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz
ARM_TOOLCHAIN_EXTRACT_DIR_NAME="${ARM_TOOLCHAIN_FILENAME%.tar.xz}"

mkdir -p ${HOME}/.local/bin

echo "Cleaning pre-existent logical links..."
rm -rf ${HOME}/bin/arm-none-eabi-*

echo "Cleaning pre-existing arm toolchain install dir..."
rm -rf ${ARM_TOOLCHAIN_INSTALL_DIR}

echo "Downloading ARM toolchain from ${ARM_TOOLCHAIN_URL} to ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME}..."
curl -L ${ARM_TOOLCHAIN_URL} --create-dirs -C - \
    -o ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME}

echo "Untaring arm toolchain in ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}..."
tar -xf ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_FILENAME} -C ${ARM_TOOLCHAIN_INSTALL_DIR}

echo "Making logical links..."
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-gcc      ${HOME}/.local/bin/arm-none-eabi-gcc
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-ld       ${HOME}/.local/bin/arm-none-eabi-ld
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-objdump  ${HOME}/.local/bin/arm-none-eabi-objdump
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-objcopy  ${HOME}/.local/bin/arm-none-eabi-objcopy
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-size     ${HOME}/.local/bin/arm-none-eabi-size
ln -s ${ARM_TOOLCHAIN_INSTALL_DIR}/${ARM_TOOLCHAIN_EXTRACT_DIR_NAME}/bin/arm-none-eabi-gdb      ${HOME}/.local/bin/arm-none-eabi-gdb

if grep -Fxq 'PATH=${HOME}/.local/bin:${PATH}' ${HOME}/.bashrc
then
    echo "${HOME}/.local/bin already exists in ${HOME}/.bashrc!"
else
    echo "Adding \${HOME}/.local/bin to PATH..."
    echo 'PATH=${HOME}/.local/bin:${PATH}' >> ${HOME}/.bashrc
    export PATH=${HOME}/.local/bin:${PATH}
fi

echo "Installation successful"
