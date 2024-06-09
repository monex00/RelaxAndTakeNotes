# Meaven

## Principali features

- **Dependency System**: Meaven è un tool che permette di gestire le dipendenze di un progetto Java. Questo significa che si occupa di scaricare le librerie necessarie al progetto, in modo automatico.
- **Multi-module builds**: Meaven permette di gestire progetti composti da più moduli, in modo da poter gestire progetti complessi e di trattare i servizi come moduli separati.
- **Consistent build model**: Meaven permette di definire un modello di build consistente, in modo da poter gestire progetti di qualsiasi dimensione.
  In un unico file mettiamo le librerie e versione
- **Project generated sites**: Inizializzazione del progetto con le cartelle e file necessari

## Che cosa è Meaven

è un project managament tool, permette di gestire il versioning e le release favorendo i principi di continuous integration e continuous deployment.
Permette anche di produrre java doc e unit test.

## Come funziona

- read: legge il file pom.xml
- build:
  - controlla le dipendenze su un repository locale
  - se non le trova le scarica da un repository remoto
  - compila il codice, esegue le fasi della build o il goal specificato

## POM

Descrive il progetto indicando:

- nome e versione
- source code location
- dipendenze
- plugin

Maven identifica univocamente i progetti usando la tripletta groupId, artifactId e version (GAV).

- groupId: identifica il progetto
- artifactId: identifica il progetto
- version: identifica la versione del progetto

Puo' essere definita il tipo di packaging da effettuare dopo una build, ad esempio jar, war, ear, ecc.

implementa un meccanismi di ereditarietà delle configurazioni, in modo da poter definire un modello di build comune per tutti i progetti.

## Comandi principali

- `mvn clean`: pulisce il progetto
- `mvn compile`: compila il progetto
- `mvn test`: esegue i test

## Utilità

Con maven non è più necessario mettere le librerie sotto version control, basta mettere le dipendenze nel file pom.xml e maven si occuperà di scaricarle.
Introduce il concetto di repository, dove vengono salvate le librerie.

## Repository

I repository sono definiti nel pom e possono ereditare da repository centrali, come maven central.
Sono utili per i produttori di librerie, che possono pubblicare le proprie librerie in un repository pubblico.

## Transitive dependencies

Maven gestisce automaticamente le dipendenze transitve, ovvero le dipendenze delle dipendenze.
Queste possono essene controllate tramite "Exclusion".
