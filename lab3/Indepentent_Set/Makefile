# g++-4.8 --std=c++11 -I  -L  -o a.o mip1_c++.cpp  -Wall -lgurobi_c++ \       
#                 -lgurobi70 -lm -lpthread   


CPP11 = -std=c++11
FLAGSRELEASE = -O2 -Wall -DDEBUG
FLAGSDEBUG = -g -ggdb
INCLUDE = /opt/gurobi702/linux64/include
LIB = /opt/gurobi702/linux64/lib 
LINKS = -lgurobi_c++ -lgurobi70 -lm -lpthread   

CC = g++-4.8


all: a.o

%.o: %.cpp
	$(CC) $(CPP11) -I $(INCLUDE) -L $(LIB) $(FLAGSRELEASE) $< -o $@ $(LINKS)

clean:
	rm -f *~ *.o

.PHONY: all clean
