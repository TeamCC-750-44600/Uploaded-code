#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;
int ledpin = 13;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
  pinMode(ledpin, OUTPUT);
}

void loop()
{ 
  static int i = 0;
  uint16_t blocks;
  uint16_t type;
  int16_t signature;
  int16_t angle;
      

  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  
  if (blocks)
  {
    i++;
  if (i%50==0)
    {

        signature = (pixy.blocks[i].signature);    
        if(signature == 1)
      {
        digitalWrite(ledpin,  HIGH);
        delay(1000);
        digitalWrite(ledpin,  LOW);        
      }
    }
  }  
}

