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
	<a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/README.md">VERSION EN ANGLAIS / ENGLISH VERSION</a>
</p>

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
Vous pouvez programmer votre carte directement en C/C++ avec l'<a target="_blank" href="https://www.arduino.cc/en/main/software">Arduino IDE</a> par USB, à condition que vous avez déja un bootloader d'installé sur votre carte. Instructions pour flasher le bootloader <a href="#bootloader">ci dessous</a>.

Dans l'IDE Arduino sélectionnez l'"Arduino Nano" dans Outils/Type de carte. Ensuite, sélectionnez le port COM (dans Outils/Port) sur lequel la carte est branchée.
Pour accéder aux fonctions course-en-cours, importez la bibilothèque "course_en_cours" dans votre croquis Arduino.
<a target="_blank" href="https://www.arduino.cc/en/Guide/Libraries">Voici un tutoriel</a> si vous avez besoin d'aide pour cette étape.

Vous devriez maintenant pouvoir programmer votre carte avec l'IDE Arduino.

#### Exemple de code:
```cpp
#include "Course_en_Cours.h"

Couse_en_Cours cec;  // create Couse_en_Cours object

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
			<td>Fonction obligatoire, doit être placée dans le loop().</td>
			<td>
				<ul>
				<li><strong>cec</strong> : variable de type Course_en_cours</li>
				</ul>
			</td>
		</tr>
		<tr>
			<td><code>cec.initialiser(bool pilotage_mode);</code></td>
			<td>Fonction définissant le mode de pilotage. Doit être placée dans le setup().</td>
			<td>
				<ul>
				<li><strong>cec</strong> : variable de type Course_en_cours</li>
				<li><strong>pilotage_mode</strong> : le mode dans lequel vous voulez piloter votre vioture. "AUTO" ou "MANU".
					<ul>
						<li>AUTO : vous pouvez controller le moteur avec la fontion palier_moteur.</li>
						<li>MANU : la fonction palier_moteur est désactivée, et le signal du récepteur RF est transmis directement a l'ESC. Vous pouvez contrôler manuellement le moteur avec une télécommande de modélisme.</li>
					</ul>
				</li>
				</ul>
			</td>
		</tr>
		<tr>
			<td><code>cec.palier_moteur(unsigned int ms, unsigned char pourcentage);</code></td>
			<td>Fonction de réglage de puissance/vitess du moteur. A utliser dans le setup() pour régler la puissance/vitesse du moteur à un moment voulu de la course. Peut-être appelée plusieurs fois pour créer différents palier de vtesse à différents moments.</td>
			<td>
				<ul>
					<li><strong>cec</strong> : variable de type Course_en_cours</li>
					<li><strong>ms</strong> : Le moment en millisecondes auquel la fonction prendra effet. Le timer démarrer juste après la mise sous tension de la carte.</li>
					<li><strong>pourcentage</strong> : Correspond à la puissance/vitesse du moteur souhaitée en pourcentages.</li>
				</ul>
			</td>
		</tr>
	</tbody>
</table>


#### Problèmes connus

Le logiciel actuel présente encore quelques problèmes :
- Si le fichier .csv n'est pas déja sur la carte SD, l'enregistrement des données sera plus long qu'attendu. Asurez-vous que le fichier existe déja sur la carte SD pour évitr le problème.
- Le temps d'enregistrement des données peut fluctuer en fonction du nombre de fonction palier_moteur appelées.
- L'objet Course_en_Cours doit obligatoirement être appelé "cec" et déclaré comme variable globale (en dehors du loop() et du setup() ou de tout autre fonction.

### Bootloader

Pour pouvoir programmer votre carte avec l'IDE Arduino vous devez d'abbord installer un bootloader sur votre carte.
Sparkfun propose déja un très bon tutoriel (Anglais) pour faire cela ici : <a target="_blank" href="https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader">Installing an arduino bootloader</a>

Voici un schéma de cablage pour installer le bootloader avec un arduino UNO (suivez les instruction de sparkfun pour les étapes d'installation).

<p align="center">
  <img src="https://github.com/heolfief/Course-en-Cours/blob/master/Documentation/files/Bootloader.png" alt="" width=800>
</p>

Avant d'installer, réglez la carte cible dans l'IDE Arduino sur "Arduino nano".

Vous pouvez maintenant programmer votre carte, comme décrit dans la section <a href="#logiciel">logicielle</a>.

## Auteurs

**Heol Fief**

- <https://github.com/heolfief>

**Dylan Gageot**

- <https://github.com/dylangageot>

## Copyright et license
heolfief/Course-en-Cours est sous license GNU GPL v3.0.
Plus d'informations dans le <a target="_blank" href="https://github.com/heolfief/Course-en-Cours/blob/master/LICENSE">fichier LICENSE</a>.
