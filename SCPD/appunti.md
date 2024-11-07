| col1 | col2 | col3 |
| ---- | ---- | ---- |
|      |      |      |
|      |      |      |

# Introduzione al Calcolo Parallelo e Distribuito (23/02)

## Differenza tra Calcolo Parallelo e Distribuito

- **Calcolo Distribuito** : si concentra sull'interoperabilità tra dispositivi indipendenti, come le applicazioni su smartphone che devono funzionare anche in assenza di connessione internet. Questo modello enfatizza la resilienza e l'autonomia operativa di ciascun nodo della rete.
- **Calcolo Parallelo** : mira al miglioramento delle prestazioni attraverso la divisione dei compiti in parti che possono essere eseguite simultaneamente su diversi processori. In caso di fallimento di un'operazione, si scarta il tentativo in corso e si riparte da capo, con l'obiettivo di ottimizzare il tempo di esecuzione totale.

## Considerazioni sul Calcolo Parallelo

Non tutti i problemi beneficiano del calcolo parallelo. L'overhead, o i costi aggiuntivi legati alla sincronizzazione e coordinazione delle esecuzioni parallele, può talvolta superare i benefici. Un esempio è la parallelizzazione di operazioni semplici come la somma di due numeri, dove il tempo necessario per coordinare i processori potrebbe eccedere il tempo di esecuzione dell'operazione stessa.

È cruciale valutare attentamente i limiti e le opportunità offerte dal calcolo parallelo prima di procedere con la sua implementazione.

## Architetture del Calcolo Parallelo

- **Cluster di Calcolo (Compute Cluster)** : Gruppi di computer indipendenti che lavorano insieme per eseguire compiti condivisi.
- **SMP (Symmetric Multi-Processing)** : Più processori condividono un'unica memoria centrale.
- **CMP (Chip Multi-Processor)** : Più processori si trovano sullo stesso chip, condividendo risorse e ottimizzando l'efficienza energetica.

Inoltre, si osserva una tendenza verso l'utilizzo di processori specializzati per compiti specifici, al fine di migliorare l'efficienza e la velocità di esecuzione. Questi includono, ad esempio, processori dedicati al parsing di JSON in server web o al controllo della sicurezza dei messaggi.

## La Fine dell'Era del "Pranzo Gratis"

La "Free Lunch Era" si riferisce al periodo in cui si riteneva che l'aumento della potenza di calcolo sarebbe continuato indefinitamente grazie alla miniaturizzazione dei transistori (Legge di Moore). Tuttavia, raggiunti i limiti fisici di questa scala, è diventato essenziale trovare nuove strade per aumentare le prestazioni, come il calcolo parallelo.

Implicazioni di questa transizione includono una maggiore enfasi su microarchitetture ottimizzate, riduzione delle latenze, integrazione di maggiori cache nei processori, e una ricerca costante verso l'efficienza energetica.

## Gestione della Cache

La cache, elemento cruciale per l'efficienza del calcolo, opera in trasparenza rispetto all'utente, simulando l'accesso alla memoria principale ma offrendo tempi di risposta significativamente inferiori. La gestione della cache implica strategie di mappatura degli indirizzi e politiche di rimpiazzamento, come il Least Recently Used (LRU), per ottimizzare l'accesso ai dati frequentemente utilizzati.

Questa introduzione mira a fornire una panoramica concisa e informativa sul calcolo parallelo e distribuito, evidenziando le sfide, le strategie e le architetture chiave in questo ambito.

# Lezione 4 1/03 (MIT slides)

## Principio di Località

La gestione efficace della cache sfrutta il principio di località del codice, essenziale per ottimizzare l'accesso ai dati:

- **Località Spaziale** : l'accesso a un dato aumenta la probabilità di accedere a dati adiacenti. Questo principio è sfruttato efficacemente da strutture dati come gli array, soprattutto quando si accede sequenzialmente agli elementi.
- **Località Temporale** : se un dato viene accesso una volta, è probabile che venga riaccesso in breve tempo. Cicli come i `for` possono capitalizzare su questo principio se organizzati correttamente.

La RAM consente accessi in qualsiasi ordine (da qua il significato di `RANDOM ACCESS MEMORY`)\, ma non tutti gli accessi hanno lo stesso costo. Cicli sequenziali, come quelli creati con l'istruzione `for`, suggeriscono al compilatore un accesso sequenziale ai dati, permettendo tecniche di prefetching, ovvero il caricamento anticipato dei dati in cache basato sulla predizione degli accessi futuri.

Le interruzioni anticipate dei cicli (`break`) possono complicare il prefetching, poiché il compilatore non può prevedere con certezza l'uscita anticipata dal ciclo.

## Parallelismo nei Cicli

Nel programmi paralleli l'ottimizzazione del compilatore protrebbe dare risultati diversi, in quanto otimizza come se fosse un programma sequenziale.

Nel contesto del parallelismo, la scelta di quale ciclo parallelizzare è critica. Generalmente, è preferibile parallelizzare il ciclo più esterno per massimizzare l'efficienza, dato che comporta l'esecuzione parallela di compiti maggiori rispetto ai cicli interni, che sono più granulari e numerosi ma con un costo inferiore per iterazione.

- **Ciclo Esterno** : esecuzione parallela di task più grandi, con tempi più lunghi ma minor frequenza.
- **Ciclo Interno** : esecuzione parallela di numerosi task più piccoli, con minor tempo di esecuzione ma alta frequenza.

Parallelizzare un algoritmo sequenziale su n core non garantisce un miglioramento proporzionale delle prestazioni (speedup di n), ma si ottiene sempre un risultato minore o uguale a n a causa dell'overhead della gestione del parallelismo.

## Ottimizzazione del compilatore

Il compilatore può ottimizzare il codice in vari modi, in realtà si basta su ottimizzazioni di codici sequenziali, ma non sempre queste ottimizzazioni sono efficaci per il codice parallelo. Potrebbero infatti modificarne la semantica, causando problemi di sincronizzazione e accesso concorrente ai dati.

## Gerarchia della Cache nei Sistemi Multicore

- **LLC (L3) cache** : condivisa tra tutti i processori, non per forza un pezzo unico, ma condivisa.
- **L2 cache** : Dedicata a ciascun processore, facilita un accesso più rapido rispetto all'LLC per quei core. (Una per processore)
- **L1 cache** : Dedicata a ciascun core, offre la latenza più bassa per l'accesso ai dati. (Una per core)

Il parallelismo può essere esteso all'interno dei singoli core attraverso il calcolo vettoriale, che consente di eseguire più operazioni simultaneamente su set di dati. Questo approccio, supportato da estensioni hardware come SSE e AVX, trova applicazione in ambiti specifici come l'elaborazione di immagini e video, ma anche in librerie di calcolo scientifico come PyTorch e TensorFlow.

# Classificazione di archittetture parallele

Divisione tra:

- Singolo server
- Cluster: nodi connessi in rete

## Classificazione di Flynn:

### (S | M) I (S | M) D

- S: Single
- M: Multiple
- I: Instruction
- D: Data

### Classificazione:

- **SISD** : Single Instruction Single Data
  - Un solo processore esegue un singolo flusso di istruzioni su un singolo flusso di dati, macchina sequenziale
- **SIMD** : Single Instruction Multiple Data
  - Un singolo flusso di istruzioni viene eseguito su più flussi di dati, vettorizzazione
  - esempio: for(i = 0; i < n; i++) a[i] = b[i] + c[i];
    - eseguo la stessa operazione su tutti gli elementi di b e c
    - | b   | 1   | 1   | 1   |
      | --- | --- | --- | --- |
      |     | +   | +   | +   |
      | c   | 1   | 1   | 1   |
      |     | =   | =   | =   |
      | a   | 2   | 2   | 2   |
- **MISD** : Multiple Instruction Single Data
  - Più flussi di istruzioni operano su un singolo flusso di dati, rarità nell'implementazione pratica.
  - Usare algortimi diversi sullo stesso dato per motivi di **robustezza**, calcolo lo stesso dato in modi diversi e confronto i risultati.
  - Un esempio potrebbe essere il Bagging nel machine learning, dove si addestrano diversi modelli su un singolo dataset e si aggregano i risultati.
- **MIMD** : Multiple Instruction Multiple Data
  - Il modello più flessibile e comune nelle architetture parallele, con più core che eseguono flussi di istruzioni indipendenti su flussi di dati distinti.
  - La memoria non viene condivisa.

Come si programma una memoria? la memoria ha due 2 api:

- lettura: signature `read(addr: int) -> int`
- scrittura: signature `write(addr: int, value: int) -> void`

Se la memoria è una shared memory, le api sono 3:

- lettura: signature `read(addr: int) -> int`
- scrittura: signature `write(addr: int, value: int) -> void`
- lock: signature `lock(addr: int) -> void` (verificare?) (leggi e scrivi in maniera atomica)

Per quanto riguarda la CPU: è il suo linguaggio macchina

# Lezione 5 (6/03) - 4 Classification

## Parallel Architectures

Usando i processi devo dicedere prima come e dove allocare le strutture dati in maniera che siano disponibili a tutti i processi.
Per i thread invece posso anche pensarci dopo, in quanto condividono lo stesso spazio di memoria.

## shared memory

Permettono di leggere e scrivere da due o più processi.
Generalmente un processo non può leggere o scrivere la memoria di un altro processo.

## Distributed memory

Ogni processore ha la propria memoria e attraverso una interconnection network possono comunicare tra loro.
Avviene tramite scambio di messaggi, viene inviato il messaggio e poi esso viene scritto in memoria.

## memory consistency & cache coherence

Il problema della consistenza della memoria è che se due processi leggono la stessa locazione di memoria, non è garantito che leggano lo stesso valore.
L'accesso alla memoria **non è una operazione atomica**:

- il processore fa una richiesta di lettura
- la memoria riceve dopo un po' la richiesta
- ricerca il dato, la memoria è una matrice, tramite l'indirizzo viene individuata prima la riga, essa viene salvata su un buffer e da esso viene estrapolato il dato ricercato.
- risponde al processore
- dopo un po' il processore riceve la risposta

Il tutto avviene tramite un dialogo sul bus.
Se ho più processori le operazioni si sovrappongono e quindi non è garantito che i processori leggano lo stesso valore.
Ma soprattutto non è garantito che se un processo fa una richiesta di lettura prima allora riceva il dato prima rispetto a un altro processo.

Il problema della consistenza della memoria è capire se esiste e se deve esistere un ordine tra le richieste alla memoria, capire quindi come avvengono le operazioni di lettura e scrittura viste dalla parte della memoria.
è possibile che l'effetto della memoria sia diverso rispetto a quello scritto nel programma a causa appunto di questi ritardi.

## Modello di consistenza sequenziale

Impone un ordine totale con cui avvengono le cose in memoria.
Se un processore scrive un dato e poi legge il dato, il dato letto deve essere uguale al dato scritto.
Ad esempio:

- A = 1
- B = 2

Quando faccio B=2 allora sono sicuro che A=1, in quanto ho un ordine totale.
Nessuna delle macchine di oggi usa questo modello, in quanto è molto restrittivo; con due memorie non sono più in grado di garantire un ordine totale, ma solo uno parziale per ognuna delle memorie.

Esempi di modelli di consistenza:

- Weak order
- Total store order

## Cache coherence

Con la cache, il problema della consistenza della memoria diventa più complesso.
In una cache di un processore A = 1, in un'altra cache di un processore A = 2.
Fare in modo che il programmatore non abbia mai la percezione che esistano valori diversi della stessa variabile in cache diverse.
Riguarda copie multiple dello stesso indirizzo, vorrei che tutte le copie siano aggiornate allo stesso valore, senza dover necessariamente andare a vedere in memoria, altrimenti renderebbe le cache inutili.
La cache coherence puo' essere risolto a livello hardware, i due processori comunicano attraverso un protocollo al fine di decidere quale valore è il corretto, il protocollo di cache coherence deve andare alla velocità delle cache, non alla velocità della memoria, sempre per non rendere unitili le cache.

Più sono le cache più questo dialogo diventa complicato e costoso (una macchina con tanti core porta il core ad andare più lentamente).
Ogni processore scalabile(per scalabile si intende che supporta la combinazione in più socket) ha un numero limite di socket supportati, in quanto altrimenti la cache coherence diventerebbe troppo costosa.

## shared memory fondamenti

- scambio di dati (shm/msg)
- sincronizzazione, avviene tramite msg
  Un msg porta informazioni sia dei dati che temporali, in quanto se un processo manda un msg ad un altro processo, il secondo processo deve essere pronto a ricevere il msg.
  Come faccio a sapere se un processo ha scritto un dato per un altro processo? e come faccio a sapere in che punto della memoria è stato scritto?
  Servirebbe un semaforo ma al livello di memoria non esiste.
  Un messaggio è una forma di sincronizzazione un po' lasca perchè non so quanto prima il messaggio è stato scritto.
  Se invio un messaggio di sincronizzazione e io parto subito dopo, il processo che riceve il messaggio parte dopo di me, ma non so quanto dopo di me.

|                  | Architettura a SHM                                                                                                                                                                                                                                                                                                                                                                                              | Architettura Distribuita                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| ---------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Scambio Dati     | Tramite scrittura e lettura in indirizzo<br /> di memoria condivisa                                                                                                                                                                                                                                                                                                                                             | Tramite scambio di messaggi                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| Sincronizzazione | Come faccio a sapere se un processo ha scritto un dato per un altro processo?<br />e come faccio a sapere in che punto della memoria è stato scritto?<br /><br />Servirebbe un semaforo ma al livello di memoria non esiste.<br />Potrebbe essere implementanto usando le api di read e write delle memorie.<br />Si può utilizzare l'operazione di scambio atomico per realizzare semafori di sincronizzazione | Sempre tramite scambio di messaggi:<br /><br /> Un msg porta informazioni sia dei dati che temporali, in quanto se un processo<br />manda un msg ad un altro processo, il secondo processo deve essere pronto a ricevere il msg.<br /><br />Un messaggio è una forma di sincronizzazione un po' lasca perchè non so quanto prima il messaggio è stato scritto.<br />Se invio un messaggio di sincronizzazione e io parto subito dopo, <br />il processo che riceve il messaggio parte dopo di me, ma non so quanto dopo di me. |

### Thread

Un processo è un programma in esecuzione, composto da un Process Control Block (PCB) che contiene informazioni come lo stato del processo, la memoria allocata, lo stack, i file aperti, ecc.

Ongi processo ha uno spazio logico di indirizzamento, quindi ogni processo ha la sua memoria. Due processi possono riferirsi alla stesso indirizzo logico ma non stanno parlando della stessa locazione di memoria.

Un thread è un processo leggero, condividono lo stesso spazio di memoria, quindi se un thread scrive un dato, un altro thread può leggerlo. L'indirizzo logico si riferisce alla stessa locazione di memoria.
Hanno un loro Process control block chiamato TCB (Thread Control Block).
Ogni thread ha un suo stack, ma condividono lo stesso heap e lo stesso blocco logico e i puntatori ai file aperti.

I processi sono generalmente indipendenti, mentre i thread sono oggetti cooperanti.

Il modello Posix permetto di creare e distruggere thead attraverso operazioni di fork e join.

è necessario definire operazioni di sincronizzazione.

## distributed memory fondamenti

- ridurre il tempo/costi di comunicazione
- dal punto di vista elettronico il numero di connessioni cresce in maniera quadratica rispetto al numero di processori

Il modo di fare parallelismo avviene tramite la creazione di diversi processi che non condividono la memoria e quindi comunicano tramite messaggi (es. Pipe, o attraverso una rete).

é composto da nodi che a loro volta possono essere multi-core.
Comprendo quindi l'uso di un livello a shared memory e un livello a scambio di messaggi.

I linguaggi di programmazione non hanno un costrutto per la comunicazione tra processi, ma è necessario utilizzare delle librerie di SO per fare ciò esempio: Pipeline o Socket.

Si è cercato di astrarre il problema creando una libreria chiamata MPI (Message Passing Interface) che permette di scrivere programmi paralleli in maniera trasparente rispetto all'architettura sottostante.

Si distinguono per **la tipologia della rete** e per la loro **diffusione geografica** (stessa stanza, stesso edificio, stesso paese, stesso continente, mondo). in funzione di questi aspetti possono essere chiamati in diversi modi: Cluster, Cloud, ecc...

# Lezione 6 (8/03) -

## thread cooperativi o fiber

Sono thread che volontariamnte lascia il controllo ad un altro thread, quindi non è il sistema operativo a decidere quando un thread deve essere eseguito. Il passaggio di controllo avviene come se venisse chiamata un'altra funzione. (Molto veloci per questo)

## stencil computation in shared memory

Il programmatore deve dividire la memoria in parti e decidere quali parti devono essere allocate in quale processo.
Riguarda spesso array divisi a pezzi e distrubuiti tra i processi.

## halo swapping

Se ho una matrice divisa in pezzi, ogni pezzo ha un bordo (alone), e questo bordo è la copia del bordo di un altro pezzo. (deciso staticamente dal programmatore, devi pensarci prima alla creazione dei processi) (migliore in termini di prestazione).

Se ho una shared memory è molto più semplice, in quanto posso accedere direttamente alla cella di memoria, perchè è divisa solo logicamente. (Peggiore in termini di prestazione, posso avere dei punti di congestione sulla memoria). (posso fare decisione dinamiche a runtime, non come prima).

## Ricapitolando

- Regole esame e raccomandazioni corso
- Introduzione sulla motivazione del parallel computing
- Introduzione alle hardware platform
- Programming model
  - SHM (lock/unlock, read/write)
    - [lock free programming](https://www.boost.org/doc/libs/1_60_0/doc/html/lockfree.html) (approfondimento se c'è tempo)
  - Message passing (sincronizzazione tramite messaggi)
  - GPU
  - Come creare thread
  - Come scambiare dati
  - Come sincronizzarsi

## Shared memory

### Memory Wall o Memory Gap

Inizialmente il tempo per accedere alla memoria e il tempo per la computazione erano simili e bilanciati.
Oggi il tempo per accedere alla memoria è molto maggiore rispetto al tempo per fare la computazione, in quanto i processori sono cresciuto di molto in termini di velocità, mentre la memoria no. Le memoria si sono sviluppate per essere più grandi e non più veloci. (Memory Wall o Memory Gap).

La chache L3 è sia condivisa tra core che distribuita tra nodi (diversi socket).

## hyper threading

I processori moderni utilizzano un'architettura chiamata pipeline, che suddivide l'esecuzione delle istruzioni in diverse fasi, tipicamente:

- Fetch (prelievo dell'istruzione dalla memoria),
- Decode (decodifica dell'istruzione),
- Execute (esecuzione dell'istruzione),
- Write (scrittura del risultato).

Hyper-Threading è una tecnologia che consente a un singolo core di gestire due thread contemporaneamente. L'idea è che, mentre uno dei thread è bloccato in una fase della pipeline (ad esempio, attende dati dalla memoria), l'altro thread può utilizzare le risorse disponibili del core per continuare a progredire. Questo sfrutta meglio le risorse del processore.

Un processore con un singolo core ma due thread attivi tramite hyper-threading non è equivalente a un processore con due core fisici. In particolare, c'è ancora una sola fase di esecuzione (execute) nella pipeline, quindi non può esserci vero parallelismo completo. Ciò significa che, anche se il processore può avanzare in alcune fasi con due thread contemporaneamente, una volta che le istruzioni raggiungono la fase di esecuzione, il processore deve gestirle in modo sequenziale o alternato, non parallelamente.

In sintesi, l'hyper-threading replica la capacità di gestire più thread solo nelle fasi iniziali della pipeline (fetch e decode), ma quando le istruzioni richiedono l'esecuzione vera e propria, le risorse fisiche limitate del core impediscono un'esecuzione parallela completa.

Bisogna sempre controllare se si hanno un certo numero di core o se si ha hyperthreading (anche chiamato contesto), in quanto con hyperThreading non raggiungerò mai lo speedup sperato.

4 tipi di istruzioni e profondità della pipeline:

- calcolo (operative)
- jump condizionale (si fermano al decode)
- jump incondizionale (si fermano al decode)
- chiamata al sistema (load e store) (le load si fermano al fetch, le store al write)

Per i programmi di calcolo intensivo l'hyper threading non è molto utile, in quanto non si ha un vero parallelismo, ma per programmi che fanno molte operazioni di I/O o condizioni è molto utile.

# Lezione 7 (13/03)

## riassunto

La cache non va veloce come i registri della cpu che eseguono le operazioni nello stesso ciclo di clock della cpu. Le cache magari ce ne mettono due:

- un ciclo per tradurre l'indirizzo logico in indirizzo fisico
- un ciclo per leggere il dato

Working set: insieme degli indirizzi acceduti da un programma, da un algoritmo o da una parte di algoritmi.

La cache funziona bene se agli stessi dati ci accedo più volte. La soluzione è il tiling in cui si divide la matrice in sottomatrici più piccole, in modo che le sottomatrici siano piccole e quindi che ci stiano in cache.
Nell'esempio di moltiplicazione di matrici, è bene che i due operandi stiano in cache, appunto perchè ci accedo più volte, mentre la matrice risultato può essere scritta direttamente in memoria in quanto l'operazione di write è una sola.

Principio di località: se accedo a un dato, è probabile che acceda a dati vicini.
Permette la costruzione di gerarchie di memoria. (più livelli di caching)
Più si arriva vicino al processore più si ha una memoria più veloce ma generalmente più piccola (piccola per via della tecnologia, potrebbe anche essere della stessa dimensione ma più veloce).

Le cache si osservano a coppie di livelli, i e i+1, e si definisce la dimensione delle linee ad esempio, qundo chiedo un dato al liv successivo non chiedo un singolo dato ma una linea di dati.

Quando ho un miss non richiedo un singolo dato al livello successivo ma una intera linea di cache, la dimensione della linea dipende da quanto probabilità di avere località spaziale(ricevo comunque una linea anche se poi magari non la uso, e questo ha un costo) e da quanto costa spostare i dati e ovviamente dalla dimensione della cache stessa.
l1 avrà linee più piccole di l2 e l2 avrà linee più piccole di l3.

Lo scambio costra quanto una funzione lineare affine, si ha un costo costante e poi cresce linearmente sulla base della dimensione del dato.

L'indirizzamento del sistema non è a byte, ma a word. quando è grande una word? dipende dal processore, ma generalmente è di 64 bit ovvero 8 byte. una linea generalmente è di 64 byte ovvero 8 word.

## Cache measurement

Si hanno due tempistiche:

- hit time: tempo per accedere alla cache
- miss penalty: tempo per accedere alla memoria principale

Solitamente sono probabilità hit = 1 - probabilità miss.

- CPU time: numeri di cicli di clock che servono per eseguire un programma.
  = clock cycle \* clock cycle time
- Clock cycle = IC \* CPI
- IC = numero di istruzioni (a livello assembly)
  - IC = IC_cpu + IC_mem
- CPI = numero medio di cicli di clock per istruzione
  - CPI è la media dei cicli di clock per istruzione
  - CPI = clock cycle / IC
  - se CPI è 16 allora vengono eseguite 16 istruzioni in un ciclo di clock
  - CPI è un dato che cattura anche il numero di istruzioni dell'algoritmo perchè è una media
- Clock cycle time = tempo per eseguire un ciclo di clock
- CPI puo' essere scomposto: (IC_cpu \ IC) \* CPI_cpu + (IC_mem \ IC) \* CPI_mem
  - CPI_cpu = numero di cicli di clock per istruzione della cpu
  - CPI_mem = numero di cicli di clock per istruzione della memoria

Più è grande la line chache più ho probabilità di avere località spaziale, ma più è grande il costo di spostare i dati.

## RISC vs CISC

Sono un modo di definere il set di istruzioni di un processore.

- RISC: Reduced Instruction Set Computer

  - poche istruzioni
  - esempio: ARM
  - poco più di 100 istruzioni

- CISC: Complex Instruction Set Computer

  - molte istruzioni, molto varie.
  - esempio: x86 (AMD, Intel)
  - più di mille istruzioni
  - il compilatore deve scegliere tra tante istruzioni, quindi è più complesso, le istruzioni non costano tutte ugualmente.
  - ci sono operazioni che variano solo per la dimensione del formato, a 16 bit, a 32 bit, a 64 bit, ecc...

Quando leggo una istruzione non so precisamente quante parole di memoria servono, se ho una istruzione a 64 bit che usa 3 indirizzi a 64 bit, allora mi servono 3 parole di memoria rendendo tutto più complesso.
Es. add a, b, c

Nelle RISC: l'idea è che ogni istruzione deve stare in una parola, facendo dei sacrifici: non ci metto gli indirizzi se non uno.

Ho due istruzioni specializzate per le **operazioni sugli indirizzi**, load e store.
load a
load b

Le **altre istruzioni lavorano** sui registri:
(a e b sui registri, indizzi a 8 bit, più piccoli perchè non sono tanti quanto in memoria)
add r1, r2, r3

store r3, c

in questo modo si ho istruzioni più piccole però ne avrò bisogno di più per fare la stessa cosa.

Con RISC il compilatore sa esattamente (è più prevedibile) quanto costa in tempo ogni istruzione, quindi è più facile fare ottimizzazioni.
Attualmente ha vinto Risc ma si usano soluzioni ibride. Il cisc viene tradotto a livello hardware in risc in maniera dinamica. Per ottimizzare esistono nei processorei decoder parallelizzati(alcuni per operazioni complesse altre per quelle semplici).
ARM invece non ha di questo problemi in quanto è un risc, con tutti i problemi di compatibilità che ne derivano.

Le gpu sono Risc.

The key operational concept of the RISC computer is that each instruction performs only one function (e.g. copy a value from memory to a register). The RISC computer usually has many (16 or 32) high-speed, general-purpose registers with a [load–store architecture](https://en.wikipedia.org/wiki/Load%E2%80%93store_architecture "Load–store architecture") in which the code for the register-register instructions (for performing arithmetic and tests) are separate from the instructions that access the main memory of the computer. The design of the CPU allows RISC computers few simple [addressing modes](https://en.wikipedia.org/wiki/Addressing_mode "Addressing mode")^[[2]](https://en.wikipedia.org/wiki/Reduced_instruction_set_computer#cite_note-Flynn54-2)^ and predictable instruction times that simplify design of the system as a whole.

## Organizzazione della cache

- Direct Mapped (usata per le istruzioni, non istruzioni load e store)
  - ogni blocco di memoria può essere messo in una sola posizione della cache
  - se ho un blocco di memoria che va in una posizione della cache, e poi ne arriva un altro che va nella stessa posizione, il primo viene buttato via.
  - è molto veloce, ma ha un alto numero di miss
  - viene usato per le istruzioni, perchè sono più critiche, perche la cache andrebbe letta ad ogni istruzione, inoltre c'è la possibilità di rileggere le stesse istruzioni(loop) devo fare solo attenzione che non ci siano conflitti.
- n-way set associative (usata per i dati, istruzioni load e store)
  - ogni blocco di memoria può essere messo in n posizioni della cache
  - è più lento, ma ha un numero di miss minore
  - è più lento in quanto in caso di conflitto devo accedere a più tabelle
  - le load e store sono in generele meno frequenti rispetto alle altre, perciò mi convienve usare una cache un po più lenta ma più efficiente.
  - più salgo di livello più la cache è grande e più è n-way set associative (n grande)

## Cache write policy

La scrittura è più complessa, esistono due tipi di policy:

- Write through:
  - scrivo sia in cache che a tutti i livelli precedenti fino alla memoria.
  - è più lenta, ma più sicura
  - avviene in più step,prima scrivo nel primo livello, e poi prima o poi queste modifiche vengono propagate
- Write back:
  - scrivo in cache e marko quella linea come scritta.
  - la scrittura verrà propagata alla memoria solo quando la linea verrà buttata via o quando un altro core fa richiesta di lettura.
  - quei dati che non servono a nessuno non vengono mai scritti in memoria se non alla fine del programma.
  - L'aspetto negativo è che la propagazione avverà solamente quando un core ne fa richiesta, quindi dovrà aspettare.
  - se qualcuno deve leggere deve attendere che la scrittura sia finita.
  - è più veloce, ma meno sicura

## Cache coherence

Se ho due copie di due cache diverse il problema è mantenerle coerenti.
Esistono dei protocolli per risolvere questo problema.
Il problema maggiore è se entrambe le copie sono state modificate, quale delle due è quella corretta?

gestione della inconsistenza della memoria:

- MESI: Modified, Exclusive, Shared, Invalid
  - associare a ogni linea di cache uno dei quattro stati
  - se voglio scrivere deve essere in stato E, le altre copie devono essere portati a I (la vera copia ce l'ho io, le altre sono invalidi)

# Lezione 8 (15/03)

## Super scalar processor

Le CPU moderne sono parallele, e usano una _mixed pipeline_.
Ciò significa che il processore esegue più istruzioni contemporaneamente al fine di mantenere la pipeline piena e sfruttare al massimo le risorse disponibili:

- Fetch multiple instructions in un singolo ciclo di clock
- Li esegue _out-of-order_ (esegue le istruzioni pronte, che hanno gli operardi pronti) distribuendole a più ALU contemporaneamente
- I risultati vengono riordinati prima di essere scritti, in modo da mantenere la correttezza del programma:
  - Bernstein's conditions: condizioni che garantiscono che il riordinamento delle istruzioni non alteri il risultato del programma.
  - Consiedera coppie di istruzioni potenzialmente dipendenti:
    - write-read
    - write-write
    - read-write
  - Se le istruzioni sono indipendenti, possono essere eseguite in parallelo.

**SMT**: Simultaneous Multi-Threading, hyper-threading

- Tecnica che consente a un singolo core di eseguire più thread contemporaneamente.
- Ogni thread ha il proprio set di registri e program counter, ma condivide le altre risorse del core.
- L'obiettivo è mantenere il core occupato quando un thread è bloccato (ad esempio, in attesa di dati dalla memoria).
- L'implementazione di SMT può variare a seconda del processore (HW multithreading), ma in generale consente di eseguire più thread contemporaneamente, migliorando l'utilizzo delle risorse del core.
- Il processore mantiene il contesto (registri, program counter, ecc.) per ogni thread e può passare rapidamente da un thread all'altro per mantenere il core occupato.

Due tipi di **HW multithreading**:

- **fine-grained**: il processore esegue istruzioni da thread diversi in modo alternato (interleaved), a livello di singole istruzioni.
- **coarse-grained**: il processore effettua switch di thread al livello di thread, uno switch avviene quando un thread va in stallo.

## Programming shared memory

Il modo più semplice per programmare un sistema a shm è utilizzare i thread.
I thread sono più leggeri dei processi, in quanto condividono lo stesso spazio di memoria.
La creazione di un nuovo thread non alloca un nuovo spazio logico di indirizzamento, ma condivide quello del processo padre. (dalle 3 alle 5 volte più veloce di un processo)

**Tempo creazione thread**: 10'000 cicli di clock

- non creo un thread per fare una addizione, lo creo per fare un lavoro più complesso
- stare intorno ad una grana computazionale: 100'000 cicli di clock

La creazione di processi costa tanto in quanto la _fork_ deve allocare un nuova entry nella tabella di allocazione ma soprattutto deve copiare la memoria del processo padre nel processo figlio.

3 aspetti:

- creazione
- trasferimento di dati
- sincronizzazione

## Thread creation

Pthread create (standard posix thread) primitiva posix per la creazione di thread.

```c
#include <pthread.h>
#include <stdio.h>

void *my_thread(void *arg) {
  printf("Hello from thread\n");
  return NULL;
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, my_thread, NULL);
  pthread_join(tid, NULL);
  return 0;
}
```

pthread_create riceve una funzione void* e un argomento void*.
Esegue la funzione passata come argomento in un nuovo thread e ritorna un void.

## Data race (DR)

occorre quando due o più thread accedono alla stessa variabile e almeno uno di essi scrive e non ci sono meccanismi di sincronizzazione.
Se due thread leggono la stessa variabile non c'è problema, ma se uno scrive e l'altro legge, allora si ha un problema.

# Lezione 9 (20/03)

Outline:

- come allocare risorse su un super computer
- come eseguire un programma su un super computer
- come misurare le prestazioni di un programma su un super computer

## Super computer

Sistemi a code, se lanci un programma questo va in coda e viene eseguito quando è il suo turno.
Utilizzo batch, diverso dal on demand, in cui si ha un server che è sempre acceso e pronto a rispondere alle richieste.

SLURM: Simple Linux Utility for Resource Management
DBS: Distributed Batch System

Faccio login sul sitema, chiamo il sistema di code per chiedere di eseguire l'esperimento. questi fanno 3 cose:

- allocano risorse (1 nodo, 1 nodo e 3 core), appena ci sono me le allocano in maniera escusiva
- gestiscono la coda, per priorità, o code con massime grandezze di risorse richiedibili, oppure code interattive
- creare report sull'uso delle risorse

## SLURM

Una partizione è una coda che ha determinate caratteristiche, lo scheduling viene fatto su più code, le code lo sceglie l'utente.

- sinfo: mostra lo stato delle partizioni
- salloc -p `<partizione>` : per code interattive
- sbatch -n `<numero di core>` -p `<partizione>` `<script>` : per code batch

Una volta allocato il nodo, ci entro dentro tramite ssh, e poi eseguo il programma tramite srun.

## Algoritmi di scheduling:

- Backfill algorithm
  Se ho un programma che richiede 10 core e un programma che richiede 5 core, e ho 10 core liberi, il programma da 5 core viene eseguito subito, in quanto so che il programma da 10 core non può essere eseguito subito.
  Esegue prima un programma piccolo in modo da liberare risorse per un programma più grande.
  Il tempo di esecuzione va specificato nel comando con il flag -time. Se non lo specifico mette la durata massima, 24 o 48 ore.
- Priority queue algorithm
  Assegna una priorità a ogni job, e sceglie il job con la priorità più alta.

Obbiettivo è massimizzare l'utilizzo delle risorse.

## Comandi:

- srun: per eseguire un comando
- sbatch: per eseguire uno script batch
- squeue: per vedere i job attualmente in esecuzione
- scontrol: per controllare i job, mostra metadati sui job
- scancel: per cancellare un job

## PBS (Portable Batch System)

Fa le stesse cose di SLURM ma con altri comandi. Posso fare tutto tramite un file sh

## System module

Permette di avere varie versione dello stesso software, e di caricare e scaricare moduli.

- module load `<nome del modulo>`: carica un modulo
- module purge: resetta i moduli

Non permette di gestire bene le dipendenze tra i moduli. La gestione delle dipendenze è lasciato al programmatore.

## SPACK

Gestore di pacchetti per HPC (High Performance Computing), permette di gestire le dipendenze tra i moduli.
A differenza degli altri, lui compilare i pacchetti e li installa in una directory specifica.
Su HPC compilare in loco è molto importante per ottimizzare le prestazioni. Il compilatore sa bene come è fatta la ram, la cpu, ecc... e quindi può fare ottimizzazioni specifiche.

## Comandi

- spack list: mostra i pacchetti disponibili
- spack install `<nome del pacchetto>`@`<version>`: installa un pacchetto
- spack info `<nome del pacchetto>`: mostra informazioni sul pacchetto, come le versioni disponibili
- spack find `<nome del pacchetto>`: mostra la versione installata
- spack find: mostra tutti i pacchetti installati

Per aprire una shell interattiva (ad esempio per provare programmi SHM):

```bash
srun -p broadwell --gpus=1 -pty bash
```

# Lezione 10 (22/03)

## MUTEX

Per evitare il Data race, si usano i mutex (mutual exclusion), che permettono di bloccare l'accesso ad una risorsa condivisa.
L'idea è quella di accedere ad un segmento di codice in mutua esclusione, in modo che un solo thread possa accedere alla risorsa condivisa alla volta.
In realtà è possibile definire un numero di thread che possono accedere alla risorsa condivisa contemporaneamente, ma è comunque un numero limitato, la differenza è lock e unlock(binari) o semafori (n-ari).

Quando qualcuno prova ad accedere alla regione critica e trova il mutex bloccato, si mette in attesa, e quando il mutex viene sbloccato, il thread viene risvegliato.
Ciò non garantisce il Data Race (riguarda la variabile, i mutex riguardano pezzi di codice), ma da gli strumenti per evitarlo.

Se voglio evitare Data race devo farlo sia in scrittura che in lettura, impattando purtroppo sulle prestazioni.

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *my_thread(void *arg) {
  pthread_mutex_lock(&mutex);
  printf("Hello from thread\n");
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, my_thread, NULL);
  pthread_join(tid, NULL);
  return 0;
}
```

## False sharing

Un conto è garantire che una variabile venga letta e scritta una alla volta, un'altro è garantire che l'ordine delle istruzioni di scrittura e lettura sia rispettato.
immaginiamo che core1 e core2 arrivvano alla memoria(o chache) attraverso un buffer di scrittura, il problema dell'ordine (o consistnza) deriva proprio dall'uso di questo buffer.

Nel caso di alcuni processori (tipo Intel) la mutua esclusione effettua il flush dei buffer prima e dopo la lock. Questo garantisce che quando usciamo dalla mutua esclusione, allora la variabile condivisa sia stata aggiornata in memoria, in modo tale che se un altro core la legge, legge l'ultima versione. Questo non garantisce che l'ordine sia totale per tutte le variabili, ma solo parziale (queste operazioni richiedono del tempo).

Questo non avviene per tutti i processori, infatti questa operazioni spendono energia, tipo i processori dei cellulari non lo fanno. i processori Arm non hanno la lock ma usano memory barrier, che garantisce che le operazioni siano eseguite in ordine. (questo è un problema per i programmatori, in quanto non sanno se il processore su cui sta girando il programma ha la lock o meno).

Il false sharing riguarda le cache, se due variabili sono vicine in memoria (si pensi ad un array dove ogni core legge e scrive ogni cella), e due core le leggono e scrivono, allora le due variabili vengono messe nella stessa linea di cache, e quindi se un core scrive su una variabile, l'altra variabile viene invalidata (questo perche il protocollo che garantisce la coerenza della cache, invalida l'intera linea di cache, non solo la variabile che è stata modificata), e quindi il core che legge la seconda variabile deve andare a leggerla in memoria, e non in cache.
In questo caso non si parla di Data race, ogni thread legge e scrive una variabile diversa, ma si ha un problema di prestazioni, in quanto si va a leggere in memoria e non in cache.
Ogni core invalida il successivo, e quindi si ha un effetto domino.

Per risolvere il problema si usa il data padding (lascio buchi nella struttura dati), al fine di garantire che le variabili siano in linee di cache diverse.
Il modo migliore di farlo è definire strutture che siano di dimensione un multiplo della dimensione della linea di cache. In questa struct ci metto una parte di dati e una parte di padding (spazio vuoto).

Un'altro modo è usare una grana computazionale, tipo due for annidati: uno scorre da blocchi di grana della stessa dimensione della linea di cache o multipli, e l'altro scorre all'interno gli elemnti all'interno della grana. Questo si traduce nell'assegnare al thread non una singola cosa da fare ma un po' di cose da fare.

Quello della grana è il miglior modo e quello più semplice per risolvere problemi di prestazioni.

Il codice va pensato in due fasi:

- ciò che succede dentro il core
- ciò che succede fra core

se ho mem distrubita sono 3:

- ciò che succede dentro il thread
- ciò che succede dentro il nodo
- ciò che succede fra nodi

poi rimane che fare fine tuning, se non va bene in termini di prestanzioni si aumenta la grana fino a raggiungere l'esecuzione simile al codice sequenziale.

# Lezione 10 (27/03)

## Sistemi di interconnessione

Collegano sistemi che siano distribuiti, o geograficamente o nello stesso edificio.

- nodi indipendenti (cpu, gpu, memoria)
- rete di interconnessione
- memoria sia indepndente sia condivisa

## Cos'è un interconnetion network

è una rete di nodi che permette di comunicare tra loro, è un insieme di nodi e collegamenti tra i nodi.
Due misure:

- latency: tempo che passa tra l'invio di un messaggio e la ricezione
  - noload: quando la rete è vuota
  - underload: quando la rete è utilizzata
- bandwidth: quanti bit al massimo posso trasmettere in una unità di tempo, (numero di messaggi per unità di clock)
- throughput: i bit attuali che posso trasmettere in una unità di tempo

Diversi aspetti influenzano le prestazioni:

- routing: come faccio a trovare il percorso migliore
- controllo di flusso: come i pacchetti da un punto e l'altro si muovono, quanti pacchetti posso inviare

Un semplice bus tra processore e memoria è una rete di interconnessione.

## Tempo invio messaggio:

T_m(k) = T_lat + k \* T_bw

- k: grandezza del messaggio
- T_lat: tempo di latenza
- T_bw: tempo di banda

T_lat invece di una costante dovrebbe essere una funzione, in quanto se la rete è vuota il tempo di latenza è minore rispetto a quando la rete è piena.

## Terminology

- Endpoint: sorgente o destinazione di un messaggio, può essere un nodo, uno switch, ecc...
  - gli endpoint possono anche essere solo di passaggio, fanno semplicemente un forwarding del messaggio senza coinvolgere il processore
- Link: collegamento tra due endpoint
- Switch: dispositivo che collega più link.

## Topologie

- Direct network: ogni nodo è collegato a un altro nodo
- Indirect network: ogni nodo è collegato a uno switch

## Diameter, degree, bisection bandwidth

- Degree: numero massimo di vicini che un nodo può avere
  - nei linear array è 2, una matrice bidimensionale è 4, tridimensionale è 6, k-dimensionale è 2k
- Diameter: lunghezza del percorso più lungo tra due nodi
  - nei linear array è n-1, nel bidimensionale è la radice quadrata di n
- Bisection bandwidth: numero minimo di link che devono essere rimossi per dividere la rete in due parti uguali. Importante perchè modella il collo di bottiglia della rete, se tutti devono scambiarsi i messaggi devono passare per questo punto. più è grande più è veloce la rete (soffre meno dell'aumento di latenza).
  - nei linear array è 1, nel bidimensionale è radice di n

## 2D Torus

Migliora il diametro e il bisection bandwidth. è una rete bidimensionale con collegamenti tra i nodi in modo toroidale.
c'è un problema, ci sono dei cavi più lunghi di altri, quindi il tempo di latenza non è costante.

n-ari k-cube: è una rete k-dimensionale in cui ogni nodo ha n vicini.
2D torus è una rete 4-ari 2-cube.

## Binary tree

Nodi sulle foglie e la struttura sovrastrante sono solo switch.

- diametro: log(n)
- degree: 3 constante
- bisection bandwidth: 1 (bottleneck), risolto dal fat tree

## hypercube

## Fat tree

migliora la bisection bandwidth, man mano che si sale si ha più banda disponibile.
Puo' essere implementata con più switch(fig 2/2), in modo da avere più banda disponibile.
k-ary n-fly
k + k/2 switch totali

# Lezione 11 (3/04)

## Dragonfly, caso multi-level

Più livelli, i grandi sistemi normalmente sono costruiti per livelli., per necessità fisiche.

## Modello lineare affine

t_0 + n \* s

## Computation to communication level

La comunicazione puo' essere sovrapposta al calcolo in alcuni casi:
(sovrapposizone: calcolare durante la comunicazione)

- il produttore lo abbia già prodotto ma il consumatore non ne abbia ancora bisogno.

Il tcp/ip solitamente non permette overlapping perchè fa chiamate al sistema operativo, quindi il sistema operativo deve essere coinvolto in ogni comunicazione, quindi calcolo e comunicazione avvengono in maniera sequenziale, se si vuole parallelizzare bisogna usare protocolli user space.

Invece di avere un buco dove il processore scrive sul buffer(dopo aver finito un calcolo) invece di fare le operazioni di calcolo, demando ad un altro processore la scrittura del buffer ovvero la comunicazione (infinyband, rdma, ecc...).

Il modo più semplice di organizzare un sistema per fare overlapping è quello di avere un buffer in entrata, un buffer per i calcoli e un buffer in uscita.

Il sistema va organizzato come una pipeline (una catena di montaggio) con stream di dati che scorrono in maniera sequenziale. Senza stream non posso fare overlapping.
Devo pensare all'algoritmo come se fosse una composizione di funzioni: g(h(f(x))) = g \* h \* f.

Ogni componente della pipeline ha un tempo di servizio Tf
Il tempo totale è T = tf1 + tf2 + tf3 + tf4 + tf5, la cosa migliore sarebbe quella di prendere il max quindi T = max(tf1, tf2, tf3, tf4, tf5), in questo caso per migliorare sarebbe meglio che i tempi siano il più possibile simili tra loro, tanto prendo sempre il max.

Se aggiungo la comunicazione ho intervalli tf1-tf2, tf2-tf3, tf3-tf4, tf4-tf5, tf5-tf6, il tempo totale è T = max(tf1, tf2-tf3, tf3-tf4, tf4-tf5, tf5), in questo caso il tempo di comunicazione è il tempo di servizio del componente successivo.
Posso trasformarlo in un problema parallelo, questo significa prende il max, ovviamente non posso farlo per lo stesso dato, per questo ho bisogno di buffer diversi. (guardare disegni su slide)

## Sync vs Async communication

- async degree: il numero di messaggi che il sendere puo' inviare prima che si debba bloccare per attendere la ricezione dal receiver

  - dipende fortemente dalla capacità del canale di comunicazione

- Sync communication: il sender si blocca finchè il receiver non ha ricevuto il messaggio, c'è contemporeaneità tra i due. (tree-way communication)

  - non trasmetto finche il receiver non è pronto
  - non ricevo finche il sender non è pronto

- Async communication: il sender non si blocca, invia il messaggio e continua a fare altro, il receiver riceve il messaggio quando è pronto.

  - bloccante: il sender si blocca finche il messaggio non è stato preso in carico dal sistema che si occupa di inviarlo, non necessariamente dal receiver. Quando ho consegnato il messaggio al Sistema operativo ad esempio posso riprendere a fare altro.
  - non bloccante: il sender invia il messaggio e continua a fare altro, il receiver riceve il messaggio quando è pronto. Il programmatore si occupa di gestire l'invio e la ricezione del messaggio.

# LEZIONE 12 (5/04)

## Metriche per misuarare le prestazioni

- speedup: quanto è veloce il programma rispetto ad un altro
- scalability: quanto è scalabile il programma, se raddoppio le risorse raddoppio le prestazioni?
  - strong scalability
  - weak scalability
- efficiency: quanto sono efficienti le risorse utilizzate

## Speedup

Misura definita come rapporto tra il tempo di esecuzione di un programma su un singolo processore e il tempo di esecuzione su più processori.
S(p) = T_1 / T_p

Quando più veloce faccio se sostuisco un calcolatore con due, con 4, con 8, ecc... processori.
In generale si pensa che se uso 8 calcolatori devo fare 8 volte più veloce, ma non è così, in quanto c'è un overhead di comunicazione, e quindi non posso fare 8 volte più veloce, ma meno.

Questa metrica è pensata per hardware uniformi, non ha senso calcolare lo speedup di un programma su cpu rispetto a una gpu. La misura riguarda più che altro in numero di processori e non il tipo di processori.
Su sistemi eterogenei è meglio chiamarlo benchmark.

Lo speedup è lineare quando lo spedup massimo con p processori è p (s(P) = p)

## Efficienza

Definita come il rapporto tra lo speedup e il numero di processori.
E = S(p) / p
può essere riscritta come:
E = T_1 / (p \* T_p)
dove T_p é p è il costo della parellizzazione.

Il caso ideale è quando l'efficienza è 1, in quanto significa che il costo della parallelizzazione è nullo. (quindi quando S(p) = p)

## Scalability vs Speedup

La differenza è che per lo speedup non è detto che i due algorithmi siano equivalenti, mentre per la scalabilità si.
Lo speedup considera la migliore versione sequenziale dell'algoritmo.

Scalability= T_par(1) / T_par(p)
Speedup = T_seq / T_par(p)

## Strong vs Weak scalability (stumenti di riferimento per il calcolo delle prestazioni)

Si parla di speedup:

- Strong scaling: la dimensione del problema è fissato; sto testando due algoritmi sullo stesso problema
  - Generalmente parallelizzare significa spesso dividere il problema
  - Nello strong scaling, visto che la dimensione rimane fissa, ogni processore lavora su un problema via via più piccolo all'aumentare di p, ad un certo punto il problema diventa troppo piccolo che non è più efficiente lavorarci sopra.
  - Si concentra nel risolvere il problema con più risorse (più velocemente).
- Weak scaling: al variare del numero di processori, varia anche la dimensione del problema
  - A volte parallelizzare significa risolvere problemi più grandi (o con maggior precisione), non necessariamente risolverli più velocemente.
  - Misura la capacità di un sistema di risolvere nello stesso tempo un problema più grande.
  - Ho un macchina grande p e ci metto T, il problema è se riesco a risolvere un problema grande il doppio con una macchina grande il doppio.
  - Si assume che la quantità di lavoro per processore rimanga costante (se radddoppio il numero di processori raddoppio anche il vettore).
  - Si concentra nel risolvere problemi più grandi(a parità di tempo o migliorandolo).

Nel progetto ricordarsi di aggingere grafici riguradanti strong e weak scaling. ([Paper progetti fatti da loro](https://www.researchgate.net/publication/352352041_Practical_Parallelization_of_Scientific_Applications_with_OpenMP_OpenACC_and_MPI/link/60dde8c5a6fdccb745fb9bcc/download?_tp=eyJjb250ZXh0Ijp7ImZpcnN0UGFnZSI6InB1YmxpY2F0aW9uIiwicGFnZSI6InB1YmxpY2F0aW9uIn19))

## Computation to communication ratio

La cosa che distingue un problema parallelo da uno sequenziale è principalmente il costo per la comunicazione, le operazioni rimangono pressochè le stesse.

Un modo per valutare la bontà di un algoritmo parallelo è il computation to communication ratio, ovvero il rapporto tra il tempo di calcolo e il tempo di comunicazione.
Infatti se il calcolo è poco non ci si può aspettare che il parallelismo sia migliore rispetto a quello sequenziale.

## Super linear speedup

Cioè che sta sopra il lineare, in generale se esistesse significherebbe che potrei costrurire un algo sequenziale migliore che non ha questo comportamento.

In realtà potrebbe capitare per diversi motivi:

- caching: più processori significa più divisione dei dati, quindi i dati sono più piccoli e ne stanno di più in cache, quindi va più veloce

## Amdahl's law, su strong scaling

é un modo di valutare un upper bound per lo speedup, ovvero il massimo speedup che posso ottenere.
è più accurato rispetto a quanto fatto fin'ora ovvero ritenerlo lineare.

Supponiamo di avere un codice che in alcune parti è seriale e in altre parallelo.

Casi in cui ho comportamento seriale:

- Seriale multicomputer: ad esempio lettura dei dati dal file system, gli altri nodi aspettano
- Seriale multiprocessor: leggo il testo e lo divido in parole (Sequenziale, tokenizer), poi ogni processore conta le parole
- Chiamate al SO: ad esempio per la comunicazione tra i processori
- Sto usando l'interprete python

Il tempo è dunque composto da due parti:

- T_ser: tempo seriale
- T_par: tempo parallelo

Assumendo che il miglior speedup che posso ottenere sia lineare (Se ho p processori e il mio tempo è x allora ci metto x/p), allora
T(p) >= T_ser + (T_par / p)

Guardare slide per altre formule

Supponiamo di avere un codice che ci mette 10, la metà è sequenziale l'altra è parallela.
Suppenonendo di avere infiniti processori, il tempo si riduce a 5, in quanto la parte parallela si riduce a 0.
Lo speedup è 2, in quanto 10/5 = 2

Quindi con infiniti processori non riesco comunque a fare meglio di 2.

## Gustafson's law, su weak scaling

Vorrei mantenere costante il tempo di esecuzione sul singolo processore, aumentatando le cose da fare e il numero di processori.
Guardare slide.

# LEZIONE 13 (12/04)

## Modelli astratti di computazione: PRAM

Servono a capire come si comporta un algoritmo in parallelo su una architecture astratta parallela.

## PRAM

Parallel Random Access Machine:

- no cache
- no Numa(Non Uniform Memory Access): cioè UMA, ovvero ogni processore ha un tempo di accesso alla memoria uguale (uniforme, costa lo stesso tempo)
- no overhead di sincronizzazione: la sincronizzazione costa 0

La comunicazione tra processori avviene tramite i meccanismi della memoria condivisa.

I processori operano in lock-step: ogni processore esegue la stessa istruzione nello stesso istante, sono tutti sincroni, fanno tutti la stessa cosa contemporaneamente.
Impossibile da realizzare in pratica, ma è un modello astratto.

Gli studi degli algo su questo sistema determinano perlomeno un lower bound per la velocità di un algoritmo parallelo, su un sistema reale non avrò mai una velocità maggiore di quella determinata da questo modello.

Guardare slide per le fasi di un istruction cycle.

## BSP (Bulk Synchronous Parallel)

Oltre che un modello potrebbe essere un paradigma di programmazione parallela.

Consiste di tre parti:

- colleziono dati dalla memoria
- scambio messaggi con altri processori(point to point)
- sincronizzo tutti processori tramite un barriel

Nel PRAM, la sincronizzazione avveniva istruzione per istruzione, qui avviene a blocchi.

Nel PRAM si assume una memoria condivisa, qui no, ogni processore ha la sua memoria e attraverso una rete di comunicazione si scambiano messaggi.
Si assume che accedere alla memoria "remota" (degli altri processori) abbia un tempo uniforme.

Gli algoritmi si dividono in superstep, ogni processore può finire il suo superstep in tempi diversi, ma non può iniziare il successivo finchè tutti gli altri non hanno finito il loro.
Si dividono in fasi:

- calcolo
  - sincronizzazione
- comunicazione
  - sincronizzazione
- calcolo (si ripete)

# LEZIONE 14 12/04

Ricordiamo che il c non supporta la programmazione parallela, quindi bisogna usare delle librerie o delle direttive per farlo.
Si possono usare i pthead, ma non sono parte del linguaggio, l'idea è quindi di estendere linguaggi sequenziali per fare programmazione parallela.

## OpenMP

Open multi Processing, libreria di programmazione shared memory, permette di scrivere programmi paralleli in maniera semplice.
Estende dei linguaggi sequenzali come C, C++, Fortran, ecc...

Si basa sull'idea di direttiva, una direttiva o pragma è una istruzione che dice al compilatore di fare qualcosa di diverso rispetto a quello che farebbe normalmente.
Possono essere liberamente ignorate dal compilatore nel caso non le riconosca.

Ci sono anche funzioni, in quanto ho bisogno di informazioni a livello di runtime, come ad esempio il numero di thread.
La direttiva è invece interpreata a livello di compilazione.

Ha anche delle variabile di ambiente, settata dalla shell e lette a runtime.

è pensato per il parallellismo a memoria condiviso, intra-node. Si è provato a estenderlo per distrubited memory, ma non è stato molto efficace.
Programma ciò che avviene nel nodo.

Nasce come libreria per parallelizzare loop, si concentra sul come trasformare un programma sequenziale in parallelo.

Normalmente lavora su un thread pool, ovvero un insieme di thread che vengono creati all'inizio e poi riutilizzati, anche se c'è la possibilità di creare e distruggere thread dinamicamente.

## Sequential equivalance

OpenMp deve garantire che il programma parallelo abbia lo stesso comportamento del programma sequenziale.
Garantisce un comportamente parallelo incrementale, ovvero permette di specificare il grado di parallelismo.
Se dico di andare con un thread solo allora esso garantisce che si comporti come il programma sequenziale.
Stessa cosa se lo compilo senza il flag di parallelizzazione (-fopenmp).

Di default il numero di thread è 1, se non specificato.

## Fork-join model

OpenMp si basa sul modello dei pthread, fornendo una libreria più ad alto livello.

Il programma parte con un master thread, è sequenziale finchè non trova una direttiva di parallelizzazione,
a quel punto si divide in più thread per una regione parallela, alla fine ho normalmente una barrier(sincronzizazzione)

In generale questo è lo schema:

- una parte sequenziale
- una parte parallela
- una barrier per la sincronizzazione (è di default ma può essere tolta)

Si comporta quindi come il modello astratto BSP.

Master thread -> fork -> parallel region -> join (barrier) -> master thread
il master thread rappresenta la parte sequenziale, mentre i thread paralleli rappresentano la parte parallela.

## Relaxed consistency

Thread in parallelo accedono alla memoria in Relaxed consistency (variante del weak-ordering) in cui sia non viene garantito un ordinamento tra load e store, l'unico modo è usare una memory barrier.
se ho due thread, uno scrivo e l'altro legge, anche se la lettura avviene dopo, non ho garanzie che la lettura legga il valore scritto, a meno che non metta una memory barrier in mezzo.
Dovrei rompere il super step e andare a leggere nel super step successivo.

Ogni thread ha una sua vista temporanea sulla memoria.

## Memory barrier

Memory barrier si ottiene attraverso una flush. Garantisce che il valore scrittto veramente arriverà in memoria.
e dopo una flush in thread leggerà veramente il valore scritto.
Se ho più thread che scrivono, non ho ci serve a niente la flush, non garantisce l'ordine tra le scritture.
Constringe la cache a essere scritta in memoria, comportando un costo in termini di prestazioni.
La flush è implicita alla fine di una regione parallela, durante la sincronizzazione.
In realtà lock e memory barrier sono concetti diversi:

- lock: sceglie un thread che può accedere alla risorsa
- memory barrier: committo le scritture in memoria

nel caso di Intel le due operazioni avvengono insieme. Per Arm non è così, e quindi bisogna fare attenzione.

## Variabili condivise

Una variabile definita nel blocco sequenziale diventa condivisa nel blocco parallelo.
Posso però definirla privata, questo significa che ogni thread ha una sua copia della variabile.
Inoltre posso devinirla firstprivate, ovvero ogni thread ha una copia della variabile inizializzata con il valore della variabile nel blocco sequenziale.
Oppure lastprivate, ovvero ogni thread ha una copia della variabile inizializzata con l'ultimo valore della variabile nel blocco parallelo(?).

## Direttive

```c
#pragma omp parallel num_threads(4)
{
  // codice parallelo eseguito da 4 thread, di default il numero di thread è il numero di core
}
```

(altri esempi su slide)

# LEZIONE 15 19/04

## Design pattern per architetture parallele

- control parallel:

  - mi faccio guidare dal flusso di esecuzione
  - task, stream parallelism:
  - task: funzione con dei dati in input e dei dati in output, rispetto ad una fuznione normale cambia che qua vengono dichiarati anche i dati in output. Inoltre i task non possono vedere i dati globali come ad esempio possono fare le funzioni normali. Vengono chiamate funzioni senza stato. E non possono connetersi con nulla che abbia uno stato, tipo un db o un file.
  - stream: nel caso del task sto definendo una funzione da eseguire, nel caso dello stream sto definendo degli esecutori. Ho una sequenza di input e output, una pipeline di esecutori con un flusso di dati che scorre tra di loro.

- data parallel:

  - mi faccio guidare dalla struttura dei dati
  - ho dei dati iniziali e penso ad un tipo di parallelismo che tende a dividere i dati in parti uguali e a fare operazioni su queste parti, sottoinsieme di input indipendenti.
  - Ogni processo lavora ad esempio su un sottoarray di un array, e poi alla fine aggrego i risultati.
  - Il modo di fare parallelismo è di **partizionare i dati**
  - Un errore è pensare di dividire l'input, l'input
  - Operazioni di data parallel:
    - map: applico una funzione a tutti gli elementi di un array
    - reduce: aggrego i risultati
    - stence: applico una funzione a tutti gli elementi di un array, ma ogni elemento dipende dai suoi vicini. Esempio media dei vicini.
  - Esempi:
    - big data
    - Dnn/gen ai
    - GPU

  ## OPENMP

  Per adesso ci siamo concentrati sul data parallel, andando a parallellizzare i loop.
  Adesso ci concentriamo sul task parallel che in openMP si realizzano con le Sections.

  ### Sections

```c
#pragma omp parallel
{
  #pragma omp sections
  {
    #pragma omp section
    {
      task1();
    }
    #pragma omp section
    {
      task2();
    }
  } // implicit barrier
} // implicit barrier
```

Ogni section è eseguita da un thread, differenti section possono essere eseguite da differenti thread. Dico possono perchè non è garantito, potrei avere un solo thread e quindi le section vengono eseguite sequenzialmente.

Alla fine della direttiva "sections" c'è una barrier.

### Primitive di sincronizzazione

- barrier: aspetta che tutti i thread abbiano raggiunto un punto
- single: (come sections, ma con una sola section) assegna un blocco di codice a un solo thread, il primo che arriva, gli altri lo skippano, ma aspettano per via di una barrier implicita alla fine del bloccato
- master: assegna solo al master(thread con id 0), non c'è barrier implicita alla fine
- critical: Tutti i thread eseguono il blocco, ma uno alla volta, gli altri aspettano
- ordered: nei loop assicura non ci sia data race tra dipendenze.
- atomic: operazioni atomiche, non possono essere interrotte da altri thread

### Task

Ci sono anche i task, che non sono nient'altro che una evoluzione delle section, in quanto posso fare cose più complesse in maniera più flessibile.
Ho una coda di cose da fare e un pool di thread che le esegue.
(meglio usare i task invece che le sections)

```c
#pragma omp parallel
{
  #pragma omp single
  {
    #pragma omp task
    {
      task1();
    }
    #pragma omp task
    {
      task2();
    }
  } // implicit barrier
} // implicit barrier
```

Guardare esempi su slide

# Lezione 16 (24/04)

## User level message passing programming

Perchè user level?
La rete è interamnte controllata dal sistema operativo.
In geneare il sistema operativo impedisce la scrittura diretta sui dispositivi hardware, appunto perchè la funzione del sistema operativo è quella di gestire le risorse hardware.
è una libreria che permette di scrivere librerie di comunicazione senza dover invocare per forza il sistema operativo. Puo' pero capitare di usare delle syscall per fare delle operazioni di basso livello. Però questo non è non scritto esplicitamente nel programma, magari succede all'interno della libreria.
Due modi di scrivere un programma con queste premesse:

- MPDM: Multiple Program Multiple Data
  - diverse macchine -> diverse programmi per ogni macchina
  - è come se avessi una architettura a microservizi
  - non funziona bene se ho tanti processi, devo scrivere un programma per ognuno di questi processi
- SPMD: Single Program Multiple Data
  - Un solo sorgente, compilato una volta sola e poi eseguito su tutte le macchine in copia.
  - Gli viene passato un identificativo al momento dell'esecuzione per capire quale copia è.
  - In funzione di questo identificativo il programma può fare operazioni diverse.
  - bisogna sfruttare bene l'allocazione dinamica in maniera da non avere problemi di memoria.

Ogni processo ha uno spazio logico di indirizzamento ma ha anche uno spazio kernel logico di indirizzamento.
Per spazio Kernel si intende la memoria che il sistema operativo può vedere, mentre per spazio logico si intende la memoria che il processo può vedere.
Quando avviene una write su un socket il messaggio viene copiato nello spazio kernel, e poi viene copiato nel buffer del socket.

## MPI

Concetti base:

- crezione di processi: indipendente dalla implementazione e dal sistema operativo
- comunicazione: invio e ricezione di messaggi
- MPI_Init:

  - inizializza l'ambiente MPI, crea una rete di comunicazione tra i processi, permette di manetene una comunicazione stabile tra i processi.
  - MPI assume di avere un trasporto sicuro sotto, se invio un messaggio l'assunzione è che arrivi. Questo avviene attraverso un circuito virtuale, un canale di comunicazione tra i processi.
  - Aspetta che tutti i processi siano pronti a comunicare.

- MPI_Finalize: termina l'ambiente MPI

  - La terminazione è un punto critico, richiede algoritmi specifici per essere fatta, consiste in:
    - far uscire i processi garantendo che siano arrivati tutti alla fine
    - garantire che non ci siano messaggi in sospeso alla fine

## tassonomie di comunicazione

- Quanti:
  - Simmetrica: point-to-point 1:1
  - Asimmetrica o collettiva: 1:n, puo' avvenire tramite un comunicatore, un gruppo di processi che comunicano tra loro.
    - In MpI vengono chiamate **operazioni** collettive, perchè spesso comportano fare un calcolo ad esempio la reduce.
    - Per questo per alcuni MPI è un modello di comunicazione e per altri è un modello di programmazione che mischia calcolo e comunicazione.
- Temporizzazione:
  - sincrona: il processo che invia si blocca finche il processo che riceve non ha ricevuto il messaggio
  - asincrono:
    - bloccante:
      - processo che invia si blocca finche il messaggio non è stato preso in carico dal sistema che si occupa di inviarlo, non necessariamente dal receiver. Quando ho consegnato il messaggio al Sistema operativo ad esempio posso riprendere a fare altro.
      - processo che riceve legge dal buffer, se è vuioto si blocca finche non arriva il messaggio
    - non bloccato: il sender invia il messaggio e continua a fare altro, il receiver riceve il messaggio quando è pronto. Il programmatore si occupa di gestire l'invio e la ricezione del messaggio.

# Leazione 17 (03/05)

# Lezione 19 (15/05)

(Slide X-Message-Passing, guardare esempi di codice)

- MPI_Datatype: permette di creare un nuovo tipo di dato.
  - MPI_Type_contiguous: crea un tipo di dato composto da più elementi dello stesso tipo
  - MPI_Type_commit: registra il tipo di dato
- MPI_Send(buffer, count, datatype, dest, tag, comm): bloccante, invia un messaggio
  - buffer: buffer di dati
  - count: numero di elementi di tipo datatype
  - datatype: tipo di dato, pressuppone che la rappresentazione tra diverse macchine sia la stessa
- MPI_Recv(buffer, count, datatype, source, tag, comm, status): bloccante, riceve un messaggio
  - buffer: buffer di dati
  - count: numero di elementi di tipo datatype
  - datatype: tipo di dato, pressuppone che la rappresentazione tra diverse macchine sia la stessa
  - source: mittente
  - tag: tag del messaggio
  - comm: comunicatore
  - status: struct di tipo MPI_Status, contiene informazioni sul messaggio ricevuto
    - MPI_Isend(...) e MPI_Irecv(...): non bloccanti
  - permettono di inviare e ricevere messaggi in maniera asincrona
  - hanno un parametro in più cioè un puntatore a una variabile di tipo MPI_Request che permette di controllare lo stato dell'operazione
  - MPI_Wait: blocca il processo fino a che il messaggio non è stato inviato o ricevuto
  - MPI_Test: controlla se il messaggio è stato inviato o ricevuto

La MPI_Isend è conveniente in quanto la copia dalla memoria principale alla memoria della scheda di rete puo' consumare tanto tempo nel quale il processore puo' andare avanti con l'esecuzione delle istruzioni del programma.
Se la copia è comunque a carico del processore principale allora non si avrà nessun vantaggio, si eseguiranno le operazioni in sequenza con in più l'overhead del contest switch.
Se non la fa il processore principale dovrebbe farla il processore della scheda di rete, questo dipende dalla scheda di rete.
Quindi in funzion della scheda di rete la Isend e la Irecv potrebbe essere peggio di usare la send e la recv bloccanti.

## Send Communication Modes

Oltre alla distinzioni tra Simmetrico e Asimmetrico, Sincrono e Asincrono, ci sono altre distinzioni:

- Standard Mode Send
- Buffered Mode: noi prorgammatori ci prendiamo carico di gestire la memoria del canale (buffer_attach)
- Synchronous Mode: Send e receive possono partire una dopo l'altra ma possono solo completare insieme
- Ready Mode: Send che funziona solo se la receive è già in attesa

Alcune combinazione hanno davvero poco senso.

## Collective communication

Comunicazione non più 1:1 ma 1:n, n:1, n:n.
Guardare esempi su slide.

Esempio:
tutti i processi hanno un array data da 10.
Partendo da un root process, quello con rank 0, crea un buf grande n*proc * 10 \_ sizeof(int) e lo riempie con i dati di tutti gli array.
MPI_Gather(data, 10, MPI_INT, buf, 10, MPI_INT, 0, MPI_COMM_WORLD);
cioè prende i dati di tutti i processi e li mette in un unico array.

- MPI_Wtime: restituisce il tempo in secondi
- MPI_Ibarrier: bloccante, aspetta che tutti i processi abbiano raggiunto il barrier, è necessario sapere quanti siano i processi. Non funziona in un mondo dinamico dove i processi vengono creati e distrutti dinamicamente.

## New MPI-2 Features

One-Sided Communication: permette di scrivere e leggere direttamente nella memoria di un altro processo senza che esso debba fare nulla.
Se la scheda di rete lo permette il processore principale, anche in questo caso, non deve fare nulla.
Con Mpi-1 potrei implementare questo funzionalità con ad esempio un thread dedicato alla ricezione dei messaggi, ma è molto più complicato.

# Lezione 20 (22/05)

## Lezione di Filippo (NVIDIA) sulle GPU

## GPU

Sfruttano tanto il parallelismo, tanti thread che fanno la stessa cosa su dati diversi.
Hanno tanti core, sui 512 core in un singolo chip.

## ARCHITETTURA

Si parte sempre dalla CPU, poi il processore decide se far eseguire il codice sulla GPU.
Tutto parte dalla CPU, per natura queste componenti eseguono in maniera asincrona:

- spostare i dati dalla CPU alla GPU
- La CPU dice alla GPU di eseguire questo codice
- La CPU puo' controllare se il lavoro è stato fatto
- Una volta finito vanno ricopiati i dati dalla GPU alla CPU

## CUDA

Estensione di C++ per scrivere programmi per GPU.
Permette di creare griglie di thread, ognuno di questi organizzati a blocchi. Quindi una griglia di blocchi.
La GPU è organizzata in streaming multiprocessor, ogni streaming multiprocessor ha un certo numero di core e una area di memoria condivisa per i thread. Tutti leggono la memoria della GPU, ma la shared memory è condivisa solo tra i thread di uno stesso blocco.

```

```
