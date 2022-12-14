
#Improve the midterm question about communication between car and motorcycles in emergency

Design and implement classes: AutoV, Car, Motorcycle, Person, Message. All the classes have get and set member functions and member function dump2JSON.

##AutoV
AutoV.cpp is the parent class of Car and Motorcycle, it gets driver information and vehical type

##Car
Car.cpp is the child class of AutoV, it gets driver information, anti crash score and message

##Motorcycle
Motorcycle.cpp is the child class of AutoV, it gets driver information, anti crash score, health score and message

##Person
Person.cpp is to have details of the person, such as name and health score

##Message
Message.cpp is to get message to each other

Create two different programs to represent communication between the car and two motorcycles: finalServer, finalClient

##finalClient create car object and its information, send alert to motorcycles in finalServer, after it gets information from motorcycles, it sends decision back to finalServer

##finalServer create motorcycle objects and information for both left and right motorcycles, send the information to finalClient


###how to run the program:
run finalServer first, then run finalClient, it will let car send alert to motorcycles, 
and then stop finalServer, it will let motorcycles send information to car, 
and then run finalServer again, then stop finalClient, it will let car send decision to motorcycles


