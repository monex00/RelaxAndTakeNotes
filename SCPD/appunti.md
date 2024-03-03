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

La RAM consente accessi in qualsiasi ordine, ma non tutti gli accessi hanno lo stesso costo. Cicli sequenziali, come quelli creati con l'istruzione `for`, suggeriscono al compilatore un accesso sequenziale ai dati, permettendo tecniche di prefetching, ovvero il caricamento anticipato dei dati in cache basato sulla predizione degli accessi futuri.

Le interruzioni anticipate dei cicli (`break`) possono complicare il prefetching, poiché il compilatore non può prevedere con certezza l'uscita anticipata dal ciclo.

## Parallelismo nei Cicli

Nel programmi paralleli l'ottimizzazione del compilatore protrebbe dare risultati diversi, in quanto otimizza come se fosse un programma sequenziale.

Nel contesto del parallelismo, la scelta di quale ciclo parallelizzare è critica. Generalmente, è preferibile parallelizzare il ciclo più esterno per massimizzare l'efficienza, dato che comporta l'esecuzione parallela di compiti maggiori rispetto ai cicli interni, che sono più granulari e numerosi ma con un costo inferiore per iterazione.

- **Ciclo Esterno** : esecuzione parallela di task più grandi, con tempi più lunghi ma minor frequenza.
- **Ciclo Interno** : esecuzione parallela di numerosi task più piccoli, con minor tempo di esecuzione ma alta frequenza.

Parallelizzare un algoritmo sequenziale su n core non garantisce un
miglioramento proporzionale delle prestazioni (speedup di n), ma si
ottiene sempre un risultato minore o uguale a n a causa dell'overhead della gestione del parallelismo.

## Gerarchia della Cache nei Sistemi Multicore

- **LLC (L3) cache** : condivisa tra tutti i core, non per forza un pezzo unico, ma condivisa.
- **L2 cache** : Specifica per coppie di core, facilita un accesso più rapido rispetto all'LLC per quei core.
- **L1 cache** : Dedicata a ciascun core, offre la latenza più bassa per l'accesso ai dati.

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
- **MISD** : Multiple Instruction Single Data
  - Più flussi di istruzioni operano su un singolo flusso di dati, rarità nell'implementazione pratica.
- **MIMD** : Multiple Instruction Multiple Data
  - Il modello più flessibile e comune nelle architetture parallele, con più core che eseguono flussi di istruzioni indipendenti su flussi di dati distinti.
