/**************************************/
// BOTZI 2026 Controller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Einlesen der Standardbibliothek, die für die Steuerung der Servomotoren benötigt wird

// Erstellen der 4 Servomotor-Objekte (wir benennen sie)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Angabe der analogen Pins für die Joysticks auf dem Arduino
const int joy1X = A3; // Joystick 1 X-Achse (horizontale Bewegung)
const int joy1Y = A2; // Joystick 1 Y-Achse (vertikale Bewegung)
const int joy2X = A1; // Joystick 2 X-Achse
const int joy2Y = A0; // Joystick 2 Y-Achse

// Angabe, an welchen digitalen Pins die Servomotoren angeschlossen sind
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Speichern der aktuellen und letzten Positionen der Servos in Grad (zu Beginn alle in der Mitte: 90 Grad)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Totzone (Dead Zone) Einstellung: Wenn der Joystick nur leicht angetippt wird oder von selbst nicht 
// exakt in die Mitte zurückkehrt, verhindert diese Sicherheitszone, dass der Roboterarm unkontrolliert ruckelt.
const int deadZone = 250; 

// Einstellen der Bewegungsgeschwindigkeiten und Verzögerungszeiten für eine flüssige Bewegung
const int stepSize = 1;               // Um wie viel Grad sich der Motor pro Schritt drehen soll
const int servoDelayTime = 14;         // Allgemeine Verzögerung in ms (am flüssigsten zwischen 10 und 20)
const int servoGripperDelayTime = 10;  // Geschwindigkeit des Greifer-Servos
const int servoArm3DelayTime = 16;     // Geschwindigkeit des Arm-Servos Nummer 3
unsigned int servoGriperMoves = 0;     // Überwacht, ob sich der Greifer gerade bewegt
unsigned int servoArm3Moves = 0;       // Überwacht, ob sich Arm 3 gerade bewegt

unsigned long lastMoveTime4 = 0; // Timer zum Abschalten des Greifermotors (damit er nicht unnötig summt)
bool isAttached4 = false;        // Überwacht, ob Servo 4 gerade Strom/Signal erhält

// Wenn der Joystick genau umgekehrt funktioniert als gewünscht, muss diese Zeile auskommentiert oder geändert werden!
#define DIRECTION_ORIGINAL

void setup() {
  // Das System starten und die Servos im Code mit den physischen Pins verbinden
  delay(500); // Eine halbe Sekunde warten, damit sich die Stromversorgung beim Start stabilisiert
  
  servo1.attach(servo1Pin);
  delay(200); // Kurze Pausen zwischen dem Einschalten der Motoren einlegen, um die Stromversorgung nicht plötzlich zu überlasten
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // Wenn Sie am Computer testen möchten, können Sie hier den Debug-Monitor aktivieren
}

void loop() {
  // Einlesen der aktuellen Position der Joysticks (sie geben einen Wert zwischen 0 und 1023 zurück)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // Das 0-1023 Joystick-Signal in den für die Servos verständlichen Bereich von 0-180 Grad umrechnen (skalieren)
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Einige Arduino Nano-Boards interpretieren die Richtungen anders. Dies ist die Standard-Richtungseinstellung:
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** Wenn sich der Arm entgegengesetzt zum Joystick bewegt, verwenden Sie den #else-Teil unten!
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // Öffnungs- und Schließwinkelbegrenzung des Greifers in Grad

  // --- BEWEGUNG DER SERVOS ---
  // Prüfen, ob sich der Joystick weiter von der Mittelstellung (512) wegbewegt hat als die Totzone (deadZone)

  // Bewegungskblock für Servo 1
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // Wenn unser Winkel kleiner als das Ziel ist, erhöhen wir ihn
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // Wenn er größer ist, verringern wir ihn
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Senden der neuen Position an den Servo
    }
    lastPos1 = currentPos1; // Speichern, wo wir beim letzten Mal standen
  }

  // Bewegungskblock für Servo 2
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // Bewegungskblock für Servo 3
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Dem Programm signalisieren, dass sich Arm 3 gerade in Bewegung befindet
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // Bewegungskblock für Servo 4 (Greifer)
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Signalisieren, dass sich der Greifer bewegt

      // Wenn der Servo des Greifers getrennt war (im Ruhezustand), aktivieren wir ihn jetzt wieder und setzen ihn unter Strom
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Die genaue Zeit der Bewegung für die automatische Abschaltung speichern
    }
    lastPos4 = currentPos4;
  }

  // Hier könnten die Positionen zum Testen auf dem Computerbildschirm ausgegeben werden:
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Verwalten von Pausen und Timings, damit die Bewegung des Roboterarms kontinuierlich und schön bleibt und nicht ruckelt
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Spezielles Warten nach der Bewegung von Arm 3
  }
  else {
    delay(servoDelayTime); // Allgemeine kleine Pause zwischen den Schritten
  }

  // AUTOMATISCHE ABSCHALTUNG: 
  // Wenn der Greifermotor sich nicht bewegt, aber eingeschaltet ist, kann er aufgrund des Haltestroms ständig summen/heiß werden.
  // Wenn seit der letzten Bewegung 500 Millisekunden (eine halbe Sekunde) vergangen sind, schalten wir die Steuerung ab (Ruhemodus).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Abschalten / Trennen
      isAttached4 = false;
  }  
}