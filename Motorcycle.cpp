

#include "Motorcycle.h"

Motorcycle::Motorcycle()
{

}

Motorcycle::Motorcycle(Person arg_driver, int arg_antiCrashScore)
{
  this->driver = arg_driver;
  this->antiCrashScore = arg_antiCrashScore;
}

void Motorcycle::setantiCrashScore(int arg_antiCrashScore)
{
  this->antiCrashScore = arg_antiCrashScore;
}

int Motorcycle::getantiCrashScore()
{
  return this-> antiCrashScore;
}

void Motorcycle::setMessage(Message arg_message)
{
    this->message = arg_message;
}

Message Motorcycle::getMessage()
{
  return this->message;
}



Json::Value
Motorcycle::dump2JSON()
{
  Json::Value result { };

  Json::Value jv_result;
  jv_result = (this->message).dump2JSON();
  result["message"] = jv_result;

  jv_result = (this->driver).dump2JSON();
  result["driver"] = jv_result;

  result["healthScore"] = this->driver.getHealthScore();

  if (this->antiCrashScore != 0)
  {
    result["antiCrashScore"] = this->antiCrashScore;
  }

  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

bool
Motorcycle::JSON2Object
(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true) ||
      (arg_jv.isObject() != true))
    {
      return false;
    }

  if ((arg_jv["antiCrashScore"]).isNull() == true)
    {
      return false;
    }

  this->message = Message {(arg_jv["message"]["message"]).asString()};
  this->antiCrashScore = (arg_jv["antiCrashScore"]).asInt();
  this->driver.setHealthScore(arg_jv["healthScore"].asInt());
  this->driver.setName((arg_jv["driver"]["name"]).asString());

  return true;
}


