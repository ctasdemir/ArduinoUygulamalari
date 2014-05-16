/*
  SD Kart İşlemleri
  Dosya oluşturma Örneği
  
  
  Arduino Kitabı 
  Coşkun Taşdemir
  Dikeyeksen Yayınları
  http://www.dikeyeksen.com
  
  	

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
String dosyaAdi;
int i;
File dir;
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
  dosya = SD.open("ornek.txt",FILE_WRITE); 
  
  if(dosya) // dosya oluşturma başarılı ise
  {
    Serial.print("Dosya acma BASARILI");
    dosya.write('A'); // Dosya içerisinde tek karakter yazdırıyoruz
    dosya.write('-'); // Dosya içerisinde tek karakter yazdırıyoruz
    dosya.println("Dosya icine veri yaziyoruz");
    dosya.close(); //Verilen dosyaya kaydedilmesi için kapatıyoruz    
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


void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}



