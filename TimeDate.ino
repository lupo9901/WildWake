void displayTime(int x, int y) {                 //Formatierung für Zeit

  lcd.setCursor(x, y);
  if (hour() >= 10) {
    lcd.print(hour());
  } else {
    lcd.print("0");
    lcd.print(hour());
  }
  lcd.print(":");
  if (minute() >= 10) {
    lcd.print (minute());
  } else {
    lcd.print("0");
    lcd.print(minute());
  }
  lcd.print(":");
  if (second() >= 10) {
    lcd.print (second());
  } else {
    lcd.print("0");
    lcd.print(second());
  }
}

void displayDate(int x, int y) {                      //Formatoierung für Datum
  lcd.setCursor(x, y);
  if (day() >= 10) {
    lcd.print (day());
  } else {
    lcd.print("0");
    lcd.print(day());
  }
  lcd.print(".");
  if (month() >= 10) {
    lcd.print (month());
  } else {
    lcd.print("0");
    lcd.print(month());
  }
  lcd.print(".");
  lcd.print(year());
}

void displayTarget(int x, int y, int hs, int ms, int ss) {                    //Formatierung für Startzeit

  lcd.setCursor(x, y);
  if (hs >= 10) {
    lcd.print(hs);
  } else {
    lcd.print("0");
    lcd.print(hs);
  }
  lcd.print(":");
  if (ms >= 10) {
    lcd.print (ms);
  } else {
    lcd.print("0");
    lcd.print(ms);
  }
  lcd.print(":");
  if (ss >= 10) {
    lcd.print (ss);
  } else {
    lcd.print("0");
    lcd.print(ss);
  }


}
