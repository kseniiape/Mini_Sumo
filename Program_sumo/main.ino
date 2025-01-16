#include <Wire.h>
#include <VL53L0X.h>
unsigned long timing;

//Адреса лазерных дальномеров
#define SensorL_newAddress 36
#define SensorLF_newAddress 37
#define SensorF_newAddress 38
#define SensorRF_newAddress 39
#define SensorR_newAddress 40

//Порты для управления програмированием адресов лазерных дальномеров
#define XSHUT_pinL 12
#define XSHUT_pinLF 11
#define XSHUT_pinF 8
#define XSHUT_pinRF 4
#define XSHUT_pinR 3

//Порты управления моторами
#define M1_1 6
#define M1_2 5
#define M2_1 10
#define M2_2 9

//Порт для стартового модуля
#define StartPin 2

/*Макрос отладки
  0-рабочий режим
  1-проверка датчиков
  2-проверка моторов
*/
#define OTLADKA 0


//Создание классов для работы с лазерными дальномерами
VL53L0X vlxL; // Левый
VL53L0X vlxLF; //Лево-Передний
VL53L0X vlxF; // Передний
VL53L0X vlxRF; //Право-передний
VL53L0X vlxR; //Правый

//Определение переменных
//Переменные направлений
int napr = 0;
int old_napr = 0;
//Переменные для датчиков линии
int left_L = 0;
int right_L = 0;
//Переменные для лазерных дальномеров
short int L, LF, F, RF, R;

int sensor = 850;
int v_f = 170;
int v_s = 160;
float speed_f = 50;

float k = 1.5;


void setup()
{
  Serial.begin(9600);

  //Конфигурация портов управления моторами
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);

  //Конфигурация порта стартового модуля
  pinMode(StartPin, INPUT);
  digitalWrite(StartPin, LOW);

  //Запуск шины I2C
  Wire.begin();
  Serial.println("START_SETUP");
  vlx_setup();
  Serial.println("END_SETUP");
  delay(500);
//Общее время после включения 5000мс (см.функцию vlx_setup)
  Serial.println("Ждём");
   digitalWrite(A2, HIGH);
  //Ждем сигнала от стартового модуля
  for (; digitalRead(StartPin) == 0;);
 digitalWrite(A2, LOW);

    vpered();
    delay(400);
    stopm();
    delay(1);
  
  
}
   
void loop()
{
  if (digitalRead(StartPin) == 1) //Проверяем был-ли дан старт с пульта 1-старт, 0-остановка
  {
    //Читаем датчики линии
    read_line();
    //Читаем лазерные датчики
    getVLX();

#if OTLADKA==1//Режим проверки датчиков
    Serial.print("IR_Left->");
    Serial.print(left_L);
    Serial.print(" IR_Right->");
    Serial.print(right_L);
    Serial.print(" L->");
    Serial.print(L);
    Serial.print(" LF->");
    Serial.print(LF);
    Serial.print(" F->");
    Serial.print(F);
    Serial.print(" RF->");
    Serial.print(RF);
    Serial.print(" R->");
    Serial.println(R);

#elif OTLADKA==2//Режим проверки моторов
    vpravo(150);
    delay(2000);
    stopm();
    delay(1000);
    vlevo(150);
    delay(2000);
    stopm();
    delay(1000);
#else//Рабочий режим
    //Serial.println("Рабочий режим");
    control_line(); //Контролируем выезд за границы полигона
    getVLX();
    poisk();//Выполняем поиск робота противника
#endif
  }
  else if (digitalRead(StartPin) == 0) //Нажата кнопка остановки поединка-стартовый модуль посылает 0
  {
    Serial.println("Стоп");
    stopm();
    delay(1);
  }
}
