#include <SoftwareSerial.h>

SoftwareSerial mySerial(6,7);

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
}

void loop
{
    String RxBuffer = "";
    while(mySerial.available())
    {
        RxBuffer = mySerial.readString();
    }
    if(RxBuffer == "1")
    {
        Serial.Println("re trai");
    }else if(RxBuffer == "2")
    {
        Serial.Println("re phai");
    }else if(RxBuffer == "0")
    {
        Serial.Println("dung");
    }
}