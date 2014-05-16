/**
 * Processing Örneği - 4
 * Processing ver ControlP5 Kütüphanesi ile
 * RGB LED Kontrolü 
 */

import controlP5.*;
import processing.serial.*;

ControlP5 controlP5;
Serial seriPort; 
ColorPicker cp; // Renj seçim nesnesi

int kirmiziDeger;
int yesilDeger;
int maviDeger;

void setup() {
  size(400, 100);
  controlP5 = new ControlP5(this);
  cp = controlP5.addColorPicker("renkSecici", 0, 0, 255, 20);  
  seriPort = new Serial(this, "COM7", 9600);
}

void draw() {
  background(cp.getColorValue()); // Arka plan rengini değiştir
  /* 
   Renk seçici nesnesindek rengin kırmızı,yeşil ve  
   mavi bileşenlerini ayırıp ilgili değişkenlere atıyoruz
   */
  kirmiziDeger = int(red(cp.getColorValue()));
  yesilDeger = int(green(cp.getColorValue()));
  maviDeger = int(blue(cp.getColorValue()));  
  delay(50);
}

/* Renk seçideki değerler değiştiğinde
 otomatik olarak çağırılan fonksiyon ile
 renk değerlerini konsola yazdırıyoruz
 */
void renkSecici(int renk) {
  println("KIRMIZI "+kirmiziDeger + " YESIL "+yesilDeger + " MAVI "+maviDeger);
  RenkGonder();
}

/* Renk değerleri,
 önce R karakter sonrasında kırmızı,yeşil,mavi
 sırasıyla gönderiliyor
 */
void RenkGonder()
{
  seriPort.write('R');
  seriPort.write(kirmiziDeger);
  seriPort.write(yesilDeger);
  seriPort.write(maviDeger);
}

