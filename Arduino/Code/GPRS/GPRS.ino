// Version pour Arduino IDE < 1.0
#include <SoftwareSerial.h>    
 
SoftwareSerial mySerial(2, 3);

int Reception =0;

void setup(){
  Serial.begin(19200);
  mySerial.begin(19200);  // Paramètres par défaut du port série du GPRS shield (19200bps 8-N-1)
  mySerial.print("\r");   // Envoyer un retour à la ligne <CR>
  delay(1000);                    // Attendre une seconde que le modem retourne "OK"
}
 
void loop()
{
      if(Serial.available()>0)
  {
    Reception=Serial.read();
    Serial.println(Reception);
  }
  // Reception appel Tel
  if(Reception==114) //lettre r
    {
      Serial.println("Reception appel Tel");
      mySerial.println("ATA");
      Reception=0;
    }
     //Emission appel Tel
   if(Reception==101) //lettre e
    {
      Serial.println("Emission appel Tel");
      delay(2000);
  mySerial.println("ATD+3360124xxxx;"); // xxxxxxxxx est le numéro a appeler.  
         
  // NB: Une boucle while serait plus appropriée que la section de code ci-dessous.
  //     Je vous propose d'appeler la fonction suivante: 
  //     relayResponse( mySerial ) 
  if(mySerial.available()) 
  {
        char c = mySerial.read();
        Serial.print( c );
      }  
      
      delay(10000); 
      delay(10000); 
    
      mySerial.println("ATH"); // Fin d'appel.
      if(mySerial.available()) // Voir commentaire précédent.
      {
        char c = mySerial.read();
        Serial.print( c );
      }
      Reception=0;  
    }

    // Envoie SMS
    if(Reception==115) //lettre s
    {
      Serial.println("Envoie SMS");
      mySerial.print("\r");   // Envoyer un retour à la ligne <CR>
      delay(1000);                    // Attendre une seconde que le modem retourne "OK"
      mySerial.print("AT+CMGF=1\r");  // Envoyer un SMS en mode texte
      delay(1000);
     
      //mySerial.print("AT+CSCA=\"+919032055002\"\r");// Configurer le centre de message SMS,  
      //delay(1000);                                  // Retirer les commentaire seulement si nécessaire et
                                                      // remplacer le No avec celui obtenu auprès de votre
                                                      // fournisseur de service mobile.
                                                      //Note: pour inclure un " dans une chaine de caractère
                                                      //  il faut utiliser la notation \"
     
      mySerial.print("AT+CMGS=\"+3360124xxxx\"\r");   // Commencer un SMS à envoyer au numéro +91....
                                                      // l'encodage du texte suivra plus bas.
                                                      // Remplacer le No avec celui de votre destinataire.
      delay(1000);
      mySerial.print("Bienvenu chez MCHobby!\r");     // Le texte du message
      delay(1000);
      mySerial.write(26);  // Equivalent du Ctrl+Z (fin de texte du SMS)
                           // Note: ici il faut utiliser l'instruction write pour écrire un byte. 
      Reception=0;
    }
     
}

