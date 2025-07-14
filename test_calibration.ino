// Arduino Speedometer - Test and Calibration Tool
// This sketch helps test and calibrate your speedometer setup

// Test configuration - adjust these to match your setup
const float wheelCircumference = 1.922; // Your wheel circumference in meters
const int pulsesPerRevolution = 48;     // Your sensor pulses per revolution

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Speedometer - Test & Calibration Tool");
  Serial.println("=============================================");
  Serial.println();
  
  // Display current configuration
  Serial.println("Current Configuration:");
  Serial.println("Wheel circumference: " + String(wheelCircumference) + " m");
  Serial.println("Pulses per revolution: " + String(pulsesPerRevolution));
  Serial.println();
  
  // Test calculations
  runSpeedTests();
  runDistanceTests();
  
  Serial.println();
  Serial.println("Calibration Help:");
  Serial.println("1. To measure wheel circumference: mark tire, roll one complete revolution, measure distance");
  Serial.println("2. To count pulses per revolution: rotate wheel slowly and count sensor pulses");
  Serial.println("3. To verify: compare calculated speed with GPS speed during test drive");
}

void loop() {
  // Static test - no loop needed
  delay(10000);
}

void runSpeedTests() {
  Serial.println("Speed Calculation Tests:");
  Serial.println("------------------------");
  
  // Test different pulse rates
  int testPulses[] = {10, 24, 48, 96, 144}; // Pulses in 1 second
  
  for (int i = 0; i < 5; i++) {
    float revolutions = (float)testPulses[i] / pulsesPerRevolution;
    float speed_kmh = (revolutions * wheelCircumference) * 3.6;
    float speed_mph = speed_kmh * 0.621371;
    
    Serial.println("Pulses: " + String(testPulses[i]) + 
                   " → Speed: " + String(speed_kmh, 1) + " km/h (" + 
                   String(speed_mph, 1) + " mph)");
  }
  Serial.println();
}

void runDistanceTests() {
  Serial.println("Distance Calculation Tests:");
  Serial.println("---------------------------");
  
  // Test different revolution counts
  int testRevolutions[] = {1, 10, 100, 1000}; // Number of wheel revolutions
  
  for (int i = 0; i < 4; i++) {
    float distance_m = testRevolutions[i] * wheelCircumference;
    float distance_km = distance_m / 1000.0;
    float distance_miles = distance_km * 0.621371;
    
    Serial.println("Revolutions: " + String(testRevolutions[i]) + 
                   " → Distance: " + String(distance_m, 1) + " m (" + 
                   String(distance_km, 3) + " km, " + 
                   String(distance_miles, 3) + " miles)");
  }
  Serial.println();
}

// Helper function to calculate wheel circumference from tire size
float calculateCircumference(int rimDiameter, int tireWidth, int aspectRatio) {
  // rimDiameter in inches, tireWidth in mm, aspectRatio as percentage
  float rimRadius_m = (rimDiameter * 25.4) / 2000.0; // Convert inches to meters
  float tireHeight_m = (tireWidth * aspectRatio / 100.0) / 1000.0; // Convert mm to meters
  float wheelRadius_m = rimRadius_m + tireHeight_m;
  return 2.0 * 3.14159 * wheelRadius_m;
}