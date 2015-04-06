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

        if(inputDuration <= 30) {
           return; 
        }
        Serial.println(inputDuration);

        if(millis() - chainDuration >= 1000) {
          chainLength = 0;
        }    

        chainDuration = millis();

        chainLength++;

        if (isShortPress()) {
          durationChain[chainLength-1] = SHORT;
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
      }
      
      if (durationChain[0] == LONG) {
        Keyboard.write('t'); 
      }   
    } else if (chainLength == 2) {
      if (durationChain[0] == SHORT) {
        if (durationChain[1] == SHORT) {
          Keyboard.write('i');  
        } else if (durationChain[1] == LONG) {
          Keyboard.write('a');
        }
      } else if (durationChain[0] == LONG) {
        if(durationChain[1] == SHORT) {
          Keyboard.write('n'); 
        } else if (durationChain[1] == LONG) {
          Keyboard.write('m');
        } 
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
  return inputDuration <= 300;
}

bool isButtonPressed() {
 return buttonState == HIGH;
}

bool isButtonReleased() {
 return buttonState == LOW;
}
