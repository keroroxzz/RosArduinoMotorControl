/*OpneCR code for M-wheel control

   by Brian Tu

   2020/10/31
*/

#include "motor.h"

//#define SHOW

void fr_A();
void fl_A();
void br_A();
void bl_A();

Motor mot_fr, mot_fl, mot_br, mot_bl;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(0.0001);

  mot_fr = Motor(3, 1, 2, 5, A0, fr_A, 0.0);
  mot_fl = Motor(6, 5, 4, 6, A1, fl_A, 0.0);
  mot_br = Motor(9, 8, 7, 7, A2, br_A, 0.0);
  mot_bl = Motor(10, 12, 11, 8, A3, bl_A, 0.0);
}

void loop() {

  if (Serial.available())
    if (Serial.find("a"))
      mot_fr.setSpeed(Serial.parseInt());
    if (Serial.find("b"))
      mot_fl.setSpeed(Serial.parseInt());
    if (Serial.find("c"))
      mot_br.setSpeed(Serial.parseInt());
    if (Serial.find("d"))
      mot_bl.setSpeed(Serial.parseInt());

  //motor control and encoder calculation
  mot_fr.update();
  mot_fl.update();
  mot_br.update();
  mot_bl.update();

#ifdef SHOW
  Serial.print("A : ");
  Serial.print(mot_fr.enc.rpm);
  Serial.print("\tB : ");
  Serial.print(mot_fl.enc.rpm);
  Serial.print("\tC : ");
  Serial.print(mot_br.enc.rpm);
  Serial.print("\tD : ");
  Serial.println(mot_bl.enc.rpm);
#endif

  delay(20);
}

void fr_A() {
  change(mot_fr.enc);
}

void fl_A() {
  change(mot_fl.enc);
}

void br_A() {
  change(mot_br.enc);
}

void bl_A() {
  change(mot_bl.enc);
}
