#!/bin/bash

for i in {1..5}; do mpirun --oversubscribe -np 1 master_exec : -np 10 slave_exec; done