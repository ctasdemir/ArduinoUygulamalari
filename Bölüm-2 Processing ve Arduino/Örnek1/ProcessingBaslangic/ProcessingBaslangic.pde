/*
  Processing Örneği - 1
 -------------------------------------------------------
 Processing ile farenin tıklandığı
 noktaya 10 piksel boyutunfa bir
 daire çizdiriliyor. Sol butona tıklandığında daire sarı,
 sağ butonla tıklandığında ise mor renkli olacak
 
 
  Arduino Kitabı 
 Coşkun Taşdemir
 Dikeyeksen Yayınları
 http://www.dikeyeksen.com 
 */

void setup()
{
  size(640, 360); // 640x360 boyutunda bir pencere oluştur
  background(0);  // Arkaplan rengi siyah (0)
  fill(100, 100, 100);
}

void draw()
{
  // Sürekli yapılacaklar işlemler burada yer alır
}

// Fare butonuna basıldığında yapılacak işlemler
void mousePressed()
{
  if (mouseButton == LEFT) {
    fill(255, 255, 0); // Sarı renkle doldur
    // Farenin tıklandığı noktaya 10 piksel 
    // çapında bir daire çizdir
    ellipse(mouseX, mouseY, 30, 30);
  }
  else
  {
    fill(255, 0, 255); // Sarı renkl
    // Farenin tıklandığı noktaya 
    // çapında bir daire çizdir
    ellipse(mouseX, mouseY, 30, 30);
  }
}


