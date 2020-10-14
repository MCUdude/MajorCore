# MajorCore
[![Build Status](https://travis-ci.org/MCUdude/MajorCore.svg?branch=master)](https://travis-ci.org/MCUdude/MajorCore)

An Arduino core for large, 8051 pin compatible, breadboard friendly AVRs, all running a [custom version of Optiboot for increased functionality](#write-to-own-flash). This core requires at least Arduino IDE v1.6.2, where v1.8.5+ is recommended.
<br/> <br/>
If you're into "generic" AVR programming, I'm happy to tell you that all relevant keywords are being highlighted by the IDE through a separate keywords file. Make sure to test the [example files](https://github.com/MCUdude/MajorCore/tree/master/avr/libraries/AVR_examples/examples) (File > Examples > AVR C code examples).
<br/> <br/>


# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [Bootloader option](#bootloader-option)
* [BOD option](#bod-option)
* [EEPROM retain option](#eeprom-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* [Printf support](#printf-support)
* [Pin macros](#pin-macros)
* [Write to own flash](#write-to-own-flash)
* **[How to install](#how-to-install)**
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
  - [PlatformIO](#platformio)
* **[Getting started with MajorCore](#getting-started-with-majorcore)**
* [Wiring reference](#wiring-reference)
* **[Development board](#majorcore-development-board)**
* **[Pinout](#pinout)**
* **[Minimal setup](#minimal-setup)**


## Supported microcontrollers
* ATmega162
* ATmega8515


## Supported clock frequencies
MajorCore supports a variety of different clock frequencies. Select the microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader.  
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external crystal/oscillator is recommended.  

You might experience upload issues when using the internal oscillator. It's factory calibrated but may be a little "off" depending on the calibration, ambient temperature and operating voltage. If uploading failes while using the 8 MHz internal oscillator you have these options:
* Edit the baudrate line in the boards.txt file, and choose either 115200, 57600, 38400 or 19200 baud.
* Upload the code using a programmer (USBasp, USBtinyISP etc.) or skip the bootloader by holding down the shift key while clicking the "Upload" button
* Use the 4, 2 or 1 MHz option instead

| Frequency   | Oscillator type             | Comment                                                       |
|-------------|-----------------------------|---------------------------------------------------------------|
| 16 MHz      | External crystal/oscillator | Default clock on most AVR based Arduino boards and MiniCore   |
| 20 MHz      | External crystal/oscillator |                                                               |
| 18.4320 MHz | External crystal/oscillator | Great clock for UART communication with no error              |
| 14.7456 MHz | External crystal/oscillator | Great clock for UART communication with no error              |
| 12 MHz      | External crystal/oscillator | Useful when working with USB 1.1 (12 Mbit/s)                  |
| 11.0592 MHz | External crystal/oscillator | Great clock for UART communication with no error              |
| 8 MHz       | External crystal/oscillator | Common clock when working with 3.3V                           |
| 7.3728 MHz  | External crystal/oscillator | Great clock for UART communication with no error              |
| 4 MHz       | External crystal/oscillator |                                                               |
| 3.6864 MHz  | External crystal/oscillator | Great clock for UART communication with no error              |
| 1 MHz       | External crystal/oscillator |                                                               |
| 1.8432 MHz  | External crystal/oscillator | Great clock for UART communication with no error              |
| 1 MHz       | External crystal/oscillator |                                                               |
| 8 MHz       | Internal oscillator         | Might cause UART upload issues. See comment above this table  |
| 4 MHz       | Internal oscillator         | Derived from the 8 MHz internal oscillator                    |
| 2 MHz       | Internal oscillator         | Derived from the 8 MHz internal oscillator                    |
| 1 MHz       | Internal oscillator         | Derived from the 8 MHz internal oscillator                    |


## Bootloader option
MajorCore lets you select which serial port you want to use for uploading. UART0 is the default port for all targets, but ATmega162 can also use UART1 for upload.
If your application doesn't need or require a bootloader for uploading code you can also choose to disable this by selecting *No bootloader*. This frees 512 bytes of flash memory.

Note that you have need to connect a programmer and hit **Burn bootloader** if you want to change any of the *Upload port settings*.


## BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br/>

| ATmega162 | ATmega8515 |
|-----------|------------|
| 4.3V      | 4.0V       |
| 2.7V      | 2.7V       |
| 1.8V      | -          |
| Disabled  | Disabled   |


## EEPROM option
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect an ISP programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.


## Link time optimization / LTO
After Arduino IDE 1.6.11 where released, There have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 or older will return an error. 
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!


## Printf support
Unlike the official Arduino cores, MajorCore has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. Note that this implementation of printf will NOT print floats or doubles. This is a limitation of the avr-libc printf implementation on AVR microcontrollers, and nothing I can easily fix.

If you're using a serial port, simply use `Serial.printf("Milliseconds since start: %ld\n", millis());`. Other libraries that inherit the Print class (and thus supports printf) are SoftwareSerial, the LiquidCrystal LCD library and the U8G2 graphical LCD library.


## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that maps "Arduino pins" to the port and port number:

```c++
// Use PIN_PB0 macro to refer to pin PB0 (Arduino pin 0)
digitalWrite(PIN_PB0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);

```


## Write to own flash
MiniCore implements [@majekw](https://github.com/majekw) fork of Optiboot, which enables flash writing functionality within the running application. This means that content from e.g. a sensor can be stored in the flash memory directly, without the need of external memory. Flash memory is much faster than EEPROM, and can handle about 10 000 write cycles.
To enable this feature your original bootloader needs to be replaced by the new one. Simply hit "Burn Bootloader", and it's done!  
Please check out the [Optiboot flasher example](https://github.com/MCUdude/MajorCore/blob/master/avr/libraries/Optiboot_flasher/examples/SerialReadWrite/SerialReadWrite.ino) for more info about how this feature works, and how you can try it on your MajorCore compatible microcontroller.


## How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**:

    ```
    https://mcudude.github.io/MajorCore/package_MCUdude_MajorCore_index.json
    ``` 

* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MiniCore** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button. Exctract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MajorCore" will show up.


#### PlatformIO
[PlatformIO](http://platformio.org) is an open source ecosystem for IoT development and supports MajorCore.

**See [PlatformIO.md](https://github.com/MCUdude/MajorCore/blob/master/PlatformIO.md) for more information.**
 

## Getting started with MajorCore
Ok, so you're downloaded and installed MajorCore, but do I get the wheels spinning? Here's a quick start guide:
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
  - If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted. 
* Open the **Tools > Board** menu item, and select a MajorCore compatible microcontroller.
* You can select at what voltage the microcontroller will shut down at by changing the *BOD setting*. Read more about BOD [here](#bod-option).
* Select your prefered clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* Hit **Burn Bootloader**. If an LED is connected to pin PB0, it should flash twice every second.
* Now that the correct fuse settings is sat and the bootloader burnt, you can upload your code in two ways:
  - Disconnect your programmer tool, and connect a USB to serial adapter to the microcontroller, like shown in the [minimal setup circuit](#minimal-setup). Then select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting some kind of timeout error, it means your RX and TX pins are swapped, or your auto reset circuity isn't working properly (the 100 nF capacitor on the reset line).
  - Keep your programmer connected, and hold down the `shift` button while clicking **Upload**. This will erase the bootloader and upload your code using the programmer tool.

Your code should now be running on your microcontroller! If you experience any issues related to bootloader burning or serial uploading, please create an issue on Github, so I can help you out.


## Wiring reference
To extend this core's functionality a bit futher, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isnt active. These functions is used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful, because they really are!

### Function list
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()
* disablePower()

### For further information please view the [Wiring reference page](https://github.com/MCUdude/MajorCore/blob/master/Wiring_reference.md)!


## MajorCore development board
If you want to play around with this Arduino core and you don't have any hardware, you can use a development board instead of wiring up the microcontroller on a breadboard. There are may development boards available, both cheap and expensive ones.
If you're interested, you should have a look at the *MajorCore development guide*; where you can find some detailed information. Link down below!

### [MajorCore development board guide](https://github.com/MCUdude/MajorCore/blob/master/development_boards.md)!


## Pinout
Since there are no standarized Arduino pinout for the ATmega8515 and ATmega162, I had to create my own. You can find the current pinout below. 
<b>Click to enlarge:</b> 
</br> </br>
<img src="http://i.imgur.com/Idvb1BI.jpg" width="800">


## Minimal setup
Here is a simple schematic showing a minimal setup using an external crystal. Skip the crystal and the two capacitors if you're using the internal oscillator. <br/>
<img src="http://i.imgur.com/Xb5ujgC.png" width="750">
