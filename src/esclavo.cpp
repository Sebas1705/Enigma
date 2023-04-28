#include <mpi.h>
#include <cstdlib>


int* decipher(int* line,int charsPerLine,int nRotors);
int* subDecipher(int* rawData, int line[], int key);


int main(int argc, char ** argv)
{
	int pid, np; //PID , number of processes
	MPI_Init();
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(pid!=0)
	{
        //Recivir argumentos (charsPerLine)(nRotors)
        int args[2];
        MPI_Recv(&args,2,MPI_INT,0,1,MPI_COMM_WORLD,NULL);
		//Ejecucion
		while(1)
		{   
            int* actualLine
			int trabajo;
			MPI_Recv(&trabajo, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(!trabajo)
				break;
			MPI_Recv(/*coords*/, /*N datos*/, /*tipo dato*/, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			ruta = algoritmoAstar(coords);
			MPI_Send(/*ruta*/, /*N datos*/, /*tipo dato*/, 0, 0, MPI_COMM_WORLD);
		}
	}
    MPI_Finalize();
}

int* decipher(int* line, int charsPerLine, int nRotors){

}

int* subDecipher(int* rawData, int line[], int key){
	for (int idx = 0; idx < nCharsPerLine; idx++)
	{
		rawData[idx] = line[idx];
	}

	int* rotorKeys = (int*)malloc(sizeof(int) * nRotors);
	int remainder = key;
	for (int idx = 0; idx < nRotors; idx++)
	{
		int divisor = pow(10, (nRotors - (1 + idx)));
		rotorKeys[idx] = (int)(remainder / divisor);
		remainder = (int)(remainder % divisor);
	}


	for (int rotorIdx = 0; rotorIdx < nRotors; rotorIdx++)
	{
		int displacement = rotorKeys[rotorIdx];
		for (int idx = 0; idx < nCharsPerLine; idx++)
		{
			rawData[idx] = rawData[idx] - displacement++;
		}
	}

	free(rotorKeys);
	return rawData;
}