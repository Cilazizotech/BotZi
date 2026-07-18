/**************************************/
// BOTZI 2026 Controller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Includiamo la libreria standard necessaria per il controllo dei servomotori

// Creiamo i 4 oggetti per i servomotori (assegniamo loro dei nomi)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Specificazione dei pin analogici per i joystick sull'Arduino
const int joy1X = A3; // Joystick 1 asse X (movimento orizzontale)
const int joy1Y = A2; // Joystick 1 asse Y (movimento verticale)
const int joy2X = A1; // Joystick 2 asse X
const int joy2Y = A0; // Joystick 2 asse Y

// Specifichiamo a quali pin digitali sono collegati i servomotori
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Memorizziamo la posizione attuale e l'ultima posizione dei servo in gradi (all'inizio tutti al centro: 90 gradi)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Configurazione della zona morta (Dead Zone): se il joystick viene solo sfiorato, o non torna esattamente 
// al centro da solo, questa zona di sicurezza impedisce al braccio robotico di oscillare o muoversi a scatti.
const int deadZone = 250; 

// Configuriamo le velocità di movimento e i tempi di attesa (ritardi) per un movimento fluido
const int stepSize = 1;               // Di quanti gradi deve ruotare il motore in un singolo passo
const int servoDelayTime = 14;         // Ritardo generale in ms (il più fluido è tra 10 e 20)
const int servoGripperDelayTime = 10;  // Velocità del servo della pinza (gripper)
const int servoArm3DelayTime = 16;     // Velocità del servo del braccio numero 3
unsigned int servoGriperMoves = 0;     // Monitora se la pinza si sta muovendo in questo momento
unsigned int servoArm3Moves = 0;       // Monitora se il braccio 3 si sta muovendo in questo momento

unsigned long lastMoveTime4 = 0; // Timer per spegnere il motore della pinza (per evitare che ronzi inutilmente)
bool isAttached4 = false;        // Monitora se il servo 4 sta ricevendo corrente/segnale in questo momento

// Se il joystick funziona esattamente al contrario di quanto desideri, questa riga va commentata o modificata!
#define DIRECTION_ORIGINAL

void setup() {
  // Avviamo il sistema e colleghiamo i servo del codice con i pin fisici
  delay(500); // Attendiamo mezzo secondo affinché l'alimentazione si stabilizzi all'avvio
  
  servo1.attach(servo1Pin);
  delay(200); // Manteniamo brevi pause tra l'accensione dei motori per non sovraccaricare improvvisamente l'alimentatore
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // Se desideri effettuare test sul computer, qui puoi attivare il monitor di debug
}

void loop() {
  // Leggiamo la posizione attuale dei joystick (restituiscono un valore compreso tra 0 e 1023)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // Convertiamo (mappiamo) il segnale 0-1023 del joystick nell'intervallo 0-180 gradi comprensibile dai servo
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Alcune schede Arduino Nano interpretano le direzioni in modo diverso. Questa è la configurazione di direzione predefinita:
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** Se il braccio si muove al contrario rispetto al joystick, usa la sezione #else sottostante!
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // Limite dell'angolo di apertura e chiusura della pinza in gradi

  // --- MOVIMENTO DEI SERVO ---
  // Verifichiamo se il joystick si è spostato dalla posizione centrale (512) più della zona morta (deadZone)

  // Blocco di movimento del servo 1
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // Se il nostro angolo è minore del target, lo aumentiamo
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // Se è maggiore, lo diminuiamo
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Inviamo la nuova posizione al servo
    }
    lastPos1 = currentPos1; // Salviamo dove eravamo rimasti l'ultima volta
  }

  // Blocco di movimento del servo 2
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // Blocco di movimento del servo 3
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Indichiamo al programma che il braccio 3 è attualmente in movimento
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // Blocco di movimento del servo 4 (pinza)
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Indichiamo che la pinza si sta muovendo

      // Se il servo della pinza era scollegato (in modalità sleep), ora lo riattiviamo e lo alimentiamo
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Salviamo il tempo esatto del movimento per lo spegnimento automatico
    }
    lastPos4 = currentPos4;
  }

  // Qui si potrebbero stampare le posizioni sullo schermo del computer per effettuare dei test:
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Gestione di pause e tempistiche per fare in modo che il movimento del braccio robotico sia continuo e fluido, invece che a scatti
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Attesa speciale dopo il movimento del braccio 3
  }
  else {
    delay(servoDelayTime); // Piccola pausa generale tra i passaggi
  }

  // SPEGNIMENTO AUTOMATICO: 
  // Se il motore della pinza non si muove ma è acceso, a causa della corrente di mantenimento può ronzare/riscaldarsi costantemente.
  // Se sono passati 500 millisecondi (mezzo secondo) dall'ultimo movimento, colleghiamo il controllo (modalità riposo).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Scollegamento
      isAttached4 = false;
  }  
}