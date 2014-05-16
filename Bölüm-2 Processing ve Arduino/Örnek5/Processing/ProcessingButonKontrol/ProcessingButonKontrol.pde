/*
 Processing Örneği - 5
 Processing ile Seriport üzerinden buton 
 durumlarının okunması
 
 Arduino'ya bağlı 4 adet butonun durumları
 Processing Toggle nesneleri ile
 görüntüleniyor 
 */



import controlP5.*;
import processing.serial.*;

ControlP5 cp5;

int col = color(255);

boolean toggleValue = false;
Serial seriPort;
byte butonDurum;
int buton1Deger, buton2Deger, buton3Deger, buton4Deger;

void setup() {
  size(300, 120);
  smooth();
  seriPort = new Serial(this, "COM7", 9600);
  cp5 = new ControlP5(this);

  cp5.addToggle("buton1")
    .setPosition(40, 40)
      .setSize(50, 50)
        ;

  cp5.addToggle("buton2")
    .setPosition(100, 40)
      .setSize(50, 50)
        ;

  cp5.addToggle("buton3")
    .setPosition(160, 40)
      .setSize(50, 50)
        ;

  cp5.addToggle("buton4")
    .setPosition(220, 40)
      .setSize(50, 50)
        ;
}

void draw() {
  background(0); 
  if (seriPort.available()>0)
  {
    butonDurum =(byte)seriPort.read();
    buton1Deger = butonDurum&0x1;
    buton2Deger = (butonDurum>>1)&0x1;
    buton3Deger = (butonDurum>>2)&0x1;
    buton4Deger = (butonDurum>>3)&0x1;

    cp5.controller("buton1").setValue(buton1Deger); 
    cp5.controller("buton2").setValue(buton2Deger); 
    cp5.controller("buton3").setValue(buton3Deger); 
    cp5.controller("buton4").setValue(buton4Deger);
  }
}

