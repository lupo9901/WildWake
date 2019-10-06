void specialMenu() {



  static bool runOnce = true;
  static int menuPage = 0;
  static int pages = 8;           //Anzahl der tatsächlichen Menüseiten PLUS EINS


  if (runOnce) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Settings");
    delay(1000);
    lcd.clear();
    runOnce = false;
  }

  static bool xSelectOld = false;

  yselect();
  xselect();

  if (xSelectActive != xSelectOld) {
    xSelectOld = xSelectActive;


    if (xSelectActive == true) {
      lcd.clear();
      menuPage ++;
    }

  }

  if (menuPage == pages) {
    menuPage = 0;
  }

  lcd.setCursor(0, 2);

  static bool n = false;
  static bool y = false;

  switch (menuPage) {

    case 0:                                  //Soll bei betätigen der wecktaste die zeit zurückgesetzt werden?
      lcd.print("TimeMode:");

      n = ySelectActive;

      if (n != y ) {
        y = n;
        if (n == true) timeMode++;
      }

      if (timeMode > 1) {
        lcd.clear();
        lcd.setCursor(0, 2);
        timeMode = 0;
      }

      lcd.print(" ");

      if (timeMode == 1) {
        lcd.print("Reset");
      }
      if (timeMode == 0) {
        lcd.print("Daily");
      }
      break;

    case 1:                            //Sollen Nachrichten angezeigt werden

      lcd.setCursor(0, 2);
      lcd.print("Messages:");
      lcd.print(" ");

      n = ySelectActive;

      if (n != y ) {
        y = n;
        if (n == true) {
          morningMessages++;
        }
      }

      if (morningMessages > 1) {
        morningMessages = 0;
      }

      lcd.print(" ");
      if (morningMessages == 1) {
        lcd.print("ON ");
      }
      if (morningMessages == 0) {
        lcd.print("OFF");
      }
      break;

    case 2:                                   //Schlummerzeit

      lcd.setCursor(0, 2);
      lcd.print("Snooze:");


      n = ySelectActive;

      if (n != y ) {
        y = n;
        if (n == true) snoozeTime++;
      }

      if (snoozeTime > 20) {
        lcd.clear();
        lcd.setCursor(0, 2);
        snoozeTime = 1;
      }

      lcd.print(" ");

      lcd.print(snoozeTime);
      lcd.print(" ");
      lcd.print("Min");

      break;

    case 3:                              //Wird open collector bei wecken geschaltet?

      lcd.setCursor(0, 2);
      lcd.print("Vibration:");


      n = ySelectActive;

      if (n != y ) {
        y = n;
        if (n == true) vibration++;
      }

      if (vibration > 1) {

        vibration = 0;
      }

      lcd.print(" ");
      if (vibration == 1) {
        lcd.print("ON ");
      }
      if (vibration == 0) {
        lcd.print("OFF");
      }
      break;

    case 4:                      //Stellt RTC Zeit ein

      lcd.setCursor(0, 2);

      lcd.print("Set Time");

      if (ySelectActive == true) {

        lcd.clear();
        lcd.setCursor(6, 1);
        lcd.print("Set to:");
        lcd.setCursor(5, 2);
        lcd.print("hh:mm:ss");
        delay(3000);
        lcd.clear();
        timeSetFlag = true;
        subMenu = 0;

        reset();
        runOnce = true;
        menuPage = 0;
        subMenu = 0;
        lcd.clear();



      }
      break;

    case 5:


      lcd.setCursor(0, 2);
 
      lcd.print("Set Date");                       //Stellt RTC Datum ein


      if (ySelectActive == true) {

        lcd.clear();
        lcd.setCursor(6, 1);
        lcd.print("Set to:");
        lcd.setCursor(5, 2);
        lcd.print("dd:mm:yy");
        delay(3000);
        lcd.clear();
        dateSetFlag = true;
        subMenu = 0;

        reset();
        runOnce = true;
        menuPage = 0;
        subMenu = 0;
        timeArray[1] = 1;
        timeArray[3] = 1;
        timeArray[5] = 0;
        lcd.clear();


      }

      break;


    case 6:                                //Statistik und credits

      lcd.setCursor(0, 2);

      lcd.print("Statistics");


      if (ySelectActive == true) {

        lcd.clear();

        lcd.setCursor(0, 1);
        lcd.print("Uptime:");
        lcd.print(" ");
        lcd.print(((millis() / 1000) / 60) / 60);
        lcd.print(" ");
        lcd.print("Hrs.");

        lcd.setCursor(0, 2);
        lcd.print("Messages:");
        lcd.print(" ");
        lcd.print(sizeof(messages) / sizeof(messages[1]));

        lcd.setCursor(0, 0);
        lcd.print("Version:");
        lcd.print(" ");
        lcd.print(wwVersion);

        lcd.setCursor(0, 3);
        lcd.print("Made by Luca Ponzio");
        delay(4000);
        lcd.clear();

        break;
      }
      break;


    case 7:                             // Zurück zu selector


      lcd.setCursor(0, 2);

      lcd.print("Exit");
      lcd.print(" ");
      lcd.write(4);

      if (ySelectActive == true) {
        delay(400);
        lcd.clear();
        reset();
        runOnce = true;
        menuPage = 0;
        subMenu = 0;


      }




      break;

  }

  lcd.setCursor(0, 3);                         //UI
  lcd.print("+    ");

  lcd.setCursor(8, 3);
  lcd.print(menuPage);
  lcd.print("/");
  lcd.print(pages - 1);


  lcd.setCursor(19, 3);
  lcd.print(">  ");

  writeToEeprom();                          //Schreibt einstellungen ins EEPROM falls geändert

}
