#!/bin/bash
set -e

OPENOCD_INSTALL_DIR=${HOME}/openocd
OPENOCD_URL="https://github.com/xpack-dev-tools/openocd-xpack/releases/download/v0.12.0-1/xpack-openocd-0.12.0-1-linux-x64.tar.gz"
OPENOCD_FILENAME="xpack-openocd-0.12.0-1-linux-x64.tar.gz"
OPENOCD_EXTRACT_DIR_NAME="${OPENOCD_FILENAME%.tar.gz}"

mkdir -p ${HOME}/.local/bin

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

echo "Installation successful"
