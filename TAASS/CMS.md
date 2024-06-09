## 1. Introduzione

### Motivazione: Perché usare i configuration Management Systems?

- **Problemi affrontati:**
  - Collaborazione tra più persone su software in continua evoluzione.
  - Supporto di più versioni del software
  - Esecuzione del software su diverse macchine e sistemi operativi
  - **Necessità di coordinamento:**
    - Gestione dei sistemi software in evoluzione.
    - Controllo dei costi legati alle modifiche di un sistema.
    - Parte di un processo di gestione della qualità più generale.

## 2. Definizione e Attività della Gestione della Configurazione Software (SCM)

### Definizione:

La gestione della configurazione software (SCM) è un insieme di pratiche ingegneristiche per gestire le modifiche ai prodotti software nel corso della loro evoluzione.

### Attività e Ruoli (in un approccio non agile):

- **Configuration Manager:** Identifica gli elementi di configurazione e definisce le procedure per creare promozioni e rilasci.
- **Change Control Board Member:** Approva o rifiuta le richieste di modifica valutando l'impatto e la stabilità del sistema.
- **Sviluppatore:** Crea promozioni(una cosa temporanea che dal local va disponibile a tutti) basate sulle richieste di modifica o attività di sviluppo normali, gestisce le modifiche e risolve i conflitti.
- **Auditor:** Seleziona e valuta le promozioni per il rilascio (review del codice), garantendo coerenza e completezza.

## 3. Scenari di Gestione della Configurazione

### Scenario 1:

- **Problema:** Un bug non rilevato fino a molto tempo dopo l'inserimento.
- **Soluzione:** Recuperare vecchie versioni per individuare la modifica che ha causato il bug.

### Scenario 2:

- **Problema:** Collaborazione tra più sviluppatori, rischio di sovrascrivere le modifiche degli altri.
- **Soluzione:** Isolare i diversi sviluppatori e unire il lavoro al termine.

## 4. Gestione delle Modifiche

### Processo Generale di Gestione delle Modifiche:

- Richiesta di modifica (può essere fatta da chiunque, inclusi utenti e sviluppatori).
- Valutazione della richiesta rispetto agli obiettivi del progetto.
- Accettazione o rifiuto della richiesta di modifica.
- Assegnazione della modifica a uno sviluppatore e implementazione.
- Verifica della modifica implementata (audit).

### Tipi di Controllo delle Modifiche:

Ci sono le promote/release policy, che definiscono chi può fare cosa e quando.+
PROGRAMMATORE --> PROMOTION --> MASTER DIRECTORY --> RELEASE --> SOFTWARE REPOSITORY --> CLIENTI

- **Promozione:** Modifica dello stato di sviluppo interno del software. Promozione del codice da locale a remote
- **Rilascio:** Distribuzione di un set di promozioni fuori dall'organizzazione di sviluppo.

## 5. Change policies

### Esempi di Politiche di Modifica:

- Nessun sviluppatore può promuovere codice sorgente che non può essere compilato senza errori e avvertimenti.
- Nessun baseline può essere rilasciato senza essere stato beta-testato da almeno 500 persone esterne.

### Formali e Informali:

- Le politiche formali sono adatte a rilasci esterni e grandi team.
- Le politiche informali sono buone per ambienti di tipo ricerca.

### Change tracking tool:

- Derivation history, che permette di vedere come un file è stato modificato nel tempo. (commit. author, date)
- Se un file ha tantissime modifiche, forse è il caso di fare refactoring.

## 6. Configuration Management plan

- Definisce chi è responsabile per le CM procedure
- Definisce le policy
- Descrive i tool che deveno essere usati

## 7. Strumenti per la Gestione della Configurazione

### Finalità degli Strumenti:

- Grande pulsante UNDO.
- Tracciamento delle modifiche:
  - Chi ha fatto le modifiche?
  - Differenze tra le versioni?
  - Quali file vengono modificati di più? (troope modifiche magari serve refactoring)
- Identificazione dei rilasci.
- Fusione delle modifiche concorrenti.

### Sistemi di Controllo delle Versioni:

- CVS
- Subversion
- Git: [http://git-scm.com/](http://git-scm.com/)
- REPO (Android)
- Mercurial
- Clearcase

### Obbiettivi del CMS:

2 obbiettivi:

- **Record keeping:** Mantenere traccia delle modifiche e delle versioni. Essere in grado di tornare a versioni precedenti. (anche se sono da solo)
- **Collaboration:** Consentire a più persone di lavorare contemporaneamente sullo stesso progetto.

### Terminologia (Esempio Git):

- **Revisione:** uno snapshot del progetto
- **Repository:** Copia master dove GIT memorizza la storia completa delle revisioni di un progetto.
- **Working copy:** Copia in cui si fanno effettivamente le modifiche.
- **Check out:** Richiesta di una working copy dal repository.
- **Commit:** Invio delle modifiche dalla working copy nel repository centrale.
- **Log message:** Commento allegato a una revisione quando viene eseguito il commit, descrivendo le modifiche.
- **Update:** Portare le modifiche degli altri dal repository nella propria working copy.(non voglio avere troppi conflitti con il commit di altri)
- **Conflict:** Situazione in cui due sviluppatori cercano di commettere modifiche nella stessa regione dello stesso file.
