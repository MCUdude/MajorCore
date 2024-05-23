# MajorCore
[![Build Status](https://travis-ci.com/MCUdude/MajorCore.svg?branch=master)](https://travis-ci.com/MCUdude/MajorCore)

An Arduino core for large, 8051 pin compatible, breadboard friendly AVRs, all running the [Urboot](#write-to-own-flash) bootloader.
This core requires at least Arduino IDE v1.8, where v1.8.9 or newer is recommended. IDE 2.x should also work.

*From MajorCore version 3 and onwards, the Optiboot bootloader has been replaced by the superior [Urboot bootloader](https://github.com/stefanrueger/urboot/). It's smaller, faster, and has automatic baud rate detection, and can read and write to EEPROM. Other cool features the bootloader provides but are not utilized by MajorCore are user program metadata stored in flash (that can easily be viewed by Avrdude -xshowall) and chip-erase functionality.
If you already have Optiboot installed and don't want to replace it with Urboot, you can still upload programs without any compatibility issues. However, if you're burning a bootloader to a new chip, Urboot is the way to go.*


# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [Bootloader option](#bootloader-option)
* [Baud rate option](#baud-rate-option)
* [BOD option](#bod-option)
* [EEPROM retain option](#eeprom-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* [Printf support](#printf-support)
* [Pin macros](#pin-macros)
* [Write to own flash](#write-to-own-flash)
* **[How to install](#how-to-install)**
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
  - [Arduino CLI Installation](#arduino-cli-installation)
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
MajorCore supports a variety of different clock frequencies. Select the microcontroller in the boards menu, then select the clock frequency. *You will have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. This also has to be done if you want to change any of the fuse settings (BOD and EEPROM settings) regardless if a bootloader is installed or not*.

Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time-critical operations, an external crystal/oscillator is recommended. The Urboot bootloader has automatic baud rate detection, so UART uploads should work fine even though the oscillator is a little too fast or too slow.

| Frequency   | Oscillator type             | Default upload speed <br/>(bootloader has auto-baud)  | Comment                                           |
|-------------|-----------------------------|-------------------------------------------------------|---------------------------------------------------|
| 16 MHz      | External crystal/oscillator | 115200                                                | Default clock on most AVR based Arduino boards    |
| 20 MHz      | External crystal/oscillator | 115200                                                |                                                   |
| 18.4320 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 14.7456 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 12 MHz      | External crystal/oscillator | 57600                                                 |                                                   |
| 11.0592 MHz | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 9.216 MHz   | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 8 MHz       | External crystal/oscillator | 57600                                                 | Common clock when working with 3.3V               |
| 7.3728 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 6 MHz       | External crystal/oscillator | 57600                                                 |                                                   |
| 4 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 3.6864 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 2 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 1.8432 MHz  | External crystal/oscillator | 115200                                                | Great clock for UART communication with no error  |
| 1 MHz       | External crystal/oscillator | 9600                                                  |                                                   |
| 8 MHz       | Internal oscillator         | 38400                                                 | Might cause UART upload issues. See comment above |
| 4 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |
| 2 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |
| 1 MHz       | Internal oscillator         | 9600                                                  | Derived from the 8 MHz internal oscillator        |


## Bootloader option
MajorCore lets you select which serial port you want to use for uploading. UART0 is the default port for all targets, but ATmega162 can also use UART1 for upload.
If your application doesn't need or require a bootloader for uploading you can also choose to disable it by selecting *No bootloader*.
This frees 384 bytes of flash memory on ATmega8/88/168/328 and 320 bytes on the ATmega48.

Note that you need to connect a programmer and hit **Burn bootloader** if you want to change any of the *Bootloader settings*.


# Baud rate option
Since Urboot has automatic baud rate detection, the upload baud rate can be changed without having to re-flash the bootloader. The default baud rate setting will pick a suited baud rate that also works with the legacy Optiboot bootloader used in earlier MajorCore versions.
The other baud rate options may or may not work, depending on the clock frequency and accuracy of the clock source. A rule of thumb is that "non-round" baud rates like 230400 works best with "non-round" clock speeds like 18.4320 MHz,
while "round" ones like 16 MHz work best with "round" baud rates like 250000.


## BOD option
Brown-out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown-out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br/>

| ATmega162 | ATmega8515 |
|-----------|------------|
| 4.3V      | 4.0V       |
| 2.7V      | 2.7V       |
| 1.8V      | -          |
| Disabled  | Disabled   |


## EEPROM option
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect an ISP programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.

Note that if you're using an ISP programmer or have the Urboot bootloader installed, data specified in the user program using the `EEMEM` attribute will be uploaded to EEPROM when you upload your program in Arduino IDE. This feature is not available when using the older Optiboot bootloader.

```cpp
#include <avr/eeprom.h>

volatile const char ee_data EEMEM = {"Data that's loaded straight into EEPROM\n"};

void setup() {
}

void loop() {
}
```


## Link time optimization / LTO
Link time optimization (LTO for short) optimizes the code at link time, usually making the code significantly smaller without affecting performance. You don't need to hit "Burn Bootloader" in order to enable or disable LTO. Simply choose your preferred option in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!


## Printf support
Unlike the official Arduino cores, MajorCore has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. Note that this implementation of printf will NOT print floats or doubles. This is disabled by default to save space but can be enabled using a build flag if using PlatformIO.

If you're using a serial port, simply use `Serial.printf("Milliseconds since start: %ld\n", millis());`. You can also use the `F()` macro if you need to store the string in flash. Other libraries that inherit the Print class (and thus supports printf) are the LiquidCrystal LCD library and the U8G2 graphical LCD library.


## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that map "Arduino pins" to the port and port number:

```c++
// Use PIN_PB0 macro to refer to pin PB0 (Arduino pin 0)
digitalWrite(PIN_PB0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);

```


## Write to own flash
MajorCore uses the excellent Urboot bootloader, written by [Stefan Rueger](https://github.com/stefanrueger). Urboot supports flash writing within the running application, meaning that content from e.g. a sensor can be stored in the flash memory directly without needing external memory. Flash memory is much faster than EEPROM, and can handle at least 10,000 write cycles before wear becomes an issue.
For more information on how it works and how you can use this in your own application, check out the [Serial_read_write](https://github.com/MCUdude/MajorCore/blob/master/avr/libraries/Flash/examples/Serial_read_write/Serial_read_write.ino) for a simple proof-of-concept demo, and
[Flash_put_get](https://github.com/MCUdude/MajorCore/blob/master/avr/libraries/Flash/examples/Flash_get_put/Flash_get_put.ino) + [Flash_iterate](https://github.com/MCUdude/MajorCore/blob/master/avr/libraries/Flash/examples/Flash_iterate/Flash_iterate.ino) for useful examples on how you can store strings, structs, and variables to flash and retrieve then afterward.


## How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.8.0 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**:

    ```
    https://mcudude.github.io/MajorCore/package_MCUdude_MajorCore_index.json
    ```

* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MajorCore** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MajorCore" will show up.

#### Arduino CLI Installation
Run the following command in a terminal:

```
arduino-cli core install MajorCore:avr --additional-urls https://mcudude.github.io/MajorCore/package_MCUdude_MajorCore_index.json
```

#### PlatformIO
[PlatformIO](http://platformio.org) is an open-source ecosystem for IoT and embedded systems, and supports MajorCore.

**See [PlatformIO.md](https://github.com/MCUdude/MajorCore/blob/master/PlatformIO.md) for more information.**


## Getting started with MajorCore
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
  - If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted.
* Open the **Tools > Board** menu item, select **MajorCore** and select your preferred target.
* You can select at what voltage the microcontroller will shut down by changing the *BOD setting*. Read more about BOD [here](#bod-option).
* Select your preferred clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* Hit **Burn Bootloader**. The LED pin will *not* toggle after the bootloader has been loaded.
* Disconnect the ISP programmer, and connect a USB to serial adapter to the target microcontroller shown in the [pinout diagram](#pinout). Select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting a timeout error, it may be because the RX and TX pins are swapped, or the auto-reset circuit isn't working properly (the 100 nF capacitor and a 10k resistor on the reset line).

Your code should now be running on your microcontroller!


## Wiring reference
To extend this core's functionality a bit further, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isn't active. These functions are used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful because they really are!

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
If you want to play around with this Arduino core and you don't have any hardware, you can use a development board instead of wiring up the microcontroller on a breadboard. There are many development boards available, both cheap and expensive ones.
If you're interested, you should have a look at the *MajorCore development guide*; where you can find some detailed information. Link down below!

### [MajorCore development board guide](https://github.com/MCUdude/MajorCore/blob/master/development_boards.md)!


## Pinout
MajorCore provides a standard, logical pinout for ATmega8515 and ATmega162. The standard LED pin is assigned to digital pin 0/PIN_PB0.
<b>Click to enlarge:</b>
</br> </br>
<img src="http://i.imgur.com/Idvb1BI.jpg" width="800">


## Minimal setup
Here is a simple schematic showing a minimal setup using an external crystal. Skip the crystal and the two capacitors if you're using the internal oscillator. <br/>
<img src="http://i.imgur.com/Xb5ujgC.png" width="750">
