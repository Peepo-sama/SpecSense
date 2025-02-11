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

void AMD(string AMD, string quiz){
    switch (AMD || quiz){
        case "Gaming":
            case "Ryzen 3":
                case "5800X" || "5900X" || "5950X" || "5950X" || "7440U" || "7320U" || "210" || "8440U":
                    cout<<"Se la usi prinicipalemente per giocare dovresi fare un upgrade";
                    break;
                break;
            case "Ryzen 5":
                break;
            case "Ryzen 7":
                break;
            case "Ryzen 9":
                break;
            default:
                cout<<"CPU non riconosciuta";
                break;
        case "Workstation":
            case "Ryzen 3":
                break;
            case "Ryzen 5":
                break;
            case "Ryzen 7":
                break;
            case "Ryzen 9":
                break;
            default:
                cout<<"CPU non riconosciuta";
                break;
        case "Server":
            case "Ryzen 3":
                break;
            case "Ryzen 5":
                break;
            case "Ryzen 7":
                break;
            case "Ryzen 9":
                break;
            default:
                cout<<"CPU non riconosciuta";
                break;
        default:
            cout<<"CPU non riconosciuta";
            break;
    }
}
void Intel()
int main() 
{
    
    StartingProgram();
    
    return 0;
}
