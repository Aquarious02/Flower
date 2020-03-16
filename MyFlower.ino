#include <Servo.h>

# define button_pin 2
# define led_pin 6
# define servo_pin 9
Servo myservo;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  6;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status
int brightness = 0;    // how bright the LED is
int fadeAmount = 3;    // how many points to fade the LED
int servo_pos = 0;
int servo_step = 4;  // 180 / (250 / fadeAmount)  
bool to_fade = false;

int state = 0; // state of flower

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(servo_pin);
  myservo.write(servo_pos);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

//  switch (state){
//   case 0:  // initial state
//       if (buttonState == HIGH) {
//         state = 1;
//         digitalWrite(LED_BUILTIN, HIGH);
//         Serial.println("state = 1");
//       } else {
//        digitalWrite(LED_BUILTIN, LOW);
//       }
//   case 1:  // fading state
//       LED_fade();
//       servo_turn();
//       delay(30);
//  }
  if (state == 0){
    if (buttonState == HIGH) {
         state = 1;
         digitalWrite(LED_BUILTIN, HIGH);
         Serial.println("state = 1");
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
  } else if (state == 1){  // fading state
       LED_fade();
       servo_turn();
       delay(50);
  }

  Serial.println(state);
}

void LED_fade(){
  analogWrite(led_pin, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    servo_step = -servo_step;
    state = 0;
    if (brightness < 0){
      brightness = 0;
      analogWrite(led_pin, brightness);
    }
  }

  Serial.print("Brightness = ");
  Serial.println(brightness);
  
}
void servo_turn(){
  servo_pos = servo_pos + servo_step;
  
  servo_pos = map(brightness, 0, 255, 5, 175);

  if (servo_pos > 175){
    servo_pos = 175;
  } else if (servo_pos < 5){
    servo_pos = 5;
  }
  myservo.write(servo_pos);
}
