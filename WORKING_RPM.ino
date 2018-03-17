#include<GOFi2cOLED.h>
#include<SoftwareSerial.h>

GOFi2cOLED lcd;
SoftwareSerial bt(10, 11); //Rx,Tx

//char rxData[20];
int rxIndex, spd, rpm;

void setup()
{
  spd = rpm = 0;
  lcd.init(0x3C);
  lcd.setTextSize(2);
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 0);

  bt.begin(38400);
  Serial.begin(38400);
  delay(2);
  bt.write("2121\r");
  while (bt.available() < 1)
  {}
  lcd.display();
  delay(1000);
  //lcd.clearDisplay();
}

void loop()
{
  spd = 0;
  lcd.clearDisplay();
  lcd.setCursor(0, 0);
  lcd.println("RPM:");
  //lcd.display();
  bt.println("2121");
  spd = getData(spd);
  lcd.setCursor(0, 16);
  lcd.println(spd);
  lcd.display();
  bt.flush();
  delay(500);
}

int getData(int a)
{
  char inChar = 'a';
  char rxData[20];
  rxIndex = a;

  while (bt.available())
  {
    
    if (bt.peek() == "\r")
    {
      //inChar = '\r';
    }
    else
    {
      inChar = bt.read();
      //delay(1);
      rxData[rxIndex++] = inChar;
    }
  }

  if (rxIndex == 0)
  {
    return -1;
  }
  else
  {
    //SPD = rxData[11]
    //Serial.println(((strtol(&rxData[9],0,16))*256 + strtol(&rxData[12],0,16))/4);
    //Serial.println(rxData[11]);
    Serial.println((strtol(&rxData[10],0,16)*256 + strtol(&rxData[13],0,16))/4);
    //Serial.println(rxData);
    //Serial.println(rxData);
    return ((strtol(&rxData[10],0,16)*256 + strtol(&rxData[13],0,16))/4);
    //return (strtol(rxData[10],0,16));
  }
}


