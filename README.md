# STM32F103xx Drivers
En este repositorio se encontraran una serie de prototipos de funciones las de drivers para el microcontrolador STM32F103C8.
Este microcontrolador es el que posee la placa BluePill.
Los prototipos tienen descripciones los cuales brindan una idea de como deben ser implementados.

# Guia de instalacion de herramientas
En las siguientes secciones se encontraran instrucciones para instalar las herramientas necesarias para compilar un programa para el microcontrolador y para flashear el mismo.

## Toolchain de ARM
Este set de herramientas es necesario para compilar un programa en nuestra PC para que pueda correrse en el microcontrolador.

### Linux
La catedra creo un script de conveniencia para poder instalar el toolchain de manera rapida y sencilla.
Este script descargara e instalara el toolchain.
Para ejecutarlo realizar lo siguiente en una terminal, estando ubicado en la raiz de este repositorio:
```bash
./scripts/install_arm_toolchain.sh
```
## ST-LINK
Las herramientas `STLINK` permiten flashear el microcontrolador, accediendo a la memoria del mismo. 

### Linux
En este repositorio se encuentra un paquete deb con un release de la herramienta.
Se puede instalar el mismo con el manejador de paquetes de la distribucion utilizada.
Por ejemplo, para sistemas Debian/Ubuntu:
```bash
sudo apt install ./tools/stlink_1.7.0-1_amd64.deb
```

# Guia de debugging con OpenOCD y GDB

* En una terminal, dejar corriendo open-ocd:
```bash
make ocd-start
```

* En otra terminal, ejecutar gdb para depurar la ejecucion del programa:
```bash
make debug
```

# Links

* [STM32F103C8 microcontroller datasheet](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html)

* [STM32F103C8 reference manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

* [Bluepill development kit](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html)
