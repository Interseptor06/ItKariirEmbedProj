// C++ code
//
int distanceThreshold = 0;

int cm = 0;

int inches = 0;

int baselineTemp = 30;

int celsius = 0;

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

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  int valor = analogRead(A1);
  valor = map(valor, 300, 750, 0, 100);
  int gas_threshold = 80;
  
  Serial.println(valor);
  if(valor >= gas_threshold){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
  
  // measure temperature in Celsius
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  //Serial.println(celsius);
  if(celsius > baselineTemp){
  	digitalWrite(6, HIGH);
  }
  else{
  	digitalWrite(6, LOW);
  }
  
  // set threshold distance to activate LEDs
  distanceThreshold = 200;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  //Serial.print(cm);
  //Serial.print("cm, ");
  //Serial.print(inches);
  //Serial.println("in");

  if (cm >= distanceThreshold) {
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(4, LOW);
	digitalWrite(2, LOW);  
  }
  delay(100); // Wait for 100 millisecond(s)
}