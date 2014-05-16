/* 
 Processing Örneği - 2
 Processing ile Seriport üzerinden 
 LED Kontrolü 
 */

// LED bağlatı pinleri
const int led_pin = 13; //Arduino UNO üzerindeki LED

void setup()
{
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  if(Serial.available()>0)
  {
    if(Serial.read() == 'H')
    {
      digitalWrite(led_pin,HIGH);
    }
    else
    {
      digitalWrite(led_pin,LOW);
    }
  }
}

