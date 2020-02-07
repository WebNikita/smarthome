#define PIN_PIR 2
#define PIN_LED 13
void setup() {
  Serial.begin(9600);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LED, OUTPUT);
}
void loop() {
  int pirVal = digitalRead(PIN_PIR);
  Serial.println(digitalRead(PIN_PIR));
  //Если обнаружили движение
  if (pirVal)
  {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("Motion detected");
  }
  else
  {
    //Serial.print("No motion");
    digitalWrite(PIN_LED, LOW);
  }
}
