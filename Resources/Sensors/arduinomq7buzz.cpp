/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 


int thresholdMQ7 = 1000; // Threshold for Buzzer-Alarm - toxic Carbon Monixide Area
int Buzzer_PIN = 3;      // Buzzer connected to digital pin 13
int MQ7_PIN = A0;        // MQ7-Sensor to analog pin A0

void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin(); 

  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  pinMode(Buzzer_PIN, OUTPUT);      // sets the digital pin as output
  pinMode(MQ7_PIN, INPUT);         // sets the analog pin as input
 
} 
void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print("Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 lcd.setCursor(0,0);
 lcd.print("Temp C | Monoxid");
 Serial.print("Temperature is: "); 
 Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?  
 
 lcd.setCursor(2,1);
 lcd.print(sensors.getTempCByIndex(0));
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 

 int sensorValueMQ7 = analogRead(MQ7_PIN);
 // print out the value you read:
 Serial.print("Carbon Monoxide: ");
 Serial.println(sensorValueMQ7);
 lcd.setCursor(11,1);
 lcd.print(sensorValueMQ7);

 if (sensorValueMQ7 >= thresholdMQ7) {
  digitalWrite(Buzzer_PIN, HIGH);   // sets the Buzzer ALARM on
 } else {
  digitalWrite(Buzzer_PIN, LOW);   // sets the Buzzer ALARM off
 }
 
 lcd.setCursor(0,1); // signals that temp update is in progress
 lcd.cursor_on();
 delay(1000); 
 lcd.cursor_off();
} 