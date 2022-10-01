//-------------------------------------------------------
#include "LiquidCrystal_I2C.h"                                                              // Library File
#include "Keypad.h"
#include "EEPROMex.h"
#include "RTClib.h"
#include "TMU220.h"

#define   RELAY            A1
#define   BUZZER           A0

#define   BOUNCE           50                                                               // Nilai Jeda Tombol (LAMA BEEP);
#define   ON               HIGH                                                             // Logika ON = 1
#define   OFF              LOW                                                              // Logika OFF = 0 
#define   UP               'C'
#define   DN               'D'
#define   ENT              '#'
#define   ESC              '*'
#define   DEL              'A'
#define   MEN              'B'


#define   timbangan        Serial1


byte rowPins[4] = {31, 33, 35, 37};                                                         // Daftar Pin Baris Keypad
byte colPins[4] = {39, 41, 43, 45}; 

char charKey[4][4] = {                                                                      // Matrix data tombol Keypad
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char lcdBuff[20];
char Key;
double old;
char id[] = "          ";
bool parsing = false;                                                                       //
bool timbang = false;
float TW, NW, GW;
int id_addr;

Epson TMU220 = Epson(11, 10);
RTC_DS1307 rtc;
Keypad pad = Keypad( makeKeymap(charKey), rowPins, colPins, 4, 4);                          // Deklarasi bawaan library Keypad
LiquidCrystal_I2C lcd (0x27, 16, 2);


//-------------------------------------------------------
