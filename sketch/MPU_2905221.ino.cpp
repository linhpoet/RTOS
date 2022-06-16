#include <Arduino.h>
#line 1 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
#line 1 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

#define ENA 13
#define IN1 12
#define IN2 11
#define IN3 10
#define IN4 9
#define ENB 8

#define pwm 112

float z =0 ;
long timer = 0;
int motorspeed = 40;

#line 20 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void setup();
#line 33 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void di_thang();
#line 46 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void rephai();
#line 59 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void dung();
#line 72 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void loop();
#line 20 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void di_thang()
{
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW); 
  digitalWrite(IN4, LOW);
  analogWrite(IN3, 100);
  analogWrite(IN2, pwm);
  digitalWrite(ENB, HIGH);
  digitalWrite(ENA, HIGH);

}

void rephai()
{
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW); 
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, 0);
  analogWrite(IN2, 100);
  digitalWrite(ENB, HIGH);
  digitalWrite(ENA, HIGH);

}

void dung()
{
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);
}


float Kp = 1;
int pwm2 = pwm;

int state = 1;
float z0;

void loop() {
    timer = millis();
    mpu6050.update();
    if(state == 1)
    {
    
    Serial.print("Lấy z0: ");
    z = mpu6050.getAngleZ();
    z0 = z;
    Serial.println(z0);
    di_thang();
    state ++;
    }
    z = mpu6050.getAngleZ(); //state 2 , vd : z=10;
    Serial.print("z=");
    Serial.println(z);
    Serial.print("z0=");
    Serial.println(z0);
    Serial.print("\pwm2=");
    Serial.println(pwm2);
    Serial.println(timer);
    if ((z - z0) > 0.1 || (z - z0) < 0.1)
    {
      pwm2 = pwm2 + Kp*(float)(z-z0);
      if(pwm2 > pwm+10) pwm2 = pwm+10;
      if(pwm2 < pwm-5 ) pwm2 = pwm-5;
    }
    else
    {
      pwm2 = pwm;
    }
    analogWrite(IN2,pwm2);

    if(state ==  2 && timer > 10000)
    {
      dung();
      delay(500);
      rephai();
      while(z + 82 > 0)
      {
        mpu6050.update();
        z = mpu6050.getAngleZ(); //state 2 , vd : z=10;
        Serial.println(z);
      }
      state++;
      z0 = z;
      di_thang();
    }
  

}

