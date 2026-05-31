#include <SoftwareSerial.h>
SoftwareSerial btSerial(2, 3); // RX, TX
int spd = 80;               // 設定速度值0-255
int timer = 500;           // 定義整數 timer

const int IN1 = 10;          //L298N IN1 pin 連接 Arduino pin 10
const int IN2 = 11;          //L298N IN2 pin 連接 Arduino pin 11
const int IN3 = 5;           //L298N IN3 pin 連接 Arduino pin 5
const int IN4 = 6;           //L298N IN4 pin 連接 Arduino pin 6

int Distset=5;               //設定車子和障礙物之間的最小距離5公分
int trigPin = 7;             //距離感測器Trig pin to Arduino pin 7
int echoPin = 8;             //距離感測器Echo pin to Arduino pin 8
long duration, distance;      //設定參數 duration and distance


void setup() 
{
  btSerial.begin(9600);
  Serial.begin(9600);     //確認藍牙傳輸速率 9600 bits/second
  pinMode(6,OUTPUT);      // Arduino 輸出電壓控制車子
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  delay(500);  
}

void loop() {            
  
  digitalWrite(trigPin, LOW);   //超音波距離感測器測定距離 distance
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);            //印出距離值 distance 在序列埠螢幕上
  

 if(distance > Distset ) {            //當距離大於所設定的最短距離 5cm 時，車子保持前進
    Forward();
    delay(100);
 }
  else                                 //當距離小於 5 cm 時，車子停止 0.5秒，後退 0.5秒，並右轉 1.0秒
   {
     Stop();
     delay(500);
     Back();
     delay(500);
    Right();
    delay(1000);
   }
  

  
  if (btSerial.available())
  {     
    char i = btSerial.read();    //把讀到的資料丟給i，這次是用char
    Serial.println(i);

    if(i == 'a')
      Forward ();
    if(i == 'b')
      Right();
    if(i == 'c')
      Back ();
    if(i == 'd')
      Left();  
    if(i == 'g')
      Stop();
    
 
}
}

void Forward(void)          //車子前進子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
} 

void Back(void)              //車子後退子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, spd);
  analogWrite(IN3,0 );
  analogWrite(IN4, spd);
} 

void Stop(void)              //車子停止子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void Left(void)              //車子左轉子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
} 

void Right(void)             //車子右轉子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
} 
