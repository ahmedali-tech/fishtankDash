#include <LiquidCrystal.h>

#define DisOxy_PIN A0     // soil moisture sensor to analog 0 pin
#define TEMP_PIN A1         // TEMP36 sensor to analog 1 pin
#define PUMP_LED_PIN 6      // blue led(water pump) to digital 6 pin
#define BUZZER_PIN 8        // buzzer(alert) to digital 8 pin
#define minDisOxy_THRESHOLD 500 // defining moiture threshold to 500
#define maxDisOxy_THRESHOLD 2000 // defining moiture threshold to 500
#define TEMP_THRESHOLD 25   // defining temperature theshold to 25 celcius

//initializing variables
int DisOxy_Value = 0; //whole number value
float temperature = 0;
int tempReading = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //defining the LCD pins


float scaler(float inputValue){
	float scaledValue = abs((inputValue - 700) / 10) ;
	return scaledValue;
}

void setup() {
  pinMode(DisOxy_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(PUMP_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  
  lcd.begin(16, 2); // setting up LCD columns for 16x2 LCD
  // 16 charaters per line. total 2 lines
  lcd.print("Temp and Oxy System");
  
  Serial.begin(9600);
}


void loop() {
  DisOxy_Value = analogRead(DisOxy_PIN);
  DisOxy_Value = scaler(DisOxy_Value);
  tempReading = analogRead(TEMP_PIN);

  //TMP36 analog value conversion to celsius
  temperature = (tempReading * 0.48828125) - 50.0;

  lcd.setCursor(0, 1);

  // condition to alternate between moisture and temperature values
  // every 1 second
  if (millis() % 2000 < 1000) {
    lcd.print("Oxygen: ");
    lcd.print(DisOxy_Value);
  } else {
    lcd.print("Temp: ");
    lcd.print(temperature);
  }

  lcd.setCursor(0, 0);
  
  //comparing temp and oxygen values to their thresholds
  //if any one of them crosses limit alert and water pump goes off
  //OR condition used between temp and moisture conditions
  Serial.println(DisOxy_Value);
  DisOxy_Value = DisOxy_Value*10;
  if ((2000 <  DisOxy_Value || DisOxy_Value < 500) || temperature > TEMP_THRESHOLD) {
    digitalWrite(PUMP_LED_PIN, HIGH); // turn on blue LED(water pump)
    tone(BUZZER_PIN, 1000); // turn on buzzer
    lcd.print("Temp Control On       ");
    }
  //if threshold not crossed
  else {
    digitalWrite(PUMP_LED_PIN, LOW); // turn off blue LED(water pump)
    noTone(BUZZER_PIN); // turn off buzzer
    lcd.print("Ready             ");
  }

  delay(1000);
}