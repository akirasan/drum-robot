/*
  DrumRobot
  by akirasan  ENE 2017

  www.akirasan.net
  Twitter: @akirasan
*/

#include <Servo.h>

Servo baqueta_izq;
Servo baqueta_der;

// Calibración de servos: modificar en función de la posición.
// La baqueta puede tener tres posiciones:
//
//          \       drum_max (altura máxima baqueta)
//           \
//            \
//    --------- ||  drum_med (a mitad del recorrido)
//            / ||
//           /  ||
//              ||  drum_corto (poca distancia del tambor: redoble)
//  (||||||||)      drum_min (TOCA el tambor)
//  |||||||||| DRUM

byte l_baqueta_izq_drum_min = 40;     // toca tambor
byte l_baqueta_izq_drum_max = 10;     // no toca tambor posición alta
byte l_baqueta_izq_drum_med = 30;     // no toca tambor posición media
byte l_baqueta_izq_drum_corto = 20;   // no toca tambor posición corto

byte l_baqueta_der_drum_min = 5;      // toca tambor
byte l_baqueta_der_drum_max = 35;     // no toca tambor
byte l_baqueta_der_drum_med = 25;     // no toca tambor
byte l_baqueta_der_drum_corto = 15;   // no toca tambor


// Definición de los PIN's donde tenemos conectados los servos
byte baqueta_izq_pin = 9;
byte baqueta_der_pin = 10;


//Las dos baquetas bajan a la vez
void all_baquetas_drums(float seg) {
  baqueta_izq.write(l_baqueta_izq_drum_min);
  baqueta_der.write(l_baqueta_der_drum_min);
  delay(100);
  baqueta_izq.write(l_baqueta_izq_drum_max);
  baqueta_der.write(l_baqueta_der_drum_max);
  delay(seg * 1000);
}

//Las dos baquetas suben a la vez al maximo
void all_baquetas_nodrums(float seg) {
  baqueta_izq.write(l_baqueta_izq_drum_max);
  baqueta_der.write(l_baqueta_der_drum_max);
  delay(seg * 1000);
}


void baqueta_izq_drum_max(float seg) {
  baqueta_izq.write(l_baqueta_izq_drum_min);
  delay(100);
  baqueta_izq.write(l_baqueta_izq_drum_max);
  delay(seg * 1000);
}

void baqueta_der_drum_max(float seg) {
  baqueta_der.write(l_baqueta_der_drum_min);
  delay(100);
  baqueta_der.write(l_baqueta_der_drum_max);
  delay(seg * 1000);
}


void baqueta_izq_drum_corto(float seg) {
  baqueta_izq.write(l_baqueta_izq_drum_min);
  delay(40);
  baqueta_izq.write(l_baqueta_izq_drum_corto);
  delay(seg * 1000);
}

void baqueta_der_drum_corto(float seg) {
  baqueta_der.write(l_baqueta_der_drum_min);
  delay(40);
  baqueta_der.write(l_baqueta_der_drum_corto);
  delay(seg * 1000);
}


void baqueta_izq_drum_medio(float seg) {
  baqueta_izq.write(l_baqueta_izq_drum_min);
  delay(95);
  baqueta_izq.write(l_baqueta_izq_drum_med);
  delay(seg * 1000);
}

void baqueta_der_drum_medio(float seg) {
  baqueta_der.write(l_baqueta_der_drum_min);
  delay(90);
  baqueta_der.write(l_baqueta_der_drum_med);
  delay(seg * 1000);
}


// le pasaremos como parámetro el número toques
void redoble(int n) {
  for (byte i = 0; i < n; i++) {
    baqueta_der_drum_corto(0.01);
    baqueta_izq_drum_corto(0.01);
  }

}


void setup() {
  Serial.begin(115200);

  baqueta_izq.attach(baqueta_izq_pin);  //pin servo baqueta izquierda
  baqueta_der.attach(baqueta_der_pin);  //pin servo baqueta derecha

  Serial.print("baqueta_izq:"); Serial.print(baqueta_izq.read());
  Serial.print("   baqueta_der:"); Serial.println(baqueta_der.read());

}



void rutina1() {
  baqueta_der_drum_medio(0.03);
  baqueta_der_drum_medio(0.03);
  baqueta_izq_drum_corto(0.15);

  baqueta_der_drum_medio(0.03);
  baqueta_der_drum_medio(0.03);
  baqueta_der_drum_corto(0.02);
  baqueta_izq_drum_corto(0.15);

  all_baquetas_drums(0.25);
  all_baquetas_drums(0.25);
}

void loop() {

  all_baquetas_nodrums(0.25);
  redoble(10);
  all_baquetas_drums(0.25);
  all_baquetas_drums(0.25);
  rutina1();
  rutina1();
  rutina1();
  all_baquetas_drums(0.5);
  all_baquetas_drums(0.25);
  all_baquetas_drums(0.25);

}

