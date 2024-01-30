#include <Servo.h>
Servo servo1, servo2, servo3, servo4;
int data;
const int trig = A1; 
const int echo = A0; 
const int trigsa= A3; const int echosa =A2;
const int trigso = A5;
const int echoso = A4;
const int sol_i = 2;
const int sol_g = 4;
const int sol_p = 5;
const int sag_i = 7;
const int sag_g= 8;
const int sag_p = 3;
const int frc_i= 12;
const int frc_g =13;
int sure,suresa,sureso = 0;
intmesafe,mesafesa,mesafeso = 0;
void setup() 
{ 
Serial.begin(38400);
servo1.attach(11);
servo2.attach(10);
servo3.attach(9); servo4.attach(6);



servo1.write(0);
servo2.write(0);
servo3.write(0);
servo4.write(0);

pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(trigsa,OUTPUT);
pinMode(echosa,INPUT);
pinMode(trigso,OUTPUT);
pinMode(echoso,INPUT);
pinMode(sol_i,OUTPUT);
pinMode(sol_g,OUTPUT);
pinMode(sol_p,OUTPUT);
pinMode(sag_i,OUTPUT);
pinMode(sag_g,OUTPUT);
pinMode(sag_p,OUTPUT);
pinMode(frc_i,OUTPUT);
pinMode(frc_g,OUTPUT);
////Serial.begin(9600);

}
String gelen_veri=""; int a,b,c,d;
bool ucgen=false; bool


kare=false;
bool yuvarlak=false;
bool iks=false;
bool donus=false;
bool dur=false;
bool sup1=false;
bool sup2=false; 
void loop() 
{
 servo1.write(a);
servo2.write(b);
servo3.write(c);
servo4.write(d); 
digitalWrite(trigsa , HIGH);
delayMicroseconds(2);
digitalWrite (trigsa , LOW);
suresa = pulseIn (echosa , HIGH);
mesafesa= (suresa/2) / 29.1 ;

Serial.println(mesafesa);

digitalWrite (trig , HIGH); delayMicroseconds(2); digitalWrite
(trig , LOW);
sure = pulseIn (echo , HIGH);
mesafe= (sure/2) / 29.1 ;

Serial.println(mesafe);

digitalWrite (trigso , HIGH);
delayMicroseconds(2);
digitalWrite(trigso , LOW); 
sureso = pulseIn(echoso , HIGH);
mesafeso = (sureso/2) / 29.1 ;

Serial.println(mesafeso);
 if ( mesafe > 20 && mesafesa < 20 && mesafeso > 20 ) //SAĞDAN BAŞLANGIÇ İLERİ
 {
 digitalWrite(sol_i , HIGH);
digitalWrite(sol_g , LOW);
digitalWrite(sag_i , HIGH);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i , HIGH);
digitalWrite(frc_g , LOW);
analogWrite(sag_p,250);
analogWrite(sol_p ,250); sup1
= true;
 }


if ( mesafe < 20 && mesafesa < 20 && mesafeso > 20 )// İLK SOLA DÖN VE İKİNCİ BU İF
İHTİMALİ İÇİN DURMA AYARINI YAP
{ 
if(dur == false)
 {
 digitalWrite(sag_i , HIGH); 
 digitalWrite(sag_g, LOW);
digitalWrite(sol_i , LOW);
digitalWrite(sol_g , LOW);
digitalWrite(frc_i ,LOW);
digitalWrite(frc_g , HIGH);
analogWrite(sag_p,250);
analogWrite(sol_p,250);
delay(1000); //birusteki if e girmemesi için sağ tek dönüş beklemesi
dur=true;
 } 
 else
 {
 digitalWrite(sol_i , LOW);
digitalWrite(sol_g , LOW);
digitalWrite(sag_i , LOW);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i , LOW);
digitalWrite(frc_g , LOW);
 } 
 } 
 if ( mesafe > 20 && mesafesa > 20 && mesafeso > 20 ) // DÜZGİT
{ 
digitalWrite(sag_i ,HIGH);
digitalWrite(sag_g, LOW);
digitalWrite(sol_i, HIGH);
digitalWrite(sol_g , LOW);


analogWrite(sag_p,250);
analogWrite(sol_p,250);
}
if ( mesafe < 20 && mesafesa > 20 && mesafeso > 20 ) //ORTAK SAĞ DÖN FIRÇA YÖN DEĞİŞ
{
if(donus==false)
 {
 digitalWrite(sol_i ,HIGH);
 digitalWrite(sol_g, LOW);
digitalWrite(sag_i , LOW);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i , HIGH);
digitalWrite(frc_g , LOW);
analogWrite(sag_p,250);
analogWrite(sol_p,250);
delay(1000); donus = true;
 }
 else // ORTAK SOL DÖN FIRÇA YÖN DEĞİŞ
 {
 digitalWrite(sol_i , LOW);
digitalWrite(sol_g , LOW);
digitalWrite(sag_g , LOW);
digitalWrite(sag_i , HIGH);
digitalWrite(frc_i , LOW);
digitalWrite(frc_g , HIGH);


analogWrite(sag_p,250); analogWrite(sol_p,250);
delay(1000); donus= false;
 }
}
if ( mesafe > 20 && mesafesa > 20 && mesafeso < 20 ) //SAĞDAN BAŞLANGIÇ İÇİN BİTMEYESOLUNDA ENGEL VARKEN GİDERSE DÜZ GİT (SAĞDA VARKEN GİDERSE ZATENSAĞDAN BAŞLAMA İLE AYNI DÜZ GİT),,,,SOLDAN BAŞLANGIÇ İÇİN DÜZ GİT
{ 
digitalWrite(sol_i ,HIGH);
digitalWrite(sol_g, LOW);
digitalWrite(sag_i, HIGH);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i , LOW);
digitalWrite(frc_g , HIGH);
analogWrite(sag_p,250);
analogWrite(sol_p,250);
}
if ( mesafe < 20 && mesafesa > 20 && mesafeso < 20 ) //SAĞDAN BAŞLANGIÇ İÇİN ÖN SOLDUR,,,SOLDAN BAŞLANGIÇ İÇİN ÖN SOL İLK SAĞA DÖN İKİNCİ ÖN SOL İÇİN DUR
{


if(sup1==true || sup2==true ) /// SAĞDAN BAŞLAMIŞSA SUP1 TRUE OLACAK VE DURACAKSOLDAN BAŞLAMIŞSA ELSEYE GİRECEK ÖNCE SAĞA DÖNECEK SUP2 TRUE OLACAKİKİNCİ ÖN SOL DA DURACAK
{ 
digitalWrite(sol_i , LOW);
digitalWrite(sol_g , LOW);
digitalWrite(sag_i, LOW);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i , LOW);
digitalWrite(frc_g, LOW);
}
else // SOLDAN BAŞLAMIŞTIR İLK ÖN SOL SAĞA DÖN
{ 
digitalWrite(sol_i ,HIGH);
digitalWrite(sol_g ,LOW); 
digitalWrite(sag_i ,LOW);
digitalWrite(sag_g , LOW);
digitalWrite(frc_i,HIGH);
digitalWrite(frc_g , LOW);
analogWrite(sag_p,250);
analogWrite(sol_p,250);
delay(1000); sup2=true;
}

}
///////////////////////////////////////////// SERVO İFLERİ if(Serial.available())
{ 
gelen_veri =(Serial.readString());
}
if(gelen_veri=="ucgen")
{
ucgen=true;
kare=false;
yuvarlak=false;
iks=false; gelen_veri="";
 }
 if(gelen_veri=="kare")
 {

ucgen=false;
kare=true;
yuvarlak=false;
iks=false;
gelen_veri="";
 
 }
 if(gelen_veri=="yuvarlak")
 {

ucgen=false;
kare=false;
yuvarlak=true; iks=false;
gelen_veri="";

 }

if(gelen_veri=="iks")
 {

ucgen=false;
kare=false;
yuvarlak=false; iks=true;

gelen_veri="";

 }

 if(gelen_veri=="ust")
 {

 if (ucgen==true) {
a=a+15;
gelen_veri="";
 } if
(kare==true)
 {
b=b+10; gelen_veri="";


 }
 if (yuvarlak==true)
 { 
    c=c+10; gelen_veri="";
 } 
 if(iks==true)
 {
d=d+15; gelen_veri="";
 }

 } 
 if(gelen_veri=="alt")
 {

 if (ucgen==true)
{ 
    a=a-15; gelen_veri="";
 } 
 if(kare==true)
 { 
    b=b-10; gelen_veri="";
 }
 if (yuvarlak==true)
 { c=c-10;
gelen_veri="";
 } 
 if(iks==true)
 { 
    d=d-15; gelen_veri="";
 }
 }


}