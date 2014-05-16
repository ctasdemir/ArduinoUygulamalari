/* 
 * Processing Örneği - 4
 * Processing ver ControlP5 Kütüphanesi ile
 * RGB LED Kontrolü   
 */

// LED bağlantı pinleri
const int kirmiziPin = 11;  // kırmızı
const int yesilPin = 10; // yeşil
const int maviPin = 9; // mavi

int kirmizi=0, yesil=0, mavi=0; // renk değerleri
int durum = 1; // gelen verileri işlemede kullanılacak
byte gelen = 0;

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  while(Serial.available()>0)
  {
    /* 
     Gelen veriler işleniyor
     R karakteri geldikten sonra sırasıyla
     kirmizi,yeşil ve mavi baytları okunuyor.
     */
    gelen = Serial.read();
    switch(durum)
    {
    case 1:
      if(gelen == 'R'){
        durum = 2;
      }
      break;

    case 2:
      kirmizi = gelen;
      durum = 3;      
      break;

    case 3:
      yesil = gelen;
      durum = 4;
      break;

    case 4:
      mavi = gelen;
      durum = 1;
      break;
    }
  }

  // Ortak anot için
  analogWrite(kirmiziPin, 255 - kirmizi);
  analogWrite(yesilPin, 255 - yesil);
  analogWrite(maviPin, 255 - mavi);

  // Ortak katot için
  /* 
   analogWrite(rpin, r);
   analogWrite(gpin, g);
   analogWrite(bpin, b);
   */
  delay(20);
}

