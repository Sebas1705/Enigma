#include <iostream>
#include <fstream>

using namespace std;

float media(string filename);

int main(int argc, char *argv[]) {

    cout << "->RecopilaciÃ³n datos de las pruebas:" << endl;
    cout << "+---------------------------------------------\\" << endl;
    cout << "| Average (Sequential): " << media("./Version_Sequential/Times.txt") << endl;
    cout << "| Average (Master-Slave): " << media("./Version_Master-Slave/Times.txt") << endl;
    //cout << "|Media Version_Maestro-Esclavo_OMP: " << media("./Version_Maestro-Esclavo_Con_OpenMP/Tiempos.txt") << endl;
    cout << "+---------------------------------------------/" << endl;

    return 0;
}

float media(string filename) {
    std::ifstream in(filename);
    int count=0;
    float sum=0;
    while(!in.eof()){
		std::string temp;
		in>>temp;
		sum+=stof(temp);
        count++;
	}
    return sum/count;
}