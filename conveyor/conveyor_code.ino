#define DIST_THRESH 100

void setup() {
  // Distance sensor
  pinMode(I0_5, INPUT);
  // Conveyor
  pinMode(R1_8, OUTPUT);
  digitalWrite(R1_8, LOW);
  // Serial Port Baud Rate
  Serial.begin(9600);
}

void loop() {
  // Distance Sensor Info
  float dist = analogRead(I0_5);
  Serial.println(dist);
  // Control Conveyor
  if (dist > DIST_THRESH){
    // Object detected, stop the conveyor
    digitalWrite(R1_8, LOW);
    // Delay to ensure safety before restarting the conveyor
    delay(1000);
  }
  else{
    // No object detected, start the conveyor
    digitalWrite(R1_8, HIGH);
  }
}
