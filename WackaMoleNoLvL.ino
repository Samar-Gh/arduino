/* Sweep
Wack A Mole 1-D 
*/

/**** Header File Include ****/
#include "pitches.h"
#include <Servo.h>
/** Variable Initialization *******/
// create servo object to control a servo
Servo myservo;   
Servo myservo2; 


// notes in the melody:
int melody1[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int melody2[] = {
  NOTE_C5, NOTE_D5, NOTE_D5, NOTE_FS4, 0, 0, 0, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations2[] = {
  4, 4, 8, 2, 16, 16, 16, 16
};


int melody3[] = {
  NOTE_C5, 0, NOTE_B4,0, NOTE_A3, 0,NOTE_B3, NOTE_C5
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int gameoverDurations[] = {
  4,4, 4, 4, 4, 4, 4,4
};

 

// Motor Positon for Horizontal and Vertical Motor
int pos = 90;
int pos1 = 130;

/*
// Reset Motor Positions 
myservo.write(pos);
myservo2.write(pos1);
*/
// Variables used in the Game section
int Point = 0;  // Points scored 
int NextLevel = 0; // Levels Reached 
static int interval = 0; // By how much should the spead increase 

const int  Mole_pos[] = {50,72,95,117,140}; // Fixed Horizontal Angles where the Moles can be seen


/**** Initilizing the Pins on the board ******/
const int buttonPin = 5;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buzzerPin = 8;   //  buzzer on Pin 8
const int Winpoint = 5;    // Points to wind a level.
int Life     = 3;
boolean buttonState;         // variable for reading the pushbutton status
boolean Flag_show = 0;


int GameOver = 0; // Flag for indication

/******** Variables for Random variables ******/
int randIndex,randIndex1;
int delay_time = 500;


boolean button_was_pressed; // previous state


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object -> Horizontal movement
  myservo.write(95);  // Initializing the position of horizontal servo
  
  myservo2.attach(3);  // attaches the servo2 on pin 3 to the servo object -> Vertical movement
  myservo2.write(95);  // Initializing the position of vertical servo
  
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // connect internal pull-up
  Serial.begin(9600); // begin communication
  button_was_pressed = false;
  //
  pinMode(buzzerPin, OUTPUT);
}

/**** Functon to get the status of the Button */
boolean handle_button()
{
  boolean event;
  int button_now_pressed = !digitalRead(buttonPin); // pin low -> pressed

  event = button_now_pressed && !button_was_pressed;
  button_was_pressed = button_now_pressed;
  return event;
}

/**** Functon for happy tone */
void WinTone()
{
  digitalWrite(ledPin, HIGH);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations1[thisNote];
    tone(buzzerPin, melody1[thisNote], noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
    
  }
  digitalWrite(ledPin, LOW);
}
 /**** Functon for disappointed tone */ 
void LooseTone()
{
  digitalWrite(ledPin, HIGH);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations2[thisNote];
    tone(buzzerPin, melody2[thisNote], noteDuration);
    digitalWrite(ledPin, HIGH);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    digitalWrite(ledPin, LOW);
    // stop the tone playing:
    noTone(buzzerPin);
  }  
  digitalWrite(ledPin, LOW);
}

void GameOverTone()
{
  digitalWrite(ledPin, HIGH);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / gameoverDurations[thisNote];
    tone(buzzerPin, melody3[thisNote], noteDuration);
    digitalWrite(ledPin, HIGH);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    digitalWrite(ledPin, LOW);
    // stop the tone playing:
    noTone(buzzerPin);
  }  
  digitalWrite(ledPin, LOW);
}





void vertical(int delay_time)
{
   //Flag_show == 1;
   myservo2.write(80);
   delay(delay_time); 
   myservo2.write(95);
   
}

void game_over(void)
{
  GameOverTone();
  Serial.print("\n****GAME OVER *****\n");
  Point = 0;
  GameOver = 0;
  NextLevel = 0;
  Flag_show = 0;
  Life     = 3;
  delay(5000);
}


void loop() 
{   
  
     if(!GameOver) // If Game is not over
     {
         /*** Move the Mole randomly to one of the holes ****/
         randIndex = random(0,5);     
         //Serial.print("\nrandIndex:\n");
         //Serial.println(randIndex);
         myservo.write(Mole_pos[randIndex]);
         randIndex1 = random(1,8);
         if(randIndex1 == 2 || randIndex1 == 4)
         {   
              Flag_show = 1;       
              delay(500);         
              vertical(delay_time);  // Show the 

              /******** Game Rule *****************/
              buttonState = handle_button();
              if(buttonState == HIGH && Flag_show == 1)
              {
                Point = Point + 1;
                WinTone();
                //Flag_show = 0;
                Serial.print("\nPoint:\n");
                Serial.println(Point); 
              }
              else if(buttonState == LOW && Flag_show == 1)
              {
                Life = Life-1;  // You have 3 Lifes 
                Serial.print("\nLife:\n");
                Serial.println(Life); 
                LooseTone();
                if(Life == 0)
                {
                  game_over();
                  //GameOverTone();
                }
              }
              delay(500);
              Flag_show = 0;
              /********** Game Rule ****************/

         }    
         /************Game Rule***************/
         // buttonState = handle_button();
         //Serial.print("\nbuttonState:\n");
         //Serial.println(buttonState);
         /*if(buttonState == HIGH && Flag_show == 1)
         {
            Point = Point + 1;
            WinTone();
            Flag_show = 0;
            
         }
         else if(buttonState == LOW && Flag_show == 1)
         {
                Life = Life-1;  // You have 3 Lifes 
                LooseTone();
                if(Life <= 0)
                {
                  game_over();
                  GameOverTone();
                }
         }
        {
          GameOver = 1; 
          Point = 0;
        }
        else if (Point == Winpoint)
        {
           NextLevel = 1;
        }
          
         }
         if(Point == 5)
         {
           LooseTone();
          
         }
         }
         /*
         else
         {
                Life = Life-1;  // You have 3 Lifes 
                LooseTone();
                
         }
         if (NextLevel)
         {
            delay_time = delay_time - 100;
         } 
    
            
            
        }
        // If the player has reached the winning point the game is paused    
        if((Point > Winpoint) || (Life <= 0))
        {
          GameOver = 1; 
          Point = 0;
        }
        else if (Point == Winpoint)
        {
           NextLevel = 1;
        }*/
     }
}

