// Course en Cours - 19/12/2017
// PROGRAMME DE TEST sur carte
// Ardunio Nano - 16MHz
// Version avec timer

// Bibliothèques
#include <MPU6050.h>
#include <Servo.h>
#include <SPI.h>
#include <SdFat.h>

// Prototype
void datalogging(void);

// Constantes et redéfinitions de types
#define SerialPort Serial
#define MANU 0
#define AUTO 1
#define INTERRUPT_MPU_PIN 2
#define MAX_LOGGING 2000
const int mode = MANU;
const int chipSelect = 4;
const int escPin = 9;
const int rc_inPin = 3;

// Diverses variables
MPU6050 imu;
Vector accel;
Servo moteur;
SdFat sd;
SdFile dataFile;
String sd_buffer;
int i;
int temps;
short commande_esc;
long double temp_interrupt = 0;
bool esc_init, datalogging_enable;
unsigned long actual_time, last_time;

// Fonction d'initialisation
void setup() {

  // Configuration pour l'interruption du pilotage manuel
  pinMode(rc_inPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rc_inPin), interruption, CHANGE);
  commande_esc = 0;

  // Port série à 115200 bauds
  SerialPort.begin(115200);

  // Attente que l'utilisateur ouvre son port série
  while (!SerialPort);

  // Initialisation de la centrale inertielle
  if (imu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G) == 0) {
    SerialPort.println("IMU non initialisée");
  } else {
    SerialPort.println("IMU initialisée");
  }

  // Initialisation du module carte SD et création
  // d'un fichier datalog.csv si inexistant
  sd.begin(chipSelect, SD_SCK_MHZ(16));

  if (!dataFile.open("datalog.csv", O_CREAT | O_WRITE)) {
    SerialPort.println("SD  non initialisée");
  } else {
    // Initialisation du fichier datalog.csv
    SerialPort.println("Fichier crée");
    dataFile.println("t;commande;x;y;z");
    SerialPort.println("SD  initialisée");
  }

  // Initialisation du signal pour l'ESC
  moteur.attach(escPin);

  // Initialisation du temps
  last_time = millis();
  SerialPort.println("Datalogging en cours");
  temps = millis();
  datalogging_enable = 1;
  i = 0;

}

// Boucle principale
void loop() {

  // Si l'ESC n'a pas été initialisé, on l'initialise
  if (!esc_init) {
    init_esc();
    esc_init = 1;
  }

  actual_time = millis();
  puissance_moteur(commande_esc);
  if (((actual_time - last_time) >= 5) && datalogging_enable) {
    last_time = actual_time;
    datalogging();
  }
}

void datalogging(void) {

  // Mise à jour des données issue de la centrale inertielle
  accel = imu.readNormalizeAccel();

  // Mise en forme de données puis écriture dans la carte SD
  sd_buffer = "";
  sd_buffer += String(i) + ';' + String(commande_esc) + ';' + String(accel.XAxis) + ';' + String(accel.YAxis) + ';' + String(accel.ZAxis);
  dataFile.println(sd_buffer);

  // Si le compteur à atteint la valeur de MAX_LOGGING, on arrête le datalogging
  // Ici la valeur maximum de i (MAX_LOGGING) doit être multiplié par deux pour
  // obtenir de le temps de logging en millisecondes : MAX_LOGGING * 2 = ms
  if (++i == MAX_LOGGING) {
    // On ferme proprement le fichier de logging
    dataFile.close();
    // On affiche le temps pris pour datalogger
    SerialPort.println("Datalogging fini :");
    SerialPort.println(millis() - temps);
    // On stop le tache de datalogging
    datalogging_enable = 0;
  }

}

void interruption() {
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

void puissance_moteur(int pourcentage) {
  int value;
  value = map(pourcentage, 0, 100, 96, 137);
  moteur.write(value);
}

void init_esc(void) {
  moteur.write(141);
  delay(3000);
  moteur.write(91);
  delay(1000);
  moteur.write(0);
  delay(1000);
}
