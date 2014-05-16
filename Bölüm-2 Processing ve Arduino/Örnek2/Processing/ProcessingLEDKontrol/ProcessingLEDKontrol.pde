/*
   Arduino Uygulamaları Kitabı
   Processing ve Arduino ile Kontrol Örneği - 2
*/

// Seri Haberleşme kütüphanesini kullanıyoruz
import processing.serial.*;

// Köşe koordinatları
float x = 100; 
float y = 50;
float w = 150;
float h = 80;

Serial seriPort;
boolean button = false;

void setup(){
 size(350,200);
 background(255);
 stroke(0);
 noFill();
 seriPort = new Serial(this,"COM40",9600); // Seri haberleşmeyi açıyoruz (9600 baud) 
}



void draw() {
  if (button) {
    fill(255);
    stroke(0);
    
  } else {
    fill(0);
    stroke(255);

  }
  /* sol üst köşesi (x,y) noktasında olan ve uzun kenarı w, 
    kısa kendarı h genişliğinde bir dikdörtgen çizdiriyoruz */
  rect(x,y,w,h); 
  fill(0x123456);  
}

/*
Fare butonuna basıldığında bu fonksiyon çağırılıyor.
Eğer butona basılan koordinat butonun köşe koordinatları
içerisinde ise buton durumunu değiştiriyoruz.

MouseX butona basılan koordinatın X bileşeni
MouseY butona basılan koordinatın Y bileşeni
*/
  
void mousePressed() {
  if (mouseX > x && mouseX < x+w && mouseY > y && mouseY < y+h) {
    if(button)
    {
      seriPort.write('H');
    }
    else
    {
      seriPort.write('L');
    }    
    button = !button; // buton değişkenini tersine çevir    
  }  
}


