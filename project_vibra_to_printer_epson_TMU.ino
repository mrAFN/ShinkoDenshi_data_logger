#include "Config.h"

//-------------------------------------------------------
void setup() {
  Serial.begin(9600);                                    // PC
  timbangan.begin(9600);                                 // Timbangan
  lcd.begin();
  rtc.begin();
  TMU220.begin();
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  lcdPrint(0, 0, "PT IMFARMIND F.I");                    // Nama anda
  lcdPrint(0, 1, "  SN 56545031   ");
  delay(3000);
  lcd.clear();

  id_addr = EEPROM.getAddress(sizeof(char) * 10);
  EEPROM.readBlock<char>(id_addr, id, 10);
  Serial.print("EEPROM ID: ");
  Serial.println(id);
}
//-------------------------------------------------------
void loop() {
  Key = pad.getKey();
  if (Key) {
    beep(BOUNCE);
    // Check nilai tombol
    if (Key == MEN) {
      menuSetting();
    } else if (Key == ENT) {
      mainProgram();
    }
    Key = char(0);
  }

  DateTime now = rtc.now();
  char dot = ' ';
  if ((millis() - old) < 500) {
    dot = ':';
  } else if ((millis() - old) > 500 and (millis() - old) < 1000) {
    dot = ' ';
  } else if ((millis() - old) > 1000) {
    old = millis();
    dot = ':';
  }
  sprintf(lcdBuff, "%02d/%02d/%04d %02d%c%02d", now.day(), now.month(), now.year(), now.hour(), dot, now.minute());
  lcdPrint(0, 0, lcdBuff);
  lcdPrint(0, 1, "B=MENU   #=ENTER");

}
//-------------------------------------------------------
