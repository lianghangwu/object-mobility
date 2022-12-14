
#ifndef _AUTOV_H_
#define _AUTOV_H_

// AutoV.h
#include "Person.h"
#include "Message.h"
#include "ecs36b_Common.h"

using namespace std;

class AutoV
{
 private:
 protected:
 public:

  Person driver;
  string vehicalType;

  
  AutoV(void);
  AutoV(Person, string);
  void setDriver(Person);
  void setVehicalType(string);

  std::string getVehicalType();
  Person getDriver();

  Json::Value dump2JSON(); // print the content of the object
  virtual bool JSON2Object(Json::Value);
};

#endif /* _AUTOV_H_ */
