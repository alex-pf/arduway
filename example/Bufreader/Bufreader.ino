String pass;

void setup() {
	Serial.begin(9600);
 
 Serial.println("Please enter password");
}

void loop() {
  Serial.println("Insert text:");
  int i = 0;
  pass = Serial.readString();
  Serial.print("The text:");
  Serial.println(pass);
}
