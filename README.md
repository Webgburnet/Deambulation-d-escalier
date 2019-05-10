# Deambulation-d-escalier

## Logiciels
| Arduino | Fritzing |
| :-----: | :------: | :-----: | :---------: | :-------: |
| ![](/icone/Arduino.png) | ![](/icone/Fritzing.png) |

## Composants
| Arduino | DFRobot | SeeedStudio |
| :-----: | :------: | :-----: |
| ![](/icone/Arduino.png) | ![](/icone/DFRobot.png) | ![](/icone/Seeed_Studio.png) |

### Arduino
| Arduino Mega  |
| :-------------: |
| ![](/composants/Arduino%20Mega.jpg) |

### Shield
| Shield | Shield |
| :-------------: | :-------------: |
| Shield Grove base | Shield grove SD Card |
| ![](/composants/SeeedStudio/Shield_Grove_Base.png) | ![](/composants/SeeedStudio/Shield_Grove_SD_Card.jpg) |
| Shield GSM/GPRS |  |
| ![](/composants/DFRobot/Shield_SIM800C_GSMGPRS_V2.0.jpg) |  |
 
### SeeedStudio
| Battement de coeur | LCD | Relais | Cables |
| :-------------: | :-------------: | :-------------: | :-------------: |
| ![](/composants/SeeedStudio/Grove_Finger-clip_Heart_Rate_Sensor.jpg) | ![](/composants/SeeedStudio/Grove_LCD_RGB_Backlight.jpg) | ![](/composants/SeeedStudio/Grove_Relay.jpg) | ![](/composants/SeeedStudio/Grove_Cable.jpg) |


### Divers
| Divers | 
| :-------------: |
| 4 Relais | 
| ![](/composants/Divers/4_Relais.png) |

## Branchement
| Fritzing |
| :-------------: |
| ![](/icone/Fritzing.png) |

![](/fritzing/Untitled_Sketch.png)

### Shield
* Grove-Shield-Carte-SD
* Grove-Shield-base
* Shield-GPRS-GSM

### Analogique
* A0: Relais
* A1: Relais
* A2: Relais
* A3: Relais
* A4: NC
* A5: NC

### Digital
* D0 : RX rs232 non utilise
* D1 : TX rs232 non utilise
* D2 : 
* D3 : 
* D4 : CS Grove-Shield-Carte-SD
* D5 : Bouton/PIR
* D6 : Bouton/PIR
* D7 : Fin de course
* D8 : Fin de course
* D9 : Speaker
* D10 : NC
* D11 : MOSI Grove-Shield-Carte-SD
* D12 : MISO Grove-Shield-Carte-SD / Start/Reboot GPRS-Shield-V2
* D13 : CLK Grove-Shield-Carte-SD
* D14 : RX GPRS-Shield-V2
* D15 : TX GPRS-Shield-V2
* D20 : Heart
* D21 : Heart
* D46 : SPEAKER

### I2C
* SDA : LCD
* SCL : LCD

### Alimentation
* Vin : NC
* GND : NC
* 5V : NC
* 3.3V : NC
* Vref : NC

### Divers 
* Ioref : NC
* Reset : NC