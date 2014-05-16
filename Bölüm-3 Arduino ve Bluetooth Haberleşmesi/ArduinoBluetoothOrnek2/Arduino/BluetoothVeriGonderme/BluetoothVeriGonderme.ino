/* 
 Arduino ve Bluetooth Örneği - 2
 
 Arduino'nun Analog girişlerinden okunan değerler
 200 ms'de bir Bluetooth modülüne gönderiliyor.
 
 HC-06 Bluetooth modülü kullanılmıştır.
 */


void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  VeriPaketiGonder();
  delay(200); 
}

/* Analog Girişlerden okunan veriler
2 baytlık integer değerleri olduğundan 
baytlara ayrılarak gönderiliyor.
Değerlerden önce 'A' ve 'B' karakterlerinin
ASCI Değerleri gönderiliyor (senkronizasyon baytları)
*/
void VeriPaketiGonder()
{
  byte gonderilecekVeri[12];
  unsigned int analogGiris = 0;
  
  analogGiris = analogRead(A0);

  gonderilecekVeri[0] = analogGiris; // Düşük değerlikli bayt (LSB)
  gonderilecekVeri[1] = analogGiris>>8; // Yüksek değerlikli bayt (MSB)
  
  analogGiris = analogRead(A1);

  gonderilecekVeri[2] = analogGiris;
  gonderilecekVeri[3] = analogGiris>>8;
  
  analogGiris = analogRead(A2);

  gonderilecekVeri[4] = analogGiris;
  gonderilecekVeri[5] = analogGiris>>8;
  
  analogGiris = analogRead(A3);

  gonderilecekVeri[6] = analogGiris;
  gonderilecekVeri[7] = analogGiris>>8;
  
  analogGiris = analogRead(A4);
  
  gonderilecekVeri[8] = analogGiris;
  gonderilecekVeri[9] = analogGiris>>8;
  
  analogGiris = analogRead(A5);

  gonderilecekVeri[10] = analogGiris;
  gonderilecekVeri[11] = analogGiris>>8;
  
  Serial.write('A'); // 1. Başlık Baytı
  Serial.write('B'); // 2. Başlık Baytı
  Serial.write(gonderilecekVeri,12);
}

