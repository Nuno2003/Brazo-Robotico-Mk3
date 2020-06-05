//Esto es la calibración del brazo
void autoHome() {
  //variables para usar la funcion millis
  unsigned long intervalo = 100;
  unsigned long tiempoanterior;
  unsigned long tiempo = millis();

  int motorSpeed = 1200;
  int finHome = 0;//final de calibracion

  while (finHome == 0) {
    while (digitalRead(buttonPin) == LOW) {
      tiempo = millis();
      anticlockwise(1);
      clockwise(3);
      if (tiempo - tiempoanterior > intervalo) {
        Serial.print("Calibrando motores 1 y 3");
        Serial.println("...");
        Serial.println(digitalRead(buttonPin));
        tiempoanterior = tiempo;
      }
      tiempo = millis();
      delayMicroseconds(motorSpeed);
    }
    if (digitalRead(buttonPin) == HIGH) {
      
      Serial.println("Has calibrado los motores 1 y 3");
      delay(500);
      finHome = 1;
    }
  }
  while (finHome == 1) {
    tiempo = millis();
    anticlockwise(2);
    if (tiempo - tiempoanterior > intervalo) {
      Serial.println(digitalRead(button2Pin));
      Serial.print("Calibrando motor 2");
      Serial.println("...");
      tiempoanterior = tiempo;
    }
    delayMicroseconds(motorSpeed);
    if (digitalRead(button2Pin) == HIGH) {
      Serial.println("Has calibrado el motor 2");
      delay(500);
      finHome = 2;
    }

    while (finHome == 2) {
      Serial.println("Has calibrado el Brazo Robotico");
      delay(5000);
      //Establecemos que esas posiciones son el punto de partida de cada uno
      posAnterior1 = 0;
      posAnterior2 = 0;
      posAnterior3 = 180;
      AutoHome = 1;
      AutoBT = 1;
      finHome = 3;
    }
  }
}
