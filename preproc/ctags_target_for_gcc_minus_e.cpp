# 1 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
# 1 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"

# 3 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino" 2
# 4 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino" 2

MPU6050 mpu6050(Wire);
# 16 "C:\\Users\\Linh\\Máy tính\\MPU_2905221\\MPU_2905221.ino"
float z =0 ;
long timer = 0;
int motorspeed = 40;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(13, 0x1);
  pinMode(12, 0x1);
  pinMode(11, 0x1);
  pinMode(10, 0x1);
  pinMode(9, 0x1);
  pinMode(8, 0x1);
}

void di_thang()
{
  digitalWrite(8, 0x0);
  digitalWrite(13, 0x0);
  digitalWrite(12, 0x0);
  digitalWrite(9, 0x0);
  analogWrite(10, 100);
  analogWrite(11, 112);
  digitalWrite(8, 0x1);
  digitalWrite(13, 0x1);

}

void rephai()
{
  digitalWrite(8, 0x0);
  digitalWrite(13, 0x0);
  digitalWrite(12, 0x0);
  digitalWrite(9, 0x0);
  digitalWrite(10, 0);
  analogWrite(11, 100);
  digitalWrite(8, 0x1);
  digitalWrite(13, 0x1);

}

void dung()
{
  digitalWrite(8, 0x0);
  digitalWrite(13, 0x0);
}


float Kp = 1;
int pwm2 = 112;

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
      if(pwm2 > 112 +10) pwm2 = 112 +10;
      if(pwm2 < 112 -5 ) pwm2 = 112 -5;
    }
    else
    {
      pwm2 = 112;
    }
    analogWrite(11,pwm2);

    if(state == 2 && timer > 10000)
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
