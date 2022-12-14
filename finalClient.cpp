
#include <iostream>
#include "ecs36b_Exception.h"

#include "Person.h"
#include "Car.h"
#include "AutoV.h"
#include "Motorcycle.h"
#include "Message.h"

#include "ecs36b_Common.h"

// for JsonRPCCPP
#include <iostream>
#include "finalserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "finalclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

using namespace jsonrpc;
using namespace std;

map<string, Motorcycle> Motorcycle_Map;
Car car;
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
  std::cout << "My Server for Car created" << std::endl;
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

    //std::cout << "motorcycles status\n";
    if (!(class_id == "Motorcycle"))
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
        strJson = ( "Motorcycle parsing error " );
        result["reason"] = strJson;
        error_code = -3;
    }

    cout << endl << object_id << " send back the information" << endl;


    Motorcycle motorcycle;
    motorcycle.JSON2Object(json_object);

    Motorcycle_Map[object_id] = motorcycle;
    receivedMessage = true;
    result["status"] = "motorcycles status received by car";


    return result;
}



int main()
{
    // object mobility
    HttpClient httpclient("http://127.0.0.1:7374");
    finalClient myClient(httpclient, JSONRPC_CLIENT_V2);


    Person car_driver = {"car driver", 77 };
    car = {car_driver, 90};
    car.setVehicalType("car");
    Message alert = {"Emergency alert ! ! ! "};
    car.setMessage(alert);


    Json::Value myv;
    try 
    {
        cout << car.dump2JSON().toStyledString() << endl;
        myv = myClient.sendMessage("send message", "Message", alert.dump2JSON(), "alert");
    } 
    catch (JsonRpcException &e) 
    {
        cerr << e.what() << endl;
    }
    std::cout << myv.toStyledString() << std::endl;



    HttpServer httpserver(7375);
    MyFinalServer s(httpserver,
        JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    s.StartListening();
    std::cout << "Hit enter to stop the server\n" << endl;
    getchar();
    s.StopListening();


    cout << endl << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << receivedMessage << endl;
    if(receivedMessage == true)
    {
        receivedMessage = false;
        Motorcycle left_motorcycle, right_motorcycle;
        for(auto x: Motorcycle_Map)
        {
            if(x.first == "left_motorcycle") left_motorcycle = x.second;
            if(x.first == "right_motorcycle") right_motorcycle = x.second;
        }

        string str = car.makeDecision(left_motorcycle, right_motorcycle);
        Message decision {str};
        car.setMessage(decision);

        try 
        {
            cout << car.dump2JSON().toStyledString() << endl;
            myv = myClient.sendMessage("send message", "Message", decision.dump2JSON(), "decision");
        } 
        catch (JsonRpcException &e) 
        {
            cerr << e.what() << endl;
        }
        std::cout << myv.toStyledString() << std::endl;

    }



    
    
    return 0;

}