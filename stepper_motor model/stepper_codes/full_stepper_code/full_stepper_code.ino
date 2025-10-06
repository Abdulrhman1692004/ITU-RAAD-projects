#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 4 // Example pin for enable control

float waitTime = 0.03;
int accelerationTerm = 80;
int roundedWaitTime;
int counter;
int dir= 1;//if dir = 1, CCW|| if dir = 0, CW

int micro_factor = 8;  //microstepping factor depends on the configuration of ms1 and ms2.



void setup() {
  Serial.begin(115200);
  Serial.print("Start");
}


void loop() {
  //stepper.runSpeed();
  // put your main code here, to run repeatedly:
digitalWrite(DIR_PIN, dir);

//rotate1constspeed(11, micro_factor);
full_rot_accelrate(micro_factor, dir);
}

//NOTE: you gotta determine your minimum and maximum accelration, positive be it or negative in these two function:
//function to return the next delay value for positive acceleration
float positiveAcceleration(float waitTime) {
    float dVelocity = waitTime * accelerationTerm;
    waitTime = 1/(dVelocity+(1/waitTime));
    if(waitTime < 0.0001){
      waitTime = 0.0001;
    }
    return waitTime;
     
}
//function to return the next delay value for negative acceleration
float negativeAcceleration(float waitTime) {
    float dVelocity = waitTime * -1 * accelerationTerm;
    waitTime = 1/(dVelocity+1/waitTime);
    return waitTime;
    
}

void rotate1constspeed(int rpm, int factor, int dir) {
  int t = 3/(160 * rpm);
     for (uint16_t i = 0; i < 200*factor; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(t);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(t);
        if(dir == 1){
      counter++;

    }
    if(dir == 0){
      counter--;
    }
  }  
}
void full_rot_accelrate(int factor, int dir){
  for(int x = 0; x < 200*factor; x++) {
    waitTime = positiveAcceleration(waitTime);
    roundedWaitTime = round(waitTime*1000000);
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(roundedWaitTime);
    digitalWrite(STEP_PIN, LOW);
    if(dir == 1){
      counter++;
    if(counter < 360){
      Serial.print("Current position = ");
      Serial.print(counter);
      }
      else{
        counter = 0;
        Serial.print("Current position = ");
        Serial.print(counter);
        
      }
      

    }
    if(dir == 0){
      counter--;
      if(counter > -360){
      Serial.print("Current position = ");
      Serial.print(counter);
      }
      else{
        counter = 0;
        Serial.print("Current position = ");
        Serial.print(counter);
        
      }
    }
}
}
void full_rot_decelrate(int factor, int dir){
  for(int x = 0; x < 200*factor; x++) {
    waitTime = negativeAcceleration(waitTime);
    roundedWaitTime = round(waitTime*1000000);
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(roundedWaitTime);
    digitalWrite(STEP_PIN, LOW);
    //dir and position
    if(dir == 1){
      counter++;
      if(counter < 360){
      Serial.print("Current position = ");
      Serial.print(counter);
      }
      else{
        counter = 0;
        Serial.print("Current position = ");
        Serial.print(counter);
        
      }
    }
    if(dir == 0){
      counter--;
      if(counter > -360){
      Serial.print("Current position = ");
      Serial.print(counter);
      }
      else{
        counter = 0;
        Serial.print("Current position = ");
        Serial.print(counter);
        
      }
    }

}
}
