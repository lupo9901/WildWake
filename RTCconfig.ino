bool getTime()                                                      //Raketenwissenschaft um ausgewählte Zeit und Datum  ins RTC zu schreiben        
{
  if ((timeSetFlag == true) && (dateSetFlag == false)) {
    tm.Hour   = ( timeArray[0] * 10) + timeArray[1] ;
    tm.Minute = ( timeArray[2] * 10) + timeArray[3] ;
    tm.Second = ( timeArray[4] * 10) + timeArray[5] ;
    return true;
  }

  if ((timeSetFlag == false) && (dateSetFlag == true)) {
    tm.Hour   = hour();
    tm.Minute = minute();
    tm.Second = second();
    return true;
  }

}



bool getDate()                        
{
  if ((dateSetFlag == true) && (timeSetFlag == false)) {
    tm.Day    = ( timeArray[0] * 10) + timeArray[1];                  
    tm.Month  = ( timeArray[2] * 10) + timeArray[3];
    tm.Year   = ((( timeArray[4] * 10) + timeArray[5]) + 2000) - 1970;
    return true;

  }

  if ((dateSetFlag == false) && (timeSetFlag == true)) {
    tm.Day    = day();                 
    tm.Month  = month();
    tm.Year   = (year() - 1970);
    return true;

  }
}
