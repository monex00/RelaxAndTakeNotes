## JEE

### Java Enterprise Edition: Cos'è, Descrizione Dettagliata e Modifiche allo Spyke

JEE è un framework per lo sviluppo di applicazione server-side compelsse e fornisce API per l'accesso ai database, la gestione delle transazioni, la sicurezza, la connettività di rete e altro ancora.

Sul piano dell'architettura di JEE abbiamo:

- **Web server**: Servlet/JSP, SOAP engine (predecessore di REST) o RMI (no interfaccia web, connesso direttamente al backend) lato front-end.
- **EJB server**: Lato back-end business logic.
  - Gli Enterprise Beans sono componenti che gestiscono la logica di business e sono indipendenti dalla piattaforma. Vengono eseguiti all'interno di un container EJB.
- **Dati/Database**: Lato storage tra cui ERP (gestionali proprietari), RDBMS (con JDBC) e JMS MOM (Message Oriented Middleware).

#### Quando Usare Enterprise Beans

Usiamo Enterprise Beans quando:

- abbiamo bisogno di scalabilità
- Transazioni che devono assicurare data integrity
- molteplici client che accedono ai dati.

#### Le Funzionalità di JEE

- **Enterprise Java Beans (EJB)**: Componenti che aiutano a costruire la logica di business di un'applicazione. Sono eseguiti all'interno di un container EJB e sono di tre tipi: session beans, entity beans e message-driven beans.
- **Java Naming and Directory Interface (JNDI)**: API per accedere ai servizi di directory e naming su diverse macchine.
- **Remote Method Invocation (RMI)**: API per la comunicazione tra processi distribuiti.
  - questi due servizi insieme implementano una business logic distrituita su diverse macchine in remoto
- **Servlets**: Presentazione dinamica e gestione delle sessioni client web.
- **Java Server Pages (JSP)**: Pagine web dinamiche.
- **Java Message Service (JMS)**: API per la messaggistica asincrona con modelli point-to-point e publish/subscribe.
- **Java Transaction API (JTA)**: API per la gestione delle transazioni distribuite (XA o CORBA OTS).
- **Java Database Connectivity (JDBC)**: API per l'accesso ai database relazionali.
- **Java Authentication and Authorization Service (JAAS)**: API per l'autenticazione e l'autorizzazione.
- **JavaMail**: API per l'invio e la ricezione di email.

### Livelli di JEE

- **Client Tier**: Interfaccia utente, browser, applet, client Java.
- **Web Tier**: Servlets, JSP, JavaBeans, JavaMail, JNDI.
- **Business Tier**: EJB, JMS, JTA, JCA.
- **Enterprise Information System (EIS) Tier**: Database, ERP, RDBMS, JMS MOM.

### EJBs (Enterprise Java Beans)

Sono componenti che implementano la logica di business e sono eseguiti all'interno di un container EJB. Sono di tre tipi: session beans, entity beans e message-driven beans.

### EJB Server

Il server EJB fornisce servizi come la Java Virtual Machine (JVM), le classi di supporto per gli EJB, funzioni base di ORB (Object Request Broker) e TP Monitor, funzioni di accesso al DB e bilanciamento del carico.

### EJB Container

Il container EJB è un ambiente di runtime per gli EJB. Fornisce servizi come:

- la gestione del ciclo di vita degli EJB
- la gestione della transazione
- la sicurezza
- la gestione delle eccezioni
- la gestione della persistenza
- la gestione delle chiamate remote.

#### Session Beans

Fanno da intermediari tra i client e le entity beans. Sono di due tipi: stateful e stateless.

#### Quando Usare un Session Bean?

- Se solo un client ha accesso ad un'istanza di bean.
- Se lo stato del bean non è persistente.
- Se il bean implementa un web service.

**Tipi di Session Bean:**

- **Stateful**: il bean mantiene lo stato della conversazione (più costoso, occupa più memoria).
- **Stateless**: il bean non mantiene lo stato della conversazione.
- **Singleton**: memorizza dati condivisi che non dipendono dalla sessione con l'utente. cross session, cross utente

Si rimuovono delle funzionalità dalle servlets e si mettono nei session beans. Possono gestire tutte le invocazioni di un client. Ricevono dati da JPA e li processano per mandarli alle servlets.

#### Entity Beans

Rappresentano i dati persistenti. Creano una tabella alla prima esecuzione per poi aggiornarla ad ogni richiesta.

Un'entità è un oggetto che rappresenta un'istanza di una tabella di database.

È una classe Java annotata con @Entity e gestita dal framework ORM JPA (Java Persistence API).

Ogni istanza è una riga nella tabella del database. Finché non viene reso persistente, vive nello heap come tutte le variabili di istanza.

### Remote Client

Un client remoto è un client che accede agli EJB da un'altra JVM. Utilizza il protocollo RMI per comunicare con il server EJB.

### JMS (Java Message Service)

Permette la comunicazione tra applicazioni distribuite e eterogenee come fanno i MOM.

**È reliable**: garantisce che il messaggio venga consegnato una volta sola.

Fornisce due modelli di messaggistica: point-to-point e publish/subscribe.

**Modelli di Messaggistica:**

- **Point-to-Point**: Un solo mittente e un solo destinatario.
  - non hanno timing dependencies
  - il receiver segnala quando il messaggio è stato processato correttamente
- **Publish/Subscribe**: Un solo mittente e più destinatari, con un topic e una coda di messaggi.
  - hanno timing dependencies: il consumatore può consumare solo messaggi pubblicati dopo la sottoscrizione### EJB Remote
