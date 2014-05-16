 /*
  Arduino – Bluetooth - Processing 
  Yazılımsal Seriport kullanımı 
  
  Yazılımsal seri port için kullanılan pinler

  Pin 11 - RX
  Pin 12 - TX  
  */
#include <SoftwareSerial.h>
SoftwareSerial softSerial(10, 11); // RX, TX

void setup()  
{
  // 1. seriportu başlatıyoru
  Serial.begin(57600);
  while (!Serial) {
    ; // Seriportun bağlanmasını bekliyoruz (Leonardo için gerekli)
  }
  // Yazılımsal seriportu başlatıyoruz 
  softSerial.begin(9600);
  
}

void loop() 
{
  /* Arduino iki portu ile köprü vazifesi görüyor
     Portlardan gelen veriler diğerine iletiliyor
  */
  if (softSerial.available()) {
    Serial.write(softSerial.read());
  }
  if (Serial.available())
    softSerial.write(Serial.read());
}

