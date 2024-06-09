# Docker

## Cos'è Docker?

In passato il compito di semplificare la gestione del ciclo di vita del sofware era stato affidato alle tecnologie di virtualizzazione con i seguenti problemi:

- **Spreco di risorse**: ogni macchina virtuale richiede un sistema operativo completo
- **Complessità**: amministrazione, aggiornamenti, backup, etc.

Anche se offrono un elevato livello di isolamento, la virtualizzazione limita fortemente il numero di virtual machine che possono essere eseguite su un singolo server fisico.

Per risolvere questi problemi è nato Docker, definizione:

_Docker è una piattaforma software che raccoglie il software in unità standardizzate chiamate container che offrono tutto il necessario per la loro corretta esecuzione, incluse librerie, strumenti di sistema, codice e runtime._

## Come funziona?

Docker funziona grazie l'uso di container che contengono l’insieme dei dati di cui necessita un’applicazione per essere eseguita:

- librerie
- altri eseguibili
- file system
- file di configurazione
- script

La creazione di un container parte dalla definizione di un'immagine trami un file di configurazione chiamato Dockerfile.
Il container è un'istanza in esecuzione di un'immagine.

Grazie a questa definizione standardizzata, i container possono essere eseguiti su qualsiasi sistema che supporti Docker, indipendentemente dal sistema operativo.

Inoltre, i container sono leggeri perchè sfruttano i servizi offerti dal kernel
del sistema operativo ospitante, invece di richiedere l’esecuzione di un kernel
virtualizzato come avviene nel caso delle VM.

## Altri concetti

- **Docker Engine**: software che permette di creare e gestire i container
- **Network**: Docker Engine crea un network virtuale per i container, permettendo la comunicazione tra di essi
- **Volume**: Docker Engine permette di creare volumi per memorizzare i dati in modo persistente
- **Docker Compose**: strumento per definire e gestire applicazioni multi-container

## Docker Registry e Docker Repository

- **Docker Registry**: servizio di storage per le immagini Docker. Possibilità di gestire privatamente un proprio Docker Registry.
- **Docker Hub**: public registry messo a disposizione da Docker.
- **Docker Repository**: collezione di immagini Docker con lo stesso nome ma differenziate per tag (versione dell'applicazione).
