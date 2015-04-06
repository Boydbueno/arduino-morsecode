const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = LOW;   // for checking the state of a pushButton

bool timerActive = false;
long inputTime;
long inputDuration;

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if (isNewState(buttonState)) {

      if (buttonState == HIGH) {
        inputTime = millis();
        timerActive = true;
        // Button is pressed, start measuring time
      } else if(timerActive == true) {
        // On release and active timer
        inputDuration = millis() - inputTime;
        Keyboard.print(inputDuration);
       
        if (isShortPress(inputDuration)) {
          Keyboard.print("Short press");
        } else { // long press
          Keyboard.print("Long press");
        }
        
        timerActive = false;
      }

  }
  // save the current button state for comparison next time
  setNewState(buttonState);
}

bool isNewState(int state) {
  return previousButtonState != state;
}

void setNewState(int state) {
  previousButtonState = state; 
}

bool isShortPress(long duration) {
  return duration <= 300;
}
