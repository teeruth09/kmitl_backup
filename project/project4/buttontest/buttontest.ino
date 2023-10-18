#include <Servo.h>
#include <LCD_I2C.h>

//before use microphone
int button = 8;
int button2 = 9;
int button3 = 10;

int led = 11;
int led2 = 12;
int led3 = 13;

int microphone = 2;


int buttonstate = 0;
int buttonstate2 = 0;
int buttonstate3 = 0;

int check = 0;


// Variables for debounce
int debounceDelay = 50; // Debounce delay in milliseconds
int debounceDelay2 = 100; // Debounce delay in milliseconds

unsigned long lastDebounceTime = 0; // Last time the button was debounced
unsigned long lastDebounceTime2 = 0; // Last time the button was debounced


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3 , INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read button states
  
  int reading = digitalRead(button);
  int reading2 = digitalRead(button2);
  int reading3 = digitalRead(button3);
  int soundcheck = digitalRead(microphone);

  // Debounce button 1
  if (millis() - lastDebounceTime > debounceDelay) 
  {
    if (reading != buttonstate) 
    {
      buttonstate = reading;
    }
  }

  // Debounce button 2
  if (millis() - lastDebounceTime2 > debounceDelay2) 
  {
    if (reading2 != buttonstate2) 
    {
      buttonstate2 = reading2;
    }
  }
  if (reading3 != buttonstate3) 
  {
    buttonstate3 = reading3;
  }
  
  Serial.print("button1 =");
  Serial.println(buttonstate);
  Serial.print("button2 =");
  Serial.println(buttonstate2);
  Serial.print("check = ");
  Serial.println(check);
  Serial.println("");
  Serial.print("button3 = ");
  Serial.println(buttonstate3);
  
  // Control LED based on button 1 state
  if (check == 1) 
  {
    if (buttonstate == LOW or buttonstate2 == LOW and check != 0)
    {
      digitalWrite(led, HIGH);
      digitalWrite(led3,LOW);
      check = 0;
     
    }
  }
  
  
  // Update check variable
  if (buttonstate == LOW and check != 1) 
  {
    if(buttonstate2 == LOW )
    {
      check = 1;
      digitalWrite(led,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
    }
  }
  if (check >= 1 and digitalRead(microphone)== HIGH)
  {
      digitalWrite(led3, LOW);
      digitalWrite(led, !digitalRead(led));
      Serial.print("led = ");
      Serial.println(digitalRead(led));
      digitalWrite(led2, !digitalRead(led2));
      Serial.print("led2 = ");
      Serial.println(digitalRead(led2));
      digitalWrite(led3, !digitalRead(led3));
      Serial.print("led3 = ");
      Serial.println(digitalRead(led3));
      check = 2;
    
  }
  if (check == 2 and buttonstate == LOW)               //ทำไฟกระพริบ
  {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led,LOW);
    delay(50);
    digitalWrite(led2,HIGH);
    delay(50);
    digitalWrite(led2,LOW);
    delay(50);
    digitalWrite(led3,HIGH);
    delay(50);
    digitalWrite(led3,LOW);
  }

  
  if(buttonstate3 == LOW)
  {
    check = 0;
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    
    Serial.println("Cutout is off");
    delay(2000);
  }
  
  
}
