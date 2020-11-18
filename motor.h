#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"

//#define SHOW

class Motor
{
    int en, in1, in2;

    float target = 0.0, v = 0.0, settle = 25.0, base_voltage=75;

    float last_tick = 0.0,
     last_angv = 0.0,
     P = 0.5,
     D = -0.005;

  public:
    Encoder enc;
    long count = 0;

    Motor() {}

    Motor(int en_i, int in1_i, int in2_i, int ext_a, int analog, void (*A)(), float init = 0.0)
    {
      en = en_i;
      in1 = in1_i;
      in2 = in2_i;
      target = init;
      enc = Encoder(ext_a, analog, A);

      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
    }

    float angularvel()
    {
      return enc.angv;
    }

    void update()
    {
      float duration = enc.update();
      float angv = enc.angv;


       float respons = P*(target-angv) + D*(angv - last_angv)/duration;
       last_angv = angv;
      
      v += respons;

      //cut the over response
      if (v > 255.0) v = 255.0;
      else if (v < -255.0) v = -255.0;

      float output = v;
      //jump through useless part
      if (output > settle)
        output += base_voltage;
      else if (output < settle)
        output -= base_voltage;

      digitalWrite(in1, v > 0 ? HIGH : LOW);
      digitalWrite(in2, v < 0 ? HIGH : LOW);
      analogWrite(en, int(abs(v)));

#ifdef SHOW
      Serial.print("in1 : ");
      Serial.print(in1);
      Serial.print(" in2 : ");
      Serial.print(in2);
      Serial.print("target : ");
      Serial.print(target);
      Serial.print(" en : ");
      Serial.print(en);
      Serial.print(" v : ");
      Serial.println(v);
#endif
    }

    void setSpeed(float sp)
    {
      target = sp;
    }
};

#endif
