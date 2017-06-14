#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BT_RX 11 //HM10의 TX가 아두이노의 RX
#define BT_TX 13 //HM10의 RX가 아두이노의 TX.. 아두이노 기준으로 선언하는것임을 염두

LiquidCrystal_I2C lcd(0x3F,16,2);
SoftwareSerial BTSerial(BT_RX,BT_TX);

bool sC = false;

void setup() 
{ 
  Serial.begin(9600); 
  // set the data rate for the BT port
  BTSerial.begin(9600);
  lcd.init();
  lcd.backlight();
} 

void loop()
{
  if( BTSerial.available() > 0 )
  { //RECEIVE
    char data = BTSerial.read();
    if( data == '[')
    {
      lcd.clear();
      lcd.print("U:");
      Serial.println();
    }
    else
    {
      lcd.print( data );
    }
    Serial.print( data );
  }

  if( Serial.available() )
  { //SEND
    char data;
    if( !sC )
    {
      data = '[';
      sC = true;
      lcd.clear();
      lcd.print("I:");
      Serial.println();
    }
    else
    {
      data = Serial.read();
      if( data == ' ' ) sC = false;
      else lcd.print( data );
    }
    
    BTSerial.write( data );
    Serial.print( data );
  }
} 
