# Introduzione al Calcolo Parallelo e Distribuito (23/02)

## Differenza tra Calcolo Parallelo e Distribuito

- **Calcolo Distribuito** : si concentra sull'interoperabilità tra dispositivi indipendenti, come le applicazioni su smartphone che devono funzionare anche in assenza di connessione internet. Questo modello enfatizza la resilienza e l'autonomia operativa di ciascun nodo della rete.
- **Calcolo Parallelo** : mira al miglioramento delle prestazioni attraverso la divisione dei compiti in parti che possono essere eseguite simultaneamente su diversi processori. In caso di fallimento di un'operazione, si scarta il tentativo in corso e si riparte da capo, con l'obiettivo di ottimizzare il tempo di esecuzione totale.

## Considerazioni sul Calcolo Parallelo

Non tutti i problemi beneficiano del calcolo parallelo. L'overhead, o i costi aggiuntivi legati alla sincronizzazione e coordinazione delle esecuzioni parallele, può talvolta superare i benefici. Un esempio è la parallelizzazione di operazioni semplici come la somma di due numeri, dove il tempo necessario per coordinare i processori potrebbe eccedere il tempo di esecuzione dell'operazione stessa.

È cruciale valutare attentamente i limiti e le opportunità offerte dal calcolo parallelo prima di procedere con la sua implementazione.

## Architetture del Calcolo Parallelo

- **Cluster di Calcolo (Compute Cluster)** : Gruppi di computer indipendenti che lavorano insieme per eseguire compiti condivisi.
- **SMP (Symmetric Multi-Processing)** : Più processori condividono un'unica memoria centrale.
- **CMP (Chip Multi-Processor)** : Più processori si trovano sullo stesso chip, condividendo risorse e ottimizzando l'efficienza energetica.

Inoltre, si osserva una tendenza verso l'utilizzo di processori specializzati per compiti specifici, al fine di migliorare l'efficienza e la velocità di esecuzione. Questi includono, ad esempio, processori dedicati al parsing di JSON in server web o al controllo della sicurezza dei messaggi.

## La Fine dell'Era del "Pranzo Gratis"

La "Free Lunch Era" si riferisce al periodo in cui si riteneva che l'aumento della potenza di calcolo sarebbe continuato indefinitamente grazie alla miniaturizzazione dei transistori (Legge di Moore). Tuttavia, raggiunti i limiti fisici di questa scala, è diventato essenziale trovare nuove strade per aumentare le prestazioni, come il calcolo parallelo.

Implicazioni di questa transizione includono una maggiore enfasi su microarchitetture ottimizzate, riduzione delle latenze, integrazione di maggiori cache nei processori, e una ricerca costante verso l'efficienza energetica.

## Gestione della Cache

La cache, elemento cruciale per l'efficienza del calcolo, opera in trasparenza rispetto all'utente, simulando l'accesso alla memoria principale ma offrendo tempi di risposta significativamente inferiori. La gestione della cache implica strategie di mappatura degli indirizzi e politiche di rimpiazzamento, come il Least Recently Used (LRU), per ottimizzare l'accesso ai dati frequentemente utilizzati.

Questa introduzione mira a fornire una panoramica concisa e informativa sul calcolo parallelo e distribuito, evidenziando le sfide, le strategie e le architetture chiave in questo ambito.
