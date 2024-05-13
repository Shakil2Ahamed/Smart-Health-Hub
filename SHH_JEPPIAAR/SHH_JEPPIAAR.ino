#define BLYNK_TEMPLATE_ID "TMPL31VcwVmqC"
#define BLYNK_TEMPLATE_NAME "iot amm"
#define BLYNK_AUTH_TOKEN "0utzif1i039ohBUkCjF6bcs6cUsprbgC"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define auth  "0utzif1i039ohBUkCjF6bcs6cUsprbgC"
const char * ssid = "iotdata";
const char * password = "12345678";
#include<LiquidCrystal.h>
LiquidCrystal lcd(19, 18, 5, 4, 2, 15); //19,18,5,4,2,15

//#include <SoftwareSerial.h>
//SoftwareSerial RFID(14,27); // RX and TX

#include <ESP32Servo.h>
#define servoPin1 14
#define servoPin2 27
#define servoPin3 26 
#define servoPin4 33

#define buz 23
#define red 21
#define green 22

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;


char c;
String tablet_count , tablet,text,CardNumber,msg;
String t1, t2, t3, t4, c1, c2, c3, c4;
int tn1,tn2,tn3,tn4,tc1,tc2,tc3,tc4;
 int count1 = 0,count2 = 0,count3 = 0,count4 = 0,card_flag=0;
BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V0) {

  tablet = param.asString();
  Serial.print("tablet");
  Serial.println(tablet);
}
BLYNK_WRITE(V1) {

  tablet_count = param.asString();
  Serial.print("tablet_count=");
  Serial.println(tablet_count);

}

void setup()
{
  pinMode(13,INPUT_PULLUP);
  pinMode(25,INPUT_PULLUP);
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  
  myservo1.attach(servoPin1);  // attaches the servo on ESP32 pin
  myservo2.attach(servoPin2);
   myservo3.attach(servoPin3);
    myservo4.attach(servoPin4);
    myservo1.write(0);
myservo2.write(0);
myservo3.write(0);
myservo4.write(0);
  
  Serial.begin(9600);
   Serial2.begin(9600);
  Serial.println("Bring your RFID Card Closer...");
  //CardNumber = "1F00693104"; 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONNECTING WIFI ");
  delay(1000);
  Blynk.begin(auth, ssid, password);
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONNECTED ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO SHH ");
  delay(2000);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
}
void loop()
{

  Blynk.run();
  Blynk.syncVirtual(V0, V1);
  if (tablet > "0000") 
  {
    t1 = tablet.substring(0, 1);
    t2 = tablet.substring(1, 2);
    t3 = tablet.substring(2, 3);
    t4 = tablet.substring(3, 4);
     // int myInt = myString.toInt();
    tn1=t1.toInt();
     tn2=t2.toInt();
      tn3=t3.toInt();
       tn4=t4.toInt();
    Serial.print("t1=");
    Serial.println(tn1);
    Serial.print("t2=");
    Serial.println(tn2);
    Serial.print("t3=");
    Serial.println(tn3);
    Serial.print("t4=");
    Serial.println(tn4);
    delay(1000);
  }
  if (tablet_count > "0000")
  {
    c1 = tablet_count.substring(0, 1);
    c2 = tablet_count.substring(1, 2);
    c3 = tablet_count.substring(2, 3);
    c4 = tablet_count.substring(3, 4);
    tc1=c1.toInt();
        tc2=c2.toInt();
            tc3=c3.toInt();
                tc4=c4.toInt();
    Serial.print("c1=");
    Serial.println(tc1);
    Serial.print("c2=");
    Serial.println(tc2);
    Serial.print("c3=");
    Serial.println(tc3);
    Serial.print("c4=");
    Serial.println(tc4);
    delay(1000);
  }

  //---------------------------------------------------------------------
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SHOW YOUR RFID");
  delay(2000);
  while (Serial2.available() > 0) {
    delay(5);
    c = Serial2.read();
    text += c;
  }
  if (text.length() > 20)
  {
    text = text.substring(1, 11);
  Serial.println("Card ID : " + text);
  //Serial.println("Access ID : " + CardNumber);

    if(text=="530020DB45")
  {
    if(tablet=="0000"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NO TABLETS FETCHED ");
      delay(2000);
    }
  else{
    card_flag=1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACCESS ACCEPTED ");
  delay(2000);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MAKE YOUR PAYMENT");
  delay(3000);
  while(digitalRead(13)&&digitalRead(25));
  if(digitalRead(13)==0)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(green,HIGH);
  lcd.print("PAYMENT SUCCESS");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PROCESSING");
  delay(2000);
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FETCHING TABLET");
  lcd.setCursor(0,1);
  lcd.print(" DETAILS  ");
  delay(2000);
  digitalWrite(green,LOW);
  
  if((card_flag==1) &&((tn1 == 1 && tc1 > 0)||(tn2 == 1 && tc2 > 0)||(tn3 == 1 && tc3 > 0)||(tn4 == 1 && tc4 > 0)))
  {
  
    while(count1 < tc1) {
      Serial.println("servo1 on");
      myservo1.write(100);
      delay(150);
      myservo1.write(0);
      delay(1000);
      count1++;
      Serial.print("count1=");
      Serial.println(count1);
       delay(1000);
    }
     while(count2< tc2) {
      Serial.println("servo2 on");
      myservo2.write(100);
      delay(150); 
      myservo2.write(0);
      delay(1000);
      count2++;
      Serial.print("count2=");
      Serial.println(count2);
      delay(1000);
      
    }
     while(count3< tc3) {
      Serial.println("servo3 on");
      myservo3.write(120);
      delay(150);
      myservo3.write(0);
      delay(1000);
      count3++;
      Serial.print("count3=");
      Serial.println(count3);
       delay(1000);
    }
     while(count4< tc4) {
      Serial.println("servo4 on");
      myservo4.write(80);
      delay(130);
      myservo4.write(0);
      delay(1000);
      count4++;
      Serial.print("count4=");
      Serial.println(count4);
      delay(1000);
    }
  
  count1 = 0;
    t1="0";
    c1="0";
    count2 = 0;
    t2="0";
    c2="0";
    count3 = 0;
    t3="0";
    c3="0";
    count4 = 0;
    t4="0";
    c4="0";
    card_flag=0;
    text="";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("COLLECT YOUR ");
  lcd.setCursor(0,1);
  lcd.print("     TABLETS     ");
  Blynk.logEvent("warning","TABLET COLLETCTED SUCCESSFULLY");
  msg="TABLET COLLECTED SUCCESFULLY ";
  text=" ";
  delay(2000);
  }
  }//END FOR YES BUTTON 
  if(digitalRead(25)==0)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PAYMENT DENIED");
  digitalWrite(red,HIGH);
  digitalWrite(buz,HIGH);
  delay(2000);
  digitalWrite(red,LOW);
  digitalWrite(buz,LOW);
    
    }
 text =" ";
}
  }
else if(text=="530020D137")
{
  lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(red,HIGH);
  digitalWrite(buz,HIGH);
  lcd.print("ACCESS DENIED");
  delay(2000);
  text = "";
  Blynk.logEvent("warning","UNAUTHORIZED USER"); }
  digitalWrite(red,LOW);
  digitalWrite(buz,LOW);
  text = "";
 }

}
