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

le cache sfrutta la proprità di località del codice:

- **località spaziale** : se accedo a un dato, è probabile che acceda a dati vicini
- **località temporale** : se accedo a un dato, è probabile che ci riacceda presto

I cicli for e gli array sfruttano bene questo principio di località se scritti nell'ordine giusto

RAM, non accedo a caso alla memoria, ma random significa che posso accedere in qualsiasi ordine, ovviamente il costo non è uguale per tutti i tipi di accesso.

Usando il for suggeriamo al compilatore che stiamo accedendo in modo sequenziale, il compilatore vuole sapere qual'è la probabilità di accedere a i + 1 dopo aver acceduto a i, se è alta allora il compilatore può fare prefetching, ovvero caricare in anticipo i dati in cache.

I break possono influenzare negativamente il prefetching, il compilatore non sa se uscirò dal ciclo o no, quindi non può fare prefetching.

Questo è il motivo per cui esistono 3 costrutti per fare cicli. Ognuno di essi ha una motivazione diversa.

Nel programmi paralleli l'ottimizzazione del compilatore protrebbe dare risultati diversi, in quanto otimizza come se fosse un programma sequenziale.

Una regola pratica per decidere quale for parallelizzare è parallelizzare il for più esterno, in quanto è quello più grosso e quello che ci mette più tempo. Mentre quello interno è più piccolo e viene eseguito più volte, ma ha un costo minore.

- **Esterno** : 4096 task in parralelo con tempo 2 alla 24 t
  - quindi poche cose grosse in parallelo
- **Interno**: 2 alla 24 task in parallelo con tempo 1 t
  - quindi tante cose piccole in parallelo

Molto spesso basta quindi parallelizzare il for più esterno.

Se ho un algortimo sequenziale, lo parallelizzo su n core, non posso aspettarmi di ottenere un speedup di n, il risultato sarà sempre minore o uguale a n.

## multicore cache hierarchy

- **LLC (L3) cache** : condivisa tra tutti i core, non per forza un pezzo unico, ma condivisa
- **L2 cache** : condivisa tra due core
- **L1 cache** : cache dedicata a ogni core

Un altro livello di pararrellismo è quello di usare il calcolo vettoriale all'interno di un core, ovvero fare più operazioni in parallelo all'interno di un core.
Anche chiamato multi-media extension (SSE, AVX, ecc), chiamato così perchè inizialmente era stato pensato per fare operazioni su immagini e video. (encoding, decoding, ecc) usano un processore dedicato vettoriale.
Può essere usato anche per oltre operazioni. A livello di codice devo andare a usare le istruzioni del processore specifico per il tipo di processore che sto usando.
Per questo viene usato per operazione specifiche e non per tutto il codice.
Viene usato da pythorch, tensorflow, ecc.

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
  - Più flussi di istruzioni operano su un singolo flusso di dati, non molto usato, non chiaro come possa essere usato
- **MIMD** : Multiple Instruction Multiple Data
  - Più flussi di istruzioni operano su più flussi di dati, macchina parallela
  - ogni core esegue un flusso di istruzioni indipendente
