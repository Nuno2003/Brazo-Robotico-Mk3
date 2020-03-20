#include <Servo.h>
Servo pinza;

const int motor1Pin1 = 28;  // 28BYJ48 In1
const int motor1Pin2 = 26; // 28BYJ48 In2
const int motor1Pin3 = 24;   // 28BYJ48 In3
const int motor1Pin4 = 22;   // 28BYJ48 In4

const int motor2Pin1 = 30;  // 28BYJ48 In1
const int motor2Pin2 = 32;  // 28BYJ48 In2
const int motor2Pin3 = 34;   // 28BYJ48 In3
const int motor2Pin4 = 36;   // 28BYJ48 In4

const int motor3Pin1 = 42;  // 28BYJ48 In1
const int motor3Pin2 = 44;  // 28BYJ48 In2
const int motor3Pin3 = 46;   // 28BYJ48 In3
const int motor3Pin4 = 48;   // 28BYJ48 In4

const int pot1Pin = A0;
const int pot2Pin = A1;
const int pot3Pin = A2;
const int pot4Pin = A3;

int stepCounter1 = 0;  // contador para los pasos
int stepCounter2 = 0;  // contador para los pasos
int stepCounter3 = 0;  // contador para los pasos

// posicion en grados
int posAnterior1 = 0; // almacena la posicion anterior

int posAnterior2 = 0; // almacena la posicion anterior

int posAnterior3 = 0; // almacena la posicion anterior

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

// Variables comunicacion
int incomingByte;   // variable para leer los bytes de entrada


void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin3, OUTPUT);
  pinMode(motor1Pin4, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);

  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor3Pin3, OUTPUT);
  pinMode(motor3Pin4, OUTPUT);
  pinza.attach(3);  // Definimos el pin de señal para el servo
  //declarar pines como salida
  Serial.begin(9600);
}

void loop() {


  int pot1Value = analogRead(pot1Pin);
  int  angle1 = map(pot1Value, 0, 1023, 0, 280);
  if (abs(angle1 - posAnterior1) > 5)posicionar(1, angle1, posAnterior1);

  int  pot2Value = analogRead(pot2Pin);
  int  angle2 = map(pot2Value, 0, 1023, 0, 330);
  if (abs(angle2 - posAnterior2) > 5)posicionar(2, angle2, posAnterior2);

  int pot3Value = analogRead(pot3Pin);
  int  angle3 = map(pot3Value, 0, 1023, 0, 200);
  if (abs(angle3 - posAnterior3) > 5)posicionar(3, angle3, posAnterior3);

  int angle4 = map(analogRead(pot4Pin), 0, 1023, 0, 75);
  servo(angle4);

  apagado();
  delay(20);
}

void servo(int angulo4) {
  // valor proporcional a la escala del servomotor (valor entre 0 y 180)
  pinza.write(angulo4);
  // angle4 = pot4Value; sobra
  delay(15); // Esperamos para reiniciar el bucle
}

void posicionar(int motor, int pos, int posAnterior) {
  int motorSpeed = 1200;   //variable para fijar la velocidad
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
