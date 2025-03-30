#include "QIK.h"
QIK QIK(15, 45, 40);  //lengths a, b, and c in mm

void setup() {
  Serial.begin(115200);
  //abad
  Serial.print("theta abad = ");
  Serial.print(QIK.getTheta(0, 20, 5, 40), 3);
  Serial.println(" deg");
  //hip
  Serial.print("theta hip = ");
  Serial.print(QIK.getTheta(1, 20, 5, 40), 3);
  Serial.println(" deg");
  //knee
  Serial.print("theta knee = ");
  Serial.print(QIK.getTheta(2, 20, 5, 40), 3);
  Serial.println(" deg");
}
void loop() {
}
