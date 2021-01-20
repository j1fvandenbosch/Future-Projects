/*
  Once upon a time there was a super cheesey but awesome show called 
  Knight Rider on NBC. (I'm dating myself here). 
  
  Anyways, the star of the show was a super intelligent (sometimes cranky & sassy), 
  car named Kit. 

  A supped up pontiac firebird Trans Am, complete with rocket launchers & NOS

  One of the coolest parts of Kit, was his scrolling Red Led's in the front of the car.

  Just google knightrider and Kit and you'll see what I mean.
  
  So.... I thought it might be cool to make Dr.Duino's built in LED's do the same thing.
   
  Ours will be green instead of red though :)
  
  So Let'jump right in!
    
  Created by Guido Bonelli, Inventor of The Dr.Duino Shield
  www.DrDuino.com  
*/
long time2Delay =0;// Generic variable for storage
int DrDuinoLed[] = {13,11,10,6,5};// Storing Pin numbers attached to LED's.

void setup() 
{
  //First lets tell the Arduino what pins the LED's of the DrDuino shield are attached to.
  for (int i =0; i<5; i++)
  {
     pinMode(DrDuinoLed[i], OUTPUT);   //Set each I/O pin in the led array to an output
  }
}

void loop() 
{
 
  
  time2Delay = random(1,6); //Pic a random value between 1&6 for a delay time.
                            //Kit would often change the rate at which the Lights would fade
                            //back and forth. So this seemed appropriate :)

  // Begin turning on LED's 11 through 5 by fading them on then off
  // Note that LED 13 is not part of this, as it doesn't support PWM directly. 
  // You could make it into a PWM pin however by doing some bit banging. 
  
  for(int i =1; i<5; i++)
  {
    for(int Fade =0; Fade<255; Fade += 10)
    {
      analogWrite(DrDuinoLed[i], Fade);
      delay(time2Delay);
    }

    
    for(int Fade =255; Fade>=0; Fade -=10)
    {
      analogWrite(DrDuinoLed[i], Fade);
      delay(time2Delay);
    }
  }

  //-----------------Reverse direction now from LED 5 back to 11
  // Note that LED 13 is not part of this, as it doesn't support PWM directly. 
  // You could make it into a PWM pin however by doing some bit banging. 

  for(int i =3; i>=2; i--)
  {
  
   for(int Fade =0; Fade<255; Fade += 10)
    {
      analogWrite(DrDuinoLed[i], Fade);
      delay(time2Delay);
    }

    
    for(int Fade =255; Fade>=0; Fade -=10)
    {
      analogWrite(DrDuinoLed[i], Fade);
      delay(time2Delay);
    }
  }
}

