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

## Table des matières

- [Présentation](#presentation)
- [Par où commencer](#par_ou_commencer)
- [Materiel](#materiel)
- [Logiciel](#logiciel)
- [Auteurs](#auteurs)
- [Copyright et license](#copyright-et-license)


## Présentation

Ce projet contient les fichiers de materiel, logiciel et de documentation pour la **compétition éducative** "course en cours" en France.
COURSE EN COURS est un dispositif pédagogique original, centré sur les **Sciences et la Technologie**. Durant une année scolaire, des **équipes de 4 à 6 collégiens ou lycéens** montent leur écurie de **bolide électrique** en utilisant les mêmes outils et processus que les ingénieurs et professionnels de la filière automobile et mobilités. Les participants imaginent, conçoivent, fabriquent, testent et font courir leur mini véhicule de course lors des **épreuves régionales**, pour accéder à la **grande Finale Nationale**.


Nous sommes deux étudiants en GEII (Génie Electrique et Informatique Industrielle) à l'<a href="https://iut-rennes.univ-rennes1.fr/les-6-departements/genie-electrique-informatique-industrielle">IUT de Rennes</a>.
Notre projet d'études consiste à intégrer un système de **télémétrie embarquée** ainsi que une fonctionnalité d'**enregistrement des données** et de **pilotage manuel** sur les blocs moteurs des voitures de la compétition. Nous avons choisis de travailler avec l'**environnement Arduino** afin de rendre la **programation** de sa voiture accessible à tous. 

Ce projet est sous **license libre GPU** (<a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">LICENSE</a>), et toutes modifications ou améliorations sont les bienvenues.

## Par où commencer

In order to be able to program your board with the arduino IDE via usb, you will first need to install a bootloader on your board. Find insruction on how to do that in the <a href="#bootloader">software section</a>.

When this step is done you should be able to programm your board like if it was an arduinon nano.

Just install the course-en-cours library (<a href="#software">link in the software section</a>) and import it to your arduino sketch.
<a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Here is a tutorial</a> if you need help for this step.

You should now be able to program your board via USB, as described in the <a href="#software">software section</a>.

## Matériel

The hardware is based on 4 main components:
- ATmega328p microcontroller (the same as the arduino uno/nano)
- MPU6050 accelerometer and gyro chip
- A FTDI chip (to program the microcontroller via USB)
- A micro SD card holder

This board is **fully arduino compatible** and should be selected in the arduino environnement as the arduino nano.

### Documents disponibles

- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Schematics.pdf">Schematics (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/BOM.pdf">Bill of materials (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.sch">Autodesk Eagle schematics file</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.brd">Autodesk Eagle board file</a>


### Schéma de brochage:
![PCB pinout](https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_pinout.jpg)

### Schéma de cablage complet du système:
<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_wiring.png" alt="" width=870>
</p>

**BE CAREFULL: You need to provide 3.3V to the board, plugging directly the 11.1V LiPo battery will kill it. You can step down the battery voltage with a standard DC/DC converter (also known as buck-converter) set to output 3.3V (min 200mA), like in the wiring diagram above.**

## Logiciel

### Firmware

<img src="https://www.arduino.cc/arduino_logo.png" alt="" width=80>
You can program your course en cours board in C/C++ directly with the <a target="_blank" href="https://www.arduino.cc/en/main/software">arduino IDE</a> via USB, assuming you already have a bootloader installed on your board. Instructions on how to flash a bootloader <a href="#bootloader">below</a>.

In the arduino IDE, select the "arduino nano" under Tools/Board, and the ATmega328p under Tools/Processor. Then select the COM port (under Tools/Port) on wich the board is plugged.
To access all the course en cours related function, just import the "course_en_cours" library to your sketch.
<a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Here is a tutorial</a> if you need help for this step.

You should now be able to program your board with the arduino software environement.


### Bootloader

In order to be able to program your board with the arduino IDE via usb, you will first need to install a bootloader on your board. Sparkfun have made an easy to understand tutorial on how to do that here : <a target="_blank" href="https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader">Installing an arduino bootloader</a>

Here is the wiring diagram to install the bootloader with an arduino UNO (follow the sparkfun tutorial for step by step instructions).

<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/Bootloader.png" alt="" width=800>
</p>

When installing the bootloader, make sure your arduino target board is the arduino nano, as this board is arduino nano compatible.

You should now be able to program your board via USB, as described in the <a href="#software">software section</a>.

## Auteurs

**Heol Fief**

- <https://github.com/heolfief>

**Dylan Gageot**

- <https://github.com/dylangageot>

## Copyright et license
heolfief/Course-en-Cours is licensed under the GNU General Public License v3.0.

See the <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">LICENSE file</a> for more informations.
