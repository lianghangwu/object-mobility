# Makefile for f2022, ecs36b
#
# g++ -std=c++14 test_GPS.cpp GPS.cpp -o test_GPS
#
# example: $ ./test_GPS 48.88 2.3

CC = g++ -std=c++14

# CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g

CFLAGS = -g -I/opt/homebrew/include

# CFLAGS = -g -D_ECS36B_HW7_ -I/usr/include/jsoncpp
# CFLAGS = -g -DNOT_RIGHT_NOW -I/usr/include/jsoncpp

# CFLAGS = -g -D_ECS36B_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# LDFLAGS = 	-L/Users/sfwu/vcpkg/installed/arm64-osx/lib -ljsoncpp
#LDFLAGS = 	-L/opt/homebrew/lib -ljsoncpp
LDFLAGS = 	-ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=		ecs36b_Common.h
INC_CL	=	AutoV.h Person.h Car.h Motorcycle.h Message.h 
OBJ	=		AutoV.o Person.o Car.o Motorcycle.o Message.o
# old: LDFLAGS = 	-lc++ -ljsoncpp

# LDFLAGS = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -lcurl -ljsonrpccpp-client


# rules.
# all: 	hw5forest hw5home hw5grandmaHome
all: 	finalClient finalServer

#
#
finalclient.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=finalServer --cpp-client=finalClient

finalserver.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=finalServer --cpp-client=finalClient


finalClient.o:		finalClient.cpp finalclient.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) finalClient.cpp

finalServer.o:		finalServer.cpp finalserver.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) finalServer.cpp


Message.o:	Message.cpp Message.h $(INC)
	$(CC) -c $(CFLAGS) Message.cpp

Person.o:	Person.cpp Person.h $(INC)
	$(CC) -c $(CFLAGS) Person.cpp

Motorcycle.o:	Motorcycle.cpp Motorcycle.h $(INC)
	$(CC) -c $(CFLAGS) Motorcycle.cpp

Car.o:	Car.cpp Car.h $(INC)
	$(CC) -c $(CFLAGS) Car.cpp

AutoV.o:	AutoV.cpp AutoV.h $(INC)
	$(CC) -c $(CFLAGS) AutoV.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(INC)
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

finalClient: finalClient.o ecs36b_JSON.o $(OBJ)
	$(CC) -o finalClient finalClient.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

finalServer: finalServer.o ecs36b_JSON.o $(OBJ)
	$(CC) -o finalServer finalServer.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)



clean:
	rm -f *.o *~ core finalClient finalServer
