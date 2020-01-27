#include <OneWire.h>
#include <ESP8266WiFi.h>

OneWire ds(13);
int f1t = 0; // Глобальная переменная для хранения значение температуры с датчика DS18B20
long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
const int TEMP_UPDATE_TIME = 500; // Определяем периодичность проверок

const char* ssid = "SmartHome";
const char* password = "dt_smartpark_2017";
const char* port = "8080";      
const char* host = "192.168.0.1";             

void setup (){
  //WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, password);
}

void loop (){
  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);
  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();
    // Формируем значение
    f1t = (data[1] << 8) + data[0]; f1t = f1t >> 4;
  }
  // Выводим полученное значение температуры в монитор порта
  String str_f1t = String(f1t);
  Serial.println(f1t);
  WiFiClient client;
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 8080)) {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    client.print(String("GET /?f3t="+ str_f1t) + " HTTP/1.1\r\n" +
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
