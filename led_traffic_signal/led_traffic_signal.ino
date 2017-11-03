
#define PIN_0 0 // PWM/I2C_SDA
#define PIN_1 1 // PWM
#define PIN_2 2 //AD1/I2C_SCL
#define PIN_3 3 //AD3/PWM/USB_D-
#define PIN_4 4 //AD2/PWM/USB_D+
#define PIN_5 5 //AD0
//trafic
#define PIN_G PIN_2
#define PIN_Y PIN_1
#define PIN_R PIN_0
#define DELAY_G 7000
#define DELAY_Y 2000
#define DELAY_R 4000
//brink ON/OFF
#define BLINK_ON false
#define BLINK_OFF true
void setup(){
  pinMode(PIN_G, true);
  pinMode(PIN_Y, true);
  pinMode(PIN_R, true);
}

void loop(){
  static int flg=0;
  clearLed();
  brinkLed(flg);
  setDelay(flg);


  flg++;
  if(flg >=3)
  {
    flg =0;
  }
  delay(1000);
}

static void clearLed()
{
  digitalWrite(PIN_G, BLINK_OFF);
  digitalWrite(PIN_Y, BLINK_OFF);
  digitalWrite(PIN_R, BLINK_OFF);
}

static void brinkLed(int flg)
{
  switch(flg)
  {
  case 0:
    digitalWrite(PIN_G,BLINK_ON);
    break;
  case 1:
    digitalWrite(PIN_Y,BLINK_ON);
    break;
  case 2:
    digitalWrite(PIN_R,BLINK_ON);
    break;
  }  
}
static void setDelay(int flg)
{
  int val_delay = 0;
  switch(flg)
  {
  case 0:
    val_delay = DELAY_G;
    break;
  case 1:
    val_delay = DELAY_Y;
    break;
  case 2:
    val_delay = DELAY_R;
    break;
  }
  delay(val_delay);

}

