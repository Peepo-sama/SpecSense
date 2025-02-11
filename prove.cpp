#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void getMemoryInfo() {
    ifstream memInfo("/proc/meminfo");
    string line;

    cout << "Informazioni Memoria:\n";
    while (getline(memInfo, line)) {
        if (line.find("MemTotal:")!= string::npos) {
            long long mem = stoll(line);
            mem = mem / 1024;
            mem = mem / 1024;
            cout << "Memoria totale: " << mem << " GB" << endl;
            break;
        }
    }
}





case "1200" || "1300X" || "2300X" || "3200G" || "3300X" || "3900X" || "3950X" || "5600X" || "5800X" || "5900X" || "5950X" || "5950X" || "7440U" || "7320U" || "210" || "8440U":   //per tutti i tipi di processori amd ryzen 3







int main() {
    getCPUInfo();
    getMemoryInfo();
    return 0;
}

