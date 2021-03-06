int state; //the state of the button
unsigned long Time; //Time to debounce switch
int input;

enum Button
{
  Idle,
  Wait,
  Low
}; //Glob var holding status of button

Button ButtonState;
int ButtonNextState(int input) //function that is to be called in loop
{
  switch (ButtonState)
  {
    case Idle: //State where nothing is happening
      {
        if (input == LOW) //If button is LOW
        {
          Time = millis(); //Record time of high to low transition
          ButtonState = Wait; //Move to Wait
          digitalWrite(13, HIGH); //Turns the LED on
        }
        break;
      }//end Idle

    case Wait: // When Button LOW; Wait for 5 millis
      {
        if (input == HIGH) //If button is HIGH
        {
          ButtonState = Idle;
        }
        else if (millis() - Time >= 5) //If 5 millis has passed
        {
          ButtonState = Low; //Setting button state to LOW
          digitalWrite(13, LOW); //Turns LED off
          return 1; //The button has been pressed
        }
        break;
      }//end Wait

    case Low: //Sets Button to LOW
      {
        if (input == HIGH)
        {
          ButtonState = Idle;
        }
        break;
      }//end Low
  }//end switch-case
  return 0;
}//end ButtonNextState
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(4, INPUT);
  Button ButtonState = Idle;
  Serial.begin(9600);
}

void loop()
{
  state = ButtonNextState(digitalRead(4)); //Calls function continually
  if (state)
  {
    Serial.println("Button has been pressed");
  }
}

