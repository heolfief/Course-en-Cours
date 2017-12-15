# Course-en-Cours

[FRENCH] **http://www.course-en-cours.com/**

This project contains hardware, software and documentation files for the "course en cours" **educationnal competition in France**.
During a year, teams of 4 to 6 middle/high school **students build their small electic car** using the same tools as engineers. the contest consists of **designing, creating, testing and running** a small model car during the** regional competitions**, to acces the **national final**.

We are two university students in electrical engineering and industrial data processing, from Rennes, France.
Our project is to **integrate embedded telemetry, datalogging and manual control** into the existings cars engines.
We choosed to works with the **Arduino environnement**, to make it possible for everybody to program their car, modify it as they like, and to make programming accesible for the young people of the competition.

This project is **realesed under the general public license and is strongly welcome to modifications**.

## Hardware

The hardware is based on 4 main components:
- ATmega328p microcontroller (the same as the arduino uno/nano)
- MPU6050 accelerometer and gyro chip
- A FTDI chip (to program the microcontroller via USB)
- A micro SD card holder

This board is **fully arduino compatible** and should be selected in the arduino environnement as the arduino nano.

PCB pinout diagram:
![PCB pinout](https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_pinout.jpg)

## Software
