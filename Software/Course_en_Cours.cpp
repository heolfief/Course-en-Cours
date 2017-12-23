#include "Course_en_Cours.h"

extern Course_en_Cours courseEnCours;

Course_en_Cours::Course_en_Cours() {

}

void interruptionDispatched(void) {
  courseEnCours.interruption();
}

void Course_en_Cours::initialiser(bool pilotage_mode) {

  // Configuration pour l'interruption du pilotage manuel
  pinMode(rc_inPin, INPUT_PULLUP);

  if (pilotage_mode == MANU)
    attachInterrupt(digitalPinToInterrupt(rc_inPin), interruptionDispatched, CHANGE);
    
  commande_esc = 0;

  // Port série à 115200 bauds
  SerialPort.begin(115200);

  // Attente que l'utilisateur ouvre son port série
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
    init_esc();
    esc_init = 1;
    last_time_log = millis();
    last_time_palier = millis();
  }

  actual_time = millis();
  // Si on est en mode AUTOMATIQUE
  if (mode == AUTO) {
    for (int j = 0; j < nb_palier; j++) {
      if (((actual_time - last_time_palier) >= tab_palier_ms[j]) && (j == palier)) {
        puissance_moteur(tab_palier_pourcentage[j]);
        commande_esc = tab_palier_pourcentage[j];
        palier++;
      }
    }
  } else {
    // On est en mode MANU
    puissance_moteur(commande_esc);
  }


  if (((actual_time - last_time_log) >= 5) && datalogging_enable && sd_init) {
    last_time_log = actual_time;
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

  if (digitalRead(rc_inPin))
    temp_interrupt = micros();
  else {
    temp_interrupt = micros() - temp_interrupt;
    if (temp_interrupt >= 1500 && temp_interrupt <= 2020)
      commande_esc = map((short) temp_interrupt, 1500, 2020, 0, 100);
    else {
      if (temp_interrupt < 1500)
        commande_esc = 0;
      else
        commande_esc = 100;
    }
  }

}

void Course_en_Cours::palier_moteur(unsigned int ms, unsigned char pourcentage) {

  if (nb_palier < MAX_PALIER) {
    tab_palier_ms[nb_palier] = ms;
    tab_palier_pourcentage[nb_palier] = pourcentage;
    nb_palier++;
  }

}
