char psw[] = "holy";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
  {
    char buf[8];
    int n = Serial.readBytes(buf, 8);
    if (n == 8 && buf[0] == psw[0] && buf[2] == psw[1] && buf[4] == psw[2] && buf[6] == psw[3])
    {
      Serial.println(int(buf[1]));
      Serial.println(int(buf[3]));
      Serial.println(int(buf[5]));
      Serial.println(int(buf[7]));
      Serial.println("---");
    }
  }
}
