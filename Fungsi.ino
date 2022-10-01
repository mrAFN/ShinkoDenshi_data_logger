//-------------------------------------------------------
float parseData() {
  String raw, data[5];
  bool parsing = false;
  int x = 0;
  if (timbangan.available() > 0) {
    raw = timbangan.readStringUntil('\n');
    Serial.println("RAW:" + raw);
  }

  if (raw[0] == '+') {
    parsing = true;
  }
  
  if (parsing) {
    for (int i = 0; i < raw.length(); i++) {
      if (raw[i] == '+' or raw[i] == ' ') {
        x++; data[x] = "";
      } else {
        data[x] += raw[i];
      }
    }
    float gram = data[1].toFloat();
    //Serial.print(F("BERAT: "));
    //Serial.print(gram, 3);
    //Serial.println(F(" gram"));
    timbanganFlush();
    beep(BOUNCE);
    return gram;
  }
  timbanganFlush();
  return -1;
}
//-------------------------------------------------------
String empatDigit(int val) {
  if (val < 10) return "000" + String(val);
  else if (val < 100) return "00" + String(val);
  else if (val < 1000) return "0" + String(val);
  else String(val);
}
//-------------------------------------------------------
void setTare() {
  Serial.println(F("SET TARE"));
  timbangan.println("T ");
  digitalWrite(RELAY, ON);
  delay(50);
  digitalWrite(RELAY, OFF);
}
//-------------------------------------------------------
void lcdPrint(byte x, byte y, String msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//-------------------------------------------------------
void lcdPrint(byte x, byte y, char* msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//-------------------------------------------------------
void lcdPrint(byte x, byte y, char msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//-------------------------------------------------------
void beep(int wait) {
  digitalWrite(BUZZER, ON);
  delay(wait);
  digitalWrite(BUZZER, OFF);
}
//-------------------------------------------------------
void timbanganFlush() {
  while (timbangan.available()) {
    String s = timbangan.readString();
  }
}
