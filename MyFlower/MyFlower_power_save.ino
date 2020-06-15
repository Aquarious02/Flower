/* See more about PowerDown at
https://tsibrov.blogspot.com/2018/02/arduino-power-down.html
*/
#include <Servo.h>
#include <math.h>
#include <avr/sleep.h>

# define button_pin 2 // Must be 2 to interrupt!
# define led_pin 6
# define servo_pin 9
# define angle_max 90
# define angle_min 33

Servo myservo;

int button_to_fade = 0;         // variable for reading the pushbutton status
int brightness = 0;    // how bright the LED is
int fadeAmount = 2;    // how many points to fade the LED
int servo_pos = 0;

bool to_fade = false; // to_fade or not to_fade

void setup() {
  pinMode(led_pin, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);  // Also interruptPin
  // attachInterrupt(digitalPinToInterrupt(button_pin), blink, CHANGE);

  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(servo_pin);
  myservo.write(angle_min);

  Serial.begin(9600);
}

void loop() {
  button_to_fade = digitalRead(button_pin);

  change_state();

//  Serial.print("to_fade = "); Serial.println(to_fade);
}

void change_state(){
  if (to_fade) {
       servo_turn();
       LED_fade();
       delay(50);
  } else {
    if (button_to_fade == HIGH) {
         to_fade = true;
         detachInterrupt(digitalPinToInterrupt(button_pin)); // interrupt forbidden
         continue // Test it!
        // digitalWrite(LED_BUILTIN, HIGH);
//         Serial.println("to_fade = "); Serial.print(to_fade);
    } else {
//        digitalWrite(LED_BUILTIN, LOW);  // To see result
    }

    if (brightness <= 0){
       digitalWrite(led_pin, LOW);
//    } else if (brightness >= 255){
//      digitalWrite(led_pin, HIGH);
    }

    attachInterrupt(digitalPinToInterrupt(button_pin), empty, CHANGE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // PowerDown - самый экономный режим
    sleep_mode();

  }
}

void LED_fade(){
//  analogWrite(led_pin, fading_brightness(brightness));
  analogWrite(led_pin, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the end of the fading:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    to_fade = false;
//    if (brightness < 0){
//      brightness = 0;
//      digitalWrite(led_pin, LOW);
//    }
  }
//  Serial.print("Brightness = "); Serial.print(brightness); Serial.print(" | new_brightness = "); Serial.println(fading_brightness(brightness));
//  Serial.print("Brightness = "); Serial.println(brightness);

}

//int fading_brightness (int old_brightness){
//  return exp(old_brightness / 46);
//  return old_brightness;
//}

void servo_turn(){
  servo_pos = map(brightness, 0, 255, angle_min, angle_max);

//  servo_pos = servo_pos + servo_step;
//  servo_pos = constrain(servo_pos, 5, 175)

  myservo.write(servo_pos);
}

void empty(){}
