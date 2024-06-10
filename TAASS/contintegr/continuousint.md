# Countinuous integration and delivery

Un team è solitamente composto da:

- sviluppatori
- product management: gruppo di persone che definisce il prodotto, decide cosa andrà nelle varie realease. Si occupa di fare il ponte tra sviluppatori e clienti
- integration e operations team: consegnano, testano e integrano il prodotto
  - integration: Merge - Build - Test
  - operation: Responsabile di far uscire la release

l'idea e di ridurre al minimo la parte di integrazione e operations (iterazioni corte), per fare questo dobbiamo automatizzare il più possibile.

alla fine di ogni iterazione:

- merging dei moduli sul main
- build del codice
- deploy del codice

## deploy

team di integrazione fa la build e passa al team operations una release e delle istruzioni e dovreanno gestire i 3 ambienti di sviluppo, test , accepance e produzione e si decide poi cosa dare al cliente

![alt text](image.png)
source control: git

## cosa si può migliorare?

- la build è manuale: integrazione
- il deploy è manuale: operations

A cosa puntiamo?:

- migliore qualità
- delivery veloce
- riduzione dei costi
- più flessibilità

Creazione di pipeline di build e di deploy

## continuous delivery !Importante

![alt text](image-1.png)

se il codice è molto può esserci la quality assurance che fa il testing da persone esterne

## Continuous integration principles and benefits

**Principles**:

- un unico ambiente (git)
- bisogna avere le commit piccole e frequenti
- automazione dei test

**Benefits**:

- less effort: meno tempo per fare il deploy
- I problemi vengono scoperti prima
- Automazione significa meno errori
- Il processo è più visibile
- Migliora la collaborazione
- Migliora la qualità del software

## differenza tra continuous deployment e continuous delivery

delivery: Il software può essere rilasciato in produzione in qualsiasi momento

deployment: il software è rilasciato in produzione in automatico tutte le volte

con piccole immagini di kubernetes è uguale

## Strategie di deployment

- **Blue green deployment**

![alt text](image-2.png)
router: posso indirizzare dove voglio con apigateway
devo far testare nuova versione?
cambio da blu a verde dal router gli utenti la usano e se non va a buon fine faccio rollback, velocissimo cambio solamente i lkservizio

- **canary deployment**

![alt text](image-3.png)
sono più incerto non sposto tutti gli utenti ma solo una parte e vedo se va bene
ho un confronto tra la nuova e la vecchia versione

- **feature flags**

![alt text](image-4.png)
ho dei flag nel codice che mi permette di dare le features nuove solamente a una parte degli utenti(o stampare cose)

## DevOps

**Development** (sviluppo) e **Operations** (organizzazione). Lo scopo di questa cultura aziendale è quello di far sì che i team di sviluppo lavorino assieme ai team organizzativi durante tutta la fase di sviluppo di un software e oltre. Ciò permette di evitare problemi di integrazione del software fin dall'inizio e facilita il controllo e la distribuzione dei programmi finiti.

## git ops

![alt text](image-5.png)

# Jenkins

primo strumento di CI/CD
oggi github actions è molto più usato

## come funziona

- modello ad eventi
- vengono startate delle build e dei deploy automatici
- posso stabilire delle policy per test e integrazioni
- IDEA:se faccio cose(test e build) frequenti scoprop prima i problemi

![alt text](image-6.png)

- posso fare testing anche negli stage

# Github actions

- githubflow: posso averre la visione strutturata dei branch
- posso fare depoloy sul cloud in modo automatico
- custom workflow: posso fare quello che voglio
  - aspetto lgie eventi
  - automatizzo gitflow
