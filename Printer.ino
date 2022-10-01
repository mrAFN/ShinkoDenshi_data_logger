//-------------------------------------------------------
void printingMode() {
  DateTime now = rtc.now();
  sprintf(lcdBuff, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  String tanggal = String(lcdBuff);
  sprintf(lcdBuff, "%02d:%02d", now.hour(), now.minute());
  String waktu = String(lcdBuff);

  Serial.println("Printing...");
  TMU220.justifyLeft();
  TMU220.println(tanggal);
  TMU220.println(waktu);
  String str_id = "NOMOR ID: " + String(id);
  TMU220.println(str_id);
  TMU220.println("--------------------------");
  TMU220.justifyLeft();
  char buff[4];
  dtostrf(TW, 3, 3, buff);
  String str_tw = "TARE WEIGHT  : " + String(buff) + " gram";
  dtostrf(NW, 3, 3, buff);
  String str_nw = "NETT WEIGHT  : " + String(buff) + " gram";
  dtostrf(GW, 3, 3, buff);
  String str_gw = "GROSS WEIGHT : " + String(buff) + " gram";
  TMU220.println(str_tw);
  TMU220.println(str_nw);
  TMU220.println(str_gw);
  TMU220.feed(6);
  Serial.println("-------------------------");
  Serial.println(tanggal);
  Serial.println(waktu);
  Serial.println(str_id);
  Serial.println("-------------------------");
  Serial.println(str_tw);
  Serial.println(str_nw);
  Serial.println(str_gw);
  Serial.println();
}
//-------------------------------------------------------
