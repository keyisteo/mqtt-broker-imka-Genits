/*     Arduino Color Sensing Door
 *      
 * by Teo Wijayarto
 *  
 */

#include <Servo.h> 

// Create a servo object 
Servo Servo1, Servo2, Servo3; 

 
#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define sensorOut 10
#define defaultRedMin 255
#define defaultRedMax 255
#define defaultGreenMin 255
#define defaultGreenMax 255
#define defaultBlueMin 255
#define defaultBlueMax 255
#define servoPin1 4
#define servoPin2 5



int frequency = 0;
int red;
int green;
int blue;


void setup() {
  //Pin Assignment  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2);
  // Setting frequency-scaling to 20% Color Sensor Setting
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  //Serial Begin
  Serial.begin(9600);
}

void colorSensor(){
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  red = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency= pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  green = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  Serial.println("  ");
  delay(100);  
  }

void servoOpen(Servo door){
   door.write(0); 
  }

void servoClose(Servo door){
  door.write(90); 
  }


void loop() {
  colorSensor();
  if(red>defaultRedMin && red<defaultRedMax && blue>defaultBlueMin && blue<defaultBlueMax && green>defaultGreenMin && green<defaultGreenMax){
    delay(2000);
    }
  else if(red>green && red>blue){
    Serial.println("Anorganik");
    servoOpen(Servo2);
    servoOpen(Servo1);
    delay(3000);
    servoClose(Servo1);
    servoClose(Servo2);
    }
  else{
    Serial.println("Organik");
    servoOpen(Servo1);
    delay(3000);
    servoClose(Servo1);
    }
}
