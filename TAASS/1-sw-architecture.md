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
  - Scalabilità: capacità di un sistema di aumentare o diminuire di scala in funzione delle necessità e disponibilità. (scalabilità di carico)
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
