String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean token = false;
unsigned long tokTime=0;
unsigned long tokLive=10;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
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
    tokTime--;
  }
  // reset token if session ended
  if (tokTime == 0) token=false;
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
  if(inputString =="-p mypass\n") token = true;
  // reset session time if user working
  tokTime=tokLive;
}
