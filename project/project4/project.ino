int IR_LED_PIN = 7;   // IR LED pin
int IR_RECEIVER_PIN = 4;  // IR receiver pin
int MICROPHONE = 6  ; 
int BUZZER_PIN = 8;  // Buzzer pin
int DEBOUNCE_DELAY = 50; // Debounce delay in milliseconds
int led_red_s = 52;
int led_green_s = 50;

int led_green = 48;


int led_delay = 70;
int x = 180;

int check = false;
int check1 = false;
int check2= false;
int check2_F = false;
int check_state_servo = false;
int check3 =false;
int check_fina = false;
bool ch_de =false;
bool t = false;


bool bf= false;
int time_bf = 5000;
const int time_min = 1;
int f_time_bf = 0;
int chb = 0;

bool sc = false;
bool sc2 =false;
bool sc3 =false;

int stack_key =0;
  
#include <Servo.h>
Servo myservo; //ประกาศตัวแปรแทน Servo
Servo myservo2;

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28};
byte colPins[COLS] = {30, 32, 34, 36};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int log_password= 53;
int password = 0;

#include <LCD_I2C.h>
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

int lcd_servo_open(){
      lcd.setCursor(3,0);
      lcd.print("OPEN DOOR");
      lcd.setCursor(3,1);
      lcd.print("..........");
      return 1;
}

int lcd_servo_close(){
      lcd.setCursor(3,0);
      lcd.print("CLOSE DOOR");
      lcd.setCursor(3,1);
      lcd.print("..........");
      return 1;
}

int lcd_chb(){
  lcd.setCursor(3,0);
  lcd.print("ERROR!!");
  lcd.setCursor(3,1);
  lcd.print(f_time_bf);
 
  return 1;
  }


int s_time_brute(){
  time_bf += chb*(time_bf*time_min);
  if(ch_de ==false){
  f_time_bf = time_bf;
  ch_de = true;
  } 
  chb +=1;
  return 1;
  }

int de_time(){
  f_time_bf -=1 ;
  return 1;
  }  




int debounceAnalogRead(int pin) {
  int val = digitalRead(pin);
  delay(DEBOUNCE_DELAY);
  int newVal = digitalRead(pin);
  if (abs(val - newVal) < 10) {
    return newVal;
  } else {
    return val;
  }
}




void setup() {
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(led_red_s, OUTPUT);
  pinMode(led_green_s, OUTPUT);

  pinMode(MICROPHONE,INPUT);
  pinMode(led_green,OUTPUT);

  
  Serial.begin(9600);
  lcd.begin(); 
  lcd.backlight();
  myservo.attach(2); // กำหนดขา 9 ควบคุม Servo
  myservo2.attach(3);
}

void loop() {
  
   if(not(sc3)){
  myservo.write(180);
  myservo2.write(180);
  digitalWrite(led_red_s,HIGH);
  digitalWrite(led_green_s,LOW);
  sc3=true;
    }

 
  
  
  if(digitalRead(BUZZER_PIN) or check){
    if(check1==false){
    lcd.setCursor(0,0);
    lcd.print("INSERT PASSWORD:))");
    lcd.setCursor(5,1);
    lcd.print("7 Digit");
    }
    check = true;
    check1 = true;
    char key = keypad.getKey();
    
    if (key != NO_KEY and check2==false) {
      stack_key +=1;
      lcd.setCursor(1,0);
      lcd.print("INSERT PASSWORD :");
      lcd.setCursor(1,1);
      lcd.print(">>>>>>>");
      lcd.setCursor(8,1);
      lcd.print(key);
      lcd.setCursor(9,1);
      lcd.print("<<<<<<<");
      delay(1000);
      lcd.clear();
      lcd.setCursor(8,0);
      lcd.print("SET");
      lcd.setCursor(8,1);
      lcd.print(stack_key);
      delay(500);
      lcd.clear();

      
      password += int(key);
      if(stack_key==1){
        if(password == log_password){
          check2=true;
          digitalWrite(led_red_s,LOW);
          digitalWrite(led_green_s,HIGH);
          }
        else{
          check2_F=true;
          check2=true;
          }
      }
      Serial.println(password);
    }

    if(check2_F == true and check2==true){
      digitalWrite(BUZZER_PIN,HIGH);
      delay(1000);
      lcd.setCursor(3,0);
      lcd.print("Fail !!");
      digitalWrite(BUZZER_PIN,LOW);
      delay(1000);
      digitalWrite(BUZZER_PIN,HIGH);
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("TOT...");
      delay(1000); 
      lcd.clear();
      check2 =false;
      check2_F = false;
      check = true;
      check1 = false;
      bf = true;
      stack_key = 0;
      password =0;
      s_time_brute();
      digitalWrite(BUZZER_PIN,LOW);
      }

    if(bf==true ){
      while(f_time_bf>0){
      lcd_chb();
      de_time();
      }
      lcd.clear();
      bf= false;
      } 
        
    

    if(check2 == true and check3==false and check2_F == false and t==false){ 
      lcd.setCursor(3,0);
      lcd.print("Success !!");
      delay(1000);
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("WELCOME :)");
      delay(1000); 
      lcd.clear();
      t=true;
      check_state_servo = true;
      }

    
      

   if(sc==false and sc2==false and check_state_servo == true){
  // put your main code here, to run repeatedly:
    for (int i = 1; i <= 180;i++){
      digitalWrite(BUZZER_PIN, HIGH);
      lcd_servo_open();             
      myservo.write(i);
      myservo2.write(i);
      Serial.println(i);                        
      delay(10); 
    }
    digitalWrite(BUZZER_PIN, LOW);
    sc = true;
    sc2 =true;
    Serial.println("1");
    lcd.clear();
  }

  if(t== true)
  {  
  digitalWrite(led_green,(digitalRead(MICROPHONE)));
  }  
  
  if(sc==true and sc2==true and digitalRead(IR_RECEIVER_PIN)){
    for (int i = 180; i > 60; i--) {
    digitalWrite(BUZZER_PIN, HIGH);
     lcd_servo_close();         
    myservo.write(i);
    myservo2.write(i);
    Serial.println(i);                        
    delay(10);
    }
    digitalWrite(BUZZER_PIN, LOW); 
   sc =false;
   sc2= false;
   check2 =false;
   check = true;
    check1 = false;
    check2_F = false;
    stack_key = 0;
    password =0;
   Serial.println("2");
   check_state_servo = false;
   digitalWrite(led_red_s,HIGH);
   digitalWrite(led_green_s,LOW);
   delay(1000);
   lcd.clear();
  }
  
    
  digitalWrite(BUZZER_PIN, LOW);
//    
  }
 
  
  if(check == false){
    lcd.setCursor(2,0);
    lcd.print("Secure Door :))");
    delay(1000);
    lcd.clear();    

 
    
    Serial.println(digitalRead(IR_RECEIVER_PIN));
    digitalWrite(IR_LED_PIN, HIGH);
    delayMicroseconds(100);  // Replace with your desired IR signal timing
    digitalWrite(IR_LED_PIN, LOW);
    delay(10);  // Wait for receiver to settle
  
    // Read status of IR receiver with debouncing
    int receiverValue = debounceAnalogRead(IR_RECEIVER_PIN);
  
    // If the receiver value is high, turn on the buzzer
    if (receiverValue == 1) {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer ON");
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("Buzzer OFF");
    }
    
    delay(100);  // Replace with your desired loop delay
  }
}
