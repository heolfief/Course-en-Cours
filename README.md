<p align="center">
  <a href="http://www.course-en-cours.com/">
    <img src="http://www.course-en-cours.com/media/uploads/documents_utils/CeC-logo2017.png" alt="" width=355 height=206>
  </a>

  <h1 align="center">Course en cours</h1>

  <p align="center">
    <a href="http://www.course-en-cours.com/">www.course-en-cours.com</a>
  </p>
</p>
<HR>
<br>

## Table of contents

- [Description](#description)
- [Where to start](#where-to-start)
- [Hardware](#hardware)
- [Software](#software)
- [Creators](#creators)
- [Copyright and license](#copyright-and-license)


## Description

This project contains hardware, software and documentation files for the "course en cours" **educationnal competition in France**.
During a year, teams of 4 to 6 middle/high school **students build their small electic car** using the same tools as engineers. the contest consists of **designing, creating, testing and running** a small model car during the** regional competitions**, to acces the **national final**.

We are two university students in electrical engineering and industrial data processing, from <a href="https://iut-rennes.univ-rennes1.fr/les-6-departements/genie-electrique-informatique-industrielle">IUT de Rennes</a>, France.
Our project is to **integrate embedded telemetry, datalogging and manual control** into the existings cars engines.
We choosed to works with the **Arduino environnement**, to make it possible for everybody to program their car, modify it as they like, and to make programming accesible for the young people of the competition.

This project is **realesed under the general public license and is strongly welcome to modifications**.

## Where to start

In order to be able to program your board with the arduino IDE via usb, you will first need to install a bootloader on your board. Sparkfun have made an easy to understand tutorial on how to do that here : <a href="https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader">Installing an arduino bootloader</a>

Here is the wiring diagram to install the bootloader with an arduino UNO (follow the sparkfun tutorial for step by step instructions).

<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/Bootloader_ICSP.png" alt="" width=789 height=413>
</p>

When installing the bootloader, make sure your arduino target board is the arduino nano, as this board is arduino nano compatible.

When this step is done you should be able to programm your board like if it was an arduinon nano.

Just install the course-en-cours library (<a href="#software">link in the software section</a>) and import it to your arduino sketch.
<a href="https://www.arduino.cc/en/Guide/Libraries">Here is a tutorial</a> if you need help for this step.

You should now be able to use the functions described in the <a href="#software">software section</a>.



## Hardware

The hardware is based on 4 main components:
- ATmega328p microcontroller (the same as the arduino uno/nano)
- MPU6050 accelerometer and gyro chip
- A FTDI chip (to program the microcontroller via USB)
- A micro SD card holder

This board is **fully arduino compatible** and should be selected in the arduino environnement as the arduino nano.

### Documents availables

- <a href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Schematics.pdf">Schematics (PDF)</a>
- <a href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/BOM.pdf">Bill of materials (PDF)</a>
- <a href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.sch">Autodesk Eagle schematics file</a>
- <a href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.brd">Autodesk Eagle board file</a>


### PCB pinout diagram:
![PCB pinout](https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_pinout.jpg)

### PCB wiring diagram:
<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_wiring.png" alt="" width=876 height=398>
</p>

## Software

## Creators

**Heol Fief**

- <https://github.com/heolfief>

**Dylan Gageot**

- <https://github.com/dylangageot>

## Copyright and license
heolfief/Course-en-Cours is licensed under the GNU General Public License v3.0.

See the <a href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">LICENSE file</a> for more informations.
