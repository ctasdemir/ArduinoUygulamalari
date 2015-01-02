/* 
   DS1307 Gerçek Zamanlı Saat Kullanımı
   Saat ve tarih ayarı yapılarak
   güncel zaman ve tarih bilgisi saniyede 1 kere
   Seri haberleşme üzerinden gönderiliyor
   
   Güncel zaman bilgisi derleme
   esnasında kaydedildiğinden bu program karta 
   yüklenip bir seferliğine çalıştırılmalıdır. 
  
  Arduino Kitabı 
  Coşkun Taşdemir
  Dikeyeksen Yayınları
  http://www.dikeyeksen.com
*/



#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

void setup () {
    Serial.begin(57600);
    Wire.begin(); // I2C haberleşmesi
    RTC.begin();  // RTC 
    
    /* RTC'ye yükleme anındaki tarih ve saat bilgisi
    gönderiliyor */
    RTC.adjust(DateTime(__DATE__, __TIME__));    
    Serial.println(__TIME__);

}

void loop () {
    DateTime zaman = RTC.now();
    
    Serial.print(zaman.year(), DEC);
    Serial.print('/');
    Serial.print(zaman.month(), DEC);
    Serial.print('/');
    Serial.print(zaman.day(), DEC);
    Serial.print(' ');
    Serial.print(zaman.hour(), DEC);
    Serial.print(':');
    Serial.print(zaman.minute(), DEC);
    Serial.print(':');
    Serial.print(zaman.second(), DEC);
    Serial.println();
    delay(1000);
}
