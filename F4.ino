#include <Adafruit_Sensor.h>

//#include <OneWire.h>
//#include <DallasTemperature.h>

#include <DHT.h> // Датчик температуры
//#include <Wire.h>   //Барометр
//#include <TroykaIMU.h> //Барометр 

#include <ESP8266WiFi.h>

#define DHTPIN 14   // Объявляем номер вывода для датчика
#define DHTTYPE DHT11

const char* ssid = "iPhone";                          //Для WIFI
const char* password = "11111111";

const char* port = "8080";       //Для сервера
const char* host = "192.168.0.1";           

DHT dht(DHTPIN, DHTTYPE); 
void setup (){
   pinMode(7, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  dht.begin();
  //Wire.begin(12,13);
	Serial.begin(115200);
	Serial.println();
	WiFi.begin(ssid, password);
  //lightMeter.begin();
}

void loop (){
//  Датчик температуры DHT11
  int temp = dht.readTemperature();
  int  humd = dht.readHumidity();
  String strtemp = String(temp);
  String strhumd = String(humd);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(humd);
  Serial.println(" *C ");
//  //Общение с сервером 
    WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 8080))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    client.print(String("GET /?f4t="+strtemp) + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: keep-alive\r\n" +
                 "\r\n"
                );
    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }


  
  //Проверка подключения к WiFi 
	if (WiFi.status() == WL_CONNECTED) {
		Serial.print ("good");
	}
	else {
		Serial.println ("bad");
	}

}
