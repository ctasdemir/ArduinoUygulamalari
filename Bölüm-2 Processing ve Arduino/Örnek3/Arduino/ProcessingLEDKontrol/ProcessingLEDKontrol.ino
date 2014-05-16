/* 
 Processing Örneği - 3 
 Processing üzerinden gelen verilerle
 4 adet LED Kontrol ediliyor
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


