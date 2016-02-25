#include <Regexp.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

boolean itsKey(char k, String inputString) {
  char buf [inputString.length()];
  inputString.toCharArray(buf,inputString.length());
  MatchState ms (buf);
  char kBuf[9] = "^\-?[\s]*";
  kBuf[2]=k;
  Serial.println(kBuf);
  if (ms.MatchCount(kBuf)>0) return true;
  else return false;
}


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(itsKey('p', inputString)) Serial.println("It's password");
    else Serial.println("It's not password!---");
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  delay (3000);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}