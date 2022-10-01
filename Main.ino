//-------------------------------------------------------
void mainProgram() {
  byte proses = 1;
  float baca;
  EEPROM.readBlock<char>(id_addr, id, 10);

  lcd.clear();
  lcdPrint(0, 0, "  TARE  WEIGHT  ");
  sprintf(lcdBuff, "  %5d.%03d g    ", (int)TW, (long(TW * 1000) % 1000));
  lcdPrint(0, 1, lcdBuff);

  timbanganFlush();

  while (1) {
    Key = pad.getKey();
    if (Key) {
      beep(BOUNCE);
      // Check nilai tombol
      if (Key == ESC) {
        lcd.clear();
        break;
      }
      Key = char(0);
    }

    baca = parseData();
    if (proses == 3) {
      GW = NW + TW;
      Serial.println(F("PROSES 3: "));
      Serial.print(F("GW: "));
      Serial.print(GW, 3);
      Serial.println(F(" gram"));
      lcdPrint(0, 0, "   PRINTING..   ");
      lcdPrint(0, 1, "  PLEASE  WAIT  ");
      printingMode();
      delay(3000);
      break;
    } else if (baca >= 0) {
      if (proses == 1) {
        TW = baca;
        lcdPrint(0, 0, "  TARE  WEIGHT  ");
        sprintf(lcdBuff, "  %5d.%03d g    ", (int)TW, (long(TW * 1000) % 1000));
        lcdPrint(0, 1, lcdBuff);
        proses = 2;
        Serial.println(F("PROSES 1: "));
        Serial.print(F("TW: "));
        Serial.print(TW, 3);
        Serial.println(F(" gram"));
        delay(3000);
        setTare();
        lcd.clear();
        lcdPrint(0, 0, "  NETT  WEIGHT  ");
        sprintf(lcdBuff, "  %5d.%03d g    ", (int)NW, (long(NW * 1000) % 1000));
        lcdPrint(0, 1, lcdBuff);
      } 
      else if (proses == 2) {
        NW = baca;
        Serial.println(F("PROSES 2: "));
        Serial.print(F("NW: "));
        Serial.print(NW, 3);
        Serial.println(F(" gram"));
        lcdPrint(0, 0, "  NETT  WEIGHT  ");
        sprintf(lcdBuff, "  %5d.%03d g    ", (int)NW, (long(NW * 1000) % 1000));
        lcdPrint(0, 1, lcdBuff);
        proses = 3;
        delay(3000);
        lcd.clear();
      }
    }
  }
  lcd.clear();
  NW = 0;
  TW = 0;
  GW = 0;
  timbanganFlush();
}
