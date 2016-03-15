#include <Regexp.h>

int led = 13;
String inputString = "";         // a string to hold incoming data
String uPass="";
String Password="1";
boolean stringComplete = false;  // whether the string is complete
boolean token = false;
unsigned long tokTime=0;
unsigned long tokLive=10;

boolean itsKey(char k, String inputString) {
  char buf [inputString.length()];
  inputString.toCharArray(buf,inputString.length());
  MatchState ms (buf);
  char kBuf[9] = "^\-?[\s]*";
  kBuf[2]=k;
  if (ms.MatchCount(kBuf)>0) return true;
  else return false;
}


void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("Parametrs:");
  Serial.println("-p <password>");
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(inputString);
    inputString = "";
    stringComplete = false;
  }
  // print Ping and token tomer if user authorized
  if(tokTime>0 and token){
    delay (3000);
    Serial.print("Ping ");
    Serial.println(tokTime);
    Serial.println(uPass);
    tokTime--;
  }
  // reset token if session ended
  if (tokTime == 0) {
    token=false;
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') stringComplete = true;
  }
  // set token if user eters the password
  if(itsKey('p', inputString)) {
    uPass = inputString;
    uPass.replace("-p ","");
    uPass.trim();
    if(uPass==Password) {
      token = true;
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  }
  // reset session time if user working
  tokTime=tokLive;
}
