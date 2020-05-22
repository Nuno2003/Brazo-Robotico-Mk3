/*
  BRAZO ROBÓTICO
  Código creado por Nuno José del Pino Escalante
  Marzo-Abril 2020
  IES Vicente aleixandre
*/

#include <Servo.h>
Servo pinza;
//Pines de conexión
//MOTOR 1
const int motor1Pin1 = 28;  // 28BYJ48 In1
const int motor1Pin2 = 26; // 28BYJ48 In2
const int motor1Pin3 = 24;   // 28BYJ48 In3
const int motor1Pin4 = 22;   // 28BYJ48 In4
//MOTOR 2
const int motor2Pin1 = 30;  // 28BYJ48 In1
const int motor2Pin2 = 32;  // 28BYJ48 In2
const int motor2Pin3 = 34;   // 28BYJ48 In3
const int motor2Pin4 = 36;   // 28BYJ48 In4
//MOTOR 3
const int motor3Pin1 = 42;  // 28BYJ48 In1
const int motor3Pin2 = 44;  // 28BYJ48 In2
const int motor3Pin3 = 46;   // 28BYJ48 In3
const int motor3Pin4 = 48;   // 28BYJ48 In4
//POTENCIOMETROS
const int pot1Pin = A0;
const int pot2Pin = A1;
const int pot3Pin = A2;
const int pot4Pin = A3;
//FINALES DE CARRERA
const int buttonPin = 3;
const int button2Pin = 4;
//BOTÓN PARA CAMBIAR DE MODO
const int button3Pin = 5;

//VARIABLES GENERALES
int stepCounter1 = 0;  // contador para los pasos del motor 1
int stepCounter2 = 0;  // contador para los pasos del motor 2
int stepCounter3 = 0;  // contador para los pasos del motor 3

//AutoHome para calibrar después de cambiar de modo
int AutoHome = 0;
int AutoBT = 0;

// Posición en grados
int posAnterior1 = 0; // almacena la posicion anterior
int posAnterior2 = 0; // almacena la posicion anterior
int posAnterior3 = 0; // almacena la posicion anterior

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

// Variable comunicacion
int value = 0;

//contador para cambiar de modos
int contador = 1;

void setup() {
  //declarar pines como entrada
  //Finales de carrera
  //usan "INPUT_PULLUP" para evitar tener que usar una resistencia, ya que arduino tiene una la cual se puede usar con esa función
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  //Botón para seleccionar los modos
  pinMode(button3Pin, INPUT);

  //declarar pines como salida
  //MOTOR 1
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin3, OUTPUT);
  pinMode(motor1Pin4, OUTPUT);
  //MOTOR 2
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  //MOTOR 3
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor3Pin3, OUTPUT);
  pinMode(motor3Pin4, OUTPUT);

  //Definimos el pin del servo de la pinza
  pinza.attach(2);

  //Abrimos el puerto serie
  Serial.begin(115200); //Está a esa velocidad ya que nuestro módulo bluetooth trabaja en esa velocidad

  //Iniciamos la calibración del brazo
  autoHome();

}


void loop() {
  //Cambio de modos
  if (digitalRead(button3Pin) == HIGH) {
    contador++ ;
    if (contador == 3) {
      contador = 1;
    }
    delay(500);
  }
  if (contador == 1) {
    manualPot(); //Modo manual
    AutoBT = 0;
  }
  if (contador == 2) {
    controlBT(); //Modo BT
    AutoHome = 0;
  }
  apagado();
}

void servo(int angulo4) { //Posicionamiento del servo
  pinza.write(angulo4);
  delay(15); // Esperamos para reiniciar el bucle
}

void posicionar(int motor, int pos, int posAnterior) { //Posicionamiento de los motores paso a paso
  int motorSpeed = 1200; //variable para fijar la velocidad
  // Numero de pasos a dar 4076 pasos es una vuelta
  float steps = (abs(pos - posAnterior)) * 4076.0 / 360.0;
  int stepsInt = int(steps);
  for (int i = 0; i < stepsInt; i++) {
    if (pos - posAnterior > 0) {
      clockwise(motor);
    }
    else {
      anticlockwise(motor);
    }
    // tiempo de espera para regular velocidad del motor
    delayMicroseconds(motorSpeed);
  }
  if (motor == 1)posAnterior1 = pos;
  if (motor == 2)posAnterior2 = pos;
  if (motor == 3)posAnterior3 = pos;
}

void clockwise(int motor) { //sentido de giro horario
  if (motor == 1) {
    stepCounter1++;
    if (stepCounter1 >= numSteps) stepCounter1 = 0;
    setOutput(motor1Pin1, motor1Pin2, motor1Pin3, motor1Pin4, stepCounter1);
  }
  if (motor == 2) {
    stepCounter2++;
    if (stepCounter2 >= numSteps) stepCounter2 = 0;
    setOutput(motor2Pin1, motor2Pin2, motor2Pin3, motor2Pin4, stepCounter2);
  }
  if (motor == 3) {
    stepCounter3++;
    if (stepCounter3 >= numSteps) stepCounter3 = 0;
    setOutput(motor3Pin1, motor3Pin2, motor3Pin3, motor3Pin4, stepCounter3);
  }
}

void anticlockwise(int motor) { //sentido de giro antihorario
  if (motor == 1) {
    stepCounter1--;
    if (stepCounter1 < 0) stepCounter1 = numSteps - 1;
    setOutput(motor1Pin1, motor1Pin2, motor1Pin3, motor1Pin4, stepCounter1);
  }
  if (motor == 2) {
    stepCounter2--;
    if (stepCounter2 < 0) stepCounter2 = numSteps - 1;
    setOutput(motor2Pin1, motor2Pin2, motor2Pin3, motor2Pin4, stepCounter2);
  }
  if (motor == 3) {
    stepCounter3--;
    if (stepCounter3 < 0) stepCounter3 = numSteps - 1;
    setOutput(motor3Pin1, motor3Pin2, motor3Pin3, motor3Pin4 , stepCounter3);
  }
}

void setOutput(int motorPin1, int motorPin2, int motorPin3, int motorPin4 , int step) {
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0)); // lee el primer bit
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1)); // lee el segundo bit
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2)); // lee el tercer bit
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3)); // lee el cuarto bit
}

void apagado() {  //apaga el motor para evitar que se sobrecaliente
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin3, LOW);
  digitalWrite(motor1Pin4, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor3Pin3, LOW);
  digitalWrite(motor3Pin4, LOW);
}
