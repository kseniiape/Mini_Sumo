void vpered() //Движение вперед
{
  digitalWrite(M1_1, HIGH);   //Направление вращения мотора
  digitalWrite(M2_2, HIGH);   //Направление вращения мотора
  analogWrite (M1_2, 120);     //Скорость вращения мотора
  analogWrite (M2_1, 120);     //Скорость вращения мотора
}
void vpered_F(float speed_f) //Движение вперед на максимальной скорости
{
  digitalWrite(M1_1, HIGH);   //Направление вращения мотора
  digitalWrite(M2_2, HIGH);   //Направление вращения мотора
  analogWrite (M1_2, speed_f);      //Скорость вращения мотора
  analogWrite (M2_1, speed_f);      //Скорость вращения мотора
}

void vpered_max() //Движение вперед на максимальной скорости
{
  digitalWrite(M1_1, HIGH);   //Направление вращения мотора
  digitalWrite(M2_2, HIGH);   //Направление вращения мотора
  analogWrite (M1_2, 50);      //Скорость вращения мотора
  analogWrite (M2_1, 50);      //Скорость вращения мотора
}

void nazad() //Движение назад
{
  digitalWrite(M1_2, HIGH);   //Направление вращения мотора
  digitalWrite(M2_1, HIGH);   //Направление вращения мотора
  analogWrite (M1_1, 180);      //Скорость вращения мотора
  analogWrite (M2_2, 180);      //Скорость вращения мотора
}

void vlevo(byte speed_m) //Поворот влево
{
  digitalWrite(M1_1, HIGH);   //Направление вращения мотора
  digitalWrite(M2_1, HIGH);   //Направление вращения мотора
  analogWrite (M1_2, speed_m);      //Скорость вращения мотора
  analogWrite (M2_2, speed_m);      //Скорость вращения мотора
}

void vpravo(byte speed_m) //Поворот вправо
{
  digitalWrite(M1_2, HIGH);   //Направление вращения мотора
  digitalWrite(M2_2, HIGH);   //Направление вращения мотора
  analogWrite (M1_1, speed_m);      //Скорость вращения мотора
  analogWrite (M2_1, speed_m);      //Скорость вращения мотора
}

void stopm()                    //Останов моторов
{
  digitalWrite(M1_1, HIGH);  //Направление вращения мотора
  digitalWrite(M1_2, HIGH);   //Направление вращения мотора
  digitalWrite(M2_1, HIGH);   //Скорость вращения мотора
  digitalWrite(M2_2, HIGH);   //Скорость вращения мотора
}
