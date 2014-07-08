//This sketch allows an Arduino to send an IR signals modulated at 38KHz. 
//It also converts a string of ASCII text into pulse train for output

//Text to Send-----------------------------------------
#define STRING "Hello World"

//Pin I/O Initiailization------------------------------
int LED = 3;                     //IR LED output pin

//Main Functions---------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()                  // Simple ping test to see if two different arduinos can send and receive pulses representing ASCII Letters
{ 
  sendPulse();               //Sends 38KHz modulated signal from IR LED
  delay(1000);
}

//Transmission Functions-------------------------------
void sendPulse()                                
{
  int i;                                        //Temporary variables                           
  int j;
  char tempChar;
  String charString;
  String tempString;
  String binString;
  
  pulse(64000);                                  //Header Delay (Will include frame delimiters, addressing, and options later on if needed)
  delayMicroseconds(64000);
  charString = STRING;                           //Get String of text
  //Serial.println(charString);                  //For debugging purposes
  
  for (i=0; i<charString.length(); i++)          //For loop converts string of text into string of binary code
  {
    tempChar = charString.charAt(i);             //Read each character of the string of text
    for(j=7;j>=0;j--)    
    {
      byte a = bitRead(tempChar, j);             //Convert each character into a ASCII equivalent binary
      tempString = String(a);                    //Use temporary variable to store current byte
      binString = String(binString+tempString);  //Add current byte to string of binary
    }
  } 
  //Serial.println(binString);                  //For debugging purposes
  
  for(i=0;i<binString.length();i++)               //Sends binary code as a pulse train to receiver         
  {
    tempChar = binString.charAt(i);               //Reads each bit of the binary code    
    if (tempChar = '0')                           //If bit is zero, sends an ON signal for 1000us and OFF signal for 1000us
    {
       pulse(1000);
       delayMicroseconds(1000);
    }
    if (tempChar = '1')                          //If bit is one, sends an ON signal for 2000us and OFF signal for 1000us
    {
       pulse(2000);
       delayMicroseconds(1000);
    }
  }
  
  pulse(64000);                                           //Footer delay (May include a frame check sequence later if needed)
  delayMicroseconds(64000);
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
  
    



