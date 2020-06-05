void controlBT() {
  while (AutoBT == 0) {
    autoHome();
  }
  if ( AutoBT == 1) {
    Serial.println("Has entrado en el modo BT");
    AutoBT = 2;
  }
  char incomingByte;   // variable para leer los bytes de entrada
  if (Serial.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = Serial.read();
    // si es un caracter ASCII entre 0 y 9
    if (incomingByte >= '0' && incomingByte <= '9') {
      //Acumula los datos numericos multiplicando por 10 el valor acumulado
      value = (value * 10) + (incomingByte - '0'); // Resta 48 que es el valor decimal del 0 ASCII
    }
    //Dependiendo de la letra que reciba se activará un motor u otro
    if (incomingByte == 'A') {
      if (value >= 250)value = posAnterior1 ;
      posicionar(1, value, posAnterior1);
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
    if (incomingByte == 'B') {
      if (value >= 350)value = posAnterior2;
      posicionar(2, value, posAnterior2);
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
    if (incomingByte == 'C') {
      if (value >= 400)value = 240;
      posicionar(3, value, posAnterior3);
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
    if (incomingByte == 'D') {
      servo(value);
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
    //Cuando recibe la E significa que ha cambiado de modo de control por bluetooth y por tanto tiene que calibrarse
    if (incomingByte == 'E')AutoBT = 0;
  }
}
