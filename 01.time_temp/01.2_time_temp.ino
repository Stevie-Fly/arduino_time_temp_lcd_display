#include <TFT_HX8357_Due.h> // https://github.com/Bodmer/TFT_HX8357_Due
#include <Sodaq_DS3231.h>  //RTC Library https://github.com/SodaqMoja/Sodaq_DS3231


float minTemperature = 100;
float maxTemperature = -40;
String dateString;
String hours;
int minuteNow=0;
int minutePrevious=0;

TFT_HX8357_Due tft = TFT_HX8357_Due();       // Invoke custom library

void setup()
{  
  rtc.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(0xC618);
  delay(100);
  printUI();
  //setRTCTime();    //kommentarfunktion rausnehmen, wenn uhrzeit eingestellt wird, einmal hochladen, dann wieder als kommentar und nochmlas upload.

}

void loop()
{
   float temperature = rtc.getTemperature();
   getAndPrintTime();
   printTemperature(temperature);
   if(temperature>maxTemperature)
  {
    maxTemperature = temperature;
    updateMaxTemperature();
  }
  if(temperature<minTemperature)
  {
    minTemperature = temperature;
    updateMinTemperature();
  }

 delay(1000);

}

void printUI()
{ 
 printDateRectangle(); 
 printTemperatureRectangle();
 printMinTemperatureRectangle();
 printMaxTemperatureRectangle();
}

void printDateRectangle()
{
  tft.fillRect(40, 7, 400,60, 0xA000);
  tft.fillRect(40, 5, 400,53, TFT_RED);
}

void printTemperatureRectangle()
{
  tft.fillRect(80, 90, 320, 125, 0x03C0);
  tft.fillRect(80, 90, 320, 120, 0x0640);

  tft.setCursor(320,130);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(10);
  tft.print("C");

  tft.setCursor(300,130);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.print("o");

  }

void printMinTemperatureRectangle()
{

  tft.fillRect(40, 251, 160, 59, 0x0015);
  tft.fillRect(40, 251, 160, 55, 0x001C);

  tft.setCursor(175,265);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(4);
  tft.print("C");

  tft.setCursor(160,258);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print("o");

}

void printMaxTemperatureRectangle()
{
  
  tft.fillRect(280, 251, 160, 59, 0x8200);
  tft.fillRect(280, 251, 160, 55, 0xDB20);


  tft.setCursor(415,265);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(4);
  tft.print("C");

  tft.setCursor(400,258);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print("o");
}

void getAndPrintTime()
{
   DateTime now = rtc.now(); //get the current date-time
   minuteNow = now.minute();
   if(minuteNow!=minutePrevious)
   {
      dateString = getDayOfWeek(now.dayOfWeek())+" ";
      dateString = dateString+String(now.date())+"/"+String(now.month());
      minutePrevious = minuteNow;
      hours = String(now.hour());
    if(now.minute()<10)
    {
      hours = hours+":0"+String(now.minute());
    }else
    {
      hours = hours+":"+String(now.minute());
    }
    printTime();
   }
}

void printTime()
{
  String dateAndTime = dateString+" "+hours;

  tft.setTextSize(2);
  char charBuf[25];
  dateAndTime.toCharArray(charBuf, 25);
  
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawCentreString(charBuf,240,15,2);

}

void setRTCTime()
{
  DateTime dt(2023, 5, 15, 16, 3, 55, 1); // Year, Month, Day, Hour, Minutes, Seconds, Day of Week
  rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
}

String getDayOfWeek(int i)
{
  switch(i)
  {
    case 1: return "Monday";break;
    case 2: return "Tuesday";break;
    case 3: return "Wednesday";break;
    case 4: return "Thursday";break;
    case 5: return "Friday";break;
    case 6: return "Saturday";break;
    case 7: return "Sunday";break;
    default: return "Monday";break;
  }
}

void printTemperature(float temperature)
{
  String Temperature;
  Temperature = String(temperature,2); 
  tft.setTextSize(6);
  tft.setCursor(110,130);
  tft.setTextColor(TFT_WHITE, 0x0640);
  tft.print(Temperature);
}

void updateMinTemperature()
{
  String Temperature;
  Temperature = String(minTemperature,2); 
  tft.setTextSize(3);
  tft.setCursor(57,270);
  tft.setTextColor(TFT_WHITE, 0x001C);
  tft.print(Temperature);
  
}

void updateMaxTemperature()
{
  String Temperature;
  Temperature = String(maxTemperature,2); 
  tft.setTextSize(3);
  tft.setCursor(297,270);
  tft.setTextColor(TFT_WHITE, 0xDB20);
  tft.print(Temperature);
}