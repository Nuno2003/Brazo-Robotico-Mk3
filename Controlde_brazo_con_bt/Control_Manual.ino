void manualPot() {
  while (AutoHome == 0) {
    autoHome();
  }
  if (AutoHome == 1) {
    Serial.println("Coloca los potenciometros en posicion 0");
    AutoHome = 2;
  }
  int pot1Value = analogRead(pot1Pin);
  int  angle1 = map(pot1Value, 0, 1023, 0, 280); //El límite de giro de este motor es de 280º
  if (abs(angle1 - posAnterior1) > 5)posicionar(1, angle1, posAnterior1);

  int  pot2Value = analogRead(pot2Pin);
  int  angle2 = map(pot2Value, 0, 1023, 0, 330);//El límite de giro de este motor es de 330º
  if (abs(angle2 - posAnterior2) > 5)posicionar(2, angle2, posAnterior2);

  int pot3Value = analogRead(pot3Pin);
  int  angle3 = map(pot3Value, 0, 1023, 0, 180);//El límite de giro de este motor es de 180º
  if (abs(angle3 - posAnterior3) > 5)posicionar(3, angle3, posAnterior3);

  int angle4 = map(analogRead(pot4Pin), 0, 1023, 0, 75); 
  servo(angle4);
  delay(20);
}
