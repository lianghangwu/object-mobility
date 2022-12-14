
#include "Car.h"

Car::Car()
{

}

Car::Car
(Person arg_driver, int arg_antiCrashScore)
{
  this->driver = arg_driver;
  this->antiCrashScore = arg_antiCrashScore;
}

void Car::setantiCrashScore(int arg_antiCrashScore)
{
  this->antiCrashScore = arg_antiCrashScore ;
}

void Car::setMessage(Message arg_message)
{
    this->message = arg_message;
}


int Car::getAntiCrashScore()
{
  return this->antiCrashScore;
}

Message Car::getMessage()
{
  return this->message;
}

std::string
Car::makeDecision(Motorcycle left, Motorcycle right)
{
    int leftScore = left.getantiCrashScore() + left.getDriver().getHealthScore();
    int rightScore = right.getantiCrashScore() + right.getDriver().getHealthScore();
    if(leftScore > rightScore) 
        return "Left Motorcycle is hit.";
    else 
        return "Right Motorcycle is hit.";
}



Json::Value
Car::dump2JSON()
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
Car::JSON2Object
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
