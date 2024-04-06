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
