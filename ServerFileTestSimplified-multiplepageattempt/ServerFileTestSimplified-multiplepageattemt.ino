#include <Wifi_S08_v2.h>

#define SSID "BLURP"
#define PASSWD "MOMENTUM"
#define BLINKPERIOD 1000
#define UPDATEPERIOD 1000

ESP8266 wifi = ESP8266(1,false);
String html = "<html>\n<title>It works!</title>\n<body>\n<h1>Congrats</h1>\n<p>You have successfully interneted.</p>\n</body>\n</html>";
int val = 0;
int light = 0;

int led = 13;
int senseL = 15;
int senseR = 14;

int lastupdate = millis();
int blinktime = millis();

char html2[500], htmlvalues[100];

void setup() {
  pinMode(led, OUTPUT);
  pinMode(senseL, INPUT);
  pinMode(senseR, INPUT);
  Serial.begin(115200);
  wifi.begin();
  Serial.println("startserver");
  wifi.startserver(SSID, PASSWD);
  Serial.println("setup complete");
  wifi.setPage("/",html);
  wifi.setPage("/values.html",html);
}

int valL;
int valR;

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println((millis()-lastupdate));
  int m = millis() - lastupdate;
  if(m > UPDATEPERIOD){
    val++;
    valL = analogRead(senseL);
    valR = analogRead(senseR);
    
    sprintf(html2,"<html>\n<body>\n<h1>Current Photoresistor Values</h1>\n<p>Left Photoresistor: %d</p>\n<p>Right Photoresistor: %d</p>\n</body>\n</html>",valL, valR);
    wifi.setPage("/",html2);
    sprintf(htmlvalues, "<html>\n<body>\n<p>~%d~%d`</p>\n</body>\n</html>",valL, valR);
    wifi.setPage("/values.html",htmlvalues);
    lastupdate = millis();
  }
  m = millis() - blinktime;
  if(m > BLINKPERIOD){
    if (light == 1){
      Serial.println("blink");
      light = 0;
      digitalWrite(led, LOW);
    }
    else{
      light = 1;
      digitalWrite(led, HIGH);
    }
    blinktime = millis();
  }
}
