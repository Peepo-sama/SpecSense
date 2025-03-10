#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm> // Si usa per la funzione any_of

#ifdef _WIN32 // (Ifdef = identifier) identifica se il sistema operativo è Windows
    #include <windows.h>
    #include <winreg.h> // Libreria per il registro di sistema (solo Windows)
#else
    #include <fstream> // Libreria per leggere i file (Linux)
#endif

using namespace std;

void StartingProgram() { 
    for (int i = 0; i < 3; i++) {
        cout << "Program starting..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Benvenuto in SpecSense!\n";
}

// Funzione per ottenere il modello della CPU (Windows e Linux)
string getCPUModel() { // Funzione per ottenere il modello della CPU
    #ifdef _WIN32
        HKEY hKey;
        char cpuModel[256];
        DWORD size = sizeof(cpuModel);
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) { // Apri il registro di sistema   
            if (RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpuModel, &size) == ERROR_SUCCESS) { 
                RegCloseKey(hKey); // Chiudi il registro di sistema
                return string(cpuModel); // Ritorna il modello della CPU
            }
            RegCloseKey(hKey); 
        }
        return "Errore nel recupero del modello della CPU (Windows)";
    #else
        ifstream cpuInfo("/proc/cpuinfo");  // Apre il file cpuinfo
        string line; // Variabile per la lettura di ogni riga del file
        while (getline(cpuInfo, line)) {  // Legge ogni riga del file
            if (line.find("model name") != string::npos) {  // Cerca la riga con il modello della CPU
                return line.substr(line.find(":") + 2); // Estrae il nome del modello
            }
        }
        return "Errore nel recupero del modello della CPU (Linux)";
    #endif
}

// Enum per la categoria della CPU
enum CPUCategory { UNKNOWN, GAMING, WORKSTATION, SERVER }; // Enum per la categoria della CPU

// Funzione per determinare la categoria della CPU
CPUCategory DetermineCategory(const string& usage) { // Determina la categoria della CPU in base all'uso
    if (usage == "Gaming" || usage == "gaming") return GAMING;
    if (usage == "Workstation" || usage == "workstation") return WORKSTATION;
    if (usage == "Data-Center" || usage == "Data-center" || usage == "data-center") return SERVER;
    return UNKNOWN;
}

// Funzione per stampare il risultato dell'analisi della CPU
void PrintAnalysisResult(bool isCompatible, const string& usage) {  // Stampa il risultato dell'analisi
    if (isCompatible) {
        cout << "La tua CPU e' adatta per " << usage << ".\n";
    } else {
        cout << "\nPotresti aver bisogno di un upgrade per " << usage << ".\n";
        if (usage == "Gaming" || usage == "gaming") {
            cout << "Puoi controllare le diverse CPU su questo sito: https://www.cpubenchmark.net/top-gaming-cpus.html\n";
        } else if (usage == "Workstation" || usage == "workstation") {
            cout << "Informazioni sulle CPU per workstation: https://www.tomshardware.com/reviews/best-performance-cpus,5683.html\n";
        } else if (usage == "Data-Center" || usage == "Data-center" || usage == "data-center") {
            cout << "Puoi controllare le CPU per i Data-Center su: https://www.serversplus.com/servers/server-processors/all-server-processors\n";
            cout << "Informazioni sulle CPU per i Data-Center: https://www.liquidweb.com/blog/server-cpu/\n";
        }
    }
}

// Analizza la CPU in base all'uso
void AnalyzeCPU(const string& cpuModel, const string& usage) {
    vector<string> gamingCPUs = {"Ryzen 5", "Ryzen 7", "Ryzen 9", "i5-12600K", "i7-12700K", "i9-12900K"};
    vector<string> workstationCPUs = {"Threadripper", "Xeon W", "Ryzen 9", "i9-13900K"};
    vector<string> dataCenterCPUs = {"EPYC", "Xeon", "Threadripper"};

    cout << "Analizzando CPU: " << cpuModel << " per utilizzo " << usage << "...\n";
    
    vector<string>* selectedCPUs = nullptr;
    if (usage == "Gaming" || usage == "gaming") selectedCPUs = &gamingCPUs;
    else if (usage == "Workstation" || usage == "workstation") selectedCPUs = &workstationCPUs;
    else if (usage == "Data-Center" || usage == "Data-center" || usage == "data-center") selectedCPUs = &dataCenterCPUs;
    else {
        cout << "Utilizzo non riconosciuto.\n";
        return;
    }

    bool isCompatible = any_of(selectedCPUs->begin(), selectedCPUs->end(), [&](const string& cpu) {  // Controlla se il modello della CPU contiene una delle stringhe selezionate
        return cpuModel.find(cpu) != string::npos;  
    });

    PrintAnalysisResult(isCompatible, usage); 
}

void checkRAM() { // Funzione per controllare la quantità di RAM
    #ifdef _WIN32
        MEMORYSTATUSEX memInfo; 
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);

        DWORDLONG totalRAM = memInfo.ullTotalPhys / (1024 * 1024); // Converti byte in MB
        DWORDLONG freeRAM = memInfo.ullAvailPhys / (1024 * 1024);

        cout << "RAM Totale: " << totalRAM << " MB" << endl;
        cout << "RAM Disponibile: " << freeRAM << " MB" << endl;
    #else
        ifstream memInfo("/proc/meminfo");
        string line;
        long totalRAM = 0, freeRAM = 0;

        while (getline(memInfo, line)) {
            if (line.find("MemTotal:") != string::npos) {
                totalRAM = stol(line.substr(line.find_first_of("0123456789"))); // Estrae il numero
            }
            if (line.find("MemAvailable:") != string::npos) {
                freeRAM = stol(line.substr(line.find_first_of("0123456789"))); 
                break;
            }
        }

        cout << "RAM Totale: " << totalRAM / 1024 << " MB" << endl;
        cout << "RAM Disponibile: " << freeRAM / 1024 << " MB" << endl;
    #endif
}

void analyzeRAM(long totalRAM) {
    struct RAMRecommendation {
        string usage;
        long recommendedMB;
    };

    RAMRecommendation recommendations[] = {
        {"gaming", 16000},
        {"workstation", 32000},
        {"data-center", 128000},
        {"Gaming", 16000},
        {"Workstation", 32000},
        {"Data-Center", 128000}
    };

    cout << "Inserisci l'uso principale (Gaming/Workstation/Data-Center): ";
    string usage;
    cin >> usage;

    for (const auto& rec : recommendations) {
        if (usage == rec.usage) {
            cout << "Per " << usage << ", e' consigliato almeno " << rec.recommendedMB << " MB di RAM." << endl;
            if (totalRAM >= rec.recommendedMB) {
                cout << "La tua RAM e' adeguata per questo utilizzo." << endl;
            } else {
                cout << "Potresti aver bisogno di un upgrade." << endl;
                cout << "Puoi informarti sulle diverse RAM qui: https://www.pcworld.com/article/541506/how-to-choose-the-right-ram.html" << endl;
            }
            return;
        }
    }
    cout << "Utilizzo non riconosciuto. Nessun suggerimento disponibile." << endl;
}

int main() {
    StartingProgram();
    while (true) {
        cout << "\nScegli un'opzione:\n";
        cout << "1 - Analizza la CPU\n";
        cout << "2 - Analizza la RAM\n";
        cout << "3 - Esci\n";
        int scelta;
        cin >> scelta;
        if (scelta == 1) {
            string cpuModel = getCPUModel();
            cout << "Modello CPU rilevato: " << cpuModel << endl;
            cout << "Inserisci l'uso principale (Gaming/Workstation/Data-Center): ";
            string usage;
            cin >> usage;
            AnalyzeCPU(cpuModel, usage); 
        } else if (scelta == 2) {
            checkRAM();
            #ifdef _WIN32
                MEMORYSTATUSEX memInfo;
                memInfo.dwLength = sizeof(MEMORYSTATUSEX);
                GlobalMemoryStatusEx(&memInfo);
                analyzeRAM(memInfo.ullTotalPhys / (1024 * 1024));
            #else
                ifstream memInfo("/proc/meminfo");
                string line;
                long totalRAM = 0;
                while (getline(memInfo, line)) {
                    if (line.find("MemTotal:") != string::npos) {
                        totalRAM = stol(line.substr(line.find_first_of("0123456789"))) / 1024;
                        break;
                    }
                }
                analyzeRAM(totalRAM);
            #endif
        } else if (scelta == 3) {
            cout << "Arrivederci!\n";
            return 0;
        }
    }
    return 0;
}
