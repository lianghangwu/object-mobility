
#include "string.h"
#include "Message.h"

Message::Message()
{
  this->message = "";
}

Message::Message(string arg_message)
{
  this->message = arg_message;
}

void Message::setMessage(std::string arg_message)
{
  this->message = arg_message;
}

string Message::getMessage()
{
  return this->message;
}

Json::Value Message::dump2JSON()
{
  Json::Value result { };

  if (this->message != "")
  {
    result["message"] = this->message;
  }
  return result;
}

bool Message::JSON2Object(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true) ||
      (arg_jv.isObject() != true))
    {
      return false;
    }

  if ((arg_jv["message"]).isNull() == true)
    {
      return false;
    }

  this->message = (arg_jv["message"]).asString();

  return true;
}


