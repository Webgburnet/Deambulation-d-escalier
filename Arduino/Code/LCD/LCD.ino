#include <rgb_lcd.h>

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Début setup");

  Serial.println("LPO Henri Brisson");
  Serial.println("18100 Vierzon");
  
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0, 0);
  lcd.print("Henri Brisson");
  lcd.setCursor(0, 1);
  lcd.print("18100 Vierzon");
  
  delay(1000);
  
  Serial.println("Fin setup");
}

void loop() {
	
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Etat:Descente");
    lcd.setCursor(0, 1);
    lcd.print("BPM=");
    lcd.setCursor(4, 1);
    lcd.print("var");
    lcd.setCursor(11, 1);
    lcd.print("bpm");
 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Etat:Montée");
    lcd.setCursor(0, 1);
    lcd.print("BPM=");
    lcd.setCursor(4, 1);
    lcd.print("var");
    lcd.setCursor(11, 1);
    lcd.print("bpm");  
}

