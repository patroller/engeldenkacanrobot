//mesafe sensörünün pinleri
int echo1=2;
int trig1=3;
int echo2=4;
int trig2=5;
int echo3=6;
int trig3=7;

//motor pinleri
const int sagileri = 8;
const int saggeri = 9;
const int solileri = 13;
const int solgeri = 12;
const int solenable = 11;
const int sagenable =10;

// ölçüm fonksiyonları

//sol taraf
float uzaklik1(int trig1, int echo1)
{
  float olcum1;
  float mesafe1;
  digitalWrite (trig1, LOW);
  delayMicroseconds(5);
  digitalWrite (trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite (trig1, LOW);
  olcum1=pulseIn (echo1, HIGH);
  mesafe1=olcum1/29/2;
  return mesafe1;
}

//ön taraf
float uzaklik2(int trig2, int echo2)
{
  float olcum2;
  float mesafe2;
  digitalWrite (trig2, LOW);
  delayMicroseconds(5);
  digitalWrite (trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite (trig2, LOW);
  olcum2=pulseIn (echo2, HIGH);
  mesafe2=olcum2/29/2;
  return mesafe2;
}

//sağ taraf
float uzaklik3(int trig3, int echo3)
{
  float olcum3;
  float mesafe3;
  digitalWrite (trig3, LOW);
  delayMicroseconds(5);
  digitalWrite (trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite (trig3, LOW);
  olcum3=pulseIn (echo3, HIGH);
  mesafe3=olcum3/29/2;
  return mesafe3;
}

//hareket fonksiyonları

void ileri(int hizsag, int hizsol)  //ileri fonksiyonu
{
analogWrite(sagenable, hizsag);
digitalWrite(sagileri,HIGH);
digitalWrite(saggeri,LOW);
analogWrite(solenable, hizsol);
digitalWrite(solileri, HIGH);
digitalWrite(solgeri,LOW);
}
void geri(int hizsag, int hizsol)    //geri fonksiyonu
{
analogWrite(sagenable, hizsag);
digitalWrite(sagileri,LOW);
digitalWrite(saggeri, HIGH);
analogWrite(solenable, hizsol);
digitalWrite(solileri, LOW);
digitalWrite(solgeri, HIGH);
}
void dur()                         //dur fonksiyonu
{
digitalWrite(sagileri, HIGH);
digitalWrite(saggeri, HIGH);
digitalWrite(solileri, HIGH);
digitalWrite(solgeri, HIGH);
}
void sag(int hizsag, int hizsol)   //sağa dönme fonksiyonu
{
analogWrite(sagenable, hizsag);
digitalWrite(sagileri,HIGH);
digitalWrite(saggeri,LOW);
analogWrite(solenable, hizsol);
digitalWrite(solileri, LOW);
digitalWrite(solgeri,HIGH);
}

void sol(int hizsag, int hizsol)    //sola dönme fonksiyonu
{
analogWrite(sagenable, hizsag);
digitalWrite(sagileri,LOW);
digitalWrite(saggeri,HIGH);
analogWrite(solenable, hizsol);
digitalWrite(solileri, HIGH);
digitalWrite(solgeri,LOW);
}

void setup() {             //giriş çıkış pinlerini ayarlayalım.
pinMode (trig1, OUTPUT);
pinMode (echo1, INPUT);
pinMode (trig2, OUTPUT);
pinMode (echo2, INPUT);
pinMode (trig3, OUTPUT);
pinMode (echo3, INPUT);
//Serial.begin(9600);   //hata ayıklama için.
}
void loop() {
while( uzaklik2(trig2, echo2 ) >= 30 && uzaklik1(trig1, echo1) >= 15 && uzaklik3(trig3, echo3) >= 15)  //sağ ve sol 15cm'den ön de 30cm'den büyükse ileri git
{
ileri(80,80);
}
dur(); // engel geldikten sonra dur
delay(100); // 0.1 saniye bekle

if( uzaklik1(trig1, echo1) >= 30 ) // solunda engel yoksa sola dön
{ 
sol(170,170); 
delay(250); // dönüş açısını belirleyen süre. Bu süreyi kendinize göre ayarlayın
dur(); // dur
delay(100);
}
else if(uzaklik3(trig3, echo3) >= 30 ){ // sol dolu ise sağa bak
sag(170,170); // engel yoksa sağa dön
delay(250); // dönüş açısını belirleyen süre. Bu süreyi kendinize göre ayarlayın
dur(); // dur
delay(100);
}
else if ( uzaklik2(trig2, echo2 ) <= 20 && uzaklik1(trig1, echo1) <= 20 && uzaklik3(trig3, echo3) <= 20) //ön, sağ ve sol 20 cm'den küçük ise geri git. 
{
geri(80,80);
delay(500);//geri gidiş süresi, çok uzun yada çok kısa geri giderse süreyi değiştirin,
sol(170,170); 
delay(250);
  }

//else  // sağ ve solda engel varsa geri gidip dönelim
//{
//geri(100,100);
//delay(700);
//}
//hata ayıklama
/* 
Serial.print("Sol mesafe=");
Serial.println(uzaklik1 (trig1, echo1));
Serial.print("On mesafe=");
Serial.println(uzaklik2 (trig2, echo2));
Serial.print("Sag mesafe=");
Serial.println(uzaklik3 (trig3, echo3));
Serial.println("---------------------------");
*/
}
