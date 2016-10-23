#8051core (work in progress title - please help me come up with a better name)
An Arduino core for large, 8051 pin compatible, breadboard friendly AVRs, all running [Optiboot 6](https://github.com/Optiboot/optiboot). Major libraries such as SD, Servo, and SPI are modified to work with this core. Still, a large amount of third-party libraries often works without any modifications. 
<br/> <br/>
This core requires at least Arduino IDE v1.6, where v1.6.11+ is recommended.
<br/> <br/>
If you're into "pure" AVR programming, I'm happy to tell you that all relevant keywords are being highlighted by the IDE through a separate keywords file. Make sure to test the [example files](https://github.com/MCUdude/8051core/tree/master/avr/libraries/AVR_examples/examples) (File > Examples > AVR C code examples).
<br/> <br/>

#Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [BOD option](#bod-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* **[Pinout](#pinout)**
* [Write to own flash](#write-to-own-flash)
* **[How to install](#how-to-install)**
	- [Boards Manager Installation](#boards-manager-installation)
	- [Manual Installation](#manual-installation)
	- [PlatformIO](#platformio)
* **[Getting started with 8051core](#getting-started-with-8051core)**
* [Wiring reference](#wiring-reference)	
* **[Minimal setup](#minimal-setup)**


##Supported microcontrollers
* ATmega162
* ATmega8515


##Supported clock frequencies
* 20 MHz external oscillator
* 16 MHz external oscillator (default)
* 12 MHz external oscillator
* 8 MHz external oscillator
* 8 MHz internal oscillator <b>*</b>
* 1 MHz internal oscillator 
 
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external oscillator is recommended. 
</br></br>
<b>*</b> There might be some issues related to the internal oscillator. It's factory calibrated, but may be a little "off" depending on the calibration, ambient temperature and operating voltage. If uploading failes while using the 8 MHz internal oscillator you have three options:
* Edit the baudrate line in the [boards.txt](https://github.com/MCUdude/8051core/blob/a1d4a54df392290ebfd5b67f41fd93fec2b94313/avr/boards.txt#L83) file, and choose either 115200, 57600, 38400 or 19200 baud.
* Upload the code using a programmer (USBasp, USBtinyISP etc.) and drop the bootloader
* Use the 1 MHz option instead


##BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br/>

| ATmega162 | ATmega8515 |
|-----------|------------|
| 4.3v      | 4.0v       |
| 2.7v      | 2.7v       |
| 1.8v      | -          |
| Disabled  | Disabled   |

##Link time optimization / LTO
After Arduino IDE 1.6.11 where released, There have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 and older will return an error. 
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!

##Pinout
Since there are no standarized Arduino pinout for the ATmega8515 and ATmega162, I had to create my own. I've tried to make it as simple and logical as possible. The standard LED pin is assigned to Arduino pin 0 (PB0), and will blink twice if you hit the reset button.
<b>Click to enlarge:</b> 
</br> </br>
<img src="http://i.imgur.com/hZGMRwH.png" width="375"> <img src="http://i.imgur.com/9cpfTGl.png" width="430">
</br>


##Write to own flash
A while ago [@majekw](https://github.com/majekw) announced that he'd [successfully modified the Optiboot bootloader](http://forum.arduino.cc/index.php?topic=332191.0) to let the running program permanently store content in the flash memory.
The flash memory is much faster than the EEPROM, and can handle about 10 000 write cycles. Simply hit "Burn Bootloader", and it's done! <br/>
Please check out the [Optiboot flasher example](https://github.com/MCUdude/8051core/blob/master/avr/libraries/Optiboot_flasher/examples/SerialReadWrite/SerialReadWrite.ino) for more info about how this feature works, and how you can try it on your 8051core compatible microcontroller.


##How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://mcudude.github.io/8051core/package_MCUdude_8051core_index.json`
  * Separate the URLs using a comma ( **,** ) if you have more than one URL
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **8051core** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

####Manual Installation
Click on the "Download ZIP" button. Exctract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "8051core" will show up.
 

##Getting started with 8051core
Ok, so you're downloaded and installed 8051core, but do I get the wheels spinning? Here's a quick start guide:
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
	- If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted. 
* Open the **Tools > Board** menu item, and select a 8051core compatible microcontroller.
* You can select at what voltage the microcontroller will shut down at by changing the *BOD setting*. Read more about BOD [here](#bod-option).
* Select your prefered clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* Hit **Burn Bootloader**. If an LED is connected to pin PB0, it should flash twice every second.
* Now that the correct fuse settings is sat and the bootloader burnt, you can upload your code in two ways:
	- Disconnect your programmer tool, and connect a USB to serial adapter to the microcontroller, like shown in the [minimal setup circuit](#minimal-setup). Then select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting some kind of timeout error, it means your RX and TX pins are swapped, or your auto reset circuity isn't working properly (the 100 nF capacitor on the reset line).
	- Keep your programmer connected, and hold down the `shift` button while clicking **Upload**. This will erase the bootloader and upload your code using the programmer tool.

Your code should now be running on your microcontroller! If you experience any issues related to bootloader burning or serial uploading, please create an issue on Github, so I can help you out.


##Wiring reference
To extend this core's functionality a bit futher, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isnt active. These functions is used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful, because they really are!

###Function list
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()	
* disablePower()

###For further information please view the [Wiring reference page](https://github.com/MCUdude/8051core/blob/master/Wiring_reference.md)!


##Minimal setup
Here is a simple schematic showing a minimal setup using an external crystal. Skip the crystal and the two capacitors if you're using the internal oscillator. <br/>
<img src="http://i.imgur.com/DG9AiKe.png" width="750">

