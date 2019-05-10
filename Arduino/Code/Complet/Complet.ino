/*
  Go to the Link to convert the audio into .wav .
  http://audio.online-convert.com/convert-to-wav
    Go to The Link
    Upload your audio you want to convert to WAV
    Change bit resolution to " 8bit ".
    Change sampling rate to " 16000Hz ".
    Change audio channels " mono " .
    Click on " Show advanced options ".
    PCM format " unsigned 8 bit ".
    Convert file.
At next page click on "direct download link"

Single timer operation: TIMER1 (Uno,Mega) or TIMER3,4 or 5 (Mega)

Les musiques sont mises à la racine

*/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>           // Inclure la librairie SD
#include "TMRpcm.h"
#include "rgb_lcd.h"

#define SDPIN 4          // Chip Select du lecteur SD
#define pin_PIR_haut 5
#define pin_PIR_bas 6
#define pin_fin_course_haut 7
#define pin_fin_course_bas 8
#define pin_RX 14
#define pin_TX 15
//#define pin_motor1 A0 // Monte broche A0
//#define pin_motor2 A1 // Descente broche A1
//#define pin_motor3 A2 // Monte broche A2
//#define pin_motor4 A3 // Descente broche A3
#define SPEAKERPIN 46 // Set sur les broches 5, 6, 11 et 46 Pour la Mega ; 9 pour la UNO
TMRpcm tmrpcm;
SoftwareSerial mySerial(pin_RX, pin_TX);
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

unsigned char battement_coeur=0;

unsigned int cles = 0;

void setup() 
{
  Serial.begin(9600);

  Serial.println("Debut setup");
  Serial.println("");
  
  Serial.println("Initialisation Ecran LCD");
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("Deambulateur");
  
  Serial.println("Initialisation Cardiaque (I2C)");
  Wire.begin();
    
  Serial.print("Initialisation Carte SD...");
  if (!SD.begin(SDPIN)) 
  {
    Serial.println("ECHEC");
  }
  Serial.println("OK !");

  Serial.println("Initialisation Speaker");
  tmrpcm.speakerPin = SPEAKERPIN ;

  Serial.println("Initialisation GSM/GPRS");
  mySerial.begin(19200);          // Paramètres par défaut du port série du GPRS shield (19200bps 8-N-1)
  mySerial.print("\r");           // Envoyer un retour à la ligne <CR>
  delay(2000);                    // Attendre une seconde que le modem retourne "OK"
  
  Serial.println("Initialisation Bouton & Fin de course");
  pinMode(pin_fin_course_haut, INPUT);
  pinMode(pin_fin_course_bas, INPUT);
  pinMode(pin_PIR_haut, INPUT);
  pinMode(pin_PIR_bas, INPUT);
  
  Serial.println("Initialisation Relais Moteur (Pont en H)");
//  pinMode(pin_motor1, OUTPUT);
//  pinMode(pin_motor2, OUTPUT);
//  pinMode(pin_motor3, OUTPUT);
//  pinMode(pin_motor4, OUTPUT);
//
//  digitalWrite(pin_motor1, LOW);
//  digitalWrite(pin_motor2, LOW);
//  digitalWrite(pin_motor3, LOW);
//  digitalWrite(pin_motor4, LOW);

  Serial.println("");
  Serial.println("Commande Moniteur Serie : ");
  Serial.println("t:jouer la musique test");
  Serial.println("e:Emission");
  Serial.println("r:Reception");
  Serial.println("f:Raccrocher");
  Serial.println("s: SMS");
  Serial.println("");
  
  Serial.println("Fin setup");
}

void loop() 
{
  boolean etat_fin_course_bas = digitalRead(pin_fin_course_bas);
  boolean etat_fin_course_haut = digitalRead(pin_fin_course_haut);
  boolean etat_PIR_bas = digitalRead(pin_PIR_bas);
  boolean etat_PIR_haut = digitalRead(pin_PIR_haut);

//    Serial.print("etat_PIR_bas = ");
//    Serial.println(etat_PIR_bas);
//    Serial.print("etat_PIR_haut = ");
//    Serial.println(etat_PIR_haut);
//    Serial.print("etat_fin_course_bas = ");
//    Serial.println(etat_fin_course_bas);
//    Serial.print("etat_fin_course_haut = ");
//    Serial.println(etat_fin_course_haut);
//    Serial.println("*************");
  
  //Rythme cardiaque
  Wire.requestFrom(0xA0 >> 1, 1);
  while (Wire.available() > 0) 
  {
    // Lire le byte entrant
    battement_coeur = Wire.read();

    // say what you got:
    Serial.print("Battement de coeur : ");
    Serial.print(battement_coeur, DEC);
    Serial.println("bpm");
    lcd.setCursor(0, 1);
    lcd.print("Coeur=");
    lcd.print(battement_coeur);
    lcd.print("bpm   ");
  }
  
  if(Serial.available() >0)
  {
    cles=Serial.read();
    Serial.print("cles : ");
    Serial.println(cles);
  }
  
  // Reception appel Tel
  if(cles==114) //lettre r
    {
      Serial.println("Reception appel Tel");
      lcd.setCursor(0, 0);
      lcd.print("Reception Appel    ");
      mySerial.println("ATA");
      delay(1000);
      cles=0;
    }

    if(cles==101) //lettre e
    {
      Serial.println("Emission appel Tel");
      lcd.setCursor(0, 0);
      lcd.print("Emission Appel    ");
      mySerial.println("ATD+33601241766;"); // xxxxxxxxx est le numéro a appeler.
      delay(1000);
      cles='t';
    }
    
//  if (( etat_fin_course_bas==0 && etat_fin_course_haut ==0 ) && ( etat_PIR_haut==0 || etat_PIR_bas==0 ) && ( battement_coeur<1 ))
//  {
//      cles=101  ;  
//   }
    
    // Raccrocher appel Tel
    if(cles==102)
    {
      mySerial.println("ATH"); // Fin d'appel.
      lcd.setCursor(0, 0);
      lcd.print("Fin Appel       ");
      delay(1000);
      cles=0;
    }

    // Envoie SMS
    if(cles==115) //lettre s
    {
      Serial.println("Envoie SMS");
      lcd.setCursor(0, 0);
      lcd.print("Envoie SMS       ");
      mySerial.print("\r");   // Envoyer un retour à la ligne <CR>
      delay(1000);                    // Attendre une seconde que le modem retourne "OK"
      mySerial.print("AT+CMGF=1\r");  // Envoyer un SMS en mode texte
      delay(1000);

      mySerial.print("AT+CMGS=\"+33601241766\"\r");   // Commencer un SMS à envoyer au numéro +91....
                                                      // l'encodage du texte suivra plus bas.
                                                      // Remplacer le No avec celui de votre destinataire.
      delay(1000);
      mySerial.print("La personne est tombe de l'escalier\r");     // Le texte du message
      delay(1000);
      mySerial.write(26);  // Equivalent du Ctrl+Z (fin de texte du SMS)
                           // Note: ici il faut utiliser l'instruction write pour écrire un byte. 
      cles=0;
    }
    
  if(cles=='t')
  {
    tmrpcm.setVolume(3);     // gestion du volume de 0 à 7
    tmrpcm.quality(0);       // qualitée audio 0 ou 1
    Serial.println("test.wav");
    tmrpcm.play("test.wav");
    cles=0;
  }
 
   //Motorisation de l'escalier
 if(etat_PIR_bas==1 && etat_PIR_haut==1)
  {
//    digitalWrite(pin_motor1, LOW);
//    digitalWrite(pin_motor2, LOW);
//    digitalWrite(pin_motor3, LOW);
//    digitalWrite(pin_motor4, LOW);
    Serial.println("Arret Critique du deambulateur");
    lcd.setCursor(0, 0);
     lcd.print("ARRET CRITIQUE    ");
    battement_coeur=0;
  }
  else
  {
    if(etat_PIR_bas==1 && etat_fin_course_haut==0)
    {
//      digitalWrite(pin_motor1, HIGH);
//      digitalWrite(pin_motor2, LOW);
//      digitalWrite(pin_motor3, HIGH);
//      digitalWrite(pin_motor4, LOW);
      Serial.println("Monte du deambulateur");
      lcd.setCursor(0, 0);
      lcd.print("MONTEE          ");

    }
    else if(etat_PIR_haut==1 && etat_fin_course_bas==0)
    {
//      digitalWrite(pin_motor1, LOW);
//      digitalWrite(pin_motor2, HIGH);
//      digitalWrite(pin_motor3, LOW);
//      digitalWrite(pin_motor4, HIGH);
      Serial.println("Descente du deambulateur");
      lcd.setCursor(0, 0);
      lcd.print("DESCENTE          ");
    }
    else
    {
//      digitalWrite(pin_motor1, LOW);
//      digitalWrite(pin_motor2, LOW);
//      digitalWrite(pin_motor3, LOW);
//      digitalWrite(pin_motor4, LOW);
      Serial.println("Arret du deambulateur");
      lcd.setCursor(0, 0);
      lcd.print("ARRETEE          ");
    }
  }
   
  
}
