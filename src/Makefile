all: master slave run 

master: Master.cpp
	mpicc Master.cpp -o master
slave: Slave.cpp
	mpicc Slave.cpp -o slave -lm

run: master slave
	mpirun -np 1 master : -np 2 slave 

