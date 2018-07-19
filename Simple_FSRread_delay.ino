int fsrPin = 0;     // the FSR and pulldown are connected to A0
int fsrReading;     // the analog reading from the FSR resistor divider
 
void setup(void) {
  Serial.begin(9600);   
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin);   
  
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading
  
  delay(10);
} 
