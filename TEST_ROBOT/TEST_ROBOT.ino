#include <AFMotor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(9, 10); // RX, TX

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

#define trig_Pin A0
#define echo_Pin A1
#define Backlight A2
#define Frontlight A3
#define SCL A4
#define SDA A5
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(OLED_RESET); 
void setup() {
    bluetoothSerial.begin(9600);
    pinMode(trig_Pin, OUTPUT);
    pinMode(echo_Pin, INPUT);
    pinMode(Backlight, OUTPUT);
    pinMode(Frontlight, OUTPUT);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.setTextColor(WHITE); 
    display.clearDisplay();
}

int measure_distance(){
    digitalWrite(trig_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pin, LOW);
    long duration = pulseIn(echo_Pin, HIGH);
    return (duration / 2) / 29.1;
}

void set_display(){
    display.setCursor(0,0);
    display.clearDisplay();
    display.setTextSize(1);
}

void go_forward(int motor_speed){
    digitalWrite(Backlight, LOW);
    digitalWrite(Frontlight, HIGH);
    motor1.setSpeed(motor_speed);
    motor4.setSpeed(motor_speed);
    motor1.run(FORWARD);
    motor4.run(BACKWARD);
    digitalWrite(Frontlight, LOW);
}

void go_forward_left(int motor_speed){
    digitalWrite(Backlight, LOW);
    digitalWrite(Frontlight, HIGH);
    motor1.setSpeed(motor_speed-60);
    motor4.setSpeed(motor_speed);
    motor1.run(FORWARD);
    motor4.run(BACKWARD);
    digitalWrite(Frontlight, LOW);
}

void go_forward_right(int motor_speed){
    digitalWrite(Backlight, LOW);
    digitalWrite(Frontlight, HIGH);
    motor1.setSpeed(motor_speed);
    motor4.setSpeed(motor_speed-60);
    motor1.run(FORWARD);
    motor4.run(BACKWARD);
    digitalWrite(Frontlight, LOW);
}

void go_backward(int motor_speed){
    digitalWrite(Backlight, LOW);
    motor1.setSpeed(motor_speed);
    motor4.setSpeed(motor_speed);
    motor1.run(BACKWARD);
    motor4.run(FORWARD);
}

void go_backward_left(int motor_speed){
    digitalWrite(Backlight, LOW);
    motor1.setSpeed(motor_speed-60);
    motor4.setSpeed(motor_speed);
    motor1.run(BACKWARD);
    motor4.run(FORWARD);
}

void go_backward_right(int motor_speed){
    digitalWrite(Backlight, LOW);
    motor1.setSpeed(motor_speed);
    motor4.setSpeed(motor_speed-60);
    motor1.run(BACKWARD);
    motor4.run(FORWARD);
}
 
void turn_right(int motor_speed){
    digitalWrite(Backlight, LOW);
    digitalWrite(Frontlight, HIGH);
    motor1.setSpeed(motor_speed-25);
    motor4.setSpeed(motor_speed-25);
    motor1.run(FORWARD);
    motor4.run(FORWARD);
    digitalWrite(Frontlight, LOW);

}

void turn_left(int motor_speed){
    digitalWrite(Backlight, LOW);
    digitalWrite(Frontlight, HIGH);
    motor1.setSpeed(motor_speed-25);
    motor4.setSpeed(motor_speed-25);
    motor1.run(BACKWARD);
    motor4.run(BACKWARD);
    digitalWrite(Frontlight, LOW);
}

void stop_motors(){
    digitalWrite(Backlight, HIGH);
    motor1.run(RELEASE);
    motor4.run(RELEASE);
    
}
char bluetooth_command;
int motor_speed = 200;
void loop() {
    
    if(bluetoothSerial.available()>0)
      {
      bluetooth_command = bluetoothSerial.read();
      delay(2);
      }
        switch(bluetooth_command)
        {
          case 'F':
          go_forward(motor_speed);
          break;
          
          case'B':
          go_backward(motor_speed);
          break;
          
          case 'L':
          turn_left(motor_speed);
          break;
          
          case'R':
          turn_right(motor_speed);
          break;

          case'Q':
          go_forward_left(motor_speed);
          break;

          case'E':
          go_forward_right(motor_speed);
          break;

          case'Z':
          go_backward_left(motor_speed);
          break;

          case'C':
          go_backward_right(motor_speed);
          break;

          case'S':
          stop_motors();
          break;
          
          case'0':
          motor_speed=160;
          break;
          
          case'1':
          motor_speed=170;
          break;
          
          case'2':
          motor_speed=180;
          break;
          
          case'3':
          motor_speed=190;
          break;
          
          case'4':
          motor_speed=200;
          break;
          
          case'5':
          motor_speed=210;
          break;
          
          case'6':
          motor_speed=220;
          break;
          
          case'7':
          motor_speed=230;
          break;
          
          case'8':
          motor_speed=240;
          break;
          
          case'9':
          motor_speed=255;
          break;
        }
       while (bluetooth_command == 'A'){
          if (measure_distance() <= 30) {
          go_backward(motor_speed);  
          delay(700);
          stop_motors();
          set_display();
          display.println("Measuring...");
          display.display();
          turn_right(210);
          delay(700);
          stop_motors();
          long distance_right = measure_distance();
          display.print("right: ");
          display.print(distance_right);
          display.println(" cm");
          turn_left(210);
          delay(700);
          stop_motors();
          display.display();
          delay(700);
          turn_left(210);
          delay(700);
          stop_motors();
          long distance_left = measure_distance();
          display.print("left: ");
          display.print(210);
          display.print(" cm");
          turn_right(210);
          delay(700);
          stop_motors();
          display.display();
          delay(700);
            if (distance_left > distance_right) 
            {
                turn_left(210);
                delay(700);
                stop_motors();
            }
            else 
            {
                turn_right(210);
                delay(700);
                stop_motors();
            }
          }
        go_forward(motor_speed);
        if(bluetoothSerial.available()>0)
        {
         bluetooth_command = bluetoothSerial.read();
         delay(2);
        }
     }
}
