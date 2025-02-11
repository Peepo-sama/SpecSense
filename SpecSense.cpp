#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <cstdlib> 
#include <ctime> 
#include <iomanip> 
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

void StartingProgram(){
    for(int i=0; i<5; i++) {
        cout<<"Program starting..."<<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void CPUInfo() {
    ifstream cpuInfo("/proc/cpuinfo"); //Apri file dove contiene le info della cpu
    string line;

    cout << "Informazioni CPU:\n";
    while (getline(cpuInfo, line)) { //Legge il file 
        if (line.find("model name") != string::npos) { //Cerca la riga con il nome del modello
            cout << line << endl;
            break;  // Prendiamo solo il primo core
        }
    }
}

int main() 
{
    StartingProgram();
    
    return 0;
}
