/*
  Statik IP Adresi alma 
  Ethernet fonksiyonları ile IP adresi statik olarak
  belirtiliyor.

  Ethernet Eklentisi Kullanılıyor (10, 11, 12, 13)
 
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

/*
IPAddress ip(192,168,1, 177);
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 255, 0);
*/

byte ip[] = {192,168,1,12};
byte gateway[] = {192,168,1,1};
byte subnet[] = {255,255,255,0};

EthernetClient client;

void setup() {
  IPAddress ipaddr;
  Serial.begin(9600);
    // Bu kontrol Arduino Leonardo için gerekli
   while (!Serial) {
    ; 
  }

Ethernet.begin(mac,ip,gateway,subnet);

/*

  // Belirlenen MAC adresi ile ethernet bağlantısını başlatıyoruz
  if (Ethernet.begin(mac,ip,gateway,subnet)) {
    Serial.println("Ethernet baglanti hatasi!");
    while(1);
  }
*/
  Serial.print("IP Adresi: ");
  
  ipaddr = Ethernet.localIP();
  
  for (byte i = 0; i < 3; i++) {
      Serial.print(ipaddr[i]);
      Serial.print(".");
  }
  Serial.println(ipaddr[3]);
}

void loop() {

}


