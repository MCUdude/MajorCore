# MajorCore development boards
In order to develop a system around a microcontroller, you sooner or later need a test environment. Such environment may be a breadboard, but also a dedicated dedicated development board. I'm going to present to you two development boards that lets you burn the bootloader and upload your program using a USB to serial adapter.

## Atmel's STK500
The [STK500 development board](http://www.atmel.com/webdoc/stk500/index.html) was released by Atmel in the early 2000s, and has a ton of great features! It's been <u>_the_</u> ultimate development board for more than a decade because of its versatility, flexibility and excellent price point. If you don't know the STK500, let me sum it up for you:
* It got an onboard programming interface (called stk500), that comminicates with a computer using a serial interface (RS-232)
* The board lets you control the operating voltage, clock frequency, analog reference voltage in software using avrdude or Atmel Studio
* It's powered from an external 12v adapter
* It supports almost all AVR microcontrollers that comes in a DIP package.
* All the IO pins are broken out
* It got eight on-board LEDs and buttons for testing
* **It got an aditional serial port for serial communication with the microcontroller**

<br/>

### Burning the bootloader using the STK500
Let's prepare the STK500 for some bootloader action! 
* Insert your microcontroller (ATmega8515 or ATmega162) in the socket called `SCKT3000D3`, and make sure it's installed the correct way. 
* Insert a crystal in the crystal socket if you're not using the internal oscillator. 
* Make sure the `XTAL1` jumper is connected, that the `OSCSEL` is connected between pin 2 and three as shown in the picture below.
* Connect the 6 pin cable between the `ISP6PIN` and the `SPROG3` connector. This will connect the stk500 programmer to the microcontroller.
* Connect the 10 pin cable between the `PORTB` and `LEDS` header (optional but recommended).
* Connect the 2 pin cable between the `RS232 SPARE` and the `PORTD` connector. The _RXD_ pin should be connected to `PD0`, and the _TXD_ pin should be connected to `PD1`.
* Apply power to the board.
* Open Arduino IDE, select the correct clock frequency option and the USB to RS-232 adapter you're going to use.
* Select the _STK500 as ISP_ option in the programmers menu.
* Connect the RS-232 adapter into the `RS232 CTRL` connector on the STK500
* Hit _Burn Bootloader_!

If everything is allright, `LED0` should now flash twice every second.

<br/>

![STK500 top view](http://i.imgur.com/R4X7UXs.jpg)


### Uploading code using the serial interface
Now that the bootloader is burnt, it's time to "Arduinoize" the STK500 by uploading code using a serial interface!
By default the STK500 doesn't support auto reset, which the bootloader relies on. To add this feature we need to do some soldering. It's a fairly simple fix, and it actually let's you use the STK500 with other microcontrollers ([MightyCore](https://github.com/MCUdude/MightyCore), [MiniCore](https://github.com/MCUdude/MiniCore), [Microcore](https://github.com/MCUdude/MicroCore)) in Arduino IDE as well. This is how it's done:

<br/>

Flip your board around and locate the `RS232 SPARE` connector. Solder a **100 nF** capacitor to pin 4 on the connector. This is the DTR pin. Solder a wire from the other end of the capacitor to the _RESET_ pin on the `SCKT3000D3` socket. I chose to use a 0805 capacitor.
![STK500 top view](http://i.imgur.com/y7yXDms.jpg)

<br/>

To prevent damage to the _RESET_ pin caused by undervoltage from the RS-232 interface, a diode needs to be solder between ground and _RESET_. I soldered a 1N4007 SMD diode near the `EXPAND0` connector. <br/>
Then you have to disconnect the `RESET` jumper marked in red on the first picture. If not, auto reset will not work. The last thing on the list is to remove the 6 pin connector.
<br/>
<br/>
Now open Arduino IDE, select the correct clock frequency and serial port, and simply hit _Upload_. Your code should now be running on the microcontroller!

<br/>

![STK500 bottom view 1](http://i.imgur.com/vrlIm3Q.jpg)
<br/>
![STK500 bottom view 2](http://i.imgur.com/93Zl9R2.jpg)


## ReadyAVR-40
The [ReadyAVR-40 development board](http://logifind.com/avr-xmega-avr32/development-boards/avr-development-board-readyavr-40-atmega16-bootloader-1126.html) is combined development board that supports both MajorCore and MightyCore compatible microcontrollers. The board has a built in CP2102 USB to serial converter, so it's more convinient than the STK500 if you're planning to use the serial interface. Just make sure the _PD0_ and _PD1_ jumpers are connected.

<br/>

![ReadyAVR](http://i.imgur.com/3CjuJwT.jpg)

<br/>
This board doesn't got auto reset, so a similar fix is required for this board as well. Simply solder a **100 nF** capacitor to pin 28 on the CP2102 chip (red arrow on the first picture), and solder a wire from the other end of the capacitor to the _RESET_ button.
