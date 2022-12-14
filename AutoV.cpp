
#include "AutoV.h"

AutoV::AutoV
(void)
{

}

AutoV::AutoV
(Person arg_driver, string arg_vehicalType)
{
  this->driver = arg_driver;
  this->vehicalType = arg_vehicalType;
}

void AutoV::setDriver(Person arg_driver)
{
  this->driver = arg_driver;
}

void AutoV::setVehicalType(string arg_vehicalType)
{
  this->vehicalType = arg_vehicalType;
}

string AutoV::getVehicalType()
{
  return this->vehicalType;
}

Person AutoV::getDriver()
{
  return this->driver;
}

Json::Value
AutoV::dump2JSON
(void)
{
  Json::Value result { };

  Json::Value jv_result;
  jv_result = (this->driver).dump2JSON();
  result["driver"] = jv_result;

  if (this->vehicalType != "")
  {
    result["vehicalType"] = this->vehicalType;
  }

  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

bool
AutoV::JSON2Object
(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true) ||
      (arg_jv.isObject() != true))
    {
      return false;
    }

  if ((arg_jv["driver"]).isNull() == true)
    {
      return false;
    }

  this->driver = Person {(arg_jv["driver"]["name"]).asString(), (arg_jv["driver"]["healthScore"]).asInt()};
  this->vehicalType = (arg_jv["vehicalType"]).asString();

  return true;
}
