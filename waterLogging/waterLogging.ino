#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
const char* AP = "realme 7";       // AP NAME
const char* PASS= "revanth04"; // AP PASSWORD
String API = "JX9B4DHLYWYSVN4K";   // API KEY
String HOST = "http://api.thingspeak.com";  // 

String field = "field1";


const int trigPin=8;
const int echoPin=7;
// const int pump=6;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(pump,OUTPUT);
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  //connecting wifi
  WiFi.begin(AP,PASS);
  while(WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(500);
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

int getSensorData(){
  long time, dist;
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin,LOW);
  time = pulseIn(echoPin,HIGH);
  dist = (time/2)/29.1;
  delay(1000);
  //Serial.println(dist);
  return dist;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED){
    int reading= getSensorData();
    String path= HOST+"/update?api_key="+ API +"&"+ field +"="+String(reading);
    HTTPClient http;
    Serial.println(path);
    http.begin(wifiClient,path.c_str());
    int httpCode = http.GET();
    if (httpCode>0){
      Serial.println("Data sending");

    }
    http.end();
  }
  delay(2000);

}
