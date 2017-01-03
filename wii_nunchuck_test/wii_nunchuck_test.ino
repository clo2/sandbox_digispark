#include <Wire.h>
//#include "DigiKeyboard.h"
#include "DigiMouse.h"
#include <string.h>

#undef int
#include <stdio.h>

uint8_t gl_outbuf[6];    // array to store arduino output
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


void procLoop() {
  int x = gl_outbuf[0];
  int y = gl_outbuf[1];

  int joy_x_axis = gl_outbuf[0];
  int joy_y_axis = gl_outbuf[1];
  int accel_x_axis = gl_outbuf[2];
  int accel_y_axis = gl_outbuf[3];
  int accel_z_axis = gl_outbuf[4];

  int z_button = 0;
  int c_button = 0;

  // byte gl_outbuf[5] contains bits for z and c buttons
  // it also contains the least significant bits for the accelerometer data
  // so we have to check each bit of byte gl_outbuf[5]
  if ((gl_outbuf[5] >> 0) & 1) z_button = 1;
  if ((gl_outbuf[5] >> 1) & 1) c_button = 1;

  if ((gl_outbuf[5] >> 2) & 1) accel_x_axis += 2;
  if ((gl_outbuf[5] >> 3) & 1) accel_x_axis += 1;

  if ((gl_outbuf[5] >> 4) & 1) accel_y_axis += 2;
  if ((gl_outbuf[5] >> 5) & 1) accel_y_axis += 1;

  if ((gl_outbuf[5] >> 6) & 1) accel_z_axis += 2;
  if ((gl_outbuf[5] >> 7) & 1) accel_z_axis += 1;

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
    gl_outbuf[cnt] = nunchuk_decode_byte (Wire.receive ());  // receive byte as an integer
    cnt++;
  }

  // If we recieved the 6 bytes, then go print them
  if (cnt >= 5)
  {
    procLoop();
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
