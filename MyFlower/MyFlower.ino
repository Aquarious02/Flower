#include <Servo.h>

# define button_pin 2
# define led_pin 6
# define servo_pin 9
Servo myservo;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  6;      // the number of the LED pin

int buttonto_fade = 0;         // variable for reading the pushbutton status
int brightness = 0;    // how bright the LED is
int fadeAmount = 3;    // how many points to fade the LED
int servo_pos = 0;
int servo_step = 4;  // 180 / (250 / fadeAmount)  

bool to_fade = false; // to_fade or not to_fade

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(servo_pin);
  myservo.write(servo_pos);

  Serial.begin(9600);
}

void loop() {
  buttonto_fade = digitalRead(buttonPin);

  if (to_fade) {  
    LED_fade();
       servo_turn();
       delay(50);
  } else {
    if (buttonto_fade == HIGH) {
         to_fade = true;
         digitalWrite(LED_BUILTIN, HIGH);
         Serial.println("to_fade = 1");
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    } 
  }
  
  Serial.print("to_fade = "); Serial.println(to_fade);
}

void LED_fade(){
  analogWrite(led_pin, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    to_fade = false;
    if (brightness < 0){
      brightness = 0;
      analogWrite(led_pin, brightness);
    }
  }
  Serial.print("Brightness = "); Serial.println(brightness);
}

void servo_turn(){
  servo_pos = map(brightness, 0, 255, 5, 175);
  
//  servo_pos = servo_pos + servo_step;
//  servo_pos = constrain(servo_pos, 5, 175)

  myservo.write(servo_pos);
}
