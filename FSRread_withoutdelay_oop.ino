class FSR
{
  // Class Member Variables
  int fsrPin;     // the FSR and pulldown are connected to A0
  int fsrReading;     // the analog reading from the FSR resistor divider
  // State Maintenance
  unsigned long previousMillis; // stores the last time the fsrReading is updated
  long interval = 50;  // interval at which to read FSR (milliseconds)

  // Constructor - creates an FSR 
  // and initializes the member variables and state
  public:
  FSR(int pin)
  {
  fsrPin = pin;
  previousMillis = 0;
  }

  void Update()
  {// check to see if it's time to read the FSR; that is, if the 
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
};

FSR fsr(0); // Assign FSR to pin A0

void setup() {
  Serial.begin(9600);   
}
 
void loop() {
  fsr.Update();  
} 
