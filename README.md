# SpecSense: Analizzatore di CPU e RAM

SpecSense è un programma che permette di analizzare la compatibilità della tua CPU e la quantità di RAM per diversi usi (Gaming, Workstation, Data-Center). Il programma rileva il modello della CPU e verifica se è adatto all'uso selezionato. Inoltre, fornisce raccomandazioni sulla quantità di RAM necessaria per ciascun utilizzo.

## Funzionalità

- **Rilevamento CPU**: Il programma rileva automaticamente il modello della CPU sia su Windows che su Linux.
- **Analisi CPU**: In base all'uso scelto (Gaming, Workstation, Data-Center), il programma verifica se la tua CPU è compatibile.
- **Verifica RAM**: Fornisce informazioni sulla RAM totale e disponibile e suggerisce una quantità minima di RAM per l'uso scelto.
- **Supporto multipiattaforma**: Funziona sia su Windows che su Linux.
- **Sicurezza**: L'accesso alle informazioni hardware avviene in modo controllato senza rischi per il sistema.

## Requisiti

- **Windows**: Dev'essere installato un'ambiente di sviluppo che supporta C++ oppure eseguire SpecSense.exe che verrà eseguito sul terminale.
- **Linux**: Compilatore C++ standard (g++).

## Come Usare

1. Clona il repository:

   ```bash
   git clone https://github.com/Peepo-sama/SpecSense.git
   cd SpecSense
2. Compila ed esegui il programma:

  - Su Windows: Usa un compilatore come MSVC o MinGW.
  
  - Su Linux: Usa g++:
    g++ main.cpp -o SpecSense
    ./SpecSense
  
3. Seleziona una delle opzioni nel menu:

    1: Analizza la CPU.
  
    2: Analizza la RAM.
  
    3: Esci.

  ## Esempio di utilizzo
  
  - Quando scegli l'opzione per analizzare la CPU, il programma rileverà automaticamente il modello della tua CPU e ti chiederà quale sia l'uso principale del sistema (Gaming, Workstation, Data-Center). In base alla scelta, ti dirà se la tua        CPU è adatta o meno.

  - Se scegli di analizzare la RAM, ti fornirà informazioni sulla RAM totale e disponibile e ti consiglierà la quantità minima necessaria per l'uso scelto.

  ## Supporto
  
  **Gaming**: Se il tuo sistema è destinato al gaming, verranno fornite informazioni su CPU e RAM consigliate per un'esperienza ottimale.

  **Workstation**: Ottimizza il sistema per applicazioni professionali con richieste elevate.

  **Data-Center**: Consigli per configurazioni server ad alte prestazioni.
  
  ## Licenza
  
  SpecSense è distribuito con licenza [MIT](https://it.wikipedia.org/wiki/Licenza_MIT). Puoi usarlo, modificarlo e distribuirlo liberamente, purché venga mantenuto il copyright e la licenza.
