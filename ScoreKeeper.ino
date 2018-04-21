/*
 * Ultrasonic Basketball Score Keeper
 * IMPORTANT: Install the NewPing library first to use this sketch
 * Working: Ultrasonic Sensor checks for a ball, if a ball is present.
 * score is incremented, flag is raised and remains raised until
 * 5secs are elapsed. After 5secs, you can score again. This is indicated
 * by an LED, YOU CAN SCORE ONLY WHILE LED IS ON.
 * Written by Shivam Gautam on April 20, 2018
 */
#include<NewPing.h>
NewPing sonar(12,11);
unsigned long before = 0;//Variable to store, when previous score was made. initially 0
const long wait = 5000;//Once a score is made, wait for 5secs
bool flag = false;//flag to indicate whether score is made or not. initially false
int score = 0;//Score Count
int led = A5;//LED indicates wait time. If LED is ON, you're good to Go!
void setup() {
  Serial.begin(115200);//Initialize Serial Comm
  pinMode(led, OUTPUT);//Set time led as OUTPUT
  digitalWrite(led, HIGH);//initially set to HIGH. You can Score now!
}

void loop() {
  unsigned long now = millis();//Variable to save current time, saved by Arduino interrupt
  //Now We'll be checking if the ball is in vicinity (distance < 20cm), IMPORTANT: Please calibrate according to basket diameter
    if(!flag && sonar.ping_cm()<20 && sonar.ping_cm()>0){
      score += 1;//increment score
      flag = true;//score is made
      before = now;//you scored just now(saved in 'now' variable)
      digitalWrite(led, LOW);//Set LED LOW until 5 secs
    }
    //Check if 5secs have elapsed since last score
    else if(now-before>=wait){
      flag = false;//Set flag false to check the sensor for ball again
      digitalWrite(led, HIGH);//LED starts indicating, You're ready again
    }
    else{
      //This deals with displaying score
      Serial.print("Current Score: ");
      Serial.print("\t");
      Serial.print(score);
      Serial.println();  
    }
}
