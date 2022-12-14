
#include "Person.h"

Person::Person(string arg_name, int arg_healthScore)
{
  this->name = arg_name;
  this->healthScore = arg_healthScore;
}

Person::Person()
{
  this->name = "";
  this->healthScore = 0;
}

void Person::setName(string arg_name)
{
  this->name = arg_name;
}

void Person::setHealthScore(int arg_healthScore)
{
  this->healthScore = arg_healthScore;
}

int Person::getHealthScore()
{
  return this->healthScore;
}

string Person::getName()
{
  return this->name;
}




Json::Value
Person::dump2JSON
(void)
{
  Json::Value result { };

  if (this->name != "")
  {
    result["name"] = this->name;
  }

  if (this->healthScore != 0)
  {
    result["healthScore"] = this->healthScore;
  }

  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

bool
Person::JSON2Object
(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true) ||
      (arg_jv.isObject() != true))
    {
      return false;
    }

  if ((arg_jv["name"]).isNull() == true)
    {
      return false;
    }

  this->name = (arg_jv["name"]).asString();
  this->healthScore = (arg_jv["healthScore"]).asInt();

  return true;
}

