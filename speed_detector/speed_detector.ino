// #include<Serial>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//settings
int sensorPin = A2;   // select the input pin for the potentiometer
int sensorPin2 = A1;   // select the input pin for the potentiometer     // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//var
double time1;
double time2;
double timeInterval;
double speedCalculated;

//adj.
const int val1 = 40;
const int val2 = 60;
const double distance = 0.04;


void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Speed(KM/H)");
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorValue2 = analogRead(sensorPin2);
  Serial.print("1: ");
  Serial.print(sensorValue);
  Serial.print("| 2: ");
  Serial.println(sensorValue2);
  if(analogRead(sensorPin) < val2)
  {
    time1 = millis();
    Serial.println("First resistor light absorption interupted");

    //wait for second photoresistor light interuption
    while(analogRead(sensorPin2) > val1)
    {
      delay(1);
    }
    
    time2 = millis();
    Serial.println("Second resistor light absorption interupted");

    //calculate time difference
    timeInterval = abs(time2 - time1);

    Serial.print("Time difference: ");
    Serial.print(timeInterval);
    Serial.println("ms.");

    //calculate speed (currently km/h, see below for different speed measures)
    speedCalculated = (distance / timeInterval)*36000 ;

    Serial.print("Calculated speed: ");
    Serial.println(speedCalculated);
    Serial.println();

    //clean LCD first row
    lcd.setCursor(6,1);
    lcd.print("    ");

    //print speed
    lcd.setCursor(6,1);
    lcd.print(speedCalculated);
    delay(200);
  }

}
