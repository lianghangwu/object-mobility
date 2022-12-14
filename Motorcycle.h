
#ifndef _MOTORCYCYLE_H_
#define _MOTORCYCYLE_H_

// Motercycle.h
#include "Message.h"
#include "AutoV.h"
#include "ecs36b_Common.h"

using namespace std;

class Motorcycle: public AutoV
{
 private:
 protected:
 public:

  int antiCrashScore;
  Message message;
  
  Motorcycle(void);
  Motorcycle(Person, int);
  void setantiCrashScore(int);
  void setMessage(Message);

  int getantiCrashScore();
  Message getMessage();

  Json::Value dump2JSON(); // print the content of the object
  virtual bool JSON2Object(Json::Value);
};

#endif /* _MOTORCYCYLE_H_ */