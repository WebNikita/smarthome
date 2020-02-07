#include "ZUNO_DS18B20.h"

#define PIN_DS18B20 11

OneWire ow(PIN_DS18B20);

DS18B20Sensor ds1820(&ow); 

byte addr1[8];
int temp; 

ZUNO_SETUP_CHANNELS
(
   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, 
                          SENSOR_MULTILEVEL_SCALE_CELSIUS, 
                          SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 
                          SENSOR_MULTILEVEL_PRECISION_TWO_DECIMALS,
                          getterTemp)
);

void setup()
{
    Serial.begin();
    Serial.println("start");
}

void loop()
{
    ds1820.scanAloneSensor(addr1);
    float temerature = ds1820.getTemperature(addr1);
    temp=int(temerature*100);
    Serial.print("Your sensor address is: ");
   
    for(int i = 0; i < 8; i++) 
    {
            Serial.print(addr1[i], HEX);
            Serial.print(" ");
    }
    Serial.println();
    
    Serial.print("Temperature: ");
    Serial.println(temerature);
    
    
    zunoSendReport(1);     
    delay(1000);
}

word getterTemp()
{
    return temp;
}
