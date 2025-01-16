void poisk()
{
  //Робот противника спереди близко
  if (F < 300 && F > 2)
  {
    
    //if (napr != 12)
    old_napr = napr;
    napr = 12;
    vpered_max();
     while (F > 2 && F < 60) {
      if (speed_f > 30) {
        speed_f = speed_f - k;
        vpered_F(speed_f);
        k = k + 1;
      }
      else {
        vpered_F(30);
      }
    }
    speed_f = 50;
    k = 1;
  }
  
    //Робот противника спереди далеко
  else if (F < 500 && F >=300)
  {
    //if (napr != 12)
    old_napr = napr;
    napr = 12;
    vpered();
    //stopm();
  }
 
  else if (R< 500 && R > 2)
  {
    napr = 3;
    vpravo(v_s);
  }
  else if (LF< 500 && LF > 2)
  {
    napr = 11;
    vlevo(v_f);
  }
  //Робот противника слева
  else if (L < 500 && L > 2)
  {
    napr = 9;
    vlevo(v_s);
  }
   /*//Робот противника справа
    else if (RF< 500 && RF > 2)
  {
    napr = 2;
    vpravo(v_f);
  }*/
  
  //Робот противника не обнаружен
  else if (F>= 500 && R>= 500 && L>= 500  && LF>=500)
  {
    //Робот ещё не видел противника ни разу
    if (napr == 0) {
      vpered_F(160);
    }
    //Раньше робот противника был слева
    else if (napr == 9) vlevo(170);
    //Раньше робот противника был справа
    else if (napr == 3) vpravo(170);
    //Раньше робот противника был спереди
    else if (napr == 12)
    {
      //Робот противника ехал справа
      if (old_napr == 3) vlevo(180);
      //Робот противника ехал слева
      else if (old_napr == 2) vlevo(190);
      else if (old_napr == 9) vpravo(180);
      else if (old_napr == 11) vpravo(190);
      else vpered();
      //Serial.println("Пока не знаю");
    }
  }
}

void read_line()
{
  //Читаем датчики линии
  left_L = analogRead(A7);
  right_L = analogRead(A6);
}   
void control_line()
{
  // Действия при выезде робота за границы ринга
  if (right_L < sensor && left_L < sensor)
  {
    stopm();
    nazad();
    delay(500);
    vpravo(150);
    delay(400);
    vpered();
  }
  else if (left_L < sensor && right_L > sensor) //Робот выехал за пределы ринга левым передним углом
  {
    stopm();
    nazad();
    delay(200);
    vpravo(150);
    delay(300);
    vpered();
  }
  else if (right_L < sensor && left_L > sensor) //Робот выехал за пределы ринга правым передним углом
  {
    stopm();
    nazad();
    delay(200);
    vlevo(150);
    delay(300);
    vpered();
  }


}

void getVLX()
{
  //Читаем лазерные датчики и ограничиваем их показания
  L = vlxL.readRangeContinuousMillimeters();
  LF = vlxLF.readRangeContinuousMillimeters();
  F = vlxF.readRangeContinuousMillimeters();
  RF = vlxRF.readRangeContinuousMillimeters();
  R = vlxR.readRangeContinuousMillimeters();
}

void vlx_setup()
{
  //Конфигурация портов для программирования лазерных дальномеров
  pinMode(XSHUT_pinL, OUTPUT);
  pinMode(XSHUT_pinLF, OUTPUT);
  pinMode(XSHUT_pinF, OUTPUT);
  pinMode(XSHUT_pinRF, OUTPUT);
  pinMode(XSHUT_pinR, OUTPUT);


  digitalWrite(XSHUT_pinL, LOW);
  digitalWrite(XSHUT_pinLF, LOW);
  digitalWrite(XSHUT_pinF, LOW);
  digitalWrite(XSHUT_pinRF, LOW);
  digitalWrite(XSHUT_pinR, LOW);
  delay(10);

  digitalWrite(XSHUT_pinL, HIGH);
  delay(100);
  vlxL.setAddress(SensorL_newAddress);
  vlxL.init();

  digitalWrite(XSHUT_pinLF, HIGH);
  delay(100);
  vlxLF.setAddress(SensorLF_newAddress);
  vlxLF.init();

  digitalWrite(XSHUT_pinF, HIGH);
  delay(100);
  vlxF.setAddress(SensorF_newAddress);
  vlxF.init();

  digitalWrite(XSHUT_pinRF, HIGH);
  delay(100);
  vlxRF.setAddress(SensorRF_newAddress);
  vlxRF.init();

  digitalWrite(XSHUT_pinR, HIGH);
  delay(100);
  vlxR.setAddress(SensorR_newAddress);
  vlxR.init();

  delay(1500);
  vlxL.setTimeout(50);
  vlxLF.setTimeout(50);
  vlxF.setTimeout(50);
  vlxRF.setTimeout(50);
  vlxR.setTimeout(50);

  vlxL.startContinuous();
  vlxLF.startContinuous();
  vlxF.startContinuous();
  vlxRF.startContinuous();
  vlxR.startContinuous();
}
