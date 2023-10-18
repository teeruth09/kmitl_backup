//int check = 1;
int input_status_led = 2;
//int buzzer = 8;

int check = 1;

void setup()
{
  pinMode(input_status_led, INPUT);
  //pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

}
void loop()
{
  Serial.println(digitalRead(input_status_led));
  
  delay(1000); // หน่วงเวลา 1000ms

}
