#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ThingSpeak.h>           
#include <WiFi.h>
#include <RTC.h>                                                  //#include <rtc_io.h>


 WiFiClient  client;
 unsigned long counterChannelNumber = 2336283;                 // Channel ID
 const char * myCounterWriteAPIKey = "QNVEUHXBRVN2PN1U";     // Write API Key
 const int FieldNumber1 = 1;                                // The field you wish to read
 

 String receivedData = "";
 String ssid;
 String pass;
 String ssid_pass;
 const char *SSID1 = "kdrsnl";
 const char *PASS = "kdrkbr12";



 const int LEDOPEN = 12;
 const int LEDCLOSE = 26;
 const int LED_BT = 13;
 const int LEDWL = 14;
 const int SW = 27;
 

 const int wakeupPinc = 33;//DEEPSLEEP UYANDIRMA PİNİ
 const int wakeupPino = 25;//DEEPSLEEP UYANDIRMA PİNİ
 RTC_DATA_ATTR char SSID2[32];
 RTC_DATA_ATTR char PASS2[32];

//Bir BLE server oluşturalım
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;



bool deviceConnected = false;
bool oldDeviceConnected = false;


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

//client bağlanıp bağlanmadığını kontrol etmek için bir class yapısı tanımlıyoruz
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      digitalWrite(LED_BT, HIGH);
 
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      digitalWrite(LED_BT, LOW);
      
    }

// BURAYA WİFİ BAĞLANDIĞINDA LEDİ OTOMATİK YAKAN CLASS YAPISI OLUŞTUR
 
};

void setup() {

  pinMode(LEDOPEN,OUTPUT);
  pinMode(LEDCLOSE,OUTPUT);
  pinMode(LED_BT,OUTPUT);
  pinMode(LEDWL,OUTPUT);
  pinMode(SW,INPUT_PULLDOWN);
  pinMode(wakeupPino,INPUT_PULLDOWN);
  pinMode(wakeupPinc,INPUT_PULLUP);
  Serial.begin(115200);//ORTAK



  WiFi.begin(SSID1, PASS);  
  delay(5000);

  WiFi.begin(SSID2, PASS2);////// SONRADAN GİRİLEN WİFİ İÇİN TEKRAR BAĞLANTI
  delay(5000);

  ThingSpeak.begin(client);

  // BLE cihazı yaratalım (görünecek isim budur)*****
  BLEDevice::init("ESP32");

  // BLE Server'ı oluşturalım
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // BLE servisi oluşturalım
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // BLE karakteristiğini oluşturalım
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  // Servisi başlatalım
  pService->start();

  // Yayın yapmayı başlatalım
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // değeri 0x00 olarak değiştirirseniz yayınlanmaz
  BLEDevice::startAdvertising();
}

void loop() {

  while (deviceConnected && WiFi.status() != WL_CONNECTED) {
    ////BT YE BAĞLIYKEN NET KAPANMASI YÜZÜNDEN NET KOPMASI OLURSA TEKRAR BAĞLANSIN DİYE.
    WiFi.begin(SSID1, PASS);
    delay(5000);
    
    WiFi.begin(SSID2, PASS2);
    delay(5000);
  
    ThingSpeak.begin(client);
    
     
       if (pCharacteristic->getValue().length() > 0) {
      receivedData = pCharacteristic->getValue().c_str();//MOBİLDEN GELEN VERİ STR, SSID_PASS VE RECEİVED DEĞİŞKENLERİ DE STR OLDUĞU İÇİN VE ZATEN WİFİYE BAĞLANMADAN HEMEN ÖNCE .c_str() KOMUTU İLE ÇEVİRİLİP YAPIŞTIRILDIĞI İÇİN BU SATIRDAKİ .c_str() KISMINI SİL ÇALIŞTIRMAYI DENE ÇALIŞIRSA SİL.
      
      ssid_pass = receivedData; 
  
      for (int i = 0; i < ssid_pass.length(); i++) 
      {
        if (ssid_pass.substring(i, i+1) == ",") 
        {
          ssid = ssid_pass.substring(0, i);
          pass = ssid_pass.substring(i+1);
          delay(2000);
          

    int n1 = ssid.length();
    char char_array1[n1 + 1];
    strcpy(char_array1, ssid.c_str());
    
    
    int n2 = pass.length();
    char char_array2[n2 + 1];
    strcpy(char_array2, pass.c_str());
    
    
    WiFi.begin(char_array1, char_array2);                 // write wifi name & password           
    delay(5000);

   if (WiFi.status() == WL_CONNECTED) {
    ThingSpeak.begin(client);
    digitalWrite(LEDWL, HIGH);

    //////////////////////////////////////// SONRADAN GİRİLEN WİFİ İÇİN TEKRAR BAĞLANTI
    strcpy(SSID2, ssid.c_str());
    strcpy(PASS2, pass.c_str());
                                    
      }
          break; // BUNU YA Bİ ÜSTÜNDE Kİ İFİN İÇİNE AL YA DA SİL. DENE ÇALIŞIRSA SİL.         
      }  
    }    
  }  
}

  // WİFİ BİLGİLERİ DOĞRU OLDUĞUNDA VE BLE BAĞLANTISI ÖNEMLİ OLMADIĞINDA. BENİM ÇALIŞACAĞIM ALAN BURASI.
  while ((!deviceConnected && WiFi.status() == WL_CONNECTED) || (deviceConnected && WiFi.status() == WL_CONNECTED))
  {
   digitalWrite(LEDWL, HIGH);
   delay(500); // bluetooth katına biraz süre tanımak için

    while (WiFi.status() == WL_CONNECTED)
    {

        if(digitalRead(SW)==1)
        {
          digitalWrite(LEDCLOSE,HIGH);
          digitalWrite(LEDOPEN,LOW);
          delay(500); //YAZDIRMA ÖNCESİ 15SN BEKLEME
          ThingSpeak.writeField(counterChannelNumber, 1, 0, myCounterWriteAPIKey);
          delay(5000);
             digitalWrite(LEDOPEN,LOW);
              esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,0);
              delay(1000);
              esp_deep_sleep_start();   
         }

          if (digitalRead(SW)==0)
          {
          digitalWrite(LEDOPEN,HIGH);
          digitalWrite(LEDCLOSE,LOW);
          delay(500); //YAZDIRMA ÖNCESİ 15SN BEKLEME
          ThingSpeak.writeField(counterChannelNumber, 1, 1, myCounterWriteAPIKey);
          delay(5000);
             
              digitalWrite(LEDCLOSE,LOW);
              esp_sleep_enable_ext0_wakeup(GPIO_NUM_25,1);
              delay(1000);
              esp_deep_sleep_start();
           }
     }          
    digitalWrite(LEDWL, LOW);
  }

    delay(500); // bluetooth katına biraz süre tanımak için
    pServer->startAdvertising(); // tekrar kendini yayınlamaya başlatalım
    Serial.println("Yayın başlatıldı");

    WiFi.begin(SSID1, PASS);//ELEKTRİK KESİLDİĞİ İÇİN WİFİ KOPTUKTAN SONRA AYNI WİFİYE TEKRAR BAĞLANMASI İÇİN. EĞER ŞİFRE DEĞİŞİMİ İÇİN KOPTUYSA ZATEN BAĞLANAMAYIP SATIRI ATLİCAK
    delay(5000);
    
    WiFi.begin(SSID2, PASS2);//ŞİFRE İLE GİRİLEN WİFİ ELEKTRİK KESİLİP KOPTUKTAN SONRA TEKRAR BAĞLANMASI İÇİN. EĞER ŞİFRE DEĞİŞİMİ İÇİN KOPTUYSA ZATEN BAĞLANAMAYIP SATIRI ATLİCAK
    delay(5000);
  
    ThingSpeak.begin(client);

    if (WiFi.status() == WL_CONNECTED)
   {
    digitalWrite(LEDWL, HIGH);
   }

}