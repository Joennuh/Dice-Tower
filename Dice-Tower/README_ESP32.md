# OLED test

## Introduction

The ESP32 compiled version of Dice Tower supports the MH-ET LIVE ESP32 MiniKit, a connected SSD1306, an display indicator light (reacts to button presses on a display module) and 2 SMD leds of which their function has not yet been defined.

The ESP32 version supports (a) virtual dice(s) on the screen.


## Types of dices

The following table is an overview of what kind of dices should be added and in which way:

| Type                 | Amount of sides | Values                  | Displayed as         |
| :------------------- | :-------------: | :---------------------: | :------------------- |
| Cube / normal die    | 6               | 1 - 6                   | Images of dots 1 - 6 |
| Octahedron normal    | 8               | 1 - 8                   | Numbers 1 - 8        |
| Mansions of madness  | 8               | 2x magnifying glass, 3x pentagram, 3x empty | Images corresponding to the values. |
| Dodecahedron         | 12              | 1 - 12                  | Numbers 1 - 12       |
| Icosahedron 1 - 10   | 20              | 2x 1 - 10                | 2x numbers 1 - 10    |
| Icosahedron 1 - 20   | 20              | 1 - 20                  | Numbers 1 - 20       |

The list above is based on my friend's Nico Jongsma wishes and the list mentioned on this Wikipedia page: <https://en.wikipedia.org/wiki/Dice>
In my opinion the Tetrahedron and Pentagonal trapezohedron are not very common and thus I decided to not include these two types of dices.

The end user should be able to choose the type of dice. This can not be mixed.

## The way of displaying dices

I want to place a maximum of 7 boxes on the screen and within these boxes do show up the randomly generated numbers or images. The end user should be able to set the amount of dices / boxes.

## Menu

The menu will be done with ArduinoMenu: <https://github.com/neu-rah/ArduinoMenu>

The proposed menu structure can be found at [idea_for_menu.txt](idea_for_menu.txt).