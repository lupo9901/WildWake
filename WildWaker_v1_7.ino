/*
        Arduino WildWaker
        by Luca Ponzio

  Description:

  Wild Waker ist ein Wecker welcher zum Wachwerden mit einem starken Motor vibriert und gleichzeitig nette Nachrichten am Display anzeigt.

  TODO:
         - Backlight automatisch ausschalten




  Changelog:
  15.07.19: Zeit wird jetzt angezeigt
  16.07.19: Counter funktioniert jetzt, Trigger bei Ablauf der Zeit auch
  17.07.19: DisplayGuard implementiert, Timer startet auf knopfdruck
  18.07.19: SelectorButton und Zählmechanismus implementiert.
  21.07.19: Zeit jetzt auswählbar und Startknopf sowie Begrüßung hinzugefügt. Erstmals nutzbar.
  23.07.19: Rechnet in den neuen Tag und nun voll funktionsfähig. Betaphase gestartet.
  24.07.19: Zeitformat 24 Studen wird eingehalten. Version 1.0 veröffentlicht. Weckerversion als Wild Waker veröffentlicht.
  26.07.19: Wecker jetzt ausschaltbar.
  27.07.19: Backlight ausschaltbar und Snooze Modus implementiert. Einstellungen als Menüpunkt hinzugefügt.
  28.07.19: Settings können jetzt im EEPROM abgelegt werden.
  30.07.19: Wird jetzt auf 20 x 4 Display Angezeigt. Cursor bewegt sich und blinkt.
  31.07.19: Bugfix: timeMode wird in EEPROM geschrieben
  07.09.19: UI buttons benannt. Note: Verursacht evtl flackern.
  01.10.19: Bugfix-> Zieht Zahl ins nächste Digit mit Solved.
  03.10.19: Runner implementiert und kleine Bugfixes (24:60 einstellbar)
  05.10.19: RTC-Zeit jetzt über Settings konfigurierbar. Reiter "Statistics" eingefügt
  06.10.19: RTC-Datum über Settings konfigurierbar. Kleine Bugfixes und Tooltips.



*/
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <EEPROM.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

String wwVersion = String(1.7);
long int diffSecs;

byte triggerFlag = 0;
byte dateExcessFlag = 0;
bool timeOut = false;

bool ySelectActive = false;
bool xSelectActive = false;


bool xButtonState = true;
bool xButtonStateOld = true;

bool yButtonState = true;
bool yButtonStateOld = true;

bool backlightCounter = true;

bool timeSetFlag = false;
bool dateSetFlag = false;

byte snoozeTime             =    EEPROM.read(21)  ;
byte vibration              =    EEPROM.read(22)  ;
byte morningMessages        =    EEPROM.read(23)  ;
byte timeMode               =    EEPROM.read(24)  ;

bool blinker;

bool parse = false;
bool config = false;


tmElements_t tm;

long int timeArray[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0};                    //Zielzeit im Array geschrieben

int ledYel = 8;                                                    // Leds initialisieren
int ledGre = 10;

int button = 4;                                                    //Buttons ebenso
int yButton = 5;

int tonePin = 6;

int subMenu = 0;

byte customChar[] = {                                             //Auswahlkreuz
  B11111,
  B10001,
  B11011,
  B10101,
  B11011,
  B10001,
  B11111,
  B00000
};

byte emptyChar[] = {                                              // Auswahlkreuz leer
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};

byte underline[] = {                                              //undeline Cursor (nicht benötigt)
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte clockSymbol[] = {
  B11011,
  B00100,
  B01110,
  B10011,
  B10101,
  B10001,
  B01110,
  B10001
};

byte returnArrow[] = {
  B10000,
  B10000,
  B10100,
  B10010,
  B11111,
  B00010,
  B00100,
  B00000
};

String messages[] = {                                   //Unbedingt Random anpassen

  "Guten Morgen!       ",
  "Du bist toll!       ",
  "Ich mag dich <3     ",
  "Heute wird toll!    ",
  "Die Sonne scheint!  ",
  "Du bist schoen!     ",
  "STEH AUF!           ",
  "Positive Vibes      ",
  "Hello you           ",
  "I lieb di!          ",
  "Lach mal :)         "
};


void setup()
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  setSyncProvider(RTC.get);



  randomSeed(analogRead(0));


  lcd.createChar(0, customChar);
  lcd.createChar(1, emptyChar);
  lcd.createChar(2, underline);
  lcd.createChar(3, clockSymbol);
  lcd.createChar(4, returnArrow);


  pinMode(ledYel, OUTPUT);
  pinMode(ledGre, OUTPUT);
  pinMode(button, INPUT);
  pinMode(yButton, INPUT);


  lcd.clear();
  lcd.setCursor( 3 , 1 );
  lcd.print("WildWake v");
  lcd.print(wwVersion);
  lcd.setCursor( 5 , 2 );
  lcd.print("by LocTec");

  delay(1000);
  reset();

  if (snoozeTime > 60) {                               //Prüfen ob Daten aus EEPROM Sinn machen

    snoozeTime = 5;
  }
  if (vibration > 1) {

    vibration = 1;
  }
  if (morningMessages > 1) {

    morningMessages = 1;
  }
  if (timeMode > 1) {

    timeMode = 1;
  }


  lcd.clear();

}

void loop() {

  displayTime(0 , 0);                                  //Zeigt die aktuelle Zeit aus dem RTC an
  displayDate(10, 0);


  if (timeOut)  subMenu = 2;               // Zeit abgelaufen?

  switch (subMenu) {                       //Hauptmenü. Steuert alle Funktionen des weckers. subMenu wird durch Funktionen angesteuert

    case 0:

      targetSelector(5, 2);

      break;

    case 1:

      timeRemaining(5 , 2 );
      break;

    case 2:

      startSequence(0 , 2);
      break;

    case 3:
      specialMenu();
      break;

  }


  settingsMenuGuard();
  writeToEeprom();
  backlightGuard();
  displayGuard();                                     //Display jede Minute clearen, dass evtle Fehler resettet werden


  digitalWrite(ledGre, HIGH);                         //Lampe auf grün - alles ok


}


void settingsMenuGuard() {                      //Ruft Settings auf wenn X&Y 4s gedrückt werden

  int enterTimer;
  static int enterTimerOld = 0;
  static int enterTrigger = 0;




  if (xSelectActive && ySelectActive) {

    enterTimer = second();

    if (enterTimer != enterTimerOld) {
      enterTimerOld = enterTimer;

      enterTrigger ++;

    }

    if (enterTrigger == 4) {
      enterTrigger = 0;

      subMenu = 3;
    }

  }


}
