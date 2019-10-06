

bool timeRemaining(int x, int y) {                                // Berechnet die Differenz wischen Aktueller und Zielzeit und printet diese auf dem Bildschirm ab
  unsigned int hrem;                                                         //Lokale Variablen für Uhrzeitformat
  unsigned int mrem;
  unsigned int srem;

  long int hs = ( timeArray[0] * 10) + timeArray[1] ;

  long int ms = ( timeArray[2] * 10) + timeArray[3] ;

  long int ss = ( timeArray[4] * 10) + timeArray[5] ;



  long int totalSecs = convertToSeconds(hour(), minute(), second());      //Rechne Aktuelle Zeit in Sekunden um

  long int targetSecs = convertToSeconds( hs , ms , ss );                     //Rechne Zielzeit in Sekunden um





  if (targetSecs - totalSecs < 0) {

    //nonValidWarning();                                               //Provisorisch um überlauf zu verhindern
    //reset();
    //subMenu = 0;                                                       //wechselt das Menü

    long int secondsToMidnight = 86400 - totalSecs;

    diffSecs = secondsToMidnight + targetSecs;




  } else {

    diffSecs = targetSecs - totalSecs;                                 //Für effektive Umrechnung wird die differenz in Sekunden gebildet...
  }


  hrem = diffSecs / 3600;                                            //Umrechnnung Sekundendifferenz in Stunden..

  mrem = (diffSecs % 3600) / 60 ;                                    //..Minuten...

  srem = ( (diffSecs % 3600) % 60);                                  //...und Sekunden.

  lcd.setCursor(x, y);                                               //Setzt Cursor, Varialble wird bei Funktion übergeben

  if (hrem >= 10) {                                                  // Unter 10? Setze eine Null vor den Einer
    lcd.print(hrem);
  } else {
    lcd.print("0");
    lcd.print(hrem);
  }
  lcd.print(":");
  if (mrem >= 10) {                                                  //dito minuten
    lcd.print (mrem);
  } else {
    lcd.print("0");
    lcd.print(mrem);
  }
  lcd.print(":");
  if (srem >= 10) {                                                  //dito sekunden
    lcd.print (srem);
  } else {
    lcd.print("0");
    lcd.print(srem);
  }



  if (diffSecs == 0) {                                              // Zeit abgelaufen ?

    timeOut = true;
    lcd.clear();
    return true;                                                    // JA

  } else {


    // NEIN

    if (digitalRead(button) == LOW) {´                     //Gehe zurück wen abgebrochen

      reset();
      subMenu = 0;

      timeOut = false;
      return false;

    }

  }

  backlightRemaining();


  lcd.setCursor(0, 3);
  lcd.print("*    ");

  lcd.setCursor(19, 3);
  lcd.print("X   ");

}

long int convertToSeconds(long int h, long int m, long int s) {        //Funktion um Zeit im Format Stunden:Minuten:Sekunden in Gesamtsekunden umzurechnen

  long int secSum = (h * 3600) + (m * 60 ) + s ;                  //In Sekunden zerlegen und aufsummieren

  return secSum;                                                     // und Gesamtsekunden zurück

}





int lastTime = 0;                                                   //für die nächse Funktion

void displayGuard() {                                              // Cleart jede Minute das Display, falls zu viele Nullen da sein sollen

  int guardTime = minute();

  if (guardTime != lastTime) {                                        // Wenn sich die Zeit ändert..

    lcd.clear();                                                      // Kommt die Putzfrau :D
    lastTime = guardTime;

  }



}

int blinkCount = 0;
int lastBlink = 0;


void blinkiblinki() {                               //Steuert den Cursor. Einfache Timer funktion

  unsigned long blinkTime = millis();

  if (blinkTime != lastBlink) {
    lastBlink = blinkTime;
    blinkCount ++;

  }


  if (blinkCount < 2) {
    blinker = true;

  }
  if (blinkCount > 4) {
    blinker = false;

  }

  if (blinkCount > 6) {
    blinkCount = 0;

  }



}



int lightOnOff = 0;
void backlightRemaining() {                               //Selbsthaltung für Backlight

  int yButtonState = digitalRead(yButton);

  if (yButtonState != yButtonStateOld) {
    yButtonStateOld = yButtonState;

    if (yButtonState == LOW) {

      lightOnOff ++;

    }
  }

  if ( lightOnOff == 0) {
    backlightCounter = true;
  }
  if ( lightOnOff == 1) {
    backlightCounter = false;

  }

  if ( lightOnOff == 2) {
    backlightCounter = true;
    lightOnOff = 0;
  }


}

void backlightGuard() {

  if (backlightCounter == true) {

    lcd.backlight();
  }

  if (backlightCounter == false) {

    lcd.noBacklight();
  }

}

void writeToEeprom() {

  static int y = 0;
  static int i = 0;
  int n;


  n = second();

  if (n != y) {
    y = n;
    i++;
  }

  if (i == 5) {
    i = 0;




    EEPROM.update(21, snoozeTime);

    EEPROM.update(22, vibration);

    EEPROM.update(23, morningMessages);

    EEPROM.update(24, timeMode);

  }

}
