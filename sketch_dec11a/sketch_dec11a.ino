#include <ESP32Servo.h>
#include <Ps3Controller.h>


#include "QIK.h"
QIK QIK(15, 60, 60);  //lengths a, b, and c in mm

//front left
Servo flh1;  // create servo object to control a servo
Servo flh2;  // create servo object to control a servo
Servo flk;   // create servo object to control a servo

//Back left
Servo blh1;  // create servo object to control a servo
Servo blh2;  // create servo object to control a servo
Servo blk;   // create servo object to control a servo

//Front right
Servo frh1;  // create servo object to control a servo
Servo frh2;  // create servo object to control a servo
Servo frk;   // create servo object to control a servo

//Back right
Servo brh1;  // create servo object to control a servo
Servo brh2;  // create servo object to control a servo
Servo brk;   // create servo object to control a servo

const int mn = 500;
const int mx = 2500;

int calib1 = 90;
int calib2 = 180;
int calib3 = 0;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Ps3.begin("d8:9e:f3:5c:ab:4d");
  Serial.println("Ready.");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  flh1.setPeriodHertz(50);  // standard 50 hz servo
  flh2.setPeriodHertz(50);  // standard 50 hz servo
  flk.setPeriodHertz(50);   // standard 50 hz servo
  blh1.setPeriodHertz(50);  // standard 50 hz servo
  blh2.setPeriodHertz(50);  // standard 50 hz servo
  blk.setPeriodHertz(50);   // standard 50 hz servo
  frh1.setPeriodHertz(50);  // standard 50 hz servo
  frh2.setPeriodHertz(50);  // standard 50 hz servo
  frk.setPeriodHertz(50);   // standard 50 hz servo
  brh1.setPeriodHertz(50);  // standard 50 hz servo
  brh2.setPeriodHertz(50);  // standard 50 hz servo
  brk.setPeriodHertz(50);   // standard 50 hz servo

  //front left
  flh1.attach(21, mn, mx);
  flh2.attach(22, mn, mx);
  flk.attach(23, mn, mx);

  //Back left
  blh1.attach(16, mn, mx);
  blh2.attach(13, mn, mx);
  blk.attach(25, mn, mx);

  //front right
  frh1.attach(19, mn, mx);
  frh2.attach(18, mn, mx);
  frk.attach(17, mn, mx);

  //Back Right
  brh1.attach(12, mn, mx);
  brh2.attach(15, mn, mx);
  brk.attach(14, mn, mx);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Ps3.isConnected()) {
    int lx = (Ps3.data.analog.stick.lx);
    int ly = (Ps3.data.analog.stick.ly);
    int rx = (Ps3.data.analog.stick.rx);

    float theta1, theta2, theta3;

    float x = map(rx, -128, 127, -50, 50);
    float y = map(lx, -128, 127, -50, 50);
    float z = map(ly, -128, 127, 20, 100);

    float hip1 = QIK.getTheta(0, x, y, z);
    float hip2 = QIK.getTheta(1, x, y, z);
    float knee = QIK.getTheta(2, x, y, z);

    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(",");
    Serial.print(int(hip1));
    Serial.print(",");
    Serial.print(int(hip2));
    Serial.print(",");
    Serial.print(int(knee));
    Serial.print(",");
    Serial.println(",");

    flh1.write(180 - int(hip1));
    flh2.write(180 - int(hip2));
    flk.write(180 - int(knee));

    blh1.write(int(hip1));
    blh2.write(180 - int(hip2));
    blk.write(180 - int(knee));

    frh1.write(int(hip1));
    frh2.write(int(hip2));
    frk.write(int(knee));

    brh1.write(180 - int(hip1));
    brh2.write(int(hip2));
    brk.write(int(knee));


  } else {
    flh1.write(calib1);
    flh2.write(calib2);
    flk.write(calib2);

    blh1.write(calib1);
    blh2.write(calib2);
    blk.write(calib2);

    frh1.write(calib1);
    frh2.write(calib3);
    frk.write(calib3);

    brh1.write(calib1);
    brh2.write(calib3);
    brk.write(calib3);
  }
}
