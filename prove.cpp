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



int main() {
    getCPUInfo();
    getMemoryInfo();
    return 0;
}

