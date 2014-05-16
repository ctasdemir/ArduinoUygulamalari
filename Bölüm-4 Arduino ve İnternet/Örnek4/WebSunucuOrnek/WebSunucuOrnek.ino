/*
 Arduino - İnternet Uygulamaları - Örnek 4
  Web Server Örneği
 
Arduino ile basit bir web sunucu örneği
Analog girişlerden okunan değerler gönderiliyor.

(Arduino >> Examples >>Ethernet >> Webserver Örneği)
 
 Circuit:
 * Ethernet eklentisi pinleri 10, 11, 12, 13
 * A0 - A5 analog pinlerine 0 - 5V veren sensörler bağlanılabilir
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  // IP adresi kendi ağınıza göre değiştirebilirsiniz
IPAddress ip(192,168,1,177);

// 80 nolu portu dinleyen bir server oluşturuyoruz.
EthernetServer server(80);

void setup() {
 // Seri haberleşme
  Serial.begin(9600);
   while (!Serial) {
    ; // Arduino Leonardo için
  }


  // Ethernet bağlantısını başlatıyoruz.
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server IP Adresi: ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // İstemcinin bağlanmasını bekliyoruz
  EthernetClient client = server.available();
  if (client) {
    Serial.println("istemci bağlandı");
    // HTTP istekleri boş bir satır ile sonlanır (\r\n)
    boolean suAnkiSatirBos = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        /* Eğer boş bir satır sonrası tekrar boş satıra geldi isek
           HTTP isteği sonlanmış demektir.
         */
        if (c == '\n' && suAnkiSatirBos) {
          // HTTTP cevabı gönderiliyor
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // Cevap verildikten sonra bağlantı kapatılacak
	  client.println("Refresh: 5");  // Sayfa 5 saniyede bir güncellenecek
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // analog kanallar yazdırılıyor.
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("Analog Giris ");
            client.print(analogChannel);
            client.print(" degeri ");
            client.print(sensorReading);
            client.println("<br />");       
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') { // newline karakteri
          // Yeni bir satıra geçiliyor
          suAnkiSatirBos = true;
        } 
        else if (c != '\r') { // return karakteri
          // Şu anki satırda yeni bir karakter alındı
          suAnkiSatirBos = false;
        }
      }
    }
    delay(1);
    // Bağlantıyı kapatıyoruz
    client.stop();
    Serial.println("istemci baglantisi kesildi");
  }
}

