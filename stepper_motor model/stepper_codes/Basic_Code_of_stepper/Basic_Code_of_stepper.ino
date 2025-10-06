#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 4 // Example pin for enable control

int micro_factor = 8;  //microstepping factor depends on the configuration of ms1 and ms2.
int counter;

void setup() {
  Serial.begin(115200);
  Serial.print("Start");
  digitalWrite(DIR_PIN, 1);
}


void loop() {
  //stepper.runSpeed();
  // put your main code here, to run repeatedly:
 // note that when dir = 1, ccw || dir = 0, cw

     for (uint16_t i = 0; i < 200*8; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2000);

    counter++;
    Serial.print("Current position:");
    Serial.print(counter);
    Serial.println();

      
  } 
}




