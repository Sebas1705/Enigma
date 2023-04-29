#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mpi.h>

#define TAG_ASK 1
#define TAG_STOP 0

int* desciphered;
void decipher(int* line,int nCharsPerLine,int nRotors,int index);
int* subDecipher(int* rawData, int line[], int key,int nCharsPerLine,int nRotors);


int main(int argc, char ** argv){
	int pid, np; //PID , number of processes
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	printf("Slave: Iniciado esclavo con PID: %d\n",pid);
	MPI_Status status;
	

	if(pid!=0)
	{
        //Recivir argumentos (charsPerLine)(nRotors)
        int args[2];
        MPI_Recv(&args,2,MPI_INT,0,TAG_ASK,MPI_COMM_WORLD,NULL);
		desciphered=(int*)malloc(sizeof(int)*args[0]);

		//Ejecucion esclava:
		int cipheredLine[args[0]];
		int index;
		while(true){
			//Recibimos la tarea:
			MPI_Recv(&cipheredLine,args[0],MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			if(status.MPI_TAG==TAG_STOP) break;
			MPI_Recv(&index,1,MPI_INT,0,TAG_ASK,MPI_COMM_WORLD,&status);

			//Realizamos tarea:
			int descipheredLine[args[0]];
			decipher(cipheredLine,args[0],args[1],index);
			for(int i=0;i<args[0];i++){
				descipheredLine[i]=desciphered[i];
			}
			//....

			//Enviamos la tarea:
			MPI_Send(&descipheredLine,args[0],MPI_INT,0,TAG_ASK,MPI_COMM_WORLD);
			MPI_Send(&index,1,MPI_INT,0,TAG_ASK,MPI_COMM_WORLD);
		}
		free(desciphered);
	}
    MPI_Finalize();
}

void decipher(int* line, int nCharsPerLine, int nRotors, int index){
	for (int lineKey = (int)pow(10, nRotors - 1); lineKey < (int)pow(10, nRotors); lineKey++){
		int* p_deciphered = (int*)malloc(sizeof(int) * nCharsPerLine);
		p_deciphered = subDecipher(p_deciphered, line, lineKey, nCharsPerLine, nRotors);

		char decipheredLine[nCharsPerLine];
		for (int idx = 0; idx < nCharsPerLine; idx++){
			decipheredLine[idx] = p_deciphered[idx];
		}
		free(p_deciphered);

		char stringKey[nRotors + 1];
		sprintf(stringKey, "%d", lineKey);
		if (!strncmp(stringKey, decipheredLine, nRotors)){
			for (int idx2 = 0; idx2 < nCharsPerLine; idx2++){
				desciphered[idx2] = decipheredLine[idx2];
			}
			printf("Descifrada linea %d con clave %d\n", index, lineKey);
			break;
		}
	}
}

int* subDecipher(int* rawData,int line[],int key,int nCharsPerLine,int nRotors){
	for (int idx = 0; idx < nCharsPerLine; idx++){
		rawData[idx] = line[idx];
	}

	int* rotorKeys = (int*)malloc(sizeof(int) * nRotors);
	int remainder = key;
	for (int idx = 0; idx < nRotors; idx++){
		int divisor = pow(10, (nRotors - (1 + idx)));
		rotorKeys[idx] = (int)(remainder / divisor);
		remainder = (int)(remainder % divisor);
	}


	for (int rotorIdx = 0; rotorIdx < nRotors; rotorIdx++){
		int displacement = rotorKeys[rotorIdx];
		for (int idx = 0; idx < nCharsPerLine; idx++){
			rawData[idx] = rawData[idx] - displacement++;
		}
	}

	free(rotorKeys);
	return rawData;
}