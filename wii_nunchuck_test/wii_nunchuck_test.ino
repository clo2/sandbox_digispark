#include <Wire.h>
//#include "DigiKeyboard.h"
#include "DigiMouse.h"
#include <string.h>

#undef int
#include <stdio.h>

uint8_t outbuf[6];    // array to store arduino output
int cnt = 0;
int topLed = 1;
int rightLed = 1;
int bottomLed = 1;
int leftLed = 1;

void nunchuck_init(void)
{
  Wire.beginTransmission (0x52);  // transmit to device 0x52
  Wire.send (0x40);   // sends memory address
  Wire.send (0x00);   // sends sent a zero.  
  Wire.endTransmission ();  // stop transmitting
}

void send_zero(void)
{
  Wire.beginTransmission (0x52);  // transmit to device 0x52
  Wire.send (0x00);   // sends one byte
  Wire.endTransmission ();  // stop transmitting
}


void showDirection() {  
  int x = outbuf[0];
  int y = outbuf[1];

//DigiKeyboard.print("x:"); 
//DigiKeyboard.print(x); 
//DigiKeyboard.print(",y:"); 
//DigiKeyboard.print(y);
//DigiKeyboard.print("\n"); 

 DigiMouse.moveY(y);
 DigiMouse.delay(500);
 DigiMouse.moveX(x);
 DigiMouse.delay(500);

  if (x < 100) {
    digitalWrite(leftLed, HIGH);
//     DigiKeyboard.println("left");
  } 
  else if (100 <= x &&  x < 180) {
    digitalWrite(leftLed, LOW);
    digitalWrite(rightLed, LOW);
  } 
  else {
    digitalWrite(rightLed, HIGH);
//     DigiKeyboard.println("right");
  }

  if (y < 100) {
    digitalWrite(bottomLed, HIGH);
//    DigiKeyboard.println("down");

  } 
  else if (100 <= y &&  y < 180) {
    digitalWrite(bottomLed, LOW);
    digitalWrite(topLed, LOW);
  } 
  else {
    digitalWrite(topLed, HIGH);
//     DigiKeyboard.println("up");
    
  }
}

void setup ()
{
  pinMode(topLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(bottomLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
//  beginSerial (19200);
//  Serial.print ("Finished setup\n");
  Wire.begin ();    // join i2c bus with address 0x52
  nunchuck_init(); // send the initilization handshake
  DigiMouse.begin();
}


void loop ()
{
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
//  DigiKeyboard.sendKeyStroke(0);
  
  Wire.requestFrom (0x52, 6); // request data from nunchuck
  while (Wire.available ()) {
    outbuf[cnt] = nunchuk_decode_byte (Wire.receive ());  // receive byte as an integer
    cnt++;
  }

  // If we recieved the 6 bytes, then go print them
  if (cnt >= 5) {
 //   print ();
    showDirection();
  }

  cnt = 0;
  send_zero (); // send the request for next bytes
  delay (50);
}



// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}
