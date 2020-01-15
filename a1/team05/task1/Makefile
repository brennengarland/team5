#output .exe, dependet on main and message object files
output: main.o message.o
	g++ main.o message.o -o output

#main object file, dependent on main.cpp
main.o: main.cpp
	g++ -c main.cpp

#message object file, dependent on message.cpp message.h
message.o: message.cpp message.h
	g++ -c message.cpp

#make clean removes everything with a .o and output.exe
clean:
	rm *.o output