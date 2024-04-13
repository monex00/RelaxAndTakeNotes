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

# Altri tipi di middleware

# Object Request Broker e standard CORBA

Obbiettivo: far comunincare oggetti software scritti in linguaggi diversi distrubuiti su macchine diverse.
I linguaggi devono essere tuttavia compatibili con il modello di oggetti.

Questo avviene tramite l'uso di interfacce: IDL (Interface Definition Language) che definisce in linguaggio comune al fine di permettere l'invocazione di metodi di oggetti remoti.

è struttrato in 3 parti:

- **client**: contiene L'idl stub che permette di invocare i metodi remoti e il DII (Dynamic Invocation Interface) che permette di invocare metodi non conosciuti a priori.

  - stub: codice generato dal compilatore IDL che permette di invocare i metodi remoti.
  - **Interface repository**: contiene le informazioni sulle interfacce e sui metodi.

- **ORB interface**: IDL compiler che genera il codice per il client e il server, si occupa di gestire la comunicazione tra i due, solitamente in maniera sincrona.

  - **IDL compiler**: genera il codice per il client e il server.

- **Object (Servant)**: contiene il codice che implementa i metodi invocati dal client.

  - **Implementation repository**: contiene le informazioni sulle implementazioni.

## Naming Service

Corba Naming Service è un servizio che permette di associare un nome ad un oggetto remoto, in modo da poterlo richiamare tramite il suo nome senza dover conoscere l'indirizzo.
Se l'indirizzo cambia in fututo il codice client non deve essere modificato.

Avviene attraverso la comunicazione di diverse componenti:

- **client**: chi richiede il servizio
- **client proxy**: rappresenta il client, chiede al broker l'indirizzo del server e manda la richiesta dopo aver fatto serializzazione (marshalling)
- **broker**: fa da intermediario tra client e server, è l'unico oggetto che deve essere aggiornato in caso di cambiamento dell'indirizzo del server
- **server proxy**: rappresenta il server, riceve la richiesta dal broker e la inoltra al server dopo aver fatto deserializzazione (unmarshalling)
- **server**: chi fornisce il servizio

## IDL

## Corba e internet

## Corba services

- Naming
- Event notification
- Persistence
- Transaction

# Message Oriented Middleware

è un middleware che permette la comunicazione tra applicazioni tramite messaggi, in modo asincrono.

- consegna garantita (fire and forget): il mittente manda il messaggio e non si preoccupa di cosa succede dopo, il ricevente riceve il messaggio tramite listener su una coda.
- disaccoppiamento mitteente/ricevente: il mittente non deve conoscere il ricevente e viceversa.

## Integrità referenziale tramite Message Oriented Middleware

Si cerca di mantere l'integrità referenziale tra i dati tra due db distribuiti attraverso l'uso di una coda su cui notifcare eventuali cambiamenti (inserimenti, cancellazioni, aggiornamenti) in modo che i db siano sempre sincronizzati.

## Pattern fire and forget

- client
- local queue via message api
- forward
- remote queue
- server

## Publish/Subscribe Middleware

- trasmissione uno a molti: multicasting push tecnology
- applicazioni event-driven: il mittente manda un messaggio e il ricevente lo riceve solo se è interessato a quel tipo di messaggio.
- ulteriore disaccoppiamento mittente/ricevente:
  - prima: non si sapeva solo dove fossero locati mittente e ricevente
  - ora: non si sa nemmeno chi siano e quanti siano i riceventi

## Pattern publish/subscribe

- publisher: chi manda il messaggio
- subscriber: chi riceve il messaggio
- event: il messaggio creato dal publisher e ricevuto dal subscriber
- event channel: il canale su cui vengono mandati i messaggi

## modelli di comunicazione tra programmi

Programma A e B.

- Conversational: A e B si scambiano messaggi in modo sincrono
- Request/Reply: A manda una richiesta a B e B risponde
- Messagge passing: A manda un messaggio a B e B lo riceve in modo asincrono
- Message queuing: A manda un messaggio a una coda e B lo riceve dalla coda
- Publish/Subscribe: A manda un messaggio a un canale e B lo riceve dal canale
