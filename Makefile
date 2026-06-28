all: medias run

medias:
	g++ Stats.cpp -o stats_exec;

run: medias
	@echo "--->VERSION_SEQUENTIAL:";
	@cd ./Version_Sequential && make && cd ..;
	@echo "--->VERSION_MASTER-SLAVE:";
	@cd ./Version_Master-Slave && make && cd ..; 
	@echo "--->TEST SUMMARY:";
	@./stats_exec;
	@echo "--->END OF TESTS";
