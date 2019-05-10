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

#include <SPI.h>
#include <SD.h>           // Inclure la librairie SD
#include "TMRpcm.h"

#define SDPIN 4          // Chip Select du lecteur SD
#define SPEAKERPIN 46 // Set sur les broches 5,6, 11 et 46 Pour la Mega ; 9 pour la UNO
TMRpcm tmrpcm;

int volume = 7; // gestion du volume de 0 à 7
int qualite = 1; // qualitée audio 0 ou 1

unsigned int cles = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.print("Initialisation Carte SD...");
  
  if (!SD.begin(SDPIN)) 
  {
    Serial.println("initialization failed!");
  }
  
  Serial.println("carte initialisée !");

  tmrpcm.speakerPin = SPEAKERPIN ;
  tmrpcm.setVolume(volume);     // gestion du volume de 0 à 7
  tmrpcm.quality(qualite);       // qualitée audio 0 ou 1
  Serial.println("Commande Moniteur Serie :");
  Serial.println("t:jouer la musique test");
  Serial.println("1:jouer la musique 1");
  Serial.println("2:jouer la musique 2");
  
}

void loop() 
{
  if(Serial.available() >0)
  {
    cles=Serial.read();
  }
  
  if(cles=='1')
  {
    tmrpcm.setVolume(3);     // gestion du volume de 0 à 7
    tmrpcm.quality(1);       // qualitée audio 0 ou 1
    Serial.println("1.wav");
    tmrpcm.play("1.wav");
    cles=0;
  }
  
  if(cles=='2')
  {
    tmrpcm.setVolume(3);     // gestion du volume de 0 à 7
    tmrpcm.quality(1);       // qualitée audio 0 ou 1
    Serial.println("2.wav");
    tmrpcm.play("2.wav");
    cles=0;
  }
  
  if(cles=='t')
  {
    tmrpcm.setVolume(3);     // gestion du volume de 0 à 7
    tmrpcm.quality(1);       // qualitée audio 0 ou 1
    Serial.println("test.wav");
    tmrpcm.play("test.wav");
    cles=0;
  }
  
}
