/*
  Arduino - İnternet Uygulamaları - Örnek 3
  Web İstemci Örneği (Internet örnekleri - 3)
 Google arama motoruna bağlanarak "Arduino" kelimesi
 aratılıyor.
  * Ethernet Eklentisi kullanılıyor(pinler 10, 11, 12, 13)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

// MAC adresi
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// DNS kullanmak istemediğimizde doğrudan Google'ın IP Adresini kullanabiliriz
//IPAddress server(74,125,232,128);  // Google'ın IP adresi 
char server[] = "www.google.com";    // Google'ın web adresi

// Statik IP adresimiz. Kendi ağınıza göre değiştirebilirsiniz.
IPAddress ip(192,168,1,12); 
EthernetClient client;

void setup() {  
  Serial.begin(9600);
   while (!Serial) {
    ; // Arduino Leonardo için
  }

  // Ethernet Bağlantısını başlatıyoruz
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Otomatik IP adresi alma basarisiz!");
    // Kendi IP adresimizle bağlantıyı başlatıyoruz
    Ethernet.begin(mac, ip);
  }
  // Başlangıç için ethernet eklentisine biraz zaman tanıyoruz
  delay(1000);
  Serial.println("Baglaniyor...");

  // Bağlantı sağlandıktan sonra gelen verileri seri haberleşme
  // üzerinden göndereceğiz. Sunucu adresine 80 nolu porttan bağlanıp
  // HTML GET isteği gönderiyoruz
  if (client.connect(server, 80)) {
    Serial.println("connected"); 
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // Bağlantı hatası oluştu
    Serial.println("Baglanti Saglanamadi!");
  }
}

void loop()
{
  // Sunucudan gelen verileri seri haberleşmeden gönderiyoruz.
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // Bağlantı kesildiyse istemci bağlantısını da durduruyoruz
  if (!client.connected()) {
    Serial.println();
    Serial.println("Baglanti Kesiliyor");
    client.stop();
    //Programı burada kilitliyoruz.
    while(true);
  }
}

