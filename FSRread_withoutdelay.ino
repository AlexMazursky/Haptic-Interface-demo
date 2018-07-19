const int fsrPin = 0;     // the FSR and pulldown are connected to A0
int fsrReading;     // the analog reading from the FSR resistor divider

long previousMillis = 0; // stores the last time the fsrReading is updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 50;  // interval at which to read FSR (milliseconds)


void setup(void) {
  Serial.begin(9600);   
}
 
void loop(void) {
  // Code that runs all the time goes here

  // check to see if it's time to read the FSR; that is, if the 
  // difference between the current time and last time you read 
  // the FSR is bigger than the interval at which you want to 
  // read the FSR.

  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you read the FSR 
    previousMillis = currentMillis;   
    fsrReading = analogRead(fsrPin);   
    Serial.print("Analog reading = ");
    Serial.print(fsrReading);     // the raw analog reading
    Serial.println();
  }
} 
