/*
 Arduino ile Sunucu üzerinden Kontrol (SunucuKomutlaKontrol)
 
 Gelen komutlarla 2 adet dijital çıkış kontrol ediliyor.
 Komutlar: led1yak,led1sondur,led2yak,led2sondur
 
 Ethernet eklentisi kullanılıyor ( 10, 11, 12, 13 )
 
 */

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 6);



// 23 nolu portu kullanıyoruz (telnet portu)
EthernetServer server(23);
boolean istemciBagli = false; // Bir istemcinin bağla / bağlı değil
String gelenVeri = "";
void setup() {
  // Ethernet bağlantısını başlatıyoruz
  Ethernet.begin(mac, ip);
  // Sunucuyu istemci bağlantısını beklemek üzere başlatıyoruz
  server.begin();
  // Seri haberleşmeyi başlatıyoruz
  Serial.begin(9600);
  while (!Serial) {
    ; // Arduino Leonardo için
  }

  Serial.print("Sunucu IP Adresi:");
  Serial.println(Ethernet.localIP());
  pinMode(13,OUTPUT);
}

void loop() {
  // Bir isteminin bağlanmasını bekliyoruz.

  EthernetClient client = server.available();


  /*
    Sunucudan ilk veri geldiğinde tamponu temizliyor ve 
   karşılama mesajı gönderiyoruz 
   */
  if (client) {
    if (!istemciBagli) {
      // İstemciden gelip okunmamış verileri temizliyoruz:
      client.flush();    
      Serial.println("Bir istemci baglandi!");
      client.println("HOSGELDINIZ!"); 
      istemciBagli = true;
    } 

    if (client.available() > 0) {
      char gelenKarakter = client.read();
      Serial.println(client.available());


      switch(gelenKarakter)
      {
      case '\n':
        if(KomutIsle(gelenVeri))
        {
          client.println("OK");
        }
        else
        {
          client.println("HATA");
        }
        gelenVeri = "";
        break;

      case '\r':
        break;

      default:
        gelenVeri += gelenKarakter;
        Serial.println(gelenVeri);

        break;
      }
    }
  }
}
/* 
 Gelen komutları kontrol eder ve doğru bir komutsa 
 komutu işletir  ve true döndürür. Komutlar
 hatalı ise bir işlem yapmadan false değeri döndürür
 */
boolean KomutIsle(String gelenKomut)
{

  Serial.print("Gelen Komut:");
  Serial.println(gelenKomut);
  if (gelenKomut.equalsIgnoreCase("LED1YAK"))
  {
    digitalWrite(13,HIGH);
    Serial.println("LED1YANDI");
  }
  else if(gelenKomut.equalsIgnoreCase("LED1SONDUR"))
  {
    digitalWrite(13,LOW);
    Serial.println("LED1SONDU"); 
  }
  else if (gelenKomut.equalsIgnoreCase("LED2YAK"))
  {
    digitalWrite(12,HIGH);
    Serial.println("LED2YANDI");    
  }
  else if(gelenKomut.equalsIgnoreCase("LED2SONDUR"))
  {
    digitalWrite(12,LOW);
    Serial.println("LED2SONDU");
  }
  else
  {
    return false;
  }
  return true;
}


