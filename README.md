# jmos

The goal of this project is to challenge myself by writing a functional RTOS for the STM32F051 Discovery dev-board/SoC completely from scratch.

I am defining "completely from scratch" as meaning a fully bare-metal project with no external dependencies, libraries, drivers, startup code, linker scripts or assistance from pre-written software or firmware of any kind.

As far as the layers from the kernel down to the bare-metal registers are concerned (and possibly all the layers from the kernel up, too), no bits will be flashed to ROM that were not exclusively compiled from code written newly for this project.

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

# Getting Started

Hardware: 
STM32F0Discovery board: https://www.digikey.com/en/products/detail/stmicroelectronics/STM32F0DISCOVERY/3045359?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&gclid=Cj0KCQjwuNemBhCBARIsADp74QTjs18nkKRnToguwQtXIAcssSx9WCRISwkd93s4XSV0hSUSAQyqGiwaAr9YEALw_wcB

Documentation:
Cortex M0 Programming Manual: https://www.st.com/resource/en/programming_manual/pm0215-stm32f0-series-cortexm0-programming-manual-stmicroelectronics.pdf
STM32F0xx Reference Manual: https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
STM32F0 Discovery Datasheet: https://www.st.com/resource/en/user_manual/um1525-stm32f0discovery-discovery-kit-for-stm32-f0-microcontrollers-stmicroelectronics.pdf

Recommended Tools (Linux env):
- (*) st-link: https://github.com/stlink-org/stlink
- (*) gdb-multiarch: `sudo apt-get install gdb-multiarch -y`
- (*) ARM GNU toolchain (arm-eabi-none-xxx): https://developer.arm.com/downloads/-/gnu-rm
- tmux: `sudo apt-get install tmux -y` or any terminal mutliplexer you like
- screen: `sudo apt-get install screen -y` or putty: `sudo apt-get install putty -y` or any other serial monitor
- improved vimrc: https://github.com/amix/vimrc

Running the code:
1. Clone the repository `git clone https://github.com/JMike360/jmos.git`
2. Build the binary image:
`cd jmos`
`make project`
3. Connect the STM32F0Discovery to the PC via USB
4. Flash the jmos.bin image to ROM:
`make flash`

Debugging:
st-link provides a nice utility for connecting to the in-circuit debugger and exposing it as a gdb server that you can connect to with any gdb instance running on the host PC.
1. Run the gdb server, connected to the SWD in-circuit debugger on the board:
`tmux` (optional)
`st-util`
2. In a parallel terminal instance, run gdb and connect to the gdb server:
type:`^B (ctrl-B), %` to split the terminal and create a parallel terminal instance (optional)
Navigate to the new window: type `^B (ctrl-B), [arrow key] or 'o'`
`cd jmos`
`gdb-multiarch`
In gdb: `target extended-remote localhost:4242`
In gdb: `file jmos.elf` to load symbol table
3. Run debug commands
In gdb: `^C` to halt execution, `b [symbol]` to add breakpoint, `c` to continue execution, `s` to step, `info reg` to dump low registers, `info b` to show breakpoints, `delete [number]` to remove breakpoint
In gdb: Full list of gdb commands for stm32 devices - https://wiki.st.com/stm32mpu/wiki/GDB_commands
4. Typical debugging loop edit->build->flash->debug without having to re-do steps 1-3:
`^B, [arrow key] or 'o'` to navigate to desired pane, `^B, %` or `^B "` to create panes and `^D` to delete panes as needed
make file edits in vim
`make clean`
`make project`
`^B, [arrow key] or 'o'` to navigate back to gdb
In gdb: `^C` to stop execution
In gdb: `load jmos.elf` to flash binary image and reload symbol table
In gdb: `r`, `y` to restart the MCU
continue debugging as normal


