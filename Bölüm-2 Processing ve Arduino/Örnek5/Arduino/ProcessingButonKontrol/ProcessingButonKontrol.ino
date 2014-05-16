/* 
 Processing Örneği - 5
 Processing ve ControlP5 Kütüphanesi ile
 buton değerlerinin görüntülenmesi
 Arduino 8,9,10,11 nolu pinlere bağlı butonların
 durumları Processing'e yollanıyor 
 */

// LED bağlatı pinleri
int pinler[] = {8,9,10,11};
char gelenVeri;
byte pinDurumu;

void setup()
{
  pinMode(pinler[0],INPUT);
  pinMode(pinler[1],INPUT);
  pinMode(pinler[2],INPUT);
  pinMode(pinler[3],INPUT); 

  Serial.begin(9600);  
}

void loop()
{
  pinDurumu = (byte)(digitalRead(pinler[3]) << 3) ||
    (byte)(digitalRead(pinler[2]) << 2) ||
    (byte)(digitalRead(pinler[1]) << 1) ||
    (byte)(digitalRead(pinler[0]));
  Serial.write(pinDurumu);

  delay(100); 
}

