/*
  Arduino - İnternet Uygulamaları - Örnek 7
  Arduino ile Xivly.com'a veri gönderilmesi Örneği
  
  DHT-11 Sensörü ile ölçülen nem ve sıcaklık değerleri
  Xivly.com'a gönderiliyor.
  Program boyutunu düşürmek için statik IP kullanabilirsiniz.
  
  Feed-id, API ID gibi değerleri kendi değerlerinizle
  değiştirmelisiniz.
  Donanım:
  Arduino UNO
  Arduino Ethernet Eklentisi
  DHT-11 Sensörü. DHT-11 Sensörü 2 nolu pine bağlı.
  
  Kütüphaneler:
  HttpClient 
  Xively 
  Adafruit DHT-11
  

*/

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>
#include "DHT.h"

#define DHTPIN 2     // DHT-11 data pini Arduino'nun 2 nolu pinine bağlı

#define DHTTYPE DHT11   // DHT 11 kullanıldığında bu tanım yapılmalı

DHT dht(DHTPIN, DHTTYPE);

// API KEY değerini bu değişkene atamalısınız
char xivelyKey[] = "API_KEY_DEGERI";
// FEED ID değeri
#define FEED_ID 123456 

// MAC Adresi
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


// Veri gönderdiğimiz sensor ID değeri
char sensorId1[] = "Sensor-Sicaklik";
char sensorId2[] = "Sensor-Nem";

// Xively veri gruplarını tanımlıyoruz.
XivelyDatastream xivelyVeriler[] = {
  XivelyDatastream(sensorId1, strlen(sensorId1), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId2,strlen(sensorId2),DATASTREAM_FLOAT)
};
// Birinci parametre feed-id değeri
XivelyFeed feed(791534998, xivelyVeriler, 2 /* veri grubu sayısı*/);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  Serial.println("Veriler Xively'e Gonderiliyor");
  Serial.println();
  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("IP Adresi alinamadı. Tekrar deneniyor");
    delay(5000);
  }
}

void loop() {
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();
  xivelyVeriler[0].setFloat(sicaklik);
  xivelyVeriler[1].setFloat(nem);
  Serial.print("Nem:% ");
  Serial.println(nem);
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik);
  
  int donusDegeri = xivelyclient.put(feed, xivelyKey);
  // Xivly'e giden HTML isteğinin sonuç değeri (200 - OK)
  Serial.print("Xivly donus degeri ");
  Serial.println(donusDegeri);
  delay(5000);
}
