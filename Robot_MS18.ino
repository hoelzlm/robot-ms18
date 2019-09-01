#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600

const char* ssid = "FRITZ!Box 7590 WO";
const char* password = "05698604142397323383";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test!");

  WiFi.mode(WIFI_STA);
  WiFi.hostname("Robot MS18");
  WiFi.begin(ssid, password);

  Serial.println(" WiFi connecting ..");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  // Start the (HTTP)-server

  server.on("/move", handelRequest);

  server.begin();
  Serial.println("Server started");


  pwm.begin();
  
  pwm.setPWMFreq(60);

  delay(10);
}

void loop() {
  server.handleClient();
}

void handelRequest() {


  if (server.arg("base")== ""){     //Parameter not found
    
  }else{     //Parameter found
    int value = (server.arg("base")).toInt();     //Gets the value of the query parameter
    turnBase(value);
  }
  
  if (server.arg("arm0")== ""){     //Parameter not found
    
  }else{     //Parameter found
    int value = (server.arg("arm0")).toInt();     //Gets the value of the query parameter
    turnMainArm(value);
  }

  if (server.arg("arm1")== ""){     //Parameter not found
    
  }else{     //Parameter found
    int value = (server.arg("arm1")).toInt();     //Gets the value of the query parameter
    turnArm1(value);
  }

  if (server.arg("arm2")== ""){     //Parameter not found
    
  }else{     //Parameter found
    int value = (server.arg("arm2")).toInt();     //Gets the value of the query parameter
    turnArm2(value);
  }
   
  server.send(200, "text / plain", "moved");
  
}

void straigthPos() {
  turnMainArm(90);
  delay(500);
  turnArm1(90);
  delay(500);
  turnArm2(90);
}

void homePos() {
  turnMainArm(40);
  turnArm1(60);
  turnArm2(180);
}


void turnBase(int value) {
  int pulselength = map(value, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(0, 0, pulselength);
}

void turnMainArm(int value) {
  int pulselength = map(value, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(1, 0, pulselength);
}

void turnArm1(int value) {
  int pulselength = map(value, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(2, 0, pulselength);
}

void turnArm2(int value) {
  int pulselength = map(value, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(3, 0, pulselength);
}

void turnGripper(int value) {
  int pulselength = map(value, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(4, 0, pulselength);
}
