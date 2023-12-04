all: Exilien_Andre_assn3

Exilien_Andre_assn3: rotorMachine.o Exilien_Andre_assn3.o
	g++ -o Exilien_Andre_assn3 rotorMachine.o Exilien_Andre_assn3.o

rotorMachine.o: rotorMachine.cpp rotorMachine.h
	g++ -c rotorMachine.cpp

Exilien_Andre_assn3.o: Exilien_Andre_assn3.cpp rotorMachine.h
	g++ -c Exilien_Andre_assn3.cpp

clean:
	rm -f *.o Exilien_Andre_assn3
