
//Pin I/O Initiailization------------------------------
#define RECEIVER 2               //IR receiver input pin
int LED = 3;                     //IR LED output pin

//Storage Variables for Faster Serial Reading----------
//digitalRead produces too much overhead at the speed at which IR operates, a faster, lower-level method is needed
#define RESOLUTION 20            //Decreasing this = more accurancy but also more noise in readings 
uint16_t pulses[100][2];         //Allows storage of 10 pulses
uint8_t currentpulse = 0;        //Current pulse counter

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
    Serial.println("Sending");
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



void getPulse()                   // Mostly adapted from AdaFruit, rewrite if possible
{
  uint16_t ONpulse   = 0;         //Initializes temporary counters for on and off pulses
  uint16_t OFFpulse  = 0;         //Have to be uint16_t to be compatabile with storage array
  
  while (PIND & (1<< RECEIVER))         //Reads for "ON" pulses and their lengths faster than digitalRead
  {
    ONpulse++;                          //Increment ONpulse counter until no more HIGH signal
    delayMicroseconds(RESOLUTION);        
    
    if ((ONpulse >= 65000) && (currentpulse != 0)) //If pulse train has ended (if signal stays HIGH):
    {                                                  //Write storage array to serial comm. and reset
       data();
       currentpulse=0;
       return;
     }
  }
  pulses[currentpulse][0] = ONpulse;  //Write to "ON" column of storage array

  while (! (PIND & _BV(RECEIVER)))      //Reads for "OFF" pulses and their lengths faster than digitalRead
  {
     OFFpulse++;                        //Increment OFFpulse counter until there is no more LOW signal
     delayMicroseconds(RESOLUTION);
     
     if ((OFFpulse >= 65000) && (currentpulse != 0)) //If pulse train has ended (if signal stays LOW):
     {                                                  //Write storage array to serial comm. and reset
       data();
       currentpulse=0;
       return;
     }
  }
  pulses[currentpulse][1] = OFFpulse; //Write to "OFF" column of storage array
  currentpulse++;                     //Increment current pulse counter
}

//Auxuiliary Functions------------------------------
void data(void) 
{
  Serial.println("Pulses in microseconds");
  Serial.println("OFF \t ON");
  for (uint8_t i = 0; i < currentpulse; i++)  //Serial output of storage array
  {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);     //**Multiply by 20 to make up for delay in getPulse function
    Serial.print("\t");                
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
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
  


