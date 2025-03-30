#ifndef QIK_H
#define QIK_H
#include "arduino.h"

class QIK {  //machine class
public:
  //class functions
  QIK(float a, float b, float c);
  float getTheta(int joint, float X, float Y, float Z);  //returns the value of theta abad, hip, or knee
};

#endif
