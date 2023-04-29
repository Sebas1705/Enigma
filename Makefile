all: medias run

medias:
	g++ Medias.cpp -o medias_exec;

run: medias
	@echo "--->VERSION_ORIGINAL:";
	@cd ./Version_original && make && cd ..;
	@echo "--->VERSION_MAESTRO-ESCLAVO:";
	@cd ./Version_Maestro-Esclavo && make && cd ..;
	#@echo "--->VERSION_MAESTRO-ESCLAVO-OMP:";
	#@cd ./Version_Maestro-Esclavo_Con_OpenMP && make && cd ..; 
	@echo "--->RESUMEN PRUEBAS:";
	@./medias_exec;
	@echo "--->FIN PRUEBAS";
