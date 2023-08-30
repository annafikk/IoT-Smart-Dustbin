#define trigPin     D8
#define echoPin     D7
#define LED_PIN     2
#include "CTBot.h"
  
long durasi;
int jarak;
int persen_jarak;
int ukuran = 40;
// Ultrasonic us(13, 15);
CTBot myBot;
String ssid = "OKESIP";
String pass = "1234567890";
String token = "5975969660:AAG-K3lObOojt0KKexbV6IUIfFCzZJbUU18";
const int id = 1111430006;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with NodeMCU V3 ESP8266");

  Serial.println("Starting TelegramBot . . .");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }

  myBot.sendMessage(id, "Tes Smart Dustbin Bot");
  myBot.sendMessage(id, "Ultrasonic Sensor HC-SR04 Test");
  myBot.sendMessage(id, "with NodeMCU V3 ESP8266");
  Serial.println("Pesan Terkirim");
}
  
void loop()
{
  TBMessage msg;
  
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  durasi = pulseIn(echoPin, HIGH);
  
  jarak = durasi * 0.034 / 2;
  persen_jarak = 100 - jarak * 100 / 35 ;
  
  Serial.println("");
  Serial.println("Monitoring Tempat Sampah :");
  
  if (jarak <= 40 && jarak >= 20)
  {
      Serial.print("Jarak Sampah: ");
      Serial.print(jarak);
      Serial.println(" cm");
    
      Serial.print("Persentase : ");
      Serial.print(persen_jarak);
      Serial.println("%");

      Serial.print("Isi : ");
      Serial.print("Kosong"); 

      myBot.sendMessage(id, "Jarak : " + String(jarak) + " cm" + "\n" + "Persentase : " + String(persen_jarak) + "%" + "\n" + "Sampah Kosong");
   }
   else if (jarak <= 8)
   {
      Serial.print("Jarak Sampah: ");
      Serial.print(jarak);
      Serial.println(" cm");
  
      Serial.print("Persentase : ");
      Serial.print(persen_jarak);
      Serial.println("%");
  
      Serial.print("Isi : ");
      Serial.print("Penuh");

      myBot.sendMessage(id, "Jarak : " + String(jarak) + " cm" + "\n" + "Persentase : " + String(persen_jarak) + "%" + "\n" + "Sampah Penuh");
   }
   else if(jarak > 8 && jarak < 20)
   { 
      Serial.print("Jarak Sampah: ");
      Serial.print(jarak);
      Serial.println(" cm");
  
      Serial.print("Persentase : ");
      Serial.print(persen_jarak);
      Serial.println("%");
  
      Serial.print("Isi : ");
      Serial.print("Sedang");

      myBot.sendMessage(id, "Jarak : " + String(jarak) + " cm" + "\n" + "Persentase : " + String(persen_jarak) + "%" + "\n" + "Sampah Sedang");
    }
    Serial.println("");
    delay(500);

    /*
     if (myBot.getNewMessage(msg))
     {
         if (msg.text.equalsIgnoreCase("JARAK")) {                                  
            myBot.sendMessage(id,"Suhu: " + String(jarak + " cm");  
         }
         else if (msg.text.equalsIgnoreCase("PERSENTASE"))
         {                               
            myBot.sendMessage(id, "Kelembaban: " + String(persen_jarak + "%"); 
         }
         else
         {                                                   
         String reply;
         reply = (String)"Halo " + msg.sender.username + (String)". Cek Tempat Sampah.";
         myBot.sendMessage(id, reply);           
         }
     }
     */
  }
