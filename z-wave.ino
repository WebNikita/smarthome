// demo sketch for connecting OneWire temperature sensor DS18B20 to Z-Uno

// add library ds18b20
#include <ZUNO_DS18B20.h>

// pin connection ds18b20
#define PIN_DS18B20 11

OneWire ow(PIN_DS18B20);

// onewire connection temperature sensors
DS18B20Sensor ds1820(&ow); 

byte addr1[8];
int temp; // here we will store the temperature

// set up channel
ZUNO_SETUP_CHANNELS(
 ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, 
 SENSOR_MULTILEVEL_SCALE_CELSIUS, 
 SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 
 SENSOR_MULTILEVEL_PRECISION_TWO_DECIMALS,
 getterTemp)
);

void setup() {
 Serial.begin();
 Serial.println("start"); 
}

void loop() {
 ds1820.scanAloneSensor(addr1);
 // obtaining readings from the sensor ds18b20
 float temerature = ds1820.getTemperature(addr1);
 // make scaled word value for report
 temp=int(temerature*100);
 Serial.print("Your sensor address is: ");
 for(int i = 0; i < 8; i++) {
 // print OneWire code
 Serial.print(addr1[i], HEX);
 Serial.print(" ");
 }
 Serial.println();
 
 Serial.print("Temperature: ");
 Serial.println(temerature);
 
 // send data to channel
 zunoSendReport(1); 
 // send every 30 second
 delay(30000);
}

word getterTemp() {
 return temp;
}
