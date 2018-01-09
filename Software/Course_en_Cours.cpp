#include "Course_en_Cours.h"

// Permet l'accès depuis l'exterieur à la variable globale
// "cec"
extern Course_en_Cours cec;

Course_en_Cours::Course_en_Cours() {
  // Constructeur de l'objet vide
}

void interruptionDispatched(void) {
  // On attache l'interruption sur notre objet "cec"
  // d'où l'importance d'appeller la variable globale
  // Course_en_Cours "cec".
  cec.interruption();
}

void Course_en_Cours::initialiser(bool pilotage_mode) {

  // Configuration pour l'interruption du pilotage manuel
  pinMode(rc_inPin, INPUT_PULLUP);

  // Si le pilotage est manuel, on ajoute une interruption sur changement d'état
  // sur le signal issu du recepteur de la télécommande
  if (pilotage_mode == MANU)
    attachInterrupt(digitalPinToInterrupt(rc_inPin), interruptionDispatched, CHANGE);
  
  // Initialisation de la variable contenant la commande pour
  // l'ESC
  commande_esc = 0;

  // Port série à 115200 bauds
  SerialPort.begin(115200);

  // Attente que l'utilisateur ouvre son port série
  // CETTE INSTRUCTION SERT AU DEBUGAGE DU PROGRAMME
  // POUR DEMARRER LE PROGRAMME A L'OUVERTURE
  while (!SerialPort);

  // Initialisation de la centrale inertielle
  if (centrale_inertielle.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G) == 0) {
    SerialPort.println("IMU non initialisée");
  } else {
    SerialPort.println("IMU initialisée");
  }

  // Initialisation du module carte SD et création
  // d'un fichier datalog.csv si inexistant
  sd.begin(chipSelect, SD_SCK_MHZ(16));

  if (!fichier.open("datalog.csv", O_CREAT | O_WRITE)) {
    SerialPort.println("SD  non initialisée");
    sd_init = 0;
  } else {
    // Initialisation du fichier datalog.csv
    SerialPort.println("Fichier crée");
    fichier.println("t;commande;x;y;z");
    SerialPort.println("SD  initialisée");
    // On assure au programme que la carte SD à été initialisé
    sd_init = 1;
  }

  // Initialisation du signal pour l'ESC
  moteur.attach(escPin);

  // Initialisation du temps, des compteurs et du mode
  datalogging_enable = 1;
  nb_log = 0;
  nb_palier = 0;
  palier = 0;
  mode = pilotage_mode;

}

void Course_en_Cours::executer() {

  // Si l'ESC n'a pas été initialisé, on l'initialise
  if (!esc_init) {
    // Calibration de l'ESC
    init_esc();
    // On assure au programme que l'initialisation à été effectué
    esc_init = 1;
    // On démarre le système de gestion des évenements fonction du temps
    last_time_log = millis();
    last_time_palier = millis();
  }

  // On actualise la valeur du temps
  actual_time = millis();
  
  // Si on est en mode AUTOMATIQUE
  if (mode == AUTO) {
    // Scrutation des paliers à effectuer si ils n'ont pas été traité
    for (int j = 0; j < nb_palier; j++) {
      if (((actual_time - last_time_palier) >= tab_palier_ms[j]) && (tab_palier_pourcentage[j] != 255)) {
        // Application de la valeur de palier
        puissance_moteur(tab_palier_pourcentage[j]);
        commande_esc = tab_palier_pourcentage[j];
        // Déclarer le palier comme traité
        tab_palier_pourcentage[j] = 255;
      }
    }
  } else {
    // On est en mode MANU : la telecommande commande le véhicule
    puissance_moteur(commande_esc);
  }

  // Est-il temps de datalogger et pouvons-nous datalogger ? (toutes les MAX_LOGGING millisecondes)
  if (((actual_time - last_time_log) >= MAX_LOGGING) && datalogging_enable && sd_init) {
    // On actualise le temps à laquel on éxecute le datalogging
    last_time_log = actual_time;
    // On effectue le datalogging
    datalogging();
  }

}

void Course_en_Cours::datalogging(void) {

  // Mise à jour des données
  valeur_accel = centrale_inertielle.readNormalizeAccel();

  // Mise en forme de données puis écriture dans la carte SD
  tampon_sd = "";
  tampon_sd += String(nb_log*5) + ';' + String(commande_esc) + ';' + String(valeur_accel.XAxis) + ';' + String(valeur_accel.YAxis) + ';' + String(valeur_accel.ZAxis);
  fichier.println(tampon_sd);

  // Si le compteur à atteint la valeur de MAX_LOGGING, on arrête le datalogging
  // Ici la valeur maximum de i (MAX_LOGGING) doit être multiplié par deux pour
  // obtenir de le temps de logging en millisecondes : MAX_LOGGING * 5 = ms
  if (++nb_log == MAX_LOGGING) {
    // On ferme proprement le fichier de logging
    fichier.close();
    SerialPort.println("Datalogging effectué");
    // On stop le tache de datalogging
    datalogging_enable = 0;
  }

}

void Course_en_Cours::puissance_moteur(unsigned int pourcentage) {

  // Conversion pourcentage vers valeur de pulsation
  int value;
  value = map(pourcentage, 0, 100, 96, 137);
  moteur.write(value);

}

void Course_en_Cours::init_esc(void) {

  // Séquence d'initialisation du moteur
  moteur.write(141);
  delay(3000);
  moteur.write(91);
  delay(1000);
  moteur.write(0);
  delay(1000);

}

void Course_en_Cours::interruption() {

  // Cette interruption permet de faire une copie du signal
  // issue du recepteur pour la télécommande de modélisme
  // L'interruption se déclanche sur un changement d'état
  
  // Si la sortie du récepteur est à l'état haut
  if (digitalRead(rc_inPin))
    // On enrengiste à quel moment cela arrive
    temp_interrupt = micros();
  else {
    // Si la sortie du récepteur est à l'état bas
    temp_interrupt = micros() - temp_interrupt;
    // On convertie la différence de temps entre le début de l'état haut
    // et l'arrivé de l'état bas en puissance moteur
    if (temp_interrupt >= 1500 && temp_interrupt <= 2020)
      // Si la différence est compris entre la valeur minimal et maximal admise,
      // on utilise la fonction map pour adapter les valeurs [1500;2020us]
      // vers [0;100%]
      commande_esc = map((short) temp_interrupt, 1500, 2020, 0, 100);
    else {
      // Sinon, on affecte des valeurs arbitraires si on est en deça des valeurs
      // min et max
      if (temp_interrupt < 1500)
        commande_esc = 0;
      else
        commande_esc = 100;
    }
  }

}

void Course_en_Cours::palier_moteur(unsigned int ms, unsigned char pourcentage) {

  // si le nombre de palier maximal n'a pas été atteint
  if (nb_palier < MAX_PALIER) {
    // On enrengistre le palier dans les tableaux associés
    tab_palier_ms[nb_palier] = ms;
    tab_palier_pourcentage[nb_palier] = pourcentage;
    // On incrémente le nombre de palier enrengistrer
    nb_palier++;
  }

}
