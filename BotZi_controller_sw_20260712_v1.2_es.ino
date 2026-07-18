/**************************************/
// BOTZI 2026 Controller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Incluimos la librería estándar necesaria para el control de los servomotores

// Creamos los 4 objetos para los servomotores (les asignamos nombres)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Especificación de los pines analógicos para los joysticks en el Arduino
const int joy1X = A3; // Joystick 1 eje X (movimiento horizontal)
const int joy1Y = A2; // Joystick 1 eje Y (movimiento vertical)
const int joy2X = A1; // Joystick 2 eje X
const int joy2Y = A0; // Joystick 2 eje Y

// Especificamos a qué pines digitales están conectados los servomotores
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Almacenamos la posición actual y la última posición de los servos en grados (al principio todos al centro: 90 grados)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Configuración de la zona muerta (Dead Zone): si el joystick se mueve solo un poco, o no regresa exactamente 
// al centro por sí mismo, esta zona de seguridad evita que el brazo robótico tiemble o se mueva sin control.
const int deadZone = 250; 

// Configuramos las velocidades de movimiento y los tiempos de espera (retardos) para un movimiento suave
const int stepSize = 1;               // Cuántos grados debe girar el motor en un solo paso
const int servoDelayTime = 14;         // Retardo general en ms (el más suave es entre 10 y 20)
const int servoGripperDelayTime = 10;  // Velocidad del servo de la pinza (gripper)
const int servoArm3DelayTime = 16;     // Velocidad del servo del brazo número 3
unsigned int servoGriperMoves = 0;     // Monitorea si la pinza se está moviendo en este momento
unsigned int servoArm3Moves = 0;       // Monitorea si el brazo 3 se está moviendo en este momento

unsigned long lastMoveTime4 = 0; // Temporizador para apagar el motor de la pinza (para que no zumbe innecesariamente)
bool isAttached4 = false;        // Monitorea si el servo 4 está recibiendo corriente/señal en este momento

// ¡Si el joystick funciona exactamente al revés de lo que deseas, debes comentar o modificar esta línea!
#define DIRECTION_ORIGINAL

void setup() {
  // Iniciamos el sistema y conectamos los servos del código con los pines físicos
  delay(500); // Esperamos medio segundo para que la fuente de alimentación se estabilice al arrancar
  
  servo1.attach(servo1Pin);
  delay(200); // Mantenemos breves pausas entre el encendido de los motores para no sobrecargar repentinamente la fuente
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // Si deseas realizar pruebas en la computadora, aquí puedes activar el monitor de depuración
}

void loop() {
  // Leemos la posición del momento de los joysticks (devuelven un valor entre 0 y 1023)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // Convertimos (mapeamos) la señal de 0-1023 del joystick al rango de 0-180 grados que entienden los servos
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Algunas placas Arduino Nano interpretan las direcciones de manera diferente. Esta es la configuración de dirección por defecto:
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** ¡Si el brazo se mueve al revés respecto al joystick, usa la sección #else de abajo!
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // Límite del ángulo de apertura y cierre de la pinza en grados

  // --- MOVIMIENTO DE LOS SERVOS ---
  // Verificamos si el joystick se ha desplazado de la posición central (512) más allá de la zona muerta (deadZone)

  // Bloque de movimiento del servo 1
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // Si nuestro ángulo es menor que el objetivo, lo aumentamos
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // Si es mayor, lo disminuimos
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Enviamos la nueva posición al servo
    }
    lastPos1 = currentPos1; // Guardamos dónde estábamos parados la última vez
  }

  // Bloque de movimiento del servo 2
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // Bloque de movimiento del servo 3
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Indicamos al programa que el brazo 3 está actualmente en movimiento
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // Bloque de movimiento del servo 4 (pinza)
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Indicamos que la pinza se está moviendo

      // Si el servo de la pinza estaba desconectado (durmiendo), ahora lo reactivamos y le suministramos corriente
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Guardamos el tiempo exacto del movimiento para el apagado automático
    }
    lastPos4 = currentPos4;
  }

  // Aquí se podrían imprimir las posiciones en la pantalla de la computadora para realizar pruebas:
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Manejo de pausas y tiempos para que el movimiento del brazo robótico sea continuo y fluido, en lugar de brusco
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Espera especial después del movimiento del brazo 3
  }
  else {
    delay(servoDelayTime); // Pequeña pausa general entre pasos
  }

  // APAGADO AUTOMÁTICO: 
  // Si el motor de la pinza no se mueve pero está encendido, debido a la corriente de mantenimiento puede zumbar/calentarse constantemente.
  // Si han pasado 500 milisegundos (medio segundo) desde el último movimiento, desconectamos su control (modo de reposo).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Desconexión
      isAttached4 = false;
  }  
}