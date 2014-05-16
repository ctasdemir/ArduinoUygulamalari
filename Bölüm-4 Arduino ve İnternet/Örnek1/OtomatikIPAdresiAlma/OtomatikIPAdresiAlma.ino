/*
  Arduino - İnternet Uygulamaları - Örnek 1
  Otomatik IP Adresi alma (DHCP)
  Ethernet fonksiyonları ile otomatik IP Adrsi
  alınıyor. Bu durumda DHCP protokolü kullanıldığından
  program belleği kullanımı artacaktır.
 
  Ethernet Eklentisi Kullanılıyor (10, 11, 12, 13)
 
 */

#include <SPI.h> 
#include <Ethernet.h>

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

EthernetClient client;

void setup() {
  IPAddress ipaddr;
  Serial.begin(9600);
  // Bu kontrol Arduino Leonardo için gerekli
   while (!Serial) {
    ; 
  }

  // Belirlenen MAC adresi ile ethernet bağlantısını başlatıyoruz
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Ethernet baglanti hatasi!");
    while(1); // Programı burada kilitliyoruz
  }
  
  ipaddr = Ethernet.localIP();
  
  Serial.print("IP Adresi: ");
  Serial.println(ipaddr);
  
}

void loop() {

}


