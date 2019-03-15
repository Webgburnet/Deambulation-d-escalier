/* 
* PROJET Demanbulateur d'escalier
* 
* Arduino Uno
* Shield Grove
* 
* A0: Relay 1
* A1: Relay 2
* A2: Relay 3
* A3: Relay 4
* A4: Cardiaque ?
* A5: 
* 
* pin0 : RX rs232 non utilise
* pin1 : TX rs232 non utilise
* pin2 : RX Bluetooth / GPRS ?
* pin3 : TX Bluetooth / GPRS ?
* 
* pin4 : 
* pin5 : PIR motion haut
* pin6 : PIR motion bas
* pin7 : Fin de course haut
* pin8 : Fin de course bas
* 
* pin9 : 
* pin10 : 
* pin11 : 
* pin12 : Cles GPRS ?
* pin13 : 
* 
* SDA :
* SCL :
* 
*/ 

#define pin_PIR_haut 5
#define pin_PIR_bas 6
#define pin_fin_course_haut 7
#define pin_fin_course_bas 8
#define pin_motor1 14 // Monte broche A0
#define pin_motor2 15 // Descente broche A1
#define pin_motor3 16 // Monte broche A2
#define pin_motor4 17 // Descente broche A3

int battement_coeur=0;

void setup() {
	Serial.begin(9600);

	pinMode(pin_fin_course_haut, INPUT);
	pinMode(pin_fin_course_bas, INPUT);
	pinMode(pin_PIR_haut, INPUT);
	pinMode(pin_PIR_bas, INPUT);

	pinMode(pin_motor1, OUTPUT);
	pinMode(pin_motor2, OUTPUT);
	pinMode(pin_motor3, OUTPUT);
	pinMode(pin_motor4, OUTPUT);

	digitalWrite(pin_motor1, LOW);
	digitalWrite(pin_motor2, LOW);
	digitalWrite(pin_motor3, LOW);
	digitalWrite(pin_motor4, LOW);
	}

void loop() {
	boolean etat_fin_course_bas = digitalRead(pin_fin_course_bas);
	boolean etat_fin_course_haut = digitalRead(pin_fin_course_haut);
	boolean etat_PIR_bas = digitalRead(pin_PIR_bas);
	boolean etat_PIR_haut = digitalRead(pin_PIR_haut);

	//  Serial.print("etat_PIR_bas = ");
	//  Serial.println(etat_PIR_bas);
	//  Serial.print("etat_PIR_haut = ");
	//  Serial.println(etat_PIR_haut);
	//  Serial.print("etat_fin_course_bas = ");
	//  Serial.println(etat_fin_course_bas);
	//  Serial.print("etat_fin_course_haut = ");
	//  Serial.println(etat_fin_course_haut);
	//  Serial.println("*************");

	//Rythme cardiaque
	if (Serial.available() > 0) 
	{
		// Lire le byte entrant
		battement_coeur = Serial.read();

		// say what you got:
		Serial.print("Recu : ");
		Serial.println(battement_coeur, DEC);
	}

	//Telephone

	//Motorisation de l'escalier
	if(etat_PIR_bas==1 && etat_PIR_haut==1)
	{
		digitalWrite(pin_motor1, LOW);
		digitalWrite(pin_motor2, LOW);
		digitalWrite(pin_motor3, LOW);
		digitalWrite(pin_motor4, LOW);
		Serial.println("Arret Critique");
		battement_coeur=0;
	}
	else
	{
		if(etat_PIR_bas==1 && etat_fin_course_haut==0 && battement_coeur>0 )
		{
			digitalWrite(pin_motor1, HIGH);
			digitalWrite(pin_motor2, LOW);
			digitalWrite(pin_motor3, HIGH);
			digitalWrite(pin_motor4, LOW);
			Serial.println("Monte");

		}
		else if(etat_PIR_haut==1 && etat_fin_course_bas==0 && battement_coeur>0)
		{
			digitalWrite(pin_motor1, LOW);
			digitalWrite(pin_motor2, HIGH);
			digitalWrite(pin_motor3, LOW);
			digitalWrite(pin_motor4, HIGH);
			Serial.println("Descente");
		}
		else
		{
			digitalWrite(pin_motor1, LOW);
			digitalWrite(pin_motor2, LOW);
			digitalWrite(pin_motor3, LOW);
			digitalWrite(pin_motor4, LOW);
			Serial.println("Arret");
			battement_coeur=0;
		}
	}
}
