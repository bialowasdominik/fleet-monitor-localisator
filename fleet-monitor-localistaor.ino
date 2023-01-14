#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
StaticJsonDocument<200> jsonBuffer; 

int gpsRxPin = 3;
int gpsTxPin = 2;
int gsmTxPin = 7;
int gsmRxPin = 6;
int serialBaud = 9600;
bool gpsReady = false;
bool gsmReady = false;

TinyGPSPlus gps;
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial gpsSerial(gpsRxPin, gpsTxPin);
SoftwareSerial gsmSerial(gsmTxPin,gsmRxPin);

//Custom chars
byte signalAntena[] = {
  B11111,
  B10101,
  B00100,
  B00100,
  B01110,
  B00100,
  B00100,
  B00100
};

byte gsmSignalOneLine[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte gsmSignalTwoLine[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte gsmSignalThreeLine[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte sateliteIcon[] = {
  B00000,
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B01110,
  B00100
};

void setup()
{
  Serial.begin(serialBaud);
  gpsSerial.begin(serialBaud);
  gsmSerial.begin(serialBaud);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, signalAntena);
  lcd.createChar(1, gsmSignalOneLine);
  lcd.createChar(2, gsmSignalTwoLine);
  lcd.createChar(3, gsmSignalThreeLine);
  lcd.createChar(4, sateliteIcon);
  DynamicJsonDocument jsonBuffer(1024);
}


void loop()
{
  if(gpsReady == false && gsmReady == false){
      showLoadingScreen();
    }
  else{
    showPulpit();
    //sendLocationData();
   }
}

void sendLocationData()
{}

void showPulpit()
{
  showGpsSatelites();
  showGsmSignal();
}

void showGpsSatelites()
{
  gpsSerial.listen();
  lcd.setCursor(0, 0);
  lcd.write((byte)4);
  lcd.setCursor(1,0);
  lcd.print(gps.satellites.value());
  if (gps.location.isValid())
  {
    lcdPrintMessage(0,1,"                ");
    lcdPrintMessage(0,1,"Lat: " + String(gps.location.lat()));
    delay(1500);
    lcdPrintMessage(0,1,"                ");
    lcdPrintMessage(0,1,"Lon: "+String(gps.location.lng()));
    delay(1500);
  }
  else{
    lcdPrintMessage(0,1,"                ");
    lcdPrintMessage(0,1,"Not Available");
    delay(1500);   
  }
}

void showGsmSignal()
{  
  lcd.setCursor(12, 0);
  lcd.write((byte)0);
  gsmSerial.listen();
  gsmSerial.println("AT+CSQ");
  int val = gsmSerial.read();
  val = map(val,0,31,0,3);
  switch(val){
    case 1:
      lcd.setCursor(13, 0);
      lcd.write((byte)1);
      break;
    case 2:
      lcd.setCursor(13, 0);
      lcd.write((byte)1);
      lcd.setCursor(14, 0);
      lcd.write((byte)2);
      break;
    case 3:
      lcd.setCursor(13, 0);
      lcd.write((byte)1);
      lcd.setCursor(14, 0);
      lcd.write((byte)2);
      lcd.setCursor(15, 0);
      lcd.write((byte)3);
      break;
  }
  
}
int updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gsmSerial.write(Serial.read());
  }
  while(gsmSerial.available()) 
  {
    Serial.write(gsmSerial.read());
  }
}

void showLoadingScreen(){
  if(gpsReady == false){
    gpsSerial.listen();
    lcd.clear();
    showInitialLoading();
    lcdPrintMessage(0,1,"GPS: ");
    showInitialLoading();
    if(gpsSerial.available() > 0){
        showInitialLoading();
        lcdPrintMessage(5,1,"OK");
        showInitialLoading();
        gpsReady == true;
      }
    else{
        lcdPrintMessage(5,1,"FAILED");
        showInitialLoading();
      }
  }
  if(gsmReady == false){
    gsmSerial.listen();
    lcd.clear();
    showInitialLoading();
    lcdPrintMessage(0,1,"GSM: ");
    showInitialLoading();
    gsmSerial.println("AT");
    if(gsmSerial.read() == -1)
    {
        showInitialLoading();
        lcdPrintMessage(5,1,"OK");
        showInitialLoading();
        gpsReady = true;
        lcd.clear();
    }
    else
    {
      lcdPrintMessage(5,1,"FAILED");
      showInitialLoading();
    }
    }
}

void lcdPrintMessage(int height, int width, String message){
  lcd.setCursor(height,width);
  lcd.print(message);
}

void showInitialLoading(){
    lcdPrintMessage(0,0,"Initializing");
    lcdPrintMessage(12,0,".");
    delay(200);
    lcdPrintMessage(13,0,".");
    delay(200);
    lcdPrintMessage(14,0,".");
    delay(200);
    lcdPrintMessage(14,0," ");
    delay(200);
    lcdPrintMessage(13,0," ");
    delay(200);
    lcdPrintMessage(12,0," ");
    delay(200);
}
