/**************************************/
// BOTZI 2026 Controller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Inclusion de la bibliothèque standard nécessaire au contrôle des servomoteurs

// Création des 4 objets pour les servomoteurs (nous leur donnons des noms)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Spécification des broches (pins) analogiques pour les joysticks sur l'Arduino
const int joy1X = A3; // Joystick 1 axe X (mouvement horizontal)
const int joy1Y = A2; // Joystick 1 axe Y (mouvement vertical)
const int joy2X = A1; // Joystick 2 axe X
const int joy2Y = A0; // Joystick 2 axe Y

// Spécification des broches (pins) numériques auxquelles les servomoteurs sont connectés
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Stockage de la position actuelle et de la dernière position des servos en degrés (au départ tous au centre : 90 degrés)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Configuration de la zone morte (Dead Zone) : si le joystick est à peine effleuré ou s'il ne revient pas 
// exactement au centre par lui-même, cette zone de sécurité empêche le bras robotisé de trembler ou de saccader.
const int deadZone = 250; 

// Configuration des vitesses de mouvement et des temps d'attente (délais) pour un mouvement fluide
const int stepSize = 1;               // De combien de degrés le moteur doit tourner en un seul pas
const int servoDelayTime = 14;         // Délai général en ms (le plus fluide se situe entre 10 et 20)
const int servoGripperDelayTime = 10;  // Vitesse du servo de la pince (gripper)
const int servoArm3DelayTime = 16;     // Vitesse du servo du bras numéro 3
unsigned int servoGriperMoves = 0;     // Surveille si la pince est actuellement en mouvement
unsigned int servoArm3Moves = 0;       // Surveille si le bras 3 est actuellement en mouvement

unsigned long lastMoveTime4 = 0; // Temporisateur pour couper le moteur de la pince (pour éviter qu'il ne bourdonne inutilement)
bool isAttached4 = false;        // Surveille si le servo 4 est actuellement alimenté/reçoit un signal

// Si le joystick fonctionne exactement à l'inverse de ce que vous souhaitez, il faut commenter ou modifier cette ligne !
#define DIRECTION_ORIGINAL

void setup() {
  // Démarrage du système et liaison des servos du code avec les broches physiques
  delay(500); // Attente d'une demi-seconde pour que l'alimentation se stabilise au démarrage
  
  servo1.attach(servo1Pin);
  delay(200); // Courtes pauses entre l'activation des moteurs pour ne pas surcharger subitement l'alimentation
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // Si vous souhaitez effectuer des tests sur l'ordinateur, vous pouvez activer le moniteur de débogage ici
}

void loop() {
  // Lecture de la position actuelle des joysticks (ils renvoient une valeur comprise entre 0 et 1023)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // Conversion (mappage) du signal 0-1023 du joystick vers la plage de 0-180 degrés compréhensible par les servos
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Certaines cartes Arduino Nano interprètent les directions différemment. C'est la configuration de direction par défaut :
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** Si le bras se déplace à l'inverse du joystick, utilisez la section #else ci-dessous !
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // Limite de l'angle d'ouverture et de fermeture de la pince en degrés

  // --- MOUVEMENT DES SERVOMOTEURS ---
  // Vérification si le joystick s'est écarté de la position centrale (512) plus que la zone morte (deadZone)

  // Bloc de mouvement du servo 1
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // Si notre angle est plus petit que la cible, on l'augmente
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // S'il est plus grand, on le diminue
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Envoi de la nouvelle position au servo
    }
    lastPos1 = currentPos1; // Sauvegarde de l'endroit où nous étions arrêtés la dernière fois
  }

  // Bloc de mouvement du servo 2
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // Bloc de mouvement du servo 3
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Indique au programme que le bras 3 est actuellement en mouvement
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // Bloc de mouvement du servo 4 (pince)
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Indique que la pince bouge

      // Si le servo de la pince était déconnecté (en veille), nous le réactivons et le mettons sous tension maintenant
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Sauvegarde du moment précis du mouvement pour la coupure automatique
    }
    lastPos4 = currentPos4;
  }

  // C'est ici que l'on pourrait afficher les positions sur l'écran de l'ordinateur pour les tests :
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Gestion des pauses et des synchronisations pour que le mouvement du bras robotisé soit continu et fluide, plutôt que saccadé
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Attente spéciale après le mouvement du bras 3
  }
  else {
    delay(servoDelayTime); // Petite pause générale entre les étapes
  }

  // COUPURE AUTOMATIQUE : 
  // Si le moteur de la pince ne bouge pas mais reste activé, il peut bourdonner/chauffer en permanence à cause du courant de maintien.
  // Si 500 millisecondes (une demi-seconde) se sont écoulées depuis le dernier mouvement, on désactive son contrôle (mode repos).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Déconnexion
      isAttached4 = false;
  }  
}