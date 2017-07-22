#include <IRremote.h>
#include <SoftwareSerial.h>

int RECV_PIN = 11; 
//int LED = 6;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
String readString;
SoftwareSerial Bluetooth(6, 7);

void setup(){
   
  //pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("ready!");
  Bluetooth.println("ready!");

  irrecv.enableIRIn(); // Start the receiver

}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
 // int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
    Bluetooth.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
    Bluetooth.print("Decoded NEC:");
  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
    Bluetooth.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
    Bluetooth.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
    Bluetooth.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");

    Bluetooth.print("Decoded PANASONIC - Address: ");
    Bluetooth.print(results->address, HEX);
    Bluetooth.print(" Value: ");
    
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
    Bluetooth.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
    Bluetooth.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
    Bluetooth.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
    Bluetooth.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  delay(500);
  Bluetooth.print(results->value, HEX);
  Bluetooth.print(" (");
  Bluetooth.print(results->bits, DEC);
  Bluetooth.println(" bits)");
  
  delay(500);
   }


void loop() {

while (Bluetooth.available())
  {
    delay(3);
    char c = Bluetooth.read();
    readString += c;
  }

 if (readString.length() >0)
  {
Serial.println(readString);

      String String_Received, Received_button, Received_bits, Received_types;
      int Counter1, Counter2; 
      String_Received = readString;
      Counter1 = String_Received.indexOf(',');
      Received_button = String_Received.substring(0,Counter1);
      char chararray1[Received_button.length()+1];
      Received_button.toCharArray(chararray1, Received_button.length()+1);
      long int Sending1 = strtoul(chararray1, 0, 16); 
      Counter2 = String_Received.lastIndexOf(',');
      Received_bits = String_Received.substring(Counter1,Counter2);
      Received_bits.replace(",", "");
      char chararray2[Received_bits.length()+1];
      Received_bits.toCharArray(chararray2, Received_bits.length()+1);
      long int Sending2 = strtoul(chararray2, 0, 16); 
      Received_types = String_Received.substring(Counter2);
      Received_types.replace(",","");
      char chararray3[Received_types.length()+1];
      Received_types.toCharArray(chararray3, Received_types.length()+1);
      long int Sending3 = strtoul(chararray3, 0, 16);
      Serial.println("Command received from Phone:");
      Serial.println(Received_button);
      Serial.println(Received_bits);
      Serial.println(Received_types);
      Serial.println(Sending1, HEX);
      Serial.println(Sending2, HEX);
      Serial.println(Sending3, HEX);
      delay(100);
      if(Received_types == "panasonic"){
      irsend.sendPanasonic(Sending2,Sending1);
      Bluetooth.println(Received_types+" Type Sent.");
      //leds();
      }
      else if(Received_types == "nec"){
      irsend.sendNEC(Sending1,32);
      Bluetooth.println(Received_types+" Type Sent. "+"Data:"+Received_button+" Bits:"+Received_bits);
      
      //leds();
      }
      else if(Received_types == "sony"){
      irsend.sendSony(Sending1, Sending2); 
      Bluetooth.println(Received_types+" Type Sent.");
      //leds();
      }
      else if(Received_types == "rc5"){
      irsend.sendRC5(Sending1, Sending2); 
      Bluetooth.println(Received_types+" Type Sent.");
      //leds();
      }
      else if(Received_types == "rc6"){
      irsend.sendRC6(Sending1, Sending2); 
      Bluetooth.println(Received_types+" Type Sent.");
      //leds();
      }
      delay(100); 
      readString="";
      irrecv.enableIRIn();
  
    }

    else if(irrecv.decode(&results)) {
   //Serial.println(results.value, HEX);
   dump(&results);
   irrecv.resume();}
   

}

/*
void leds(){
 digitalWrite(LED, HIGH);
 delay(100); 
  digitalWrite(LED, LOW);
  delay(100);
}*/






