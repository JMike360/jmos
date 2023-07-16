# jmos

The goal of this project is to challenge myself by writing a functional RTOS for the STM32F051 Discovery dev-board/SoC completely from scratch.

I am defining "completely from scratch" as meaning a fully bare-metal project with no external dependencies, libraries, drivers, startup code, linker scripts or assistance from pre-written software or firmware of any kind.

As far as the layers from the kernel down to the bare-metal registers are concerned, no bits will be flashed to ROM that were not exclusively compiled from code written newly for this project.

As an end goal, I'm shooting for a number of things:
 - Support for task scheduling and process forking
 - Process isolation, support for process-level dynamic memory allocation
 - Some level of peripheral multiplexing (i.e. SysTick based timers, maybe certain GPIO pins or communication peripherals)
 - A simple file system
 - Full use of MSP (Main stack pointer) and PSP (Process Stack Pointer) separation between OS/IRQ handler code and process code
 - A simple shell to launch user space processes
 - Basic I/O support through a serial UART connection (to allow keyboard input and support communication to a host PC)
 - Possibly HDMI support to display shell output, boot messages, etc

*Someone who has taken an OS class please let me know if I'm missing anything super important*
