const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = LOW;   // for checking the state of a pushButton

int buttonState;

bool timerActive = false;
long inputTime;
long inputDuration;

enum duration {
  SHORT,
  LONG 
};

duration durationChain[4];
int chainLength = 0;
long chainDuration;

void setup() {
  pinMode(buttonPin, INPUT);
  chainDuration = millis();
  Keyboard.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (hasNewButtonState()) {

      if (isButtonPressed()) {
        inputTime = millis();
      } else if(isButtonReleased())  {
        // Measure input duration time
        inputDuration = millis() - inputTime;

        if(inputDuration <= 55) {
           return; 
        }
        Serial.println(inputDuration);

        if(millis() - chainDuration >= 1000) {
          chainLength = 0;
        }    

        chainDuration = millis();

        if(chainLength == 5) {
          chainLength = 0;  
        }
        
        chainLength++;
                
        if (isShortPress()) {
          durationChain[chainLength-1] = SHORT;
        } else if(isVeryLongPress()) {
          removePreviousCharacter();
          chainLength = 0;
        } else { // long press
          durationChain[chainLength-1] = LONG;
        } 
       
        if (chainLength > 1) {
          removePreviousCharacter();  
        }  
          
        outputCharacter();
      }

  }
  // save the current button state for comparison next time
  setNewState(buttonState);
}

void removePreviousCharacter() {
  Keyboard.write(8);
}

void outputCharacter() {
    if (chainLength == 1) {
      if (durationChain[0] == SHORT) {
        Keyboard.write('e');  
      } else if (durationChain[0] == LONG) {
        Keyboard.write('t'); 
      }
    } else if (chainLength == 2) {
      if (durationChain[0] == SHORT && durationChain[1] == SHORT) {
          Keyboard.write('i');  
      } else if (durationChain[0] == SHORT && durationChain[1] == LONG) {
          Keyboard.write('a');
      } else if (durationChain[0] == LONG && durationChain[1] == SHORT) {
          Keyboard.write('n'); 
      } else if (durationChain[1] == LONG && durationChain[1] == LONG) {
          Keyboard.write('m');
      }
    } else if (chainLength == 3) {
       if (durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == SHORT) {
          Keyboard.write('s');
       } else if(durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == LONG) {
          Keyboard.write('u'); 
       } else if(durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == SHORT) {
          Keyboard.write('r'); 
       } else if(durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == LONG) {
          Keyboard.write('w'); 
       } else if(durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == SHORT) {
          Keyboard.write('d'); 
       } else if(durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == LONG) {
          Keyboard.write('k'); 
       } else if(durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == SHORT) {
          Keyboard.write('g');
       } else if(durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == LONG) {
          Keyboard.write('o'); 
       }
    } else if (chainLength == 4) {
      if (durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == SHORT && durationChain[3] == SHORT) {
        Keyboard.write('h');
      } else if (durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == SHORT && durationChain[3] == LONG) {
        Keyboard.write('v');
      } else if (durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == LONG && durationChain[3] == SHORT) {
        Keyboard.write('f');
      } else if (durationChain[0] == SHORT && durationChain[1] == SHORT && durationChain[2] == LONG && durationChain[3] == LONG) {
        Keyboard.write(176);
      } else if (durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == SHORT && durationChain[3] == SHORT) {
        Keyboard.write('l');
      } else if (durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == SHORT && durationChain[3] == LONG) {
        Keyboard.write('ä');
      } else if (durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == LONG && durationChain[3] == SHORT) {
        Keyboard.write('p');
      } else if (durationChain[0] == SHORT && durationChain[1] == LONG && durationChain[2] == LONG && durationChain[3] == LONG) {
        Keyboard.write('j');
      } else if (durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == SHORT && durationChain[3] == SHORT) {
        Keyboard.write('b');
      } else if (durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == SHORT && durationChain[3] == LONG) {
        Keyboard.write('x');
      } else if (durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == LONG && durationChain[3] == SHORT) {
        Keyboard.write('c');
      } else if (durationChain[0] == LONG && durationChain[1] == SHORT && durationChain[2] == LONG && durationChain[3] == LONG) {
        Keyboard.write('y');
      } else if (durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == SHORT && durationChain[3] == SHORT) {
        Keyboard.write('z');
      } else if (durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == SHORT && durationChain[3] == LONG) {
        Keyboard.write('q');
      } else if (durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == LONG && durationChain[3] == SHORT) {
        Keyboard.write('ö');
      } else if (durationChain[0] == LONG && durationChain[1] == LONG && durationChain[2] == LONG && durationChain[3] == LONG) {
        Keyboard.write(' ');
      }
    }
}

bool hasNewButtonState() {
  return previousButtonState != buttonState;
}

void setNewState(int state) {
  previousButtonState = state; 
}

bool isShortPress() {
  return inputDuration <= 200;
}

bool isVeryLongPress() {
  return inputDuration >= 800;
}

bool isButtonPressed() {
 return buttonState == HIGH;
}

bool isButtonReleased() {
 return buttonState == LOW;
}
