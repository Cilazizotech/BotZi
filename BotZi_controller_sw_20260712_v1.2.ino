/**************************************/
// BOTZI 2026 Conntroller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Beolvassuk a szervómotorok irányításához szükséges gyári könyvtárat

// Létrehozzuk a 4 darab szervómotor objektumot (elnevezzük őket)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// A joystickok analóg lábainak (pinjeinek) megadása az Arduinón
const int joy1X = A3; // 1-es joystick X tengely (vízszintes mozgás)
const int joy1Y = A2; // 1-es joystick Y tengely (függőleges mozgás)
const int joy2X = A1; // 2-es joystick X tengely
const int joy2Y = A0; // 2-es joystick Y tengely

// Megadjuk, hogy a szervómotorok melyik digitális lábakra (pinekre) vannak kötve
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Eltároljuk a szervók aktuális és legutóbbi helyzetét fokban (kezdésnek mind középen: 90 fok)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Holtjáték (Dead Zone) beállítása: ha a joystickot csak kicsit pöccintjük meg, vagy magától nem áll pontosan középre, 
// ez a biztonsági sáv megakadályozza, hogy a robotkar össze-vissza rángatózzon.
const int deadZone = 250; 

// Beállítjuk a mozgási sebességeket és a várakozási időket (késleltetéseket) a finom mozgásért
const int stepSize = 1;               // Egy lépésben hány fokot forduljon a motor
const int servoDelayTime = 14;         // Általános késleltetés ms-ban (10 és 20 között a legsimább)
const int servoGripperDelayTime = 10;  // A csipesz (gripper) szervójának sebessége
const int servoArm3DelayTime = 16;     // A 3-as számú kar szervójának sebessége
unsigned int servoGriperMoves = 0;     // Figyeli, hogy mozog-e épp a csipesz
unsigned int servoArm3Moves = 0;       // Figyeli, hogy mozog-e épp a 3-as kar

unsigned long lastMoveTime4 = 0; // Időzítő a csipeszmotor lekapcsolásához (hogy ne zúgjon feleslegesen)
bool isAttached4 = false;        // Figyeli, hogy a 4-es szervó épp kap-e áramot/jelet

// Ha a joystick pont fordítva működik, mint szeretnéd, ezt a sort kell kikommentezni vagy módosítani!
#define DIRECTION_ORIGINAL

void setup() {
  // Elindítjuk a rendszert, és összekötjük a kódbeli szervókat a fizikai lábakkal
  delay(500); // Várunk fél másodpercet, hogy az áramellátás stabilizálódjon az induláskor
  
  servo1.attach(servo1Pin);
  delay(200); // Kis szüneteket tartunk a motorok bekapcsolása között, hogy ne terheljük le hirtelen a tápot
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // Ha tesztelni szeretnéd a számítógépen, itt kapcsolhatod be a hibakereső monitort
}

void loop() {
  // Beolvassuk a joystickok aktuális állását (0 és 1023 közötti értéket adnak vissza)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // A joystick 0-1023 közötti jelét átszámoljuk (leképezzük) a szervóknak érthető 0-180 fokos tartományra
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Némelyik Arduino Nano máshogy értelmezi az irányokat. Ez az alapértelmezett irány beállítás:
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** Ha a kar fordítva mozog a joystickhoz képest, használd az alatta lévő #else részt!
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // A csipesz nyitási és zárási szöghatára fokban

  // --- SZERVÓK MOZGATÁSA ---
  // Megnézzük, hogy a joystick elmozdult-e a középállástól (512-től) jobban, mint a holtjáték (deadZone)

  // 1-es szervó mozgató blokk
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // Ha kisebb a szögünk, mint a cél, növeljük
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // Ha nagyobb, csökkentjük
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Kiküldjük az új pozíciót a szervónak
    }
    lastPos1 = currentPos1; // Elmentjük, hol álltunk legutóbb
  }

  // 2-es szervó mozgató blokk
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // 3-as szervó mozgató blokk
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Jelezzük a programnak, hogy a 3-as kar épp mozgásban van
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // 4-es szervó (csipesz) mozgató blokk
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Jelezzük, hogy mozdul a csipesz

      // Ha a csipesz szervója le volt választva (aludt), most újra aktiváljuk és áram alá helyezzük
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Elmentjük a mozgás pontos idejét az automatikus lekapcsoláshoz
    }
    lastPos4 = currentPos4;
  }

  // Itt lehetne kiíratni a pozíciókat a teszteléshez a számítógép képernyőjére:
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Szünetek és időzítések kezelése, hogy a robotkar mozgása folyamatos és szép legyen, ne pedig rángatózó
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Speciális várakozás a 3-as kar mozgása után
  }
  else {
    delay(servoDelayTime); // Általános kis szünet a lépések között
  }

  // AUTOMATIKUS LEKAPCSOLÁS: 
  // Ha a csipeszmotor nem mozog, de be van kapcsolva, a tartóáram miatt folyamatosan zúghat/melegedhet.
  // Ha eltelt 500 ezredmásodperc (fél másodperc) az utolsó mozgás óta, lekapcsoljuk róla a vezérlést (pihenő mód).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Lekapcsolás
      isAttached4 = false;
  }  
}