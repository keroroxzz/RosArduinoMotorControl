#ifndef ENCODER_H
#define ENCODER_H

const int PINMAP[] = {2, 3, 4, 7, 8, 42, 45, 72, 75};

class Encoder
{
    int
    ext_pin[2],
            arduino_pin[2];

    unsigned long last_tick = 0;
    long last_count = 0;


  public:
    long count = 0;
    float rpm=0;

    Encoder() {}

    Encoder(int ext_a, int ext_b, void (*A)(), void (*B)())
    {
      ext_pin[0] = ext_a;
      arduino_pin[0] = PINMAP[ext_pin[0]];

      ext_pin[1] = ext_b;
      arduino_pin[1] = PINMAP[ext_pin[1]];


      pinMode(arduino_pin[0], INPUT_PULLUP);
      attachInterrupt(ext_pin[0], A, CHANGE);

      pinMode(arduino_pin[1], INPUT_PULLUP);
      attachInterrupt(ext_pin[1], B, CHANGE);
    }

    bool state()
    {
      return digitalRead(arduino_pin[0]) == digitalRead(arduino_pin[1]);
    }

    float update(float target)
    {
      float duration = (millis() - last_tick) / 1000.0;
      float dif = (count - last_count) / 720.0;

      last_tick = millis();
      count = 0; //experimental
      //last_count = count;

      rpm = dif / duration * 60.0;

      return (target - rpm)/duration;
    }
};

void change(Encoder &enc, int channel)
{
  bool state = enc.state();
  if (channel == 0)
    if (state)
      enc.count++;
    else
      enc.count--;
  else if (!state)
    enc.count++;
  else
    enc.count--;
}

#endif
