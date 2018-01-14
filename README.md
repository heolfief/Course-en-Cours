<p align="center">
	<a target="_blank" href="http://www.course-en-cours.com/">
		<img src="http://www.course-en-cours.com/media/uploads/documents_utils/CeC-logo2017.png" alt="" width=360>
	</a>

<h1 align="center">Course en cours</h1>

<p align="center">
	<a target="_blank" href="http://www.course-en-cours.com/">www.course-en-cours.com</a>
</p>
</p>
<HR>
<br>

<p align="center">
	<img src="https://github.com/heolfief/Course-en-Cours/blob/master/Resources/france-circle-128.png" width=30>
	<a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/README_FR.md">VERSION EN FRANCAIS / FRENCH VERSION</a>
</p>

## Table of contents

- [Description](#description)
- [Where to start](#where-to-start)
- [Hardware](#hardware)
- [Software](#software)
- [Creators](#creators)
- [Copyright and license](#copyright-and-license)


## Description

This project contains hardware, software and documentation files for the "course en cours" **educationnal competition in France**.
During a year, teams of 4 to 6 middle/high school **students build their small electic car** using the same tools as engineers. the contest consists of **designing, creating, testing and running** a small model car during the **regional competitions**, to acces the **national final**.

We are two university students in electrical engineering and industrial data processing, from <a href="https://iut-rennes.univ-rennes1.fr/les-6-departements/genie-electrique-informatique-industrielle">IUT de Rennes</a>, France.
Our project is to **integrate embedded telemetry, datalogging and manual control** into the existings cars engines.
We choosed to works with the **Arduino environnement**, to make it possible for everybody to program their car, modify it as they like, and to make programming accesible for the young people of the competition.

This project is **realesed under the general public license and is strongly welcome to modifications**.

## Where to start

In order to be able to program your board with the arduino IDE via usb, you will first need to install a bootloader on your board. Find insruction on how to do that in the <a href="#bootloader">software section</a>.

When this step is done you should be able to programm your board like if it was an arduinon nano.

Just install the course-en-cours library (<a href="#software">link in the software section</a>) and import it to your arduino sketch.
<a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Here is a tutorial</a> if you need help for this step.

You should now be able to program your board via USB, as described in the <a href="#software">software section</a>.



## Hardware

The hardware is based on 4 main components:
- ATmega328p microcontroller (the same as the arduino uno/nano)
- MPU6050 accelerometer and gyro chip
- A FTDI chip (to program the microcontroller via USB)
- A micro SD card holder

This board is **fully arduino compatible** and should be selected in the arduino environnement as the arduino nano.

### Documents availables

- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Schematics.pdf">Schematics (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/BOM.pdf">Bill of materials (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.sch">Autodesk Eagle schematics file</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.brd">Autodesk Eagle board file</a>
- <a href="https://github.com/heolfief/Course-en-Cours/tree/master/Hardware/Gerbers">Gerber files</a>


### Board form factor
<table border="0">
	<tbody>
		<tr>
			<th align="center"><img src="https://github.com/heolfief/Course-en-Cours/blob/master/Resources/dim.png" alt="" width=400></th>
			<th align="center"><img src="https://github.com/heolfief/Course-en-Cours/blob/master/Resources/echelle.png" alt="" width=400></th>
		</tr>
	</tbody>
</table>


### PCB pinout diagram:
![PCB pinout](https://github.com/heolfief/Course-en-Cours/blob/master/Resources/PCB_pinout.jpg)

### PCB wiring diagram:
<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Resources/PCB_wiring.png" alt="" width=870>
</p>

**BE CAREFULL: You need to provide 3.3V to the board, plugging directly the 11.1V LiPo battery will kill it. You can step down the battery voltage with a standard DC/DC converter (also known as buck-converter) set to output 3.3V (min 200mA), like in the wiring diagram above.**

## Software

### Firmware

<img src="https://www.arduino.cc/arduino_logo.png" alt="" width=80>
You can program your course en cours board in C/C++ directly with the <a target="_blank" href="https://www.arduino.cc/en/main/software">arduino IDE</a> via USB, assuming you already have a bootloader installed on your board. Instructions on how to flash a bootloader <a href="#bootloader">below</a>.

In the arduino IDE, select the "arduino nano" under Tools/Board, and the ATmega328p under Tools/Processor. Then select the COM port (under Tools/Port) on wich the board is plugged.
To access all the course en cours related function, just import the "course_en_cours" library to your sketch.
<a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Here is a tutorial</a> if you need help for this step.

You should now be able to program your board with the arduino software environement.

#### Needed libraries

- [MPU6050](https://github.com/jarzebski/Arduino-MPU6050) by **_jarzebski_** : Allows us to use the IMU.
- [SDFat](https://github.com/greiman/SdFat) by **_greiman_** : Allows us to get a high speed SD card communication.

#### Exemple code:
```cpp
#include "Course_en_Cours.h"

Couse_en_Cours cec;	 // create Couse_en_Cours object

void setup() {
	cec.initialiser(AUTO);
	cec.palier_moteur(1000,0);
	cec.palier_moteur(5000,50);
	cec.palier_moteur(7500,75);
}

void loop() {
	cec.executer();
}
```
<table>
	<tbody>
		<tr>
			<th align="center">Function</th>
			<th align="center">Description</th>
			<th align="center">Parameters</th>
		</tr>
		<tr>
			<td><code>cec.executer(void);</code></td>
			<td>Mandatory function, needs to be run in the loop().</td>
			<td>
				<ul>
				<li><strong>cec</strong> : a variable of type Course_en_cours</li>
				</ul>
			</td>
		</tr>
		<tr>
			<td><code>cec.initialiser(bool pilotage_mode);</code></td>
			<td>Function to set the driving mode. Needs to be run in the setup().</td>
			<td>
				<ul>
				<li><strong>cec</strong> : a variable of type Course_en_cours</li>
				<li><strong>pilotage_mode</strong> : the mode you want your car to run in. Can be set to "AUTO" or "MANU".
					<ul>
						<li>AUTO : you can drive the motor within your arduino code with the palier_moteur function.</li>
						<li>MANU : palier_moteur functions are disabled, and remote control signal is redirected to the ESC. You can manualy drive the motors with a remote.</li>
					</ul>
				</li>
				</ul>
			</td>
		</tr>
		<tr>
			<td><code>cec.palier_moteur(unsigned int ms, unsigned char pourcentage);</code></td>
			<td>The motor power step function. Use it in the setup() to set a fixed power/speed to the motor at a certain time. Can be called several times to create differents steps at different times. </td>
			<td>
				<ul>
					<li><strong>cec</strong> : a variable of type Course_en_cours</li>
					<li><strong>ms</strong> : the time in milieconds you want the function to take effect. Timer starts right after power-up.</li>
					<li><strong>pourcentage</strong> : this sets the power/speed of the motor, in percentage.</li>
				</ul>
			</td>
		</tr>
	</tbody>
</table>


#### Known issues

The actual software have some issues :
- If the .csv file is not already on the SD card, the logging would be slower than expected. Make sure that the file already exists on the card.
- The logging time may vary depending of how many steps (palier_moteur functions) you have added.
- The object Course_en_Cours must be called "cec" and declared as global variable (away from the loop() and setup(), or from any fonction).

### Bootloader

In order to be able to program your board with the arduino IDE via usb, you will first need to install a bootloader on your board. Sparkfun have made an easy to understand tutorial on how to do that here : <a target="_blank" href="https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader">Installing an arduino bootloader</a>

Here is the wiring diagram to install the bootloader with an arduino UNO (follow the sparkfun tutorial for step by step instructions).

<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Resources/Bootloader.png" alt="" width=800>
</p>

When installing the bootloader, make sure your arduino target board is the arduino nano, as this board is arduino nano compatible.

You should now be able to program your board via USB, as described in the <a href="#software">software section</a>.

## Creators

**Heol Fief**

- <https://github.com/heolfief>

**Dylan Gageot**

- <https://github.com/dylangageot>

## Copyright and license
heolfief/Course-en-Cours is licensed under the GNU General Public License v3.0.

See the <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">LICENSE file</a> for more informations.
