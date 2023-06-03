#include "CTBot.h"
#include "DHT.h"


#define DHTPIN D5     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

CTBot myBot;
TBMessage msg;

int botRequestDelay = 1500;   // mean time between scan messages
long lastTimeBotRan;     // last time messages' scan has been done

void handleNewMessages(int numNewMessages);

String ssid  = "JioFiber-FWHd6"    ; // Enter WIFI Username
String pass  = "iewaelaixeejooch"; // Enter WIFI Password
String token = "6051918158:AAE0Deu2KgyRfkbjoaXgzfdPMGcKS8QxHYk"; // test the token from Telegram Bor

void setup()
{
  Serial.begin(115200);
  dht.begin();
  Serial.println("Starting TelegramBot...");
  
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()){
   
    Serial.println("\n testConnection OK");
//    myBot.sendMessage(5591139722, "testConnection OK"); 
  }
  else
  {
    Serial.println("\ntestConnection NOK");
  }

 
}

void loop()
{
    delay(2000);
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  String humid = "Humidity: " + String(h) + " % \n";
  String temp = "Temperature: " + String(t) + "°C, " + String(f) + "°F \n";
  if (myBot.getNewMessage(msg)) {
     if (msg.text.equalsIgnoreCase("Temp")) {    
          
          Serial.println(temp);
          Serial.println(msg.sender.id);
          myBot.sendMessage(msg.sender.id, temp); 
          Serial.println(temp);
    }
   }
   
}
