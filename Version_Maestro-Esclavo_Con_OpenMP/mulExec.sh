#!/bin/bash

for i in {1..5}; do mpirun -np 1 master_exec : -np 5 slave_exec; done