# jmos

The goal of this project is to challenge myself by writing a functional RTOS for the STM32F051 Discovery dev-board/SoC completely from scratch.

I am defining "completely from scratch" as meaning a fully bare-metal project with no external dependencies, libraries, drivers, startup code, linker scripts or assistance from pre-written software or firmware of any kind.

As far as the layers from the kernel down to the bare-metal registers are concerned (and possibly all the layers from the kernel up, too), no bits will be flashed to ROM that were not exclusively compiled from code written newly for this project.

As an end goal, I'm shooting for a number of things:
 - [ ] Support for task scheduling and process forking
 - [ ] Process isolation, support for process-level dynamic memory allocation
 - [ ] Some level of peripheral multiplexing (i.e. SysTick based timers, maybe certain GPIO pins or communication peripherals)
 - [ ] A simple file system
 - [ ] Full use of MSP (Main stack pointer) and PSP (Process Stack Pointer) separation between OS/IRQ handler code and process code
 - [ ] A simple shell to launch user space processes
 - [x] Basic I/O support through a serial UART connection (to allow keyboard input and support communication to a host PC)
 - [ ] Possibly HDMI support to display shell output, boot messages, etc

*Someone who has taken an OS class please let me know if I'm missing anything super important*

# Getting Started

### Hardware: \
STM32F0Discovery board: https://www.digikey.com/en/products/detail/stmicroelectronics/STM32F0DISCOVERY/3045359?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&gclid=Cj0KCQjwuNemBhCBARIsADp74QTjs18nkKRnToguwQtXIAcssSx9WCRISwkd93s4XSV0hSUSAQyqGiwaAr9YEALw_wcB \
FDTI serial to USB board: https://www.amazon.com/HiLetgo-FT232RL-Converter-Adapter-Breakout/dp/B00IJXZQ7C/ref=sr_1_8?keywords=ftdi+usb+to+serial&qid=1691784056&sr=8-8

### Documentation: \
Cortex M0 Programming Manual: https://www.st.com/resource/en/programming_manual/pm0215-stm32f0-series-cortexm0-programming-manual-stmicroelectronics.pdf \
STM32F0xx Reference Manual: https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf \
STM32F0 Discovery Datasheet: https://www.st.com/resource/en/user_manual/um1525-stm32f0discovery-discovery-kit-for-stm32-f0-microcontrollers-stmicroelectronics.pdf 

### Recommended Tools (Linux env):
- (*) st-link: https://github.com/stlink-org/stlink
- (*) gdb-multiarch: `sudo apt-get install gdb-multiarch -y`
- (*) ARM GNU toolchain (arm-eabi-none-xxx): https://developer.arm.com/downloads/-/gnu-rm
- tmux: `sudo apt-get install tmux -y` or any terminal mutliplexer you like
- screen: `sudo apt-get install screen -y` or putty: `sudo apt-get install putty -y` or any other serial monitor
- improved vimrc: https://github.com/amix/vimrc

### Running the code:
1. Clone the repository `git clone https://github.com/JMike360/jmos.git`
2. Build the binary image: \
`cd jmos` \
`make project` 
3. Connect the STM32F0Discovery to the PC via USB
4. Flash the jmos.bin image to ROM: \
`make flash` 

### Debugging: \
st-link provides a nice utility for connecting to the in-circuit debugger and exposing it as a gdb server that you can connect to with any gdb instance running on the host PC. 
1. Run the gdb server, connected to the SWD in-circuit debugger on the board: \
`tmux` (optional) \
`st-util` 
2. In a parallel terminal instance, run gdb and connect to the gdb server: \
type:`^B (ctrl-B), %` to split the terminal and create a parallel terminal instance (optional) \
Navigate to the new pane: type `^B (ctrl-B), [arrow key] or 'o'` \
`cd jmos` \
`gdb-multiarch` \
In gdb: `target extended-remote localhost:4242` \
In gdb: `file jmos.elf` to load symbol table 
3. Run debug commands \
In gdb: `^C` to halt execution, `b [symbol]` to add breakpoint, `c` to continue execution, `s` to step, `info reg` to dump low registers, `info b` to show breakpoints, `delete [number]` to remove breakpoint \
In gdb: Full list of gdb commands for stm32 devices - https://wiki.st.com/stm32mpu/wiki/GDB_commands 
4. Typical debugging loop edit->build->flash->debug without having to re-do steps 1-3: \
`^B, [arrow key] or 'o'` to navigate to desired pane, `^B, %` or `^B "` to create panes and `^D` to delete panes as needed \
make file edits in vim \
`make clean` \
`make project` \
`^B, [arrow key] or 'o'` to navigate back to gdb \
In gdb: `^C` to stop execution \
In gdb: `load jmos.elf` to flash binary image and reload symbol table \
In gdb: `r`, `y` to restart the MCU \
continue debugging as normal

### USART Serial Monitoring:\
The foundation of the Basic Input/Output System is the USART serial communication peripheral.\
The code assumes the board and USART pins are wired like this:
![image](https://github.com/JMike360/jmos/assets/21974835/04878658-5ed6-46ad-80ce-8e1704725fb1)

To perform I/O operations with the USART, it is necessary to attach a serial monitoring program (i.e. screen or putty).\
The USART peripheral is configured in the code to use 9600 baud, 1 start bit, 8 data bits, 1 stop bit. \
Luckily, these are the defaults for screen as well, so we should be able to just run:\
`sudo screen /dev/ttyUSB0`, or if you like, `sudo screen /dev/ttyUSB0 9600,cs8` (sudo is used because often USB0 is a permission-restricted device)

If ttyUSB0 does not bring up the USART output, or respond to USART input, it is possible that the FTDI board is connected to a different serial tty device.\
Resource for setting up serial monitoring: https://www.cyberciti.biz/hardware/5-linux-unix-commands-for-connecting-to-the-serial-console/ \
There are various ways of listing the serial devices in use, and determining which one corresponds to the FTDI board. I'll post the one I used if I can find it again.

**Update:** It appears that the USART BRR divisor may need to be calibrated/set on not just a per-device basis, but also a per-session basis. I've found that if you run into garbled characters, this can be corrected by lowering the brr value by a small increment (like 0x5 or 0x8) and observing whether this produces fewer garbled characters per input. More investigation is probably needed to determine why the calibration needs to be set so often, but for now I've just moved the brr setting into an argument to init_usart() to make this a bit easier/more obvious.




