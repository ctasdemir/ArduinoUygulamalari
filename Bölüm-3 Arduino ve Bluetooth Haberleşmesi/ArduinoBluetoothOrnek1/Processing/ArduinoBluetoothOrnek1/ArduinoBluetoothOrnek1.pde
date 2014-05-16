/* 
   Processing ile Android İşletim Sistemi Üzerinde
   Bluetooth protokolü kullanımı Örneği - 1
   
   Kullanılan Processing Kütüphaneleri:
   - ControlP5
   - Ketai
   
   Butonların boyutlarını ve konumlarını
   cihazınızın ekran özelliklerine göre değiştirimeniz
   gerekebilir (setSize ve setPosition fonksiyonları)
    
   Arduino Kitabı 
   Coşkun Taşdemir
   Dikeyeksen Yayınları
   http://www.dikeyeksen.com
 */
import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*;
import controlP5.*;
import ketai.sensors.*;

KetaiBluetooth bt;
KetaiList kliste;
KetaiSensor sensor;
ControlP5 cp5;

ArrayList devicesDiscovered = new ArrayList();
Textlabel myTextlabelA;

byte[] led1_Acik = {'A'};
byte[] led1_Kapali = {'B'};

byte[] led2_Acik = {'C'};
byte[] led2_Kapali = {'D'};

byte[] led3_Acik = {'E'};
byte[] led3_Kapali = {'F'};

byte[] led4_Acik = {'G'};
byte[] led4_Kapali = {'H'};

void setup() {
  // Processing penceresi cihazın ekran boyutlarında olacak
  size(displayWidth, displayHeight); 
  orientation(PORTRAIT);
  background(0);
    // Toggle Nesnelerini oluşturuyoruz
  cp5 = new ControlP5(this); // Kontrol nesnesini oluştur 

  // Toggle nesnelerini ekliyoruz  
  cp5.addToggle("led1") // led1 ismini veriyoruz
    .setPosition(40, 40) // nesnenin konumu
    .setSize(500, 200) // nesnenin boyutu (genişlik,yükseklik)
    .setValue(false) // başlangıç durumu (false)
    .setMode(ControlP5.SWITCH) // anahtar görünümü
            ;

  cp5.addToggle("led2")
    .setPosition(40, 260)
      .setSize(500, 200)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led3")
    .setPosition(40, 480)
      .setSize(500, 200)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led4")
    .setPosition(40, 700)
      .setSize(500, 200)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;

  cp5.addToggle("led5")
    .setPosition(40, 920)
      .setSize(500, 200)
        .setValue(false)
          .setMode(ControlP5.SWITCH)
            ;
            
  bt = new KetaiBluetooth(this);

  // Bluetooth bağlantısını başlatıp cihazları dinlemeye başlıyoruz
 // bt.start();
    
  // Eşleşilen Bluetooth cihazlarının listesi alınıyor
  kliste = new KetaiList(this, bt.getPairedDeviceNames()); 
}



void draw() {
 
}

/* Bluetooth cihazlarının listesinden seçim yapılan
   cihaza bağlanıyoruz.
   Bir seçim yapıldığında bu fonksiyon otomatik olarak
   çağırılıyor
*/
void onKetaiListSelection(KetaiList klist) {
  String secim = kliste.getSelection();
  bt.connectToDeviceByName(secim);  
  // listeyi yok ediyoruz
  kliste = null;
}

/* Toggle nesnelerinin durumu değiştiğinde çağırılan fonksiyonlar */
void led1(boolean bayrak) {
  if (bayrak==true) {           
      bt.broadcast(led1_Acik);
  } 
  else {      
    bt.broadcast(led1_Kapali);
   }
}

void led2(boolean bayrak) {
  if (bayrak==true) {
    bt.broadcast(led2_Acik);
  } 
  else {
    bt.broadcast(led2_Kapali);  
  }
}

void led3(boolean bayrak) {
  if (bayrak==true) {
    bt.broadcast(led3_Acik);
  } 
  else {
    bt.broadcast(led1_Kapali);
  }
}

void led4(boolean bayrak) {
  if (bayrak==true) {
    bt.broadcast(led4_Acik);    
  } 
  else {
    bt.broadcast(led4_Kapali);   
  }
}
