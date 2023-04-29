all: enigma run

enigma: Enigma.cpp
	@g++ Enigma.cpp -o enigma_exec -fopenmp

run: enigma_exec
	@./mulExec.sh