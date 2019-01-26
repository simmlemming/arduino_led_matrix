long last_ms = 0;
int br = 0;

#define DAY_TO_NIGHT_RATIO 10
#define DAY_THRESHOLD 20

// [br, lr, mr, is_day]
int getBrightness(int res[]) {
  long now = millis();
  if (now - last_ms < 500) {
    return br;
  }

  br = getManualBrightness(res);
  bool day = isDay(res);

  if (!day) {
    br = br / DAY_TO_NIGHT_RATIO;
  }

  print(res);
  last_ms = now;

  return br;
}

bool isDay(int values[]) {
  int lr = analogRead(PIN_LR) / 10;
  bool isDay = lr > DAY_THRESHOLD;

  values[1] = lr;
  values[3] = isDay;

  return isDay;
}

int getManualBrightness(int values[]) {
  int mr = analogRead(PIN_MR);

  int mr_a = constrain(mr - 624, 0, 1023);
  int br = map(mr_a, 0, 400, 0, 99);

  values[0] = br;
  values[2] = mr / 10;
  
  return br;
}

void print(int res[]) {
  Serial.print(res[0]);

  if (!res[3]) {
    Serial.print(" (NIGHT)");    
  }

  Serial.print(" LR = ");
  Serial.print(res[1]);
  Serial.print(", MR = ");
  Serial.println(res[2]);  
}
