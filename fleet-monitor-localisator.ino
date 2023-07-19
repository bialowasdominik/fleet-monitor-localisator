#include <TinyGPS++.h>
#include <SoftwareSerial.h>

String apn = "internet";
String url = "http://10.0.0.1:82/api/device/1/position";
String data,time,result;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(9, 8);
SoftwareSerial gsmSerial(11,10);

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);
  Serial.println("---DEVICE START---");
  gsm_config_gprs();
}

void loop()
{
  gpsSerial.listen();
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      prepare_data();
  if (millis() > 60000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void prepare_data()
{
  if (gps.location.isValid()&&gps.date.isValid()&&gps.time.isValid())
  {
    data = String(gps.date.year())+"-"
    +((gps.date.month()<10)?"0"+String(gps.date.month()):String(gps.date.month()))+"-"
    +((gps.date.day()<10)?"0"+String(gps.date.day()):String(gps.date.day()));
    
    time = ((gps.time.hour()<10)?"0"+String(gps.time.hour()):String(gps.time.hour()))
    +":"+((gps.time.minute()<10)?"0"+String(gps.time.minute()):String(gps.time.minute()))
    +":"+((gps.time.second()<10)?"0"+String(gps.time.second()):String(gps.time.second())); 
    
    result = "{\"Longitude\": \""+String(gps.location.lng(), 6)+"\",\"Latitude\": \""
    +String(gps.location.lat(), 6)+"\",\"Time\": \""+data+"T"+time+"\",\"DeviceId\": \"1\"}";
    
    Serial.println(result);
    gsm_http_post(result);
  }
  else
  {
    Serial.println("GPS DATA NOT AVAILABLE");
  }
  Serial.println();
  delay(1000);
}

void gsm_http_post(String postdata) {
  gsm_send_serial("AT+HTTPDATA=192,5000");
  gsm_send_serial(postdata);
  gsm_send_serial("AT+HTTPACTION=1");
}

void gsm_config_gprs() {
  gsm_send_serial("AT+SAPBR=3,1,Contype,GPRS");
  gsm_send_serial("AT+SAPBR=3,1,APN," + apn);
  gsm_send_serial("AT+SAPBR=1,1");
  gsm_send_serial("AT+SAPBR=2,1");
  gsm_send_serial("AT+HTTPINIT");
  gsm_send_serial("AT+HTTPPARA=CID,1");
  gsm_send_serial("AT+HTTPPARA=URL," + url);
  gsm_send_serial("AT+HTTPPARA=CONTENT,application/json");
}

void gsm_send_serial(String command) {
  gsmSerial.listen();
  Serial.println("Send ->: " + command);
  gsmSerial.println(command);
  long wtimer = millis();
  while (wtimer + 3000 > millis()) {
    while (gsmSerial.available()) {
      Serial.write(gsmSerial.read());
    }
  }
  Serial.println();
}
