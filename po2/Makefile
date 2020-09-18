all: commander process_manager

CC=g++
#CFLAGS = -ggdb -Wall
CFLAGS = 

commander: commander.cpp 
	$(CXX) $(CFLAGS) commander.cpp -o commander

process_manager: process_manager.cpp pcb.h pcb.cpp queue_array.h 
	$(CXX) $(CFLAGS) process_manager.cpp pcb.cpp  -o process_manager


