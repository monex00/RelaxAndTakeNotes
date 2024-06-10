# Kafka

Kafka è un sistema di messaggistica distribuito che implementa il publish/subscribe pattern tramite un log distribuito di messaggi.

In linea generale è tutto ciò che è rabbitMq ma è pensato per essere scalabile e con permanenza dei messaggi.

Caratteristiche Principali

- High-throughput: Efficiente nel gestire volumi elevati di messaggi, mantenendo alte prestazioni.
- Fault-tolerant: Resistente a guasti hardware e software grazie alla sua architettura distribuita.
- Loosely Coupled: Indipendenza tra produttori e consumatori di messaggi.
  Reliable and Durable: Assicura l'affidabilità nella consegna dei messaggi e la loro persistenza a lungo termine.

## Difetti dei principali sistemi di messaggistica

- **Scalabilità limitata**
- **Smaller message size**
- **Non fault-tolerant**

## Architettura

Kafka è organizzato in cluster, in cui ogni nodo è chiamato broker.

All'interno di un cluster c'è una organizzaione piramidale di nodi, in cui il nodo leader è il nodo principale e gli altri nodi vengono chiamati worker node.
Il leader effettua controlli sullo stato e ne gestisce la replicazione in caso di guasto.
Ogni nodo comunica con con l'altro tramite scambio di messaggi.

I messagi vengono replicati nelle code che sono presenti in ogni nodo.

## Apache zookeeper

Servizio che permette di effettuare la configurazione dei broker e di effettuare l'assegnamento dei nodi ai diversi gruppi.

## Partizioni

All'interno dei cluster, i broker mantengono partizioni di topic (code).

All'interno della partizione, gli eventi (i messaggi) vengono mantenuti in ordine di arrivo e hanno una durata di vita limitata, non vengono consumati.

L'aggiunta di eventi nella partizione avviente tramite unica operazione di append.

Ogni messaggio ha le seguente informazioni:

- **Timestamp**
- **Idenfier**
- **Payload**

L'offset, l'indice di dove si è arrivati nella partizione, è mantenuto dal consumer.

Ogni topic (coda) ha uno o più partizione (replica) mantenute da uno o più broker.
Le partizioni permetto di:

- scalare il carico
- garantire fault-tolerance
- ottenere maggior throughput

Ogni partizione deve stare necessariamente su una singola macchina.

## Retention policy

In Kafka, i messaggi vengono mantenuti per un periodo di tempo definito, dopo il quale vengono eliminati. C'è un default retention policy configurabile e tale retention policy può essere configurata a livello di topic (per-topic basis).

Kafka garantisce che un consumer legga sempre i messaggi in ordine.
Gli eventi possono essere letti più volte, non come i tradizionali sistemi di messaggistica.

In generale kafka implemenenta un raw database, utilizzando il pattern publish/subscribe.
