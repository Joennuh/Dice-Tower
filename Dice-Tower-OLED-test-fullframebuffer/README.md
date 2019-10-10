# OLED test

## Introduction

This directory is used to test an attached OLED to the MH-ET LIVE MiniKit ESP32.
The idea is to use the screen to show messages like "Dice detected" and "Continous light mode on" but also to use it for throwing virtual dices.

In this directory the sketch utilizes the fullframe buffer option of the U8G2 library.

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

## Hardware

I try to design the software and PCB in that way that both the MH-ET LIVE MiniKit ESP32 as the Wemos D1 mini can be connected. The Wemos D1 mini would have ofcourse less functionality (e.g. no screen and virtual dioce).

For the display and menu-buttons I'm planning to design a seperate PCB that can be connected through a serial cable to the main PCB. That seperate PCB can hold the SSD1306 128 x 64 OLED and the 3 menu buttons. Since there is a conenctor left in the DB-9 serial cable this can be used for a status led or something.