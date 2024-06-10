# Microservizi

Raffinamento di SOA (Service Oriented Architecture), i microservizi sono un'architettura software che organizza un'applicazione come un insieme di servizi indipendenti, ciascuno dei quali è responsabile di un'area di funzionalità.

## Perchè popolari

- Cambiamenti più rapidi
- higher availability
- Scalabilità più a grana fine
- Facilemente integrabile con CI/CD

## Cos'è un microservizio

Un microservizio è un servizio software che è progettato per essere piccolo e modulare. Ogni microservizio è progettato per eseguire una singola funzione o un insieme di funzioni correlate.

Indipendenza:

- Data storage: ogni microservizio ha il proprio database.
- deployment: ogni microservizio può essere distribuito indipendentemente dagli altri.
- changeability: un microservizio può essere modificato senza influenzare gli altri microservizi.
- tecnologica

## Vantaggi

- Più facile lavorare con più team
- Individual deployment
- Indipendenza tecnologica: ogni microservizio può essere scritto in un linguaggio di programmazione diverso.
- Scaling
- Fault isolation

## Challenges

- Avoid complex interations: inefficienti o chatty (troppe chiamate)
- Monitoring: più difficile monitorare un sistema di microservizi rispetto a un sistema monolitico.
- Gestione dei dati distribuiti: ogni microservizio ha il proprio database, quindi è necessario gestire i dati distribuiti.
  - Problema quando una applicazione ha bisogno di fare tante join di tabelle.

## Microservices heaven

L'ideale sarebbe avere un sistema di microservizi in cui la comunicazione avviene solamente in maniera asincrona.
Nella realtà però è difficile evitare la comunicazione sincrona, quindi meglio avere sistemi ibridi.

Benefici nell'usare comunicazione asincrona:

- gestisce automaticamente il downtime durante il redeploy
- isola slow services
- più facile aggiungere nuovi servizi

## Error isolation

Tramite l'uso di microservizi è possibile isolare gli errori, in modo che un errore in un microservizio non influenzi gli altri microservizi.

Ad esmepio, sarebbe meglio avere un microservizio a parte dedicato all'uso di una particolare libreria, in modo che se ci sono problemi con quella libreria, non influenzino gli altri microservizi.

## Esempi di architetture

- Hub and spoke
  - Uso un api gateway per comunicare con i microservizi
- Event-driven
  - I microservizi comunicano tramite eventi su un message broker (queue)
- hybrid: event-driven e rpc
  - I microservizi comunicano sia tramite eventi che tramite chiamate rpc.

In generale l'api gateway può fungere anche da load balancer.
Il load balancer è fondamentale in una architettura di microservizi, in quanto permette di bilanciare il carico tra i vari microservizi.

## Eureka server

Server che funge da service registry, permette di registrare i microservizi in maniera tale da poterli richiamare tramite nome e non tramite indirizzo ip.

## Microservices Boundary

- **Bounded Context**: un microservizio dovrebbe avere un contesto ben definito, in modo che sia chiaro cosa fa e cosa non fa.
- **Circular dependencies**: evitare dipendenze circolari tra microservizi.
- **Chatty communication**: evitare comunicazioni troppo frequenti tra microservizi.

## hosting options

- **VMs**
- **PaaS**: Platform as a Service
- **Containers**: Docker
  - Startare tutto con docker compose è molto comodo.
- **Kubernetes**: orchestratore di container
  - build in dns
  - load balancing

## Business domain centric

L'individuazione dei microservizi dovrebbe essere fatta in base al dominio di business, in modo che ogni microservizio sia responsabile di un'area di funzionalità ben definita.
Partendo dalle Crc cards, si possono individuare le funzionalità e quindi i servizi.

# Seconda parte

## Greenfield vs Brownfield

- **Greenfield**: partire da zero, nessun sw preesistente quindi nessun vincolo.
  - Si può inizaire con un design non a microservizi e poi migrare a microservizi.
- **Brownfield**: partire da un sistema già esistente, quindi bisogna fare refactoring.
  - I servizi sono tutti mescolati
  - Indivuduo le diverse funzionalità dalla business logic
  - Tiro fuori i microservizi associandogli un proprio db
  - Aggiungo un message borker per garantire la comunicazione con l'architettura già esistente.
  - Aggiungo una componente di Monitoring e una di Logging (utile per fare rollback in caso di problemi)
  - Itero.
  - Refactoring:
    - code refactoring
    - database refactoring

## Domain driver design

Tramite il Domain driver design si possono individuare i microservizi in base al dominio di business.
Si individuano i concetti alla base del dominio e i concetti che invece sono fuori dal contesto.

**Bounded context**: un microservizio dovrebbe avere un contesto ben definito, in modo che sia chiaro cosa fa e cosa non fa.

## Pattern di comunicazione

- Competing workers pattern
  - Una coda di messaggi con più worker che leggono i messaggi.
  - i worker sono in competizione, solo uno processerà il messaggio.
- Fan-out pattern
  - Un messaggio viene inviato a tutti i worker.
- Request/acknowledge con callback
  - Il client invia un messaggio e riceve subito un ack.
  - Tramite callback riceve la risposta dal server successivamente.

## Design patterns

- nel singolo servizio:
  - **Facade pattern**: Una singola interfaccia per accedere alle funzionalità di un servizio.
    - Information hiding
    - shared model
    - decoupling
  - **Proxy**: Un proxy per accedere a un servizio remoto.
    - wrapper ad un legacy system
  - **Stateless pattern**: Non voglio mantere lo stato all'interno del servzio perciò lo scambio ogni volta nella richiesta.
- composizione di servizi:
  - **Broker composition**: Una coda di task che vengono processati da più servizi.
    ![alt text](https://file+.vscode-resource.vscode-cdn.net/d%3A/UnitoStuff/RelaxAndTakeNotes/TAASS/micros/image-3.png)
  - **Aggregate composition**: Un servizio che aggrega i risultati di più servizi.
  - ![alt text](https://file+.vscode-resource.vscode-cdn.net/d%3A/UnitoStuff/RelaxAndTakeNotes/TAASS/micros/image-4.png)
  - **Chained composition**: Un servizio che chiama un altro servizio che chiama un altro servizio. Invocazione concatenata di servizi.
    ![alt text](https://file+.vscode-resource.vscode-cdn.net/d%3A/UnitoStuff/RelaxAndTakeNotes/TAASS/micros/image-5.png)
  - **Proxy composition**: Api gateway che fa da proxy per chiamare i servizi.
  - ![alt text](https://file+.vscode-resource.vscode-cdn.net/d%3A/UnitoStuff/RelaxAndTakeNotes/TAASS/micros/image-6.png)
  - **Branch composition**: Un ibrido tra chained e aggregate composition.
  - ![alt text](https://file+.vscode-resource.vscode-cdn.net/d%3A/UnitoStuff/RelaxAndTakeNotes/TAASS/micros/image-7.png)
- data consistency:
  - **Two-phase commit**
  - **Saga pattern**:
    - saga log
    - Sub request
    - compensating request
    - cordinator di richeste tra i servizi
  - **Eventual consistency**: Garantisco la consistenza dei dati in un secondo momento. Gestisco l'inconsistenza a posteriori.

## API Gateway

api gateway è un servizio che fa da intermediario tra i client e i microservizi.
Fornisce funzionalità come:

- autenticazione
- rate limiting
- load balancing
- caching
- logging
- monitoring
