#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"

class Motor
{
    int en, in1, in2;

    float target = 0.0, v = 0.0;

  public:
    Encoder enc;
    long count = 0;

    Motor() {}

    Motor(int en_i, int in1_i, int in2_i, int ext_a, int ext_b, void (*A)(), void (*B)())
    {
      en = en_i;
      in1 = in1_i;
      in2 = in2_i;

      enc = Encoder(ext_a, ext_b, A, B);

      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
    }

    void update()
    {
      float err = enc.update(target)/1000.0;

      v += err;

      if(v>255.0) v=255.0;
      else if(v<-255.0) v=-255.0;
      
      digitalWrite(in1, v > 0 ? HIGH : LOW);
      digitalWrite(in2, v < 0 ? HIGH : LOW);
      analogWrite(en, int(abs(v)));
      Serial.println(enc.rpm);
    }

    void setSpeed(float sp)
    {
      target = sp;
    }
};

#endif
