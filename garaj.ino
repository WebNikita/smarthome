#include <SoftwareSerial.h>
#include <Servo.h> 

// Пин для сервопривода
int servoPin1 = 8;//левая
int servoPin2 = 9;//правая
int input;
String card;

// Создаем объект
Servo Servo1;//левая
Servo Servo2;//правая

SoftwareSerial RFIDSerial(11, 10); // RX, TX

void setup()
{
 
  Servo1.attach(servoPin1);//левая
  Servo2.attach(servoPin2);//правая

  // закрытие левой
  Servo1.write(60);
  //закрытие правой
  Servo2.write(90);
  
  // Очищаем буфер
  Serial.flush();
  // Устанавливаем скорость работы с портом
  Serial.begin(9600);
  // Устанавливаем скорость работы с модулем RDM630
  RFIDSerial.begin(9600);
  card="";
}

void loop()
{
  // если есть данные, то
  if (RFIDSerial.available() > 0)  
  {
    // читаем блок данных с модуля RDM630 и заносим их в переменную input
    input = RFIDSerial.read();
    // присваиваем все считанные в переменную input значения переменной s, так как за 1 цикл loop мы получаем 1 значение, а их 12
    card+=input;  // то же самое, что и s=s+input;
    // если длинна кода равна 26 символам (в памяти чипа можно разместить 26 байт информации), то
    if (card.length()==26) 
    {
      // выводим данные
      Serial.println("Card UID:");
      Serial.println(card);
    } 
    if (card==25267484868496852535049663)
    {
      // откртие левой
       Servo1.write(150);
      //открытие правой
       Servo2.write(0);
    }
    card="";
  }
}
