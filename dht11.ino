#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 14

#define DHTTYPE DHT11   

const char* ssid = "SmartHome";
const char* password = "dt_smartpark_2017";
const char* port = "8080";      
const char* host = "192.168.0.1";           

DHT dht(DHTPIN, DHTTYPE);

void setup (){
  //WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  WiFi.begin(ssid, password);
}

void loop (){

  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int f1t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  //if (isnan(h) || isnan(t) || isnan(f)) {
    //Serial.println(F("Failed to read from DHT sensor!"));
    //return;
  //}

  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);

  //Serial.print(F("Humidity: "));
  //Serial.print(h);
  //Serial.print(F("Temperature: "));
  //Serial.print(f1t);
  //Serial.print(F("°C "));
  //Serial.print(f);
  //Serial.print(F("°F  Heat index: "));
  //Serial.print(hic);
  //Serial.print(F("°C "));
  //Serial.print(hif);
  //Serial.println(F("°F"));









  String str_f1t = String(f1t);
  String str_h = String(h);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%Temperature: "));
  Serial.println(f1t);
  WiFiClient client;
  client.connect(host,8080);
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 8080)) {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    client.print(String("GET /?f3t="+ str_f1t)+ " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: keep-alive\r\n" +
                 "\r\n"
                );
    client.print(String("GET /?f4t="+ str_h)+ " HTTP/1.1\r\n" +
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

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print ("good");
  }
  else {
    Serial.println ("bad");
  }

}
