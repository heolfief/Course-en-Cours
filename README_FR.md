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

Pour pouvoir programmer votre carte course en cours avec l'IDE d'arduino via USB, vous devez d'abord y installer un bootloader.
Vous trouverez les instructions nécessaires dans la section <a href="#logiciel">logicielle</a>.

Après cette étape faite, vous devriez pouvoir programmer votre carte comme si elle était un arduino nano.

Il vous suffit d'installer la bibliothèque course-en-cours (<a href="#logiciel">lien dans la section logicielle</a>) et importez-la dans votre croquis arduino. <a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Voici un tutoriel</a> pour importer une bibliothèque si vous avez besion d'aide.

Vous pouvez maintenant programmer votre carte, comme décrit dans la section <a href="#logiciel">logicielle</a>.

## Matériel

La cartre est basée sur quarte principaux composants :
- Un microcontrôleur ATmega328p (le même que pour l'Arduino UNO/Nano)
- Un accéléromètre et gyroscope MPU6050
- Une puce FTDI (pour programmer le microcontrôleur par USB)
- Un conecteur de cartes micro SD

Cette carte est **entièrement compatible Arduino** et doit être selectionnée dans l'IDE Arduino comme un Arduino nano.

### Documents disponibles

- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Schematics.pdf">Schéma électrique (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/BOM.pdf">Liste des composants (PDF)</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.sch">Autodesk Eagle fichier schéma</a>
- <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/Hardware/Carte%20course%20en%20cours.brd">Autodesk Eagle fichier routage</a>


### Schéma de brochage:
![PCB pinout](https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_pinout.jpg)

### Schéma de cablage complet du système:
<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/PCB_wiring.png" alt="" width=870>
</p>

**ATTENTION : Vous devez alimenter la carte en 3,3V, la brancher directement à la batterie 11,1V la détruierait. Vous pouvez abaisser la tension de la baterie vers du 3,3V grace à un module convertisseur DC/DC standard (aussi appelé buck-converter) réglé en 3,3V (min 200mA), comme sur le schéma ci dessus.**

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
heolfief/Course-en-Cours est sous license GNU GPL v3.0.
Plus d'informations dans le <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">fichier LICENSE</a>.
