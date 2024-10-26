# Lezione 7 (13/03)

## Riassunto

Le cache della CPU non sono veloci come i registri, che eseguono operazioni nello stesso ciclo di clock della CPU. Le cache possono richiedere più cicli per completare un'operazione:

- Un ciclo per tradurre l'indirizzo logico in indirizzo fisico.
- Un ciclo per leggere il dato.

### Working Set

Il **working set** rappresenta l'insieme degli indirizzi di memoria acceduti da un programma o algoritmo. La cache funziona efficacemente se gli stessi dati vengono riutilizzati più volte. Un'ottimizzazione comune è il **tiling**, dove le matrici vengono suddivise in sottomatrici più piccole che possono entrare interamente in cache, migliorando l'efficienza.

Ad esempio, nella moltiplicazione di matrici, è vantaggioso che i due operandi siano presenti in cache, poiché verranno acceduti ripetutamente. La matrice risultante, invece, può essere scritta direttamente in memoria perché l'operazione di scrittura è eseguita una sola volta.

### Principio di Località

Il **principio di località** afferma che se un dato viene acceduto, è probabile che dati vicini vengano acceduti a breve. Questo principio permette la costruzione di gerarchie di memoria, dove più ci si avvicina al processore, più la memoria diventa veloce ma di dimensioni ridotte.

Le cache operano in coppie di livelli (es. L1, L2, L3) e utilizzano linee di cache: quando viene richiesto un dato, viene caricata una linea di dati, non solo il singolo dato richiesto. La dimensione della linea dipende dalla località spaziale e dal costo di trasferimento dei dati, con linee di dimensione crescente man mano che si sale nei livelli della cache (L1 ha linee più piccole di L2, e così via).

Il costo del trasferimento dati è modellabile come una funzione lineare affine: esiste un costo fisso, al quale si aggiunge un costo lineare in base alla dimensione del dato.

L'indirizzamento del sistema non è a byte, ma a **word**. La dimensione di una word dipende dal processore, solitamente 64 bit (8 byte). Una linea di cache è spesso di 64 byte, cioè 8 word.

## Misurazione della Cache

Si considerano due metriche principali:

- **Hit time**: il tempo necessario per accedere alla cache.
- **Miss penalty**: il tempo necessario per accedere alla memoria principale quando c'è un miss in cache.

La probabilità di un hit è generalmente espressa come `1 - probabilità di miss`.

### CPU Time

Il tempo di CPU è calcolato in base ai cicli di clock richiesti per eseguire un programma:

- CPU time = `numero di clock cycle * clock cycle time`.
- Clock cycle = `IC * CPI`.
- IC = numero di istruzioni a livello assembly (Instruction Count).
  - IC = IC_cpu + IC_mem.
- CPI = numero medio di cicli di clock per istruzione:
  - CPI = `clock cycle / IC`.
  - Un CPI di 16 indica che in media vengono eseguite 16 istruzioni per ciclo di clock.
- Clock cycle time = tempo per eseguire un ciclo di clock.

Il CPI può essere scomposto in due componenti:

- `(IC_cpu / IC) * CPI_cpu` (cicli di CPU).
- `(IC_mem / IC) * CPI_mem` (cicli di memoria).

Una linea di cache più grande aumenta la probabilità di località spaziale, ma aumenta anche il costo di spostamento dei dati.

## RISC vs CISC

I set di istruzioni di un processore possono essere classificati come:

- **RISC** (Reduced Instruction Set Computer):

  - Esempio: ARM.
  - Poche istruzioni, circa 100.
  - Ogni istruzione occupa una sola parola di memoria, e ci sono istruzioni dedicate per gestire gli indirizzi (load/store).
  - Più prevedibile, quindi più facile da ottimizzare.

- **CISC** (Complex Instruction Set Computer):

  - Esempio: x86 (Intel, AMD).
  - Più di mille istruzioni, molte delle quali variano per formato (16, 32, 64 bit).
  - Il compilatore deve scegliere tra molte istruzioni, il che rende l'ottimizzazione più complessa.

Le istruzioni CISC possono richiedere un numero variabile di parole di memoria, rendendo tutto più complesso. Attualmente, le architetture CISC sono tradotte in istruzioni RISC a livello hardware, tramite decoder paralleli.

Le GPU utilizzano architetture RISC.

## Organizzazione della Cache

### Direct Mapped

- Ogni blocco di memoria può essere messo in una sola posizione della cache.
- Veloce, ma con un alto numero di miss.
- Utilizzata principalmente per le istruzioni.

### N-Way Set Associative

- Ogni blocco di memoria può essere messo in **n** posizioni della cache.
- Più lenta rispetto a direct-mapped, ma con meno miss.
- Utilizzata principalmente per i dati, come nelle istruzioni di load/store.
- All'aumentare del livello della cache (L1, L2, L3), aumenta anche il numero di modi (**n**).

## Cache Write Policy

Esistono due politiche principali per la scrittura in cache:

- **Write through**:

  - Scrittura sia in cache che a tutti i livelli di memoria.
  - Più lenta, ma più sicura.
  - La scrittura è propagata ai livelli superiori con un ritardo.

- **Write back**:

  - Scrittura solo in cache, con marcatura della linea come modificata.
  - La scrittura è propagata solo quando la linea viene rimossa dalla cache o un altro core richiede il dato.
  - Più veloce, ma meno sicura. Potrebbe causare attese quando un altro core necessita del dato.

## Coerenza della Cache (Cache Coherence)

Quando ci sono più copie dello stesso dato in diverse cache, il problema è mantenerle coerenti. Questo viene risolto tramite protocolli di coerenza.

### Protocollo MESI

Il protocollo **MESI** associa a ogni linea di cache uno dei quattro stati:

- **M**odified: la linea è stata modificata e la copia è esclusiva.
- **E**xclusive: la linea è presente solo in una cache, ma non è stata modificata.
- **S**hared: la linea è presente in più cache, non modificata.
- **I**nvalid: la linea è invalida e deve essere aggiornata.
