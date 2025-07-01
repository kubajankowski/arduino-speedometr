const int signalPin = 2;           
volatile unsigned int pulses = 0;
unsigned long previousTime = 0;
float wheelCircumference = 1.922; //17" wheel, 225/40 tire
int pulsesPerRevolution = 1;       

void setup() {
  pinMode(signalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(signalPin), countPulse, RISING);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();
  if (now - previousTime >= 1000) { // Every second
    float revolutions = (float)pulses / pulsesPerRevolution;
    float speed = (revolutions * wheelCircumference) * 3.6; // m/s to km/h
    Serial.print("Speed km/h: ");
    Serial.println(speed);

    pulses = 0;
    previousTime = now;
  }
}

void countPulse() {
  pulses++;
}
