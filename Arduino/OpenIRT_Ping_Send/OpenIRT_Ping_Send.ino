//This sketch allows an Arduino to send an arbitary pattern of IR signals modulated at 38KHz. 
//It is meant to be used a ping test.

//Pin I/O Initiailization------------------------------
int LED = 3;                     //IR LED output pin

//Main Functions---------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()                  // Simple ping test to see if two different arduinos can send and receive arbirtary pulses
{ 
  sendPulse();               //Sends 38KHz modulated signal from IR LED
  delay(1000);
}

//Transmission Functions-------------------------------
void sendPulse()
{
  int i=0;
  for (i=0; i<3;i++)              //Send an arbitary pulse pattern 3 times
  {
    pulse(2000);                  // 38KHz Modulated "ON" Pulse
    delayMicroseconds(1500);      // "Off" Pulse
    pulse(370);
    delayMicroseconds(800);
    pulse(1700);
    delayMicroseconds(400);  
    pulse(660);
    delayMicroseconds(1000);
    Serial.println("Sent");
  }
}

void pulse(long microseconds)     //**Adapted from pulseIR code found on Adafruit
{
  cli();                          // Turn off background interrupts to reduce overhead
  while (microseconds > 0)           //38KHz Modulation (13us on and 13us off) to reduce noise
  {
     digitalWrite(LED, HIGH);  
     delayMicroseconds(10);                                     
     digitalWrite(LED, LOW);   
     delayMicroseconds(10);                                         
     microseconds -= 26;            //Subtract the 26us to perform this operation from total time
  }
  sei();                          // Turn them back on
}
  
    



