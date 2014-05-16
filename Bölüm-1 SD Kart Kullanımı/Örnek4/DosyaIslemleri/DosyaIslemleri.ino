/*
 SD Kart İşlemleri Örneği - 4
 Dosya İşlemleri Örneği
 
 
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
char dosya_adi[] ="ornek.txt";
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
   menuGoster();

}

void loop()
{
  char giris;
  if(Serial.available()>0)
  {
    giris = Serial.read();

    switch(giris)
    {
    case 'y':
    case 'Y': // Yazma İşlemi
      dosyaKaydetme();
      menuGoster();
      break;
    case 'o':
    case 'O':
     dosyaOkuma();
     menuGoster();
     break;
   case 's':
   case 'S':
     dosyaSilme();
     menuGoster();
   break;
    }

}
}

void menuGoster()
{
 
  Serial.println("\nY - Yazma Islemi");
  Serial.println("S - Silme Islemi");
  Serial.println("O - Okuma Islemi"); 
}
void dosyaKaydetme()
{
   Serial.println("Girilen veriler dosyaya kaydedilecek");
   Serial.println("Kaydi bitirmek icin noktaya(.) basıp gonderin");

  char giris;
  /* Yazmak üzere ornek.txt adına bir dosya oluşturuyoruz */
  dosya = SD.open(dosya_adi,FILE_WRITE);  

  if(dosya) // dosya oluşturma başarılı ise
  {
    while(1)
    {         
      giris = Serial.read();
      if(giris !=-1)
      {
        if(giris == '.')
        {
          Serial.println("Dosya kaydedildi");
          break;
        }
        dosya.write(giris); // Dosya içerisinde tek karakter yazdırıyoruz
      }
    }
  }
  else //Dosya oluşturma başarısız
  {
    Serial.println("Dosya acma BASARISIZ!");
    return;
  }
  dosya.close();  

}

void dosyaOkuma()
{
     /* Okuma üzere ornek.txt adına bir dosya oluşturuyoruz */
      dosya = SD.open(dosya_adi,FILE_READ); 


      if(dosya) // dosya açma başarılı ise
      {
        Serial.println("\n ------Dosya icerigi------");
        while(dosya.available()>0)
        {
          Serial.write(dosya.read()); 
        }
        Serial.println("\n ------Dosya sonu------");
      }
      else
      {
        Serial.println("Dosya bulunamadı!");
      }
    }
    
void dosyaSilme()
{
  SD.remove(dosya_adi);
}



