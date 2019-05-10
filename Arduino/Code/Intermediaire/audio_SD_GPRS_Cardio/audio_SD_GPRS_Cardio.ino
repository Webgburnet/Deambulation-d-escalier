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

#define SDPIN 4          // Chip Select du lecteur SD
#define SPEAKERPIN 46 // Set sur les broches 5, 6, 11 et 46 Pour la Mega ; 9 pour la UNO
TMRpcm tmrpcm;
SoftwareSerial mySerial(14, 15);

unsigned char battement_coeur=0;

unsigned int cles = 0;

void setup() 
{
  Serial.begin(9600);
  
  Wire.begin();
  
  Serial.print("Initialisation Carte SD...");
  if (!SD.begin(SDPIN)) 
  {
    Serial.println("initialization failed!");
  }
  Serial.println("carte initialisée !");
  Serial.println("");

  tmrpcm.speakerPin = SPEAKERPIN ;
  
  mySerial.begin(19200);          // Paramètres par défaut du port série du GPRS shield (19200bps 8-N-1)
  mySerial.print("\r");           // Envoyer un retour à la ligne <CR>
  Serial.println("Commande Moniteur Serie : ");
  Serial.println("t:jouer la musique test");
  Serial.println("e:Emission");
  Serial.println("r:Reception");
  Serial.println("f:Raccrocher");
  Serial.println("s: SMS");
  Serial.println("");

  delay(1000);                    // Attendre une seconde que le modem retourne "OK"
}

void loop() 
{
  //Rythme cardiaque
  Wire.requestFrom(0xA0 >> 1, 1);
  if (Wire.available() > 0) 
  {
    // Lire le byte entrant
    battement_coeur = Wire.read();

    // say what you got:
    Serial.print("Recu : ");
    Serial.println(battement_coeur, DEC);
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
      mySerial.println("ATA");
      cles=0;
    }

    if(cles==101) //lettre e
    {
      Serial.println("Emission appel Tel");
      mySerial.println("ATD+33601241766;"); // xxxxxxxxx est le numéro a appeler.
      delay(10000);
//      tmrpcm.setVolume(3);     // gestion du volume de 0 à 7
//      tmrpcm.quality(0);       // qualitée audio 0 ou 1
//      Serial.println("test.wav");
//      tmrpcm.play("test.wav");  
      cles='t';
    }
    // Raccrocher appel Tel
    if(cles==102)
    {
      mySerial.println("ATH"); // Fin d'appel.
      cles=0;
    }

    // Envoie SMS
    if(cles==115) //lettre s
    {
      Serial.println("Envoie SMS");
      mySerial.print("\r");   // Envoyer un retour à la ligne <CR>
      delay(1000);                    // Attendre une seconde que le modem retourne "OK"
      mySerial.print("AT+CMGF=1\r");  // Envoyer un SMS en mode texte
      delay(1000);
     
      //mySerial.print("AT+CSCA=\"+778255826\"\r");// Configurer le centre de message SMS,  
      //delay(1000);                                  // Retirer les commentaire seulement si nécessaire et
                                                      // remplacer le No avec celui obtenu auprès de votre
                                                      // fournisseur de service mobile.
                                                      //Note: pour inclure un " dans une chaine de caractère
                                                      //  il faut utiliser la notation \"
     
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
  
}
