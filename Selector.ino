
int yButtonCounter = 0;                                 //Enthält die zu schreibende Zahl, wird öfters angepasst, also dynamisch


int  xState = 0;

int hourBound;
int minBound;
int secBound;
int hourMin;
int minMin;
int secMin;

/*

  Lässt den User am Display die gewünschte Zeit im Format hh:mm:ss auswählen und bestätigen.
  Bei Bestätigung wird die Zeit an den Timer übergeben


*/
void targetSelector(int x, int y) {

  //  lcd.cursor();
  //  lcd.blink();

  if (dateSetFlag == true) {                 //Datum Set modus? Ändere Grenzen zum Einstellen

    hourBound   = 31;
    minBound    = 12;
    secBound    = 99;
    hourMin     = 1;
    minMin      = 1;
    secMin      = 0;


  }

  if (dateSetFlag == false) {                 //Normaler Modus? Lege grenzen für Gültige Zeit fest

    hourBound = 23;
    minBound = 59;
    secBound = 59;
    hourMin     = 0;
    minMin      = 0;
    secMin      = 0;
  }

  yButtonCounter = timeArray[xselect()];                  // Holt sich Zeit aus array 
  timeArray[xselect()] = yselect();                       //Schreibt die gewählte Zeit ins Array. Position wird mit Button gewählt




  if (((timeArray[0] * 10) + timeArray[1]) > hourBound ) {                 //Begrenzungen für Zeitformat

    timeArray[0] = 0;
    timeArray[1] = hourMin;

  }

  if ((timeArray[1]) > 9 ) {

    timeArray[0]++;
    timeArray[1] = 0;

  }



  if (((timeArray[2] * 10) + timeArray[3]) > minBound ) {

    timeArray[2] = 0;
    timeArray[3] = minMin;

  }

  if ((timeArray[3]) > 9) {

    timeArray[2]++;
    timeArray[3] = 0;

  }

  if (((timeArray[4] * 10) + timeArray[5]) > secBound ) {

    timeArray[4] = 0;
    timeArray[5] = secMin;

  }

  if ((timeArray[5]) > 9 ) {

    timeArray[4]++;
    timeArray[5] = 0;

  }


  lcd.setCursor(x , y);                                   //printet die Zeit am Display

  //lcd.cursor();
  //lcd.blink();

  lcd.print(timeArray[0]);
  lcd.print(timeArray[1]);
  lcd.print(":");
  lcd.print(timeArray[2]);
  lcd.print(timeArray[3]);
  lcd.print(":");
  lcd.print(timeArray[4]);
  lcd.print(timeArray[5]);

  if (xselect() == 6 ) {                                 //zeigt die Auswahlbox zum bestätigen des Timers

    //lcd.setCursor(x + 9 , y);
    lcd.print(" ");
    lcd.write(0);

    if (ySelectActive == true) {                           //Wechselt zum Timer

      if (timeSetFlag == false && dateSetFlag == false) {        //wenn kein SET modus ausgewählt ist
        subMenu = 1;
        delay(100);
        lcd.clear();
      }

      if (timeSetFlag == true) {                                 //Ist SET modus ausgewählt?

        // Schreibe Zeit ins RTC

        if (getTime() && getDate()) {                          //Hole Zeit aus timeArray aund schreibe aufs RTC
          parse = true;
          // and configure the RTC with this info
          if (RTC.write(tm)) {
            config = true;
            setSyncProvider(RTC.get);
          }
        }

        if (config) {
          lcd.clear();
          lcd.setCursor(5, 2);
          lcd.print("Time Set.");
          delay(1000);
          timeSetFlag = false;
          reset();
          config = false;

          lcd.clear();

        } else {

          lcd.clear();
          lcd.setCursor(5, 2);
          lcd.print("Error.");
          delay(1000);
          timeSetFlag = false;
          reset();
          config = false;

          lcd.clear();


        }

        timeSetFlag = false;
        dateSetFlag = false;
      }

      if (dateSetFlag == true) {                             //SET mode für Datum


        if (getTime() && getDate()) {                       //Schreibe ins RTC
          parse = true;
          // and configure the RTC with this info
          if (RTC.write(tm)) {
            config = true;
            setSyncProvider(RTC.get);
          }
        }

        if (config) {
          lcd.clear();
          lcd.setCursor(5, 2);
          lcd.print("Date Set.");
          delay(1000);
          dateSetFlag = false;
          reset();
          config = false;

          lcd.clear();

        } else {

          lcd.clear();
          lcd.setCursor(5, 2);
          lcd.print("Error.");
          delay(1000);
          dateSetFlag = false;
          reset();
          config = false;

          lcd.clear();


        }
      }

    }



  } else {

    lcd.print(" ");
    lcd.write(1);

  }

  blinkiblinki();                                          //callt status des underline cursors

  if (blinker == true) {

    switch (xselect()) {                                   //Es folgt etwas Raketenwissenschaft damit der cursor blinkt wo er soll

      case 0:

        lcd.setCursor((x + xselect()) + 7 , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect(), y + 1);
        lcd.write(2);

        break;

      case 1:
        lcd.setCursor((x + xselect()) - 1 , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect(), y + 1);
        lcd.write(2);
        break;

      case 2:
        lcd.setCursor((x + xselect()) - 1 , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect() + 1, y + 1);
        lcd.write(2);
        break;

      case 3:
        lcd.setCursor((x + xselect())  , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect() + 1, y + 1);
        lcd.write(2);
        break;

      case 4:
        lcd.setCursor((x + xselect()) , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect() + 2, y + 1);
        lcd.write(2);
        break;

      case 5:
        lcd.setCursor((x + xselect()) + 1  , y + 1);
        lcd.print(" ");

        lcd.setCursor(x + xselect() + 2, y + 1);
        lcd.write(2);
        break;

      case 6:
        lcd.setCursor((x + xselect()) + 1  , y + 1);
        lcd.print(" ");

        break;



    }

  } else {

    lcd.setCursor(x , y + 1);
    lcd.print("          ");


  }


  if (xState == 7) {                                //reset
    xState = 0;
  }


  if (timeSetFlag || dateSetFlag == true) {                  //Zeit den SET Modus an

    lcd.setCursor(0, 2);
    lcd.print("SET> ");

  }

  lcd.setCursor(0, 3);                             //UI buttons
  lcd.print("+    ");

  lcd.setCursor(19, 3);
  lcd.print(">  ");

  //  lcd.noCursor();
  //  lcd.noBlink();

}



int yselect() {                                      //Frägt Y Button ab. "Entprellt" und zählt rauf

  int yButtonState = digitalRead(yButton);

  yButtonCounter = timeArray[xState];

  runner(0);                                          //Runner für yButton (0);


  if (yButtonState != yButtonStateOld) {
    yButtonStateOld = yButtonState;

    if (yButtonState == LOW) {
      yButtonCounter ++;

      ySelectActive = true;



    } else {

      ySelectActive = false;
    }
  }



  return yButtonCounter;

}

int  xselect() {                                      //fragt X button ab, zählt hoch 

  int xButtonState = digitalRead(button);



  if (xButtonState != xButtonStateOld) {
    xButtonStateOld = xButtonState;

    if (xButtonState == LOW) {
      xState ++;
      xSelectActive = true;
    } else {
      xSelectActive = false;
    }


  }




  return xState;



}


void runner(int side) {                                  //Läufer. Wenn User länger auf yButton drückt startet automatisch ein Hochlauf 


  unsigned long enterTimer;
  unsigned long enterTimerOld;
  static unsigned long enterTrigger = 0;




  if (ySelectActive) {

    enterTimer = millis();

    if (enterTimer != enterTimerOld) {               //Zähler bei Änderung
      enterTimerOld = enterTimer;

      enterTrigger ++;

      if (enterTrigger >= 10) {                    //Wenn zähler Wert übeschreitet. Treshhold für Zähler start. 10ms fühlt sich natürlich an

        if (enterTrigger % 2 == 0) {              //Zähle alle zwei ms hoch

          switch (side) {

            case 0:
              yButtonCounter++;

              break;

            case 1:

              xState++;

              break;

            case 3:
              //reserve
              break;
          }


        }

        //TODO
      }

    }

  } else {

    enterTrigger = 0;
  }
}
