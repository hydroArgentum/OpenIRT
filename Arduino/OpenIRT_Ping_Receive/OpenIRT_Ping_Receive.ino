//This sketch allows an Arduino to receive IR signals modulated at 38KHz. 
//It then converts the signals into ACSII characters 

//Pin I/O Initiailization------------------------------
#define RECEIVER 2               //IR receiver input pin
int LED = 3;                     //IR LED output pin

//Storage Variables for Faster Serial Reading----------
//digitalRead produces too much overhead at the speed at which IR operates, a faster, lower-level method is needed
#define RESOLUTION 15            //Decreasing this = more accurancy but also more noise in readings 
uint16_t pulses[100][2];          //Allows storage of 10 pulses
uint8_t currentpulse = 0;        //Current pulse counter

//Main Functions---------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.println("Receiving");
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

void data(void) 
{
  int i;                                          //Temporary Variables
  int j;
  String tempString;
  String binString;
  
  for (uint8_t i = 0; i < currentpulse; i++)      //Serial output of storage array
  {              
    //Serial.print(pulses[i][1] * RESOLUTION, DEC);  //For debugging purposes
    //Serial.print('\t');
    if (pulses[i][1]*RESOLUTION <1500)            //If ON Signal from pulse received is approx 1000ms 
    {                                                //Then add a zero to string of binary
      tempString = String(0);
      binString = String(binString+tempString);  
      //Serial.println(0);                        //For debugging
    }
    else
    {
      tempString = String(1);                    //If ON Signal from pulse received is closer to 2000ms
      binString = String(binString+tempString);    //Then add a one to string of binary
      //Serial.println(1);                        //For debugging
    }
  }
  
  //Serial.println(binString);                   //For debugging
  
  for (i=0; i<binString.length(); i+=8)                  //Reads string of binary, "1 byte" at a time, and creates an ASCII character from each byte             
  {
       int totalCount=0;                                 //More temporary index variables
       char tempChar;
       int tempCount=0;
       
       for (j=7;j>=0;j--)                                
       {
         tempChar  = binString.charAt(j+i);              //Read each bit of the string of binary into a character
         tempCount = ((int)tempChar - 48)*pow(2,7-j);    //Convert character into integer, then multiplies it by 2^7-j to get positional value of the  bit (ex: if 1 is 3rd bit from the left, then its value is 4)
         //Serial.print(tempCount);                      //For debugging
         //Serial.print("-");
         if (tempCount != 0)                             //This if statement is to correct errors in operations on Arduinos
         {
           if (j < 6)
           {
             tempCount = tempCount +1;
           }
         }
         //Serial.print(tempCount);                      //For debugging
         //Serial.print(" ");
         totalCount= totalCount+tempCount;               //Add up the values of each bit in the byte 
       }
       Serial.println("  ");
       Serial.println((char)totalCount);                 //Converts the total value into an ASCII character
  } 
}




