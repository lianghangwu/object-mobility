
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "finalserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "finalclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include <time.h>
#include "Person.h"
#include "Car.h"
#include "AutoV.h"
#include "Motorcycle.h"
#include "Message.h"
#include "ecs36b_Common.h"

using namespace jsonrpc;
using namespace std;



Motorcycle left_motorcycle;
Motorcycle right_motorcycle;

bool receivedMessage = false;



class MyFinalServer: public finalServer
{
public:
  MyFinalServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value sendMessage(const std::string& action,
			   const std::string& class_id,
			   const Json::Value& json_object,
			   const std::string& object_id);
};

MyFinalServer::MyFinalServer(AbstractServerConnector &connector, serverVersion_t type): finalServer(connector, type)
{
  std::cout << "My Server for Motorcycle created" << std::endl;
}

// member functions

Json::Value
MyFinalServer::sendMessage
(const std::string& action, const std::string& class_id,
 const Json::Value& json_object, const std::string& object_id)
{
    int error_code = 0;
    Json::Value result;
    std::string strJson;

    std::cout << "motorcycles status\n";
    if (!(class_id == "Message"))
    {
        result["status"] = "failed";
        strJson = ( "class " + class_id + " unknown");
        result["reason"] = strJson;
        error_code = -1;
    }

    if (object_id.empty())
    {
        result["status"] = "failed";
        strJson = ( "object_id null ");
        result["reason"] = strJson;
        error_code = -2;
    }

    if ((json_object.isNull() == true) || (json_object.isObject() == false))
    {
        result["status"] = "failed";
        strJson = ( "message parsing error " );
        result["reason"] = strJson;
        error_code = -3;
    }


    Message message_received;
    message_received.JSON2Object(json_object);

    left_motorcycle.setMessage(message_received);
    right_motorcycle.setMessage(message_received);
    receivedMessage = true;

    cout << left_motorcycle.dump2JSON().toStyledString() << endl;
    cout << right_motorcycle.dump2JSON().toStyledString() << endl;

    result["status"] = object_id + " received by motorcycles";


    return result;
}


int main()
{
    // object mobility
    HttpClient httpclient("http://127.0.0.1:7375");
    finalClient myClient(httpclient, JSONRPC_CLIENT_V2);



    
    Person left_motorcycle_driver = {"left_motorcycle_driver", 70};
    left_motorcycle = {left_motorcycle_driver, 30};
    left_motorcycle.setVehicalType("motorcycle");

    Person right_motorcycle_driver = {"right_motorcycle_driver", 85};
    right_motorcycle = {right_motorcycle_driver, 20};
    right_motorcycle.setVehicalType("motorcycle");
    
 

    HttpServer httpserver(7374);
    MyFinalServer s(httpserver,
            JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    s.StartListening();
    std::cout << "Hit enter to stop the server\n" << endl;
    getchar();
    s.StopListening();


    Json::Value myv;
    cout << endl << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << receivedMessage << endl;
    if(receivedMessage == true)
    {
        receivedMessage = false;

        cout << endl << "motor send message back !!" << endl;
        
        try 
        {
            cout << left_motorcycle.dump2JSON().toStyledString() << endl;
            myv = myClient.sendMessage("send message", "Motorcycle", left_motorcycle.dump2JSON(), "left_motorcycle");
        } 
        catch (JsonRpcException &e) 
        {
            cerr << e.what() << endl;
        }
        std::cout << myv.toStyledString() << std::endl;

        try 
        {
            cout << right_motorcycle.dump2JSON().toStyledString() << endl;
            myv = myClient.sendMessage("send message", "Motorcycle", right_motorcycle.dump2JSON(), "right_motorcycle");
        } 
        catch (JsonRpcException &e) 
        {
            cerr << e.what() << endl;
        }
        std::cout << myv.toStyledString() << std::endl;
    }



    return 0;

}