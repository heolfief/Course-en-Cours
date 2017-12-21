// Bibliothèques
#include <MPU6050.h>
#include <Servo.h>
#include <SPI.h>
#include <SdFat.h>

// Constantes
#define SerialPort Serial
#define MANU 0
#define AUTO 1
#define MAX_LOGGING 2000
#define MAX_PALIER 20
const int chipSelect = 4;
const int escPin = 9;
const int rc_inPin = 3;

void interruptionDispatched(void);

class Course_en_Cours {
	
		public:
			Course_en_Cours(void);
			void executer(void);
			void initialiser(bool pilotage_mode);
			void palier_moteur(unsigned int ms, unsigned char pourcentage);
			void interruption(void);
			
		private:
			
			void datalogging(void);
			void puissance_moteur(unsigned int pourcentage);
			void init_esc(void);
			
			MPU6050 centrale_inertielle;
			Vector valeur_accel;
			Servo moteur;
			SdFat sd;
			SdFile fichier;
			String tampon_sd;
			int nb_log, nb_palier;
			short commande_esc;
			long double temp_interrupt;
			bool esc_init, datalogging_enable, mode;
			unsigned long actual_time, last_time_log, last_time_palier;
			unsigned int tab_palier_ms[MAX_PALIER];
			unsigned char tab_palier_pourcentage[MAX_PALIER];
			
};
