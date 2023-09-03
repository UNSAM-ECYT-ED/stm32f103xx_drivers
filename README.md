# STM32F103xx Drivers
En este repositorio se encontraran una serie de prototipos de funciones las de drivers para el microcontrolador STM32F103C8.
Este microcontrolador es el que posee la placa BluePill.
Los prototipos tienen descripciones los cuales brindan una idea de como deben ser implementados.

# Guia de instalacion de herramientas
Para instalar las herramientas necesarias para compilar y depurar codigo en su PC, por favor siga las instrucciones encontradas en [INSTALL.md](INSTALL.md).

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
