#include <Adafruit_Sensor.h>

#include <OneWire.h>
#include <DallasTemperature.h>

//#include <DHT.h> // Датчик температуры
//#include <DHT_U.h>  // Датчик температуры
#include <Wire.h>   //Барометр
#include <TroykaIMU.h> //Барометр 

#include <ESP8266WiFi.h>

#define ONE_WIRE_BUS 14
//#define DHTPIN 14   // Объявляем номер вывода для датчика
//#define DHTTYPE DHT11

OneWire oneWire(ONE_WIRE_BUS);


Barometer barometer;   //объект для работы с барометром
DallasTemperature sensors(&oneWire);

const char* ssid = "SmartHome";                          //Для WIFI
const char* password = "dt_smartpark_2017";

const char* port = "8080";       //Для сервера
const char* host = "192.168.0.1";           
   
//DHT dht(DHTPIN, DHTTYPE); 
void setup (){
  WiFi.mode(WIFI_AP_STA);
//  dht.begin();
  Wire.begin(12,13);
  Serial.begin(115200);
  Serial.println();
  barometer.begin();
  sensors.begin();
  WiFi.begin(ssid, password);
}

void loop (){
   sensors.requestTemperatures();
     int temperature = sensors.getTempCByIndex(0);
     String strtemperature = String(temperature);
     Serial.println(temperature);
     
//  //Общение с сервером 
    WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 8080))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
     client.print(String("GET /?f3t="+strtemperature) + " HTTP/1.1\r\n" +
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
