/*
  SD Kart İşlemleri Örneği - 2
  Dosya Okuma Örneği

  SD kart kök dizinindeki ornek.txt
  Uzantılı dosyanın içeriği okunarak
  Serial Monitor’de görüntüleniyor
  
  
 ** SD Kart Bağlantıları
 ** MOSI - pin 11 (Arduino Uno/Duemilanove/Diecimila)
 ** MISO - pin 12 (Arduino Uno/Duemilanove/Diecimila)
 ** CLK -  pin 13  (Arduino Uno/Duemilanove/Diecimila)
 ** CS -   Kullanılan SD kart bağlantısına göre değişebilir. Bu örnekte
 4. pini kullanıyoruz
*/

// SD kart kütüphanesini kullanıyoruz 
#include <SD.h>

// Dosya nesnesi
File dosya; 
void setup()
{
  Serial.begin(9600);
  //Arduino Leonardo için seri portun aktif olmasını bekliyoruz
   while (!Serial) {
    ; 
  }
  Serial.print("SD card Baslatiliyor!");
  // SD kütüphanesinin çalışması içi SPI SS pininin çıkış olarak ayarlanması gerekiyor
  // Bu Arduino UNO için 10, Mega içinse 53
  pinMode(10, INPUT);

  // SD kart CS pinini 4 nolu dijital pine bağladık.
  if (!SD.begin(4)) {
    Serial.println("SD Kart Hatasi!");
    return;
  }
  
  Serial.println("SD Kart baslatma basarili");
  
  /* Yazmak üzere ornek.txt adına bir dosya oluşturuyoruz */
  dosya = SD.open("ornek.txt",FILE_READ); 
  
  if(dosya) // dosya oluşturma başarılı ise
  {
    Serial.print("Dosya acma BASARILI");
   while(dosya.available()>0)
   {
     Serial.write(dosya.read());
   }
  }
  else // dosya açma başarısız
  {
    Serial.print("Dosya acma BASARISIZ");
  }  
}

void loop()
{
  //Dosya işleminden başka bir işlem yapmıyoruz.
}


