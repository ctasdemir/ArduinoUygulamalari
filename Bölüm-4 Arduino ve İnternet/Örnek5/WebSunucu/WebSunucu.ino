/*
  Arduino ile Basit bir Web Sunucusu 
  Web sunucusuna gönderilen istekler ile 2 adet LED kontrol ediliyor.
  
  8 ve 9 nolu dijital pinlere 2 Adet LED Bağlı (470 Ohm'luk dirençler ile)
    
  Arduino Ethernet Eklentisi ve WebDuino kütüphanesi kullanılmıştır.
  WebDuino Kütüphanesi: https://github.com/sirleech/Webduino
*/

#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"

#define LED1 8
#define LED2 9
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
boolean LED1Durum = false;
boolean LED2Durum = false;

static uint8_t ip[] = { 192, 168, 1, 6 };

/* Bir webserver nesnesi oluşturuyoruz.
Bütün gelen dosya istekleri kök dizin olarak görülmesi için
önek bölümünü boş bırakıyoruz. Bütün istekler
http://webserver-adresi/dosya-adi şeklinde gelecek.  */

#define ONEK ""
WebServer webserver(ONEK, 80);

/* Ana sayfa isteği geldiğinde çağırılacak fonksiyon */
void anaSayfa(WebServer &server, WebServer::ConnectionType baglantiTipi, char *, bool)
{

  server.httpSuccess();

  if (baglantiTipi != WebServer::HEAD)
  {
    LEDdurumlariniGoster(server);
  }
}

void led1AcKomut(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
    digitalWrite(LED1,HIGH);
    LEDdurumlariniGoster(server);
  }
}

void led1KapatKomut(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
    digitalWrite(LED1,LOW);   
    LEDdurumlariniGoster(server);
  }
}

void led2AcKomut(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
     digitalWrite(LED2,HIGH);    
     LEDdurumlariniGoster(server);
  }
}

void led2KapatKomut(WebServer &server, WebServer::ConnectionType type, char * , bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
    digitalWrite(LED2,LOW);
    LEDdurumlariniGoster(server);
  }
}

void LEDdurumlariniGoster(WebServer &server)
{
   /* 
   P() makrosu ile string'leri RAM yerine program
   belleğine kaydedebiliyoruz. Server'a gönderirken de
   printP() fonksiyonunu kullanıyoruz
   */
    P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Arduino Web Sunucusu</title>"
    "</head>"
    "<body>";
    
    server.printP(htmlHead);
    /*
    LED'lerin durumlarını yazdırıyoruz ve açma / kapama
    işlemleri için linkleri yazdırıyoruz
    */
    server.print("<h1>LED1:</h1>");
    if(digitalRead(LED1))
    {
      server.print("AÇIK");
      server.println("<a href=\"led1Kapat\"> KAPAT</a>");
    }
    else
    {
      server.print("KAPALI");
      server.println("<a href=\"led1Ac\"> AÇ</a>");
    }
    server.print("<h1>LED2:</h1>");
    if(digitalRead(LED2))
    {
      server.println("AÇIK");
      server.println("<a href=\"led2Kapat\"> KAPAT</a>");
    }
    else
    {
      server.println("KAPALI");
      server.println("<a href=\"led2Ac\"> AÇ</a>");
    }
}

void setup()
{
  // LED Pinlerini çıkış olarak ayarlıyoruz
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);

  /* IP ve MAC adresi ile ethernet bağlantısını başlatıyoruz */
  Ethernet.begin(mac, ip);

  /* Web sunucuya gelen isteklere göre çağırılacak fonksiyonları listeye ekliyoruz */
  
  /* Varsayılan istek */
  webserver.setDefaultCommand(&anaSayfa);
  /* ana sayfa isteği geldiğinde */
  webserver.addCommand("index.html", &anaSayfa);
  /* Diğer istekler */
  webserver.addCommand("led1Ac", &led1AcKomut);
  webserver.addCommand("led1Kapat", &led1KapatKomut);
  webserver.addCommand("led2Ac", &led2AcKomut);
  webserver.addCommand("led2Kapat", &led2KapatKomut);

  /* Sunucuyu başlatıyoruz */
  webserver.begin();
}

void loop()
{
  char webserver_tampon[64];
  int boyut = 64;

  /* Sürekli olarak gelen istekleri işliyoruz */
  webserver.processConnection(webserver_tampon, &boyut);
}
