/* 
   SD kart ve DS1307 Gerçek Zamanlı Saat kullanılarak
   zaman bilgisiyle birlikte veri kaydetme örneği
   
   Örnek olarak kullanılan LM35 sensörüyle sıcaklık bilgisi
   elde edilip tarih ve saat ile birlikte SD-kart içerisindeki
   dosyaya kaydediliyor.
   
   Zaman bilgisinin doğru gösterilebilmesi için ds1307 ayarlama
   örnek programı derlenerek bir kere yüklenip çalıştırılmalıdır.
 
   Ethernet Shield üzerindeki SD-Kart yuvası kullanılmıştır.
   Harici bir sd-kart eklentisi kullanılırsa bağlantılar
   aşağıdaki şekilde olmalıdır:

 ** SD Kart Bağlantıları
 ** MOSI - pin 11 (Arduino Uno/Duemilanove/Diecimila)
 ** MISO - pin 12 (Arduino Uno/Duemilanove/Diecimila)
 ** CLK -  pin 13  (Arduino Uno/Duemilanove/Diecimila)
 ** CS -   Kullanılan SD kart bağlantısına göre değişebilir. Bu örnekte
 4. pini kullanıyoruz
 
 Arduino Kitabı 
 Coşkun Taşdemir
 Dikeyeksen Yayınları
 http://www.dikeyeksen.com
*/

#include <Wire.h> // I2C (Two wire) haberleşme
#include <SD.h>   // SD kart kütüphanesi
#include "RTClib.h" // DS1307 RTC kütüphanesi


RTC_DS1307 RTC;
int sicaklikPin = A0; // LM35'in bağlanacağı pin
File dosya; // kayıt edilecek dosyaya ait değişken

void setup () {
    Serial.begin(57600); // seri haberleşme
    Wire.begin(); // I2C haberleşmesi
    RTC.begin();  // RTC 
    
  Serial.print("SD card Baslatiliyor!");
  // SD kütüphanesinin çalışması içi SPI SS pininin çıkış olarak ayarlanması gerekiyor
  // Bu Arduino UNO için 10, Mega içinse 53
  pinMode(10, INPUT);

  /* Ethernet shield üzerinde SD kart CS pinini 4 nolu pine bağlı
     Harici bir sd-kart eklentisi kullanıyorsanız ilgili pin nosunu
     kullanmalısınız
   */
  
  if (!SD.begin(4)) {
    Serial.println("SD Kart Hatasi!");
    hataDurumuOlustu();
  }
  
  Serial.println("SD Kart baslatma basarili");
  
  /* Yazmak üzere ornek.txt adına bir dosya oluşturuyoruz */
  dosya = SD.open("veri.txt",FILE_WRITE); 
  
  if(dosya) // dosya oluşturma başarılı ise
  {
    Serial.println("Dosya acma BASARILI");
  }
  else // dosya açma başarısız
  {
    Serial.println("Dosya acma BASARISIZ");
    hataDurumuOlustu();
  }  
}

void loop () {
  /* 
   Dosyaya verilerin kaydedilmesini sağlamak için
   her seferinde dosyayı açıp işlem sonunda kapatıyoruz
  */
   dosya = SD.open("veri.txt",FILE_WRITE); 
  
   DateTime zaman = RTC.now();   
   Serial.print("SICAKLIK:");
   Serial.println(SicaklikOlc());
   dosya.print("SICAKLIK:");
   dosya.println(SicaklikOlc());
   dosya.print(zaman.year(), DEC);
   dosya.print('/');
   dosya.print(zaman.month(), DEC);
   dosya.print('/');
   dosya.print(zaman.day(), DEC);
   dosya.print(' ');
   dosya.print(zaman.hour(), DEC);
   dosya.print(':');
   dosya.print(zaman.minute(), DEC);
   dosya.print(':');
   dosya.print(zaman.second(), DEC);
   dosya.println();
   dosya.close(); //Verilen dosyaya kaydedilmesi için kapatıyoruz        
   delay(1000);
}

/* 
   LM35 sensörü üzerinden sıcaklık değeri hesaplanıyor 
   LM35 sensörü santigrat başına 10 mV üretiyor
   Fonksiyon sıcaklık değerini döndürüyor.
*/
int SicaklikOlc()
{
  float gerilim;
 int sicaklik;
  gerilim = analogRead(sicaklikPin);              // Sensörden gelen değeri oku
  gerilim = (gerilim / 1023) * 5000; // mV cinsinden gerilimi buluyoruz
  Serial.println(gerilim);
  sicaklik = gerilim / 10;// Gerilim değerini sıcaklığa çeviriyoruz
  return sicaklik;  
}

void hataDurumuOlustu()
{
  // Hata oluştuğunda programı olduğu yerde kilitliyoruz
  while(1);
}
