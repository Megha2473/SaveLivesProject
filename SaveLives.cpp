//Configuration of an electronic chip using arduino code written in cpp in Arduino IDE
//Hardware Requirements-Arduino UNO board, USB cable connecter for Arduino UNO,Ultra Sonic HC-SR04, Jumper wires male to female
//Software requirements-Arduino software, Processing software


int distanceThreshold = 0;
int cm = 0;
int inches = 0;
//Before the setup(), we create variables to store the target distance threshold
//the sensor value in centimeters (cm) and inches
//They're called int because they are integers, or any whole number.


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
//the function readUltrasonicDistance() is used to describe the sensor code and keep it separate from the main body of the program.
//The function definition starts with what type of data the function will return, or send back to the main program
//In this case the function returns a long, which is a decimal point number with many digits
//Then in parentheses are the arguments the function takes. int triggerPin, int echoPin are the variable declarations for your sensor's connection pins.
void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
// The serial monitor connection is established with Serial.begin
//Pins 2, 3, and 4 are configured as outputs to control the LEDs.
void loop()
{
  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(inches);
  Serial.println("in");
  if (cm > distanceThreshold) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  //To convert centimeters to inches, divide by 2.54
  //Printing to the serial monitor helps you observe the distance change more granularly than the LED states show alone.
  if (cm <= distanceThreshold && cm > distanceThreshold - 100) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  if (cm <= distanceThreshold - 100 && cm > distanceThreshold - 250) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  if (cm <= distanceThreshold - 250 && cm > distanceThreshold - 350) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  if (cm <= distanceThreshold - 350) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(100); // Wait for 100 millisecond(s)
}
//The loop's six if statements evaluate for different ranges of distance between 0 and 350cm, lighting up more LEDs the closer the object.

//If you want to see a more obvious change in bar graph lights
//you can change the distanceThreshold variable and/or the range that you are looking at by changing the arguments in the if() statements
//This is called calibration.
