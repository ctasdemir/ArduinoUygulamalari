/* 
 Processing ile Android İşletim Sistemi Üzerinde
 Bluetooth protokolü kullanımı Örneği - 1
 
 Processing üzerinden gelen verilerle
 Arduino 8,9,10,11 nolu pinlere bağlı
 4 adet LED Kontrol ediliyor.
 A,C,E,G karakterleri geldiğinde LED'ler yakılıyor
 B,D,F,H karakterleri geldiğinde ise LED'ler söndürülüyor
 
 */

// LED bağlatı pinleri
int ledler[] = {
  8,9,10,11};
char gelenVeri;
void setup()
{
  pinMode(ledler[0],OUTPUT);
  pinMode(ledler[1],OUTPUT);
  pinMode(ledler[2],OUTPUT);
  pinMode(ledler[3],OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  while(Serial.available()>0)
  {
    gelenVeri = Serial.read();
    switch(gelenVeri)
    {
    case 'A':
      digitalWrite(ledler[0],HIGH);
      break;
    case 'B':
      digitalWrite(ledler[0],LOW);
      break;
    case 'C':
      digitalWrite(ledler[1],HIGH);
      break;
    case 'D':
      digitalWrite(ledler[1],LOW);
      break;
    case 'E':
      digitalWrite(ledler[2],HIGH);
      break;
    case 'F':
      digitalWrite(ledler[2],LOW);
      break;
    case 'G':
      digitalWrite(ledler[3],HIGH);
      break;
    case 'H':
      digitalWrite(ledler[3],LOW);
    }
  }
}


