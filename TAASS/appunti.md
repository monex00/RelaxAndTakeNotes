# Software architecture overview

## Evoluzione client server

**Enterprise application**: applicazioni che supportano i processi aziendali (solitamente per grandi aziende)

- Passaggio da Host solution a Mini solution a Client Server:
  - **Host solution**: un unico computer che fa tutto (es. mainframe con telescrivente o scheda perforata per l'interazione con l'utente)
  - **Mini solution**: un computer che fa tutto (es. mainframe con terminale)

**End User** : utente finale

- Da stand alone pc a pc networking a client server
  - **Stand alone pc**: un pc che fa tutto, applicazioni scaricate in locale
  - **Pc networking**: più pc collegati in rete

**Client server**: un server che fa da intermediario tra più client

## Componenti

3-tier architecture:

- **Presentation tier**: interfaccia utente
- **Business logic tier**: elaborazione dati
- **Data tier**: memorizzazione dati

SERVER - NETWORK - CLIENT

## Classificazione soluzioni client/server

- **TimeSharing**: un server che fa tutto, come i legacy system (legacy system: sistema informatico obsoleto)
  -Server: Data, logic, presentation
  -Client: Un terminale con singola finestra
- **Client presentation**:
  -Server: Data, logic
  -Client: Presentation, terminale con più finestre (x-terminal)
- **Distibuited application**:
  -Server: Data, Logic
  -Client: Logic, presentation
- **Central database**:
  -Server: Data
  -Client: Logic, presentation
- **Distriubited database**: parte dei dati anche sul client (es. Cellulari)
  -Server: Data
  -Client: Data, Logic, presentation

## Central database

Caratteristiche:

- Two phase commit: garantisce che i dati siano consistenti
- Standards: SQL, ODBC, JDBC

Vantaggi:

- Alta produttivita dei linguaggi 4GL (4Gl = linguaggi di programmazione di alto livello)
- Buona standardizzazione

Limiti:

- Scalabilità
- Solo E-R model

## Fat client

il client ha tutto il necessario per funzionare (applicazione driver e protocolli), il server è solo un database

Problemi:

- Per accedere ad un dato devo necessariamente fare uso della rete, pregiudicando le prestazioni
- Uso delle risorse del client
- Difficile scalabilità, c'è un bottleneck sui dati
  - Scalabilità: capacità di un sistema di crescere in modo lineare con l'aumento delle risorse
- Manutenzione costosa
- Accesso ai dati poco protetto, il client accede direttamente ai dati

## Miglioramenti al modello database server

### Stored procedure

Le stored procedure sono codice SQL che viene eseguito sul server, il client invia solo la richiesta e il server esegue la procedura e invia il risultato.

Il problema è che non sono portabili perchè dipendono dal DBMS.

### Replicazioni asincrone

Sistemi organizzati tramite un database primario e uno o più secondari, i dati vengono replicati in modo asincrono e poi sincronizzati periodicamente.

## Sistemi etereogenei

Sistemi composti da diversi SO e da componenti sviluppati con diversi linguaggi di programmazione.

# Middleware

Anche chiamati "software glue", sono software che permettono la comunicazione tra applicazioni diverse. Offrono funzionalità che non sono presenti nei sistemi operativi ma che sarebbe troppo costoso implementare in ogni applicazione.

**_Software di sistema che permette l'interazione a livello applicativo fra programmi in ambiente distribuito"_**

Forniscono soluzioni al problema di collegare nuove applicazioni con i vecchi legacy system.

## Tipi di middleware

- **TP-Monitor**
- **Message Oriented Middleware**
- **Publish/Subscribe Middleware**
- **Object Request Broker**
- **Object Transaction monitor**

## TP-Monitor (Online Transaction Processing)

Caratteristiche: - proprietà ACID (Atomicity, Consistency, Isolation, Durability) delle tx - sincronizzazione tramite la Two Phase Commit - Load balancing: distribuzione del carico di lavoro tra i server - Gestione pool di risorse

Vantaggi:

- Scalabilità e tuning per grandi sistemi
- adatti ad applicazioni **mission critical**
  - **mission critical**: applicazioni il cui malfunzionamento può causare danni economici o di altro tipo

Limiti:

- pochi standard
- pochi linguaggi di programmazione solo 4GL

## Principali servizi di un TP-Monitor

In caso di sovraccarico i TP-Monitor possono allocare e duplicare i servizi di un'applicazione su più macchine fisiche diverse.

Possono poi effettuare il bilanciamento del carico (**load balancing**) per distribuire il carico di lavoro tra le macchine fisiche equivalenti, senza che l'utente se ne accorga.

Inoltre possono gestiore la **high availability** ovvero la disponibilità del servizio, garantendo che il servizio sia sempre disponibile tirando su un'altra macchina in caso di guasto.

Il load balancing porta con se problemi di **sincronizzazione**, dovendo gestire dati su più macchine diverse.

I principali servizi sono:

- Gestione dei processi del server:
  - Attivazione
  - funneling: fare da imbuto per le richieste in arrivo
  - monitoraggio
  - bilanciamento del carico
- Gestione delle transazioni
- Gestione della comunicazione client-server

## Two Phase Commit

protocollo che consente la gestione delle transazioni in ambiente distribuito, avviene in due passi:

1. **Prepare**: il coordinatore chiede ai partecipanti se sono pronti a fare il commit mandando un messaggio di prepare.
2. **Commit**: se tutti i partecipanti rispondono positivamente, il coordinatore manda un messaggio di commit, altrimenti se qualcuno risponde negativamente o non risponde viene mandato un messaggio di rollback.

## Funneling

Il funneling è un meccanismo che permette di gestire le richieste in arrivo in modo da non sovraccaricare il server. Il Tp-monitor gestisce una coda di richieste in arrivo e le smista in modo da non sovraccaricare il server.
