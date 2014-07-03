//This sketch allows an arduino to receive IR signals modulated at 38KHz. 
//It is meant to be used a ping test.

//Storage Variables for Faster Serial Reading----------
//digitalRead produces too much overhead at the speed at which IR operates, a faster, lower-level method is needed
#define RECEIVER 2               //IR receiver input pin
#define SAMPLING 20     //Decreasing this = more accurancy but also more noise in readings 
uint16_t pulses[100][2];          //Allows storage of 10 pulses
uint8_t currentpulse = 0;        //Current pulse counter

//Main Functions---------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Receiving");
  Serial.println("Pulses in microseconds");
  Serial.println("OFF \t ON");
}

void loop()                  // Simple ping test to see if two different arduinos can send and receive arbirtary pulses
{
  getPulse();                //Receives 38KHz modulated signals from environment
}

//Transmission Functions-------------------------------
void getPulse()                   // Mostly adapted from AdaFruit
{
  uint16_t ONpulse   = 0;         //Initializes temporary counters for on and off pulses
  uint16_t OFFpulse  = 0;         //Have to be uint16_t to be compatabile with storage array
  
  while (PIND & (1<< RECEIVER))         //Reads for "ON" pulses and their lengths faster than digitalRead
  {
    ONpulse++;                          //Increment ONpulse counter until no more HIGH signal
    delayMicroseconds(SAMPLING)  
    
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
     delayMicroseconds(SAMPLING);
     
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

void data(void) 
{
  Serial.println("------");
  for (uint8_t i = 0; i < currentpulse; i++)  //Serial output of storage array
  {
    Serial.print(pulses[i][0] * SAMPLING, DEC);     //**Multiply by 20 to make up for delay in getPulse function
    Serial.print("\t");                
    Serial.println(pulses[i][1] * SAMPLING, DEC);
  }
}



