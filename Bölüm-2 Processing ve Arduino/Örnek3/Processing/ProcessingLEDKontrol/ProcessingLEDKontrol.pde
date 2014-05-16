/*
  Processing Örneği - 3
 Processing ile Seriport üzerinden 
 LED Kontrolü 
 
 4 toggle nesnesi ile Arduino'ya
 bağlı olan 4 adet LED kontrol ediliyor
 
 ControlP5 kütüphanesindeki Toggle kontrolleri
 kullanılıyor
 */


import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
Serial seriPort;

void setup() {
  size(420, 100);

  cp5 = new ControlP5(this); // Kontrol nesnesini oluştur
  seriPort = new Serial(this, "COM7", 9600); //seri port nesnesini oluştur

  // Toggle Nesnelerini oluşturuyoruz 
  cp5.addToggle("led1") // led1 ismini veriyoruz
    .setPosition(40, 40) // nesnenin konumu
      .setSize(50, 20) // nesnenin boyutu (en,boy)
        .setValue(false) // başlangıç durumu (false)
          .setMode(ControlP5.SWITCH) // anahtar görünümü
            ;

  cp5.addToggle("led2")
    .setPosition(140, 40)
      .setSize(50, 20)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led3")
    .setPosition(240, 40)
      .setSize(50, 20)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led4")
    .setPosition(340, 40)
      .setSize(50, 20)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led5")
    .setPosition(440, 40)
      .setSize(50, 20)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;
  background(0); //arkaplan siyah
}

void draw() {
}
/* led1 toggle nesnesin tıklandığında çağırılacak olan fonksiyon
 gelen bayrağın durumuna göre (true / false) ilgili veri
 seri haberleşme üzerinden gönderiliyor
 */
void led1(boolean bayrak) {
  if (bayrak==true) {
    seriPort.write('A');
    println("LED-1 yakıldı");
  } 
  else {
    seriPort.write('B');
    println("LED-1 söndürüldü");
  }
}

void led2(boolean bayrak) {
  if (bayrak==true) {
    seriPort.write('C');
    println("LED-2 yakıldı");
  } 
  else {
    seriPort.write('D');
    println("LED-2 söndürüldü");
  }
}

void led3(boolean bayrak) {
  if (bayrak==true) {
    seriPort.write('E');
    println("LED-3 yakıldı");
  } 
  else {
    seriPort.write('F');
    println("LED-3 söndürüldü");
  }
}

void led4(boolean bayrak) {
  if (bayrak==true) {
    seriPort.write('G');
    println("LED-4 yakıldı");
  } 
  else {
    seriPort.write('H');
    println("LED-4 söndürüldü");
  }
}

