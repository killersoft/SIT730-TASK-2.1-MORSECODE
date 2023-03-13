int Push_Button = D2;
int External_LED = D6;
int Internal_LED = D7;

int MorseBaseDelayTime = 250;  //1 TIME UNIT
byte PushButtonState = LOW;  // Set this once, no point re-init'ing it in a loop eh !
char MyMorseName[] = "--. .-. . --. --- .-. -.--   "; // "GREGORY" in morse code dots and dashes, with a suitable space for another word or repeat of name.

void setup() {
  pinMode(Push_Button, INPUT_PULLUP);
  pinMode(External_LED, OUTPUT);
  pinMode(Internal_LED, OUTPUT);
}

void loop() {

  PushButtonState = digitalRead(Push_Button); //Read the state of the pushbutton, noting the button is on internal pullup, and grounds when pressed

  if (PushButtonState == LOW) {   // If button is pressed and is grounded
        do // Start the morse code loop do/while
        {
            
            for (int i = 0; i < strlen (MyMorseName); i++) {  // Read the MyMorseName character by character and limited by the length of the array
                char c = MyMorseName[i]; //get next character
                
                if (c=='.'){ // IF A DOT
                   digitalWrite(External_LED, HIGH); //Turn on LED
                   delay(MorseBaseDelayTime); //The length of a dot is 1 time unit.
                }
                if (c=='-'){
                   digitalWrite(External_LED, HIGH); 
                   delay(MorseBaseDelayTime*3); //A dash is 3 time units.
                }
               if (c==' '){ //Notably the LED should already be OFF, so just a matter of making sure the time off is still about correct.
                   delay(MorseBaseDelayTime*3);  //The space between letters is 3 time units
                }
                digitalWrite(External_LED, LOW); // Kill any ON LED's from above
                delay(MorseBaseDelayTime); // The space between symbols (dots and dashes) of the same letter is 1 time unit.
                PushButtonState = digitalRead(Push_Button);  //We need to check for a button push in this for loop to break out and reset !!
                if (PushButtonState == LOW){
                    digitalWrite(Internal_LED, HIGH); //INTERNAL CODE TO SEE ON THE BOARD THAT THE BUTTON WAS PRESSED
                    delay(2000); // JUST LONG ENOUGH TO SEE THE LED CHANGE
                    digitalWrite(Internal_LED, LOW); //TURN OFF THAT LED
                    break; //breaks the for loop and start over
                }
            } //end of for loop
            delay(MorseBaseDelayTime*7); // If we broke out then wait the appropriate amount of time for the next word
        }while(TRUE);
  } //End of outer if
}
