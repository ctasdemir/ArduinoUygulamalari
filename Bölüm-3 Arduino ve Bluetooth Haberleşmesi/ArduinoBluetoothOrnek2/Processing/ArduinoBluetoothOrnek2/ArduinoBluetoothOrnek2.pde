/* 
 Processing ile Android İşletim Sistemi Üzerinde
 Bluetooth protokolü kullanımı Örneği - 2
 
 Kullanılan Processing Kütüphaneleri:
 - ControlP5
 - Ketai (Versiyon 9)
 
 Arduino'dan gönderilen veriler çözümlenerek alınan
 değerler Knob nesneleri ile gösteriliyor.
 
 (Processing 2.0.3 versiyonu kullanılmıştır)
 (baglantiIsmi değişkeni Bluetooth bağlantı ismine göre değiştirilmeldir)
 
 Butonların boyutlarını ve konumlarını
 cihazınızın ekran özelliklerine göre değiştirimeniz
 gerekebilir (setSize ve setPosition fonksiyonları)
 
 */

import controlP5.*;
import ketai.net.bluetooth.*;
import android.bluetooth.*;
import ketai.ui.*;

KetaiBluetooth bt; // Bluetooth nesnesi
ControlP5 cp5;     // ControlP5 nesnesi
String baglantiIsmi = "=AR-BT"; // Bağlanacağımız bluetooth modülün bağlantı ismi

Knob[] myKnobs = new Knob[6]; // 6 adet Knob nesnesi kullanacağız

/* Veri paketi çözme işlemleri ile ilgili değişkenler */
int paketDurumu = 0; // Paket çözme durumları
boolean veriGeldi = false; // Veri geldiğini gösteren bayrak değişken
int paketIndeks = 0;
byte[] veriler = new byte[12]; // Analog giriş verilerini tutan dizi
byte[] gelenVeri = new byte[50]; // Bluetooth'dan gelen verilerin kopyalanacağı geçici tampon

void setup() {
  size(displayWidth, displayHeight); // Cihazın ekran boyutlarında bir pencere oluştur
  orientation(PORTRAIT); // Ekranı Porte moduna al
  background(255); // Arkaplan Beyaz
  cp5 = new ControlP5(this); // Kontrol nesnesini oluştur  
  bt = new KetaiBluetooth(this); // Bluetooth nesnesini oluştur  

  bt.start(); //Bluetooth bağlantısını başlat
  
  bt.getPairedDeviceNames(); // Eşleşilmiş cihaz listesini oluştur
  bt.connectToDeviceByName(baglantiIsmi);  // Bluetooth modülüne bağlan

/* 
 Knob nesneleri oluşturuluyor. Knob dizisinin her bir elemanı
 bir Know nesnesine karşılık geliyor.
*/
  myKnobs[0] = cp5.addKnob("analog1")
    .setRange(0, 1023) // Değer aralığı (0-1023)
      .setValue(0) // Başlangıçtaki değer (0)
        .setPosition(50, 70) // Ekrandaki pozisyon (x,y)
          .setRadius(150); // Nesnenin yarıçapı

  myKnobs[1] = cp5.addKnob("analog2")
    .setRange(0, 1023)
      .setValue(0)
        .setPosition(360, 70)
          .setRadius(150);

  myKnobs[2] = cp5.addKnob("analog3")
    .setRange(0, 1023)
      .setValue(0)
        .setPosition(50, 470)
          .setRadius(150);

  myKnobs[3] = cp5.addKnob("analog4")
    .setRange(0, 1023)
      .setValue(0)
        .setPosition(360, 470)
          .setRadius(150);

  myKnobs[4] = cp5.addKnob("analog5")
    .setRange(0, 1023)
      .setValue(0)
        .setPosition(50, 870)
          .setRadius(150);

  myKnobs[5] = cp5.addKnob("analog6")
    .setRange(0, 1023)
      .setValue(0)
        .setPosition(360, 870)
          .setRadius(150);
}

void draw() {  
  if (veriGeldi)
  {
    veriGeldi = false; // Bayrağı indiriyoruz
    paketCoz(gelenVeri); // Gelen veriler çözümlenmeye gönderiliyor.
  }
}



/* Bluetooth'tan veri alındığında bu fonksiyon çağırılıyor
 Verileri veri adlı dizi içerisinden okuyabiliriz.
 */
void onBluetoothDataEvent(String veriGonderen, byte[] veri) {
  gelenVeri = veri; // Gelen veriler geçici tampona yükleniyor
  veriGeldi = true; // Bayrağı kaldırıyoruz
}

/* 
Bluetooth'dan gelen veriler içerisinde senkronizasyon baytları
bulunduktan sonra 12 baytlık veri alınıp çözme fonksiyonuna
iletiliyor.
*/
void paketCoz(byte[] veri)
{
  /* Gelen dizinin içerisindeki her bir bayt okuyarak
     paket çözme işlemini gerçekleştiriyoruz */
  for (int i = 0; i< veri.length;i++) {  

    switch(paketDurumu)
    {
    /* 
       Önce 'A' karakterinin gelip gelmediğine bakılıyor
       geldiyse bir sonraki duruma geçiliyor 
    */
    case 0:
      if (veri[i] == 'A')
      {
        paketDurumu = 1;
      }
      break;
    /* 
       'A' karakterinden sonra 'B' karakteri olup olmadığına 
       bakılıyor. Varsa bir sonraki duruma geçiliyor. Yoksa
       ilk duruma geri dönülüyor.
    */
    case 1:
      if (veri[i] == 'B')
      {
        paketDurumu = 2;
      }
      else
      {
        paketDurumu = 0;
      }   
      break;
    /* 'A' ve 'B' karakterleri geldikten sonra gelen 12 bayt veri 
       okunuyor ve çözümleniyor. Bu işlemlerden sonrra başa 
       dönülüyor 
    */
    case 2:
      veriler[paketIndeks++] = veri[i];
      // Tüm veriler okundu. Artık başa dönebiliriz.
      if (paketIndeks == 12)
      {
        gelenVeriyiCoz(veriler);
        paketDurumu = 0;
        paketIndeks = 0;
      }
      break;
    }
  }
}
/* 12 baytlık veri 6 adet analog girişe ait değerleri içeriyor
   Her bir analog değer 2 bayttan oluşuyor. Bu değerler
   yüksek ve düşük değerlikli baytların birleştirilmesiyle
   elde ediliyor.
   
   Elde edilen değerler Knob nesnelerine atanarak görüntüleniyor.
 */
void gelenVeriyiCoz(byte[] veri)
{
  int analogGiris = int(veri[0]) + int(veri[1]<<8);  
  myKnobs[0].setValue(analogGiris);

  analogGiris = int(veri[2]) + int(veri[3]<<8);   
  myKnobs[1].setValue(analogGiris);

  analogGiris = int(veri[4]) + int(veri[5]<<8);  
  myKnobs[2].setValue(analogGiris);

  analogGiris = int(veri[6]) + int(veri[7]<<8);  
  myKnobs[3].setValue(analogGiris);

  analogGiris = int(veri[8]) + int(veri[9]<<8);  
  myKnobs[4].setValue(analogGiris);

  analogGiris = int(veri[10]) + int(veri[11]<<8);  
  myKnobs[5].setValue(analogGiris);
}

