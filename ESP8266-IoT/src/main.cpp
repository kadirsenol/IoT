#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD

#include <RemoteXY.h>
#include <dht11.h>
#include <Servo.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "TTNET_ZyXEL_PFHN"
#define REMOTEXY_WIFI_PASSWORD "0AcA2FaA4537b"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "d925b33adeb67003acf3349904cee624"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,3,0,66,0,220,0,16,87,2,1,0,42,35,12,12,24,31,15,15,
  2,31,76,69,68,0,1,0,34,12,12,12,18,7,12,12,12,31,43,0,
  1,0,51,12,12,12,32,7,12,12,1,31,45,0,129,0,6,53,18,6,
  2,52,41,5,24,80,111,116,32,68,101,196,159,101,114,105,40,111,104,109,
  41,58,0,67,5,56,53,20,5,40,52,20,5,2,26,11,129,0,33,4,
  18,6,15,0,33,6,24,83,101,114,118,111,32,77,111,116,111,114,0,129,
  0,41,27,18,6,26,24,12,6,24,76,69,68,0,129,0,5,53,18,6,
  3,63,31,6,24,83,196,177,99,97,107,108,196,177,107,32,194,176,67,0,
  129,0,37,53,18,6,38,63,20,6,24,78,101,109,32,37,0,67,5,9,
  53,20,5,7,71,20,5,2,26,11,67,5,37,53,20,5,38,71,20,5,
  2,26,11,69,0,13,53,10,10,27,77,10,10,1,67,5,22,53,20,5,
  2,89,58,7,2,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 

    // output variables
  char potasyometre[11];  // string UTF8 end zero 
  char sicaklik[11];  // string UTF8 end zero 
  char nemdeger[11];  // string UTF8 end zero 
  int16_t sound_1; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  char klimadurum[31];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;

#define Led 13
#define DHT11PIN 2

dht11 DHT11;
Servo sg90; 

int pos = 0;
float pot;
float sic;
float nem;
int chk;
void setup() 
{
  RemoteXY_Init (); 

  pinMode (Led, OUTPUT);
  sg90.attach(9); 
}

void loop() 
{ 
  RemoteXY_Handler ();

//SICAKLIK NEM
  chk= DHT11.read(DHT11PIN);
  sic = DHT11.temperature;  
  nem = DHT11.humidity;
  dtostrf(sic, 0, 1, RemoteXY.sicaklik);
  dtostrf(nem, 0, 1, RemoteXY.nemdeger);


//POTASYOMETRE
 pot=analogRead(A0);
 dtostrf(pot,0,2,RemoteXY.potasyometre);


//SERVO MOTOR
 if (RemoteXY.button_2!=0) 
  {
  pos=pos+15;
    sg90.write(pos);
    delay(250); 
  }

if (RemoteXY.button_3!=0) 
  {
     pos=pos-15;
    sg90.write(pos);
    delay(250); 
  }


//LED
  if (RemoteXY.button_1!=0) 
  {
 digitalWrite(Led,HIGH);
}
else 
{
digitalWrite(Led,LOW);
}

if (sic>=33 || nem>=50)
{
RemoteXY.sound_1 = 1;
sprintf(RemoteXY.klimadurum, "Klimayı Çalıştır");
}
else {
  RemoteXY.sound_1 = 0;
sprintf(RemoteXY.klimadurum, "Klimayı Çalıştırma");
}

}
