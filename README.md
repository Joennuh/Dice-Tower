# Dice-Tower
**Create some interaction effects for your homemade Dice Tower.**

![ESP8266](https://img.shields.io/badge/ESP-8266-000000.svg?longCache=true&style=flat&colorA=CC101F)
[![GitHub license](https://img.shields.io/github/license/Joennuh/Dice-Tower)](https://github.com/Joennuh/Dice-Tower/blob/master/LICENSE)
![GitHub repo size](https://img.shields.io/github/repo-size/Joennuh/Dice-Tower)
![GitHub last commit (branch)](https://img.shields.io/github/last-commit/Joennuh/Dice-Tower/master)
[![Gitter](https://badges.gitter.im/Dice-Tower/community.svg)](https://gitter.im/Dice-Tower/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

## Work in progress
This README.md needs to be enriched with photo's, images, etc. This is something I strive to add during the progress of the project.

## Short introduction
The Dice Tower project is a project where a good friend / ex-colleague came up with. He wanted to build a Dice Tower himself. To get an idea of what a Dice Tower could look like please Google the term: <https://www.google.com/search?tbm=isch&q=dice+tower>

My friend doesn't have the knowledge of the electronics and programming. The more I explained which parts and skills are needed, the simpler the electronic part of the project should be according to my friend. For me it was more like a challenge to get the elektronics working in such a way that totally fits in his cool looking Dice Tower.

My friend wanted to build a Dice Tower which have a kind of skull on the front of the tower. In that skulls there will be placed 2 red leds as eyes which should blink when a dice is put in the tower. Then he wanted a campfire somehere on the object. This will be simmulated with 3 yellow leds (lights up as orange in my opinion). Then he wants to connect 4 miniature lanterns which should be permanantly lit. And finally he also wants to put 20 cold white leds in the tower which also should be lit permanently.

The things I added to the ideas of my colleague:
- A Wemos D1 mini to add interaction and animation effects to the Dice Tower.
- A SW-18010P vibration sensor to detect the dice rolling through the tube of the Dice Tower.
- A configuration button.
- A configuration light (indicates whether a button press has been fetched or provide the status of things going on).
- A power-light to see whether the project gets powered correctly.
- A nice PCB design to flatten the space needed to drive all the leds. The original idea consisted of a main board with all connections to the leds soldered on it, then put a "interactive module" on top of that and at last a Wemos D1 mini on top of that. With a nice own designed PCB we got 1 layer less.

## Materials
### PCB
Ofcourse you can build the project on a prototype board but if you want a nice looking PCB you can let a PCB manafacturer create it. I have designed a PCB at [EasyEDA](https://www.easyeda.com). You can find it here: <https://easyeda.com/Joennuh/Dice-Tower>

From [EasyEDA](https://www.easyeda.com) you can easily send the Gerber files to [JLCPCB](https://www.jlcpcb.com) without the need to download and upload the Gerber files. Manufacturing the PCB already starts at $2,= and you nowadays can select several colors. I would advise to use black to keep in the theme of a dark Dice Tower with skull.

I have no assocation to EasyEDA and JLCPCB and thus this explanation is not sponsored by EasyEDA nor JLCPCB.

### Development board
The heart of the machine is the Wemos D1 mini. Theoretically any Arduino campatible development board can drive the project but since I have quite a few Wemos D1 mini's lying around I decided to go with that board. Currently the project doesn't use the WiFi capability of the Wemos D1 mini but the advantage of the choise to use this board is that WiFi functions can be added easily later on.

### Leds and resistors
As long that you do not exceed the following limits you can use any led:
- Maxmimum 3.3V, 12 mA for the leds driven by the Wemos D1 mini (eyes, campfire and configuration/status led).
- Maxmimum 3.3V for the power led (not driven by GPIO but still the 3.3V power of the Wemos D1 mini).
- Maxmimum 5V for any other led.

As far as we found the data for it we do use the leds and resistors in the table below. We also specify to which power line it will be connected.

| Amount | Color          | Working voltage | Working current | Function                       | Power | Resistor |
| -----: | :------------- | :-------------- | :-------------- | :----------------------------- | :---- | :------- |
| 2      | red            | 1.9 - 2.1 V     | 20 mA           | Eyes                           | 3.3V  | 100 Ω    |
| 3      | yellow         | 1.9 - 2.1 V     | 20 mA           | Campfire                       | 3.3V  | 100 Ω    |
| 1      | green          | 1.9 - 2.1 V     | 20 mA           | Configuration / status led     | 3.3V  | 100 Ω    |
| 20     | cold white     | 3.0 - 3.2 V     | 20 mA           | Lights in the tower            | 5V    | 100 Ω    |
| 4      | warm white (1) | 3.1 V (1)       | 20 mA (1)       | Lanterns around collection bin | 5V    | 100 Ω    |

You will also need a 4.7 kΩ resistor for the configuration button.

(1): The seller of the miniature lanterns did not specify the exact color, working voltage and working current. The seller only specified that it should operate on 3 to 5 volts. I assume it will be a warm white led with a working voltage of 3.1 and a working current of 20 mA.

### Configuration button
Any button could do but for the PCB I have chosen for a sidewards 6 x 6 mm tactile button. Any depth of the button could do but I use the default one of 5 mm.

### Trigger
The trigger provides a signal to the D3 pin of the Wemos D1 mini when a dice rolling through the tube of the Dice Tower has been detected. The trigger can be a anything that shorts the D3 pin of the Wemos D1 mini to ground. This could be for example 2 pieces of aluminium hitting each other when a dice rolls on it. Me and my friend choose to use a SW-18010P vibration sensor to sens the vibration fot the dice through the tube. It's best to attach the vibration sensor on the outside of the tube somehwere on the almost the end of the tube. It is also best to leave some space around the end of the tube so that the tube can vibrate enough to let the vibration sensor detect vibrations.

### Header pins
There are several ways to connect all leds to the mainboard but on the PCB I designed have been decided in a way that you can choose to use pin headers (female or male). In that case you need a double row header. I would advise an easily breakable female double row header.

On the left side of the PCB I designed you'll need 2 x 24 pins (so a double row of 24 pins). On top you'll need 2 x 5 pins (so a double row of 5 pins. The pins for the trigger can be a single row (1 x 2 pins). The connection for the power output (e.g. for powering sensors) can be 2 x 2 pins (so a double row of 2 pins). Ofcourse you can also decide to go for 2 single rows instead of double rows. I think single rows are more easily breakable.

### Wires
To connect the leds from somewhere in the tower to your board you'll also needs wires. Wrapping wire will do. It is advisable to use black and red wires to easily distinguish the negative and positive sides coming from the leds.

Ofcourse you also will need a micro-USB cable to power the board through the Wemos D1 mini.

### Heatshrink tubes
To protect the leads of the leds it is advisble to use some heatshrink tubes around the exposed leads. This is to prevent any accidental shortage.

## Software
The software can be downloaded from this Github repository under the GPL 3.0 license. Currently the software doesn't use WiFi cpability of the Wemos D1 mini but this can be subject of change in the future.

### Startup
By default at startup all leds will go on and off one by one to test the leds. During this test the onboard led of the Wemos D1 mini will stay on.

### Default program
After the selftest the yellow leds will start flickering at random intensity to simulate a campfire. The red leds of the eyes will stay lit permanently on a low intensity. When pin D3 of the Wemos D1 mini got HIGH the red leds will blink a few times and they stay on for about 2 seconds.

### Configuration button
A short press on the configuration button will manually trigger the blinking red leds. The green configuration / status led will shortly blink to confirm the short press.

A long press on the configuration button will change to the "permanently lit program". The green configuration / status led will blink for a second after you released the button to confirm the long press.

The last button state is a double click which currently does nothing. The green configuration / status led will blink shortly twice to confirm the double click.

### Permanently lit program
In the permanently lid program the yellow leds will stop flickering and are permanently lit at full intensity. The red leds will be lit at low intenisty and are permanently lit at full intensity for about 3 seconds upon dice detection.
