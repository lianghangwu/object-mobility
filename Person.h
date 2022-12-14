
#ifndef _PERSON_H_
#define _PERSON_H_

// Person.h

#include "Message.h"
#include "ecs36b_Common.h"

using namespace std;

class Person
{
private:
public:
  string name;
  int healthScore;

  Person(string, int);
  Person();
  void setHealthScore(int);
  void setName(string);

  string getName();
  int getHealthScore();
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value);
};

#endif  /* _PERSON_H_ */
