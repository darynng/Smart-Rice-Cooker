//nodeMCU v1.0 (black) with Arduino IDE

#define BLYNK_TEMPLATE_ID "TMPL2SDorTEw7"
#define BLYNK_TEMPLATE_NAME "RICE COOKER"
#define BLYNK_AUTH_TOKEN "Utuvw7PjJ6qRU2LtWMZ6ZzitO94xDex3"
#define BLYNK_PRINT Serial //output is serial monitor
#define APP_DEBUG

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TP-Link_6A0C_5G";
char pass[] = "48783750";

// Create servo object
Servo servo1;
#define red D0
#define green D3
long t = 120000; // set cooking time to 2 min
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD has 0x27 address, 16 columns, 2 rows
BlynkTimer timer;
bool run_timer = true; // controls whether the timer for decrementTime should continue 

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1); // specify pins for SDA, SCL
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  servo1.attach(D4);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Meal's ready in");
  lcd.setCursor(0,1);
  lcd.print(t/1000/60);
  lcd.setCursor(2,1);
  lcd.print("minutes");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(60000L, decrementTime); // run decrementTime every minute
} 

void decrementTime() { 
  if (run_timer && t/1000/60>0) {
    time_display();
    t -= 60000; 
    }
  else {
    run_timer =  false; // stop decrementTime 
    green_LED();
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Meal's ready!"); // show message on LCD
    Blynk.logEvent("meal_ready"); // notify on app
    } 
}

void time_display() {
  lcd.setCursor(0, 1);
  lcd.print(t/1000/60);
}

void red_LED(){
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
}

void green_LED(){
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}


void ingredient() {
  int angle;
  for (angle = 0; angle < 110; ++angle) { 
    servo1.write(angle); }
  for (angle = 110; angle > 0; --angle) {
    servo1.write(angle);}
  decrementTime();   
}

BLYNK_WRITE(V1) {
  int n = param.asInt(); // Get serving number input
} 

BLYNK_WRITE(V0) { // Start button pressed
  int start = param.asInt(); //  start is 1 if button is pressed
  if (start == 1) { // start --> red led + ingredient --> decrementTime --> green led + finish message
    run_timer = true;
    red_LED();
    ingredient(); 
  }
}

void loop() {
  Blynk.run();
  timer.run(); // use to run timer.setInterval for decrementTime
}