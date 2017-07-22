#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);
 
char c=' ';
char c2=' ';
void setup() 
{
    // start the serial communication with the computer
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
}
 
void loop()
{
 
     // Read from HC-05 and send to Arduino Serial Monitor
    if (Serial.available())
    {  
        c = Serial.read();
        mySerial.write(c);

    }
   else if (mySerial.available())
    {
      c = mySerial.read();
        Serial.write(c);
    }
 
 
}

