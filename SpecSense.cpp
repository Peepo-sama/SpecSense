#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    #include <winreg.h> // Libreria per il registro di sistema (solo Windows)
#else
    #include <fstream>
#endif

using namespace std;

void StartingProgram() {
    for (int i = 0; i < 3; i++) {
        cout << "Program starting..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Funzione per ottenere il modello della CPU su Windows (INTERNET)
#ifdef _WIN32
string getCPUModel() {
    HKEY hKey;
    char cpuModel[256];
    DWORD size = sizeof(cpuModel);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpuModel, &size) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return string(cpuModel);
        }
        RegCloseKey(hKey);
    }
    return "Errore nel recupero del modello della CPU";
}
#else
// Funzione per ottenere il modello della CPU su Linux (INTERNET)
string getCPUModel() {
    ifstream cpuInfo("/proc/cpuinfo"); 
    string line;
    while (getline(cpuInfo, line)) { 
        if (line.find("model name") != string::npos) { 
            return line.substr(line.find(":") + 2); // Estrae il nome del modello
        }
    }
    return "Errore nel recupero del modello della CPU";
}
#endif

// Enum per la categoria della CPU
enum CPUCategory { UNKNOWN, GAMING, WORKSTATION, SERVER };

// Funzione per determinare la categoria della CPU
CPUCategory DetermineCategory(const string& usage) {
    if (usage == "Gaming") return GAMING;
    if (usage == "Workstation") return WORKSTATION;
    if (usage == "Server") return SERVER;
    return UNKNOWN;
}

// Funzione per verificare se una CPU è adatta a un determinato uso
bool isCPUCompatible(const string& cpuModel, const vector<string>& cpuList) {
    return any_of(cpuList.begin(), cpuList.end(), [&](const string& cpu) {
        return cpuModel.find(cpu) != string::npos;
    });
}

// Funzione per stampare il risultato dell'analisi della CPU
void PrintAnalysisResult(bool isCompatible, const string& usage) {
    if (isCompatible) {
        cout << "La tua CPU e' adatta per " << usage << ".\n";
    } else {
        cout << "\nPotresti aver bisogno di un upgrade per " << usage << ".\n";
        if (usage == "Gaming") {
            cout << "Puoi controllare le diverse CPU su questo sito: https://www.cpubenchmark.net/top-gaming-cpus.html\n";
        } else if (usage == "Workstation") {
            cout << "Informazioni sulle CPU per workstation: https://www.tomshardware.com/reviews/best-performance-cpus,5683.html\n";
        } else if (usage == "Server") {
            cout << "Puoi controllare le CPU per server su: https://www.serversplus.com/servers/server-processors/all-server-processors\n";
            cout << "Informazioni sulle CPU per server: https://www.liquidweb.com/blog/server-cpu/\n";
        }
    }
}

// Funzione principale di analisi della CPU
void AnalyzeCPU(const string& cpuModel, const string& usage) {
    vector<string> gaming_cpus = {"Ryzen 5", "Ryzen 7", "Ryzen 9", "i5-12600K", "i7-12700K", "i9-12900K"};
    vector<string> workstation_cpus = {"Threadripper", "Xeon W", "Ryzen 9", "i9-13900K"};
    vector<string> server_cpus = {"EPYC", "Xeon", "Threadripper"};

    cout << "Analizzando CPU: " << cpuModel << " per utilizzo " << usage << "...\n";

    switch (DetermineCategory(usage)) {
        case GAMING:
            PrintAnalysisResult(isCPUCompatible(cpuModel, gaming_cpus), usage);
            break;
        case WORKSTATION:
            PrintAnalysisResult(isCPUCompatible(cpuModel, workstation_cpus), usage);
            break;
        case SERVER:
            PrintAnalysisResult(isCPUCompatible(cpuModel, server_cpus), usage);
            break;
        default:
            cout << "Utilizzo non riconosciuto.\n";
    }
}

// Funzione per controllare se "sensors" è installato
bool isSensorsInstalled() {
    return system("which sensors > /dev/null 2>&1") == 0;
}

// Funzione per installare lm-sensors
void installSensors() {
    cout << "Il pacchetto 'lm-sensors' non e' installato. Vuoi installarlo? (s/n): ";
    char choice;
    cin >> choice;
    
    if (choice == 's' || choice == 'S') {
        cout << "Installazione di lm-sensors in corso...\n";
        system("sudo apt update && sudo apt install -y lm-sensors");
        cout << "Configurazione di lm-sensors...\n";
        system("sudo sensors-detect");
    } else {
        cout << "lm-sensors non installato. Impossibile controllare le ventole.\n";
    }
}

// Funzione per ottenere la velocità delle ventole
void getFanSpeed() {
#ifdef _WIN32
    cout << "Su Windows, il controllo delle ventole richiede un software esterno come OpenHardwareMonitor.\n";
#else
    if (!isSensorsInstalled()) {
        installSensors();
    }

    cout << "Controllo della velocita' delle ventole...\n";
    system("sensors | grep 'fan'");
#endif
}

int main() {
    StartingProgram();
    while (true) {
        cout << "Benvenuto in SpecSense!\n";
        cout << "Scegli un opzione:\n";
        cout << "1 - Analizza la tua CPU\n";
        cout << "2 - Analizza la velocita' delle ventole\n";
        cout << "3 - Esci\n";
        int scelta;
        cin >> scelta;
        if (scelta ==  1) {
            string cpuModel = getCPUModel();
            cout << "Modello CPU rilevato: " << cpuModel << endl;
            string usage;
            cout << "Inserisci l'uso principale (Gaming/Workstation/Server): ";
            cin >> usage;
            AnalyzeCPU(cpuModel, usage);
        } else if (scelta == 2) {
            getFanSpeed();
        } else if (scelta == 3) {
            cout << "Arrivederci!\n";
            return 0;
        }
    }
    return 0;
}
