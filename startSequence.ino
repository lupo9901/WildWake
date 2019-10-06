
int randomVal = 0;
void startSequence(int x, int y) {

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  static bool runOnce = true;
  if (runOnce) {
    lcd.clear();
    backlightCounter = true;
    lcd.setCursor(x, y);

    if (morningMessages == 1) {
      randomVal = random( 0 , 10 );
      lcd.print(messages[randomVal]);
    }

    if (morningMessages == 0) {

      lcd.print("      Waking...");

    }
    runOnce = false;


  }

  digitalWrite(7, HIGH);
  //tone(7, 5);
  if (vibration == 1) {
    digitalWrite(6, HIGH);               //Enable Open collector

  }

  if (digitalRead(button) == LOW) {

    reset();

    if (timeMode == 0) {
      subMenu = 1;
    }
    if (timeMode == 1) {
      subMenu = 0;
    }

    runOnce = true;
    delay(200);

  }


  if (digitalRead(yButton) == LOW) {                          //Snooze funktion

    reset();

    timeArray[0] = (hour()    /   10)   + 0 ;
    timeArray[1] = (hour()    %   10)   + 0 ;
    timeArray[2] = (minute()  /   10)   + (snoozeTime  /   10) ;
    timeArray[3] = (minute()  %   10)   + (snoozeTime  %   10) ;
    timeArray[4] = (second()  /   10)   + 0 ;
    timeArray[5] = (second()  %   10)   + 0 ;
    timeArray[6] = 0 ;

    subMenu = 1;
    runOnce = true;
    delay(200);

  }

  lcd.setCursor(0, 3);
  lcd.print("SNZ   ");

  lcd.setCursor(19, 3);
  lcd.print("X");



}


void nonValidWarning() {
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print("Time not valid");
  delay(1000);
  lcd.clear();

}

void reset() {

  lcd.clear();

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  if (timeMode == 1) {
    memset(timeArray, 0, sizeof(timeArray));
  }

  diffSecs = 0;
  yButtonState = true;
  yButtonStateOld = true;
  yButtonCounter = 0;
  ySelectActive = false;
  xButtonState = true;
  xButtonStateOld = true;
  xState = 0;
  timeOut = false;
  backlightCounter = true;


  lcd.clear();
  lcd.home();
  lcd.print("Loading..");
  delay(500);
  lcd.clear();



}
