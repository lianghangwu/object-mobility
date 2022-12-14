#ifndef _CAR_H_
#define _CAR_H_

// Car.h
#include "Person.h"
#include "Message.h"
#include "AutoV.h"
#include "ecs36b_Common.h"
#include "Motorcycle.h"

using namespace std;

class Car: public AutoV
{
 private:
 protected:
 public:

  int antiCrashScore;
  Message message;

  
  Car(void);
  Car(Person, int);
  void setantiCrashScore(int);
  void setMessage(Message);

  int getAntiCrashScore();
  Message getMessage();
  string makeDecision(Motorcycle, Motorcycle);

  Json::Value dump2JSON(); // print the content of the object
  virtual bool JSON2Object(Json::Value);

};

#endif /* _MOTORCYCYLE_H_ */
