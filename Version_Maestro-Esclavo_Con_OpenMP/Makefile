all: master slave run 

master: Master.cpp
	@mpicc -fopenmp Master.cpp -o master_exec -lstdc++ -L/usr/local/lib -lmpichcxx -lmpi_cxx -lmpi

slave: Slave.cpp
	@mpicc Slave.cpp -o slave_exec -lm -lstdc++ -lmpi_cxx

run: master_exec slave_exec
	@./mulExec.sh

