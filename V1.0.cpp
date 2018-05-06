// GOFi2cOLED is the display library that I use.
// Here is a link to the creators' GitHub page https://github.com/hramrach/GOFi2cOLED
// Here is their website where I found details about it and a few examples (the website is currently not working)
//  http://www.geekonfire.com/wiki/index.php?title=I2C_OLED_Panel(128x64)#Example_Demonstrations
#include <GOFi2cOLED.h>
 
GOFi2cOLED lcd;
 
// This is a character buffer that will store the data from Serial port
char rxData[20];
 
char inChar=0;
int rxIndex=0, flag=0;
 
void setup()
{
  // Initializing the OLED Display
  lcd.init(0x3C);
  lcd.setTextSize(1);
  lcd.setTextColor(WHITE);
  lcd.setCursor(0,0);
 
  // Initializing the Vcc Pin for HC-05 as the OLED is occupying the 5V pin
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
 
  // Run a quick test of the display at the same time allowing us to enter AT mode
  // by holding down on the button on HC-05
  lcd.display();
  delay(2000);
 
  Serial.begin(38400);  
 
  while(!Serial)
  {
    ;
  }
 
  lcd.clearDisplay();
 
 
 
  Serial.println("AT");  
  getResponse();
 
  lcd.clearDisplay();
  lcd.println(rxData);
  lcd.display();
 
  /*
  Serial.println("AT+UART?");
  getResponse();
 
  lcd.setCursor(0,32);
  lcd.println(rxData);
  lcd.display();
  */
}//End of setup
 
void loop()
{
 
}
 
// The getResponse function collects incoming data from the UART into rxData buffer
// and only exits when a carriage return character is seen.
void getResponse()
{
  while(inChar != '\n')
  {
    if(Serial.available() > 0)
    {
      flag = 1;
      if(Serial.peek() == '\n')
      {
        inChar = Serial.read();
        rxData[rxIndex]='\0';
        rxIndex=0;
      }
      else
      {
        inChar = Serial.read();
        rxData += inChar;
        rxIndex++;
        //rxData[rxIndex++] = inChar;
      }
    }
  }
}//End of UDF
 
// Thank you for spending your time to help me out :)
