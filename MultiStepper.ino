#include <AccelStepper.h>

//Varibales de Ultrasonicos
const int Echo = 21;  // Echo del sensor de enfrente
const int Trig = 19;  // Trig del sensor de enfrente

const int EchoD = 2;   // Echo del sensor derecha
const int TrigD = 15;  // Trig del sensor derecha

const int EchoI = 23;  // Echo del sensor Izquierda
const int TrigI = 22;  // Trig del sensor Izquierda

AccelStepper motorI(4, 26, 33, 25, 32);
AccelStepper motorD(4, 27, 12, 14, 13);

int distanciaAdelante, distanciaDerecha, distanciaIzquierda;

void setup()
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(TrigD, OUTPUT);
  pinMode(EchoD, INPUT);

  pinMode(TrigI, OUTPUT);
  pinMode(EchoI, INPUT);

  Serial.begin(9600);
  Serial.println("Funcionando");
  // Configure each stepper
  motorI.setMaxSpeed(500);
  motorD.setMaxSpeed(500);

  motorI.setSpeed(500);
  motorD.setSpeed(500);

  motorI.setAcceleration(5000);
  motorD.setAcceleration(5000);
}

void loop()
{
  distanciaAdelante = ping(Trig, Echo);
  //Serial.println((String)distanciaAdelante);
  if (distanciaAdelante > 10)
  {
    adelante();
  }
  else
  {
    izquierda();
  }

  //  adelante();
  //  izquierda();
  //  derecha();
}

int ping(int TriggerPin, int EchoPin)
{
  long duracion, distanciaCm;

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duracion = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

  distanciaCm = duracion * 10 / 292 / 2;  //convertimos a distancia, en cm
  return distanciaCm;
}

void adelante()
{
  motorI.move(-1024);
  motorD.move(-1024);
  while (motorI.distanceToGo() != 0)
  {
    motorI.run();
    motorD.run();
  }
}

void izquierda()
{
  motorI.move(512);
  motorD.move(-512);
  while (motorI.distanceToGo() != 0)
  {
    motorI.run();
    motorD.run();
  }
}

void derecha()
{
  motorI.move(-512);
  motorD.move(512);
  while (motorI.distanceToGo() != 0)
  {
    motorI.run();
    motorD.run();
  }
}
