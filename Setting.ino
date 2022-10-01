//-------------------------------------------------------
void menuSetting() {
  lcd.clear();
  int menu = 1;
  while (1) {
    Key = pad.getKey();
    if (Key) {
      beep(BOUNCE);
      if (Key == UP) {
        menu++;
        if (menu > 2) menu = 1;
      } else if (Key == DN) {
        menu--;
        if (menu < 1) menu = 2;
      } else if (Key == ESC) {
        delay(50);
        Key = char(0);
        lcd.clear();
        break;
      } else if (Key == ENT) {
        switch (menu) {
          case 1: settingRTC(); break;
          case 2: settingData(1); break;
        }
      }
      Key = char(0);
    }

    lcdPrint(0, 0, " MENU PARAMETER ");
    switch (menu) {
      case 1: lcdPrint(0, 1, "  SETTING  JAM  "); break;
      case 2: lcdPrint(0, 1, "    NOMOR ID    "); break;
    }
  }
}

//-------------------------------------------------------
void settingRTC() {
  lcd.clear();                                                                              // Hapus data tampilan LCD
  int pos = 0;
  int sor = 0;
  char buff[13];                                                                            // array 3 kota untuk 0 - 999
  for (int i = 0; i < 16; i++) {                                                            // clear data char array
    buff[i] = char(0);
  }
  while (1) {
    Key = pad.getKey();                                                                     // Baca Keypad
    if (Key) {                                                                              // Jika Keypad ada tombol ditekan
      beep(BOUNCE);
      // Check nilau tombol
      if (byte(Key) >= 48 and byte(Key) <= 57) {
        if (pos < 12) {
          lcdPrint(pos + sor, 1, String(Key));
          buff[pos] = Key;
          pos++;
          if (pos == 2) sor = 1;
          else if (pos == 4) sor = 2;
          else if (pos == 8) sor = 3;
          else if (pos == 10) sor = 4;
          if (pos >= 12) pos = 11;
        }
      } else if (Key == DEL) {                                                              // Jika tombol yang ditekan DEL
        if (pos >= 0) {
          lcdPrint(pos + sor, 1, ' ');
          buff[pos] = 0;
          pos--;
          if (pos == 1) sor = 0;
          else if (pos == 3) sor = 1;
          else if (pos == 7) sor = 2;
          else if (pos == 9) sor = 3;
          if (pos <= 0) pos = 0;
        }
      } else if (Key == ENT) {                                                              // Jika tombol yang ditekan ENT
        String s = String(buff[4]) + String(buff[5]) + String(buff[6]) + String(buff[7]);
        int thn = s.toInt();
        s = String(buff[2]) + String(buff[3]);
        int bln = s.toInt();
        s = String(buff[0]) + String(buff[1]);
        int tgl = s.toInt();
        s = String(buff[8]) + String(buff[9]);
        int jam = s.toInt();
        s = String(buff[10]) + String(buff[11]);
        int mnt = s.toInt();
        s = String(tgl) + ", " + String(bln) + ", " + String(thn) + ", " + String(jam) + ", " + String(mnt);
        // {2,1,8,2,2,0,2,2,1,4,2,4}
        Serial.println(s);
        rtc.adjust(DateTime(thn, bln, tgl, jam, mnt, 0));                                   // Simpan data RTC
        delay(50);
        lcd.clear();
        lcdPrint(0, 0, "  SETTING  JAM  ");
        lcdPrint(0, 1, "  SIMPAN  DATA  ");
        delay(2000);
        break;                                                                              // Keluar Menu
      } else if (Key == ESC) {                                                              // Jika tombol yang ditekan ESC
        delay(50);
        break;                                                                              // Keluar Menu
      }
      Key = char(0);
    }
    lcdPrint(0, 0, "  SETTING  JAM  ");
    lcdPrint(2, 1, '/');
    lcdPrint(5, 1, '/');
    lcdPrint(10, 1, ' ');
    lcdPrint(13, 1, ':');
  }
  lcd.clear();
}
//-------------------------------------------------------
void settingData(int menu) {
  lcd.clear();                                                                              // Hapus data tampilan LCD
  int pos = 0;
  double val;                                                                                  // Nilai posisi dan nilai EEPROM
  char buff[11];                                                                             // array 3 kota untuk 0 - 999
  for (int i = 0; i < 10; i++) {                                                             // clear data char array
    buff[i] = char(0);
  }
  while (1) {
    Key = pad.getKey();                                                                     // Baca Keypad
    if (Key) {                                                                              // Jika Keypad ada tombol ditekan
      beep(BOUNCE);
      // Check nilai tombol
      if (byte(Key) >= 48 and byte(Key) <= 57) {
        if (pos <= 10) {
          lcdPrint(pos + 3, 1, String(Key));
          buff[pos] = Key;
          pos++;
          if (pos >= 10) pos = 10;
        }
      } else if (Key == DEL) {                                                              // Jika tombol yang ditekan DEL
        if (pos >= 0) {
          lcdPrint(pos + 3, 1, ' ');
          buff[pos] = 0;
          pos--;
          if (pos <= 0) pos = 0;
        }
      } else if (Key == ENT) {                                                              // Jika tombol yang ditekan MEN
        Serial.println("STR ID: " + String(buff));
        EEPROM.writeBlock<char>(id_addr, buff, 10);
        EEPROM.readBlock<char>(id_addr, id, 10);
        Serial.print("EEPROM ID: ");
        Serial.println(id);
      } else if (Key == ESC) {                                                              // Jika tombol yang ditekan ESC
        beep(BOUNCE);
        delay(50);
        lcd.clear();
        break;                                                                              // Keluar Menu
      }
      Key = char(0);
    }
    sprintf(lcdBuff, "ID:%s   ", id);
    lcdPrint(0, 0, lcdBuff);
    lcdPrint(0, 1, "  [");
    lcdPrint(13, 1, "]  ");
  }
}
