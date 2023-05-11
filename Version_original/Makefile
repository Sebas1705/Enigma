all: enigma run

enigma: Enigma.cpp
	@g++ Enigma.cpp -o enigma_exec -fopenmp -O2;

run: enigma_exec
	@./mulExec.sh;