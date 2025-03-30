#include "QIK.h"

//variables
float a, b, c, L, angle;

//Library Content
QIK::QIK(float _a, float _b, float _c) {
  a = _a;
  b = _b;
  c = _c;
}

float QIK::getTheta(int joint, float X, float Y, float Z) {
  L = pow(X, 2) + pow(Y, 2) + pow(Z, 2); 
  //calculates abad, hip, or knee angle
  switch (joint) {
    case 0:  //abad
      angle = atan(X / Z) + acos(a / (sqrt(pow(X, 2) + pow(Z, 2))));
      break;
    case 1:  //hip
      angle = (PI / 2) - asin(-Y / sqrt(L - pow(a, 2))) - acos((pow(b, 2) - pow(a, 2) - pow(c, 2) + L) / (2 * b * sqrt(L - pow(a, 2))));
      break;
    case 2:  //knee
      angle = acos((pow(a, 2) + pow(b, 2) + pow(c, 2) - L) / (2 * b * c));
      break;
  }
  return (angle * (180 / PI));  //converts angle to degrees and returns the value
}
