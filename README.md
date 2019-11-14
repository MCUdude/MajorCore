# MajorCore
An Arduino core for large, 8051 pin compatible, breadboard friendly AVRs, all running a [custom version of Optiboot](https://github.com/Optiboot/optiboot). Major libraries such as SD, Servo, and SPI are modified to work with this core. Still, a large amount of third-party libraries often works without any modifications. 
<br/> <br/>
This core requires at least Arduino IDE v1.6, where v1.6.11+ is recommended.
<br/> <br/>
If you're into "generic" AVR programming, I'm happy to tell you that all relevant keywords are being highlighted by the IDE through a separate keywords file. Make sure to test the [example files](https://github.com/MCUdude/MajorCore/tree/master/avr/libraries/AVR_examples/examples) (File > Examples > AVR C code examples).
<br/> <br/>


# Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [Bootloader option](#bootloader-option)
* [BOD option](#bod-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* [Printf support](#printf-support)
* [Write to own flash](#write-to-own-flash)
* **[How to install](#how-to-install)**
	- [Boards Manager Installation](#boards-manager-installation)
	- [Manual Installation](#manual-installation)
* **[Getting started with MajorCore](#getting-started-with-majorcore)**
* [Wiring reference](#wiring-reference)
* **[Development board](#majorcore-development-board)**
* **[Pinout](#pinout)**
* **[Minimal setup](#minimal-setup)**


## Supported microcontrollers
* ATmega162
* ATmega8515


## Supported clock frequencies
* 16 MHz external oscillator (default)
* 20 MHz external oscillator
* 18.432 MHz external oscillator<b>*</b>
* 12 MHz external oscillator
* 8 MHz external oscillator
* 8 MHz internal oscillator <b>**</b>
* 1 MHz internal oscillator 
 
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external oscillator is recommended. 
</br></br>

<b>*</b> When using the 18.432 MHz option (or any frequency by which 64 cannot be divided evenly), micros() is 4-5 times slower (~110 clocks). It reports the time at the point when it was called, not the end.
This clock frequency is not recommended if your application relies on accurate timing, but is [superb for UART communication](http://wormfood.net/avrbaudcalc.php?bitrate=300%2C600%2C1200%2C2400%2C4800%2C9600%2C14.4k%2C19.2k%2C28.8k%2C38.4k%2C57.6k%2C76.8k%2C115.2k%2C230.4k%2C250k%2C.5m%2C1m&clock=18.432&databits=8). 
Millis() is not effected, only micros() and delay(). Micros() executes equally fast at all clock speeds, but returns wrong values with anything that 64 doesn't divide evenly by.
<br/>

<b>**</b> There might be some issues related to the internal oscillator. It's factory calibrated, but may be a little "off" depending on the calibration, ambient temperature and operating voltage. If uploading failes while using the 8 MHz internal oscillator you have three options:
* Edit the baudrate line in the [boards.txt](https://github.com/MCUdude/MajorCore/blob/034ddfe8fb9b95178c07c723c98fc90dfdf3c89c/avr/boards.txt#L99) file, and choose either 115200, 57600, 38400 or 19200 baud.
* Upload the code using a programmer (USBasp, USBtinyISP etc.) and skip the bootloader
* Use the 1 MHz option instead


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

## Link time optimization / LTO
After Arduino IDE 1.6.11 where released, There have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it slower. In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 and older will return an error. 
Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!


## Printf support
Unlike the official Arduino cores, MajorCore has printf support out of the box. If you're not familiar with printf you should probably [read this first](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). It's added to the Print class and will work with all libraries that inherit Print. Printf is a standard C function that lets you format text much easier than using Arduino's built-in print and println. Note that this implementation of printf will NOT print floats or doubles. This is a limitation of the avr-libc printf implementation on AVR microcontrollers, and nothing I can easily fix.

If you're using a serial port, simply use `Serial.printf("Milliseconds since start: %ld\n", millis());`. Other libraries that inherit the Print class (and thus supports printf) are SoftwareSerial, the LiquidCrystal LCD library and the U8G2 graphical LCD library.


## Write to own flash
MiniCore implements [@majekw](https://github.com/majekw) fork of Optiboot, which enables flash writing functionality within the running application. This means that content from e.g. a sensor can be stored in the flash memory directly, without the need of external memory. Flash memory is much faster than EEPROM, and can handle about 10 000 write cycles.
To enable this feature your original bootloader needs to be replaced by the new one. Simply hit "Burn Bootloader", and it's done!  
Please check out the [Optiboot flasher example](https://github.com/MCUdude/MajorCore/blob/master/avr/libraries/Optiboot_flasher/examples/SerialReadWrite/SerialReadWrite.ino) for more info about how this feature works, and how you can try it on your MajorCore compatible microcontroller.


## How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://mcudude.github.io/MajorCore/package_MCUdude_MajorCore_index.json`
  * Separate the URLs using a comma ( **,** ) if you have more than one URL
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MajorCore** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button. Exctract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MajorCore" will show up.
 

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
