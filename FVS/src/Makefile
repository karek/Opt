# g++-4.8 --std=c++11 -I  -L  -o a.o mip1_c++.cpp  -Wall -lgurobi_c++ \       
#                 -lgurobi70 -lm -lpthread   


CPP11 = -std=c++11
FLAGS = -O2 -DDEBUG
FLAGSRELEASE = $(FLAGS) -Wall
FLAGSDEBUG = -g -ggdb
INCLUDE = /opt/gurobi702/linux64/include
LIB = /opt/gurobi702/linux64/lib 
LINKS = -lgurobi_c++ -lgurobi70 -lm -lpthread   

CC = g++-4.8


all: FeedbackVertexSet Verifier

solutions/lp_cycles.o: solutions/lp_cycles.cpp solutions/lp_cycles.h 
	$(CC) $(CPP11) -I $(INCLUDE) -L $(LIB) $(FLAGS) solutions/lp_cycles.cpp -c  -o $@ $(LINKS)

%.o: %.cpp %.h 
	$(CC) $(CPP11) $(FLAGS) -c $< -o $@ 
#	$(CC) $(CPP11) -I $(INCLUDE) -L $(LIB) $(FLAGSRELEASE) -c $< -o $@ $(LINKS)

FeedbackVertexSet: Main.cpp lib/Translator.o lib/Graph.o solutions/lp_cycles.o
	$(CC) $(CPP11) -I $(INCLUDE) -L $(LIB) $(FLAGSRELEASE) lib/Translator.o lib/Graph.o solutions/lp_cycles.o Main.cpp -o build/$@ $(LINKS)

Verifier: OutputVerifier.cpp
	$(CC) $(CPP11) $(FLAGSRELEASE) $< -o build/$@

clean:
	rm -f *~ *.o lib/*.o solutions/*.o

.PHONY: all clean
 
