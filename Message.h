
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <strings.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception> 
#include <time.h>
#include "ecs36b_Common.h"

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

using namespace std;

class Message
{
 private:
 protected:
 public:
  string message;
  Message(void);
  Message(string);

  void setMessage(string);
  string getMessage();

  Json::Value dump2JSON(); // print the content of the object
  virtual bool JSON2Object(Json::Value);
};


#endif /* _MESSAGE_H_ */
