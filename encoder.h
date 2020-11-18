#ifndef ENCODER_H
#define ENCODER_H

const int PINMAP[] = {2, 3, 4, 7, 8, 42, 45, 72, 75};

class Encoder
{
    int
    ext_pin,
            arduino_pin[2];

    unsigned long last_tick = 0;
    long last_count = 0;


  public:
    long count = 0;
    float angv=0;

    Encoder() {}

    Encoder(int ext, int analog, void (*A)())
    {
      ext_pin = ext;
      arduino_pin[0] = PINMAP[ext_pin];
      
      arduino_pin[1] = analog;

//set pin mode
      pinMode(arduino_pin[0], INPUT_PULLUP);
      attachInterrupt(ext_pin, A, CHANGE);

      pinMode(arduino_pin[1], INPUT);
    }

    bool state()
    {
      return digitalRead(arduino_pin[0]) == digitalRead(arduino_pin[1]);
    }

    float update()
    {
      float duration = (millis() - last_tick)/1000.0;
      float da = count/180.0*3.14159;

      last_tick = millis();
      count = 0;

      angv = da / duration * 60.0;
      
      return duration;
    }
};

void change(Encoder &enc)
{
  bool state = enc.state();
  if (state)
    enc.count++;
  else
    enc.count--;
}

#endif
