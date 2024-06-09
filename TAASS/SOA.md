# Service oriented archietecture

Si basa sul concetto di sofware diviso a componenti/servizi. Nasce dall'evoluzione delle architetture legacy, che erano monolitiche e difficili da mantenere, per poi arrivare ad archittetture a microservizi.
Nasce da esigenze aziendali di avere una infrastruttura di integrazione che permetta di integrare sofware di diverse aziende

## Before SOA

Silos verticali che realizzano funzioni aziendali: - impossibile rilasciare i silos in modo indipendente, o tutto o niente - connessioni a database intricate, su funzioni aziendali complesse è difficile da mantenere

## After SOA

Le funzioni aziendali vengono realizzate tramite servizi più piccoli, che possono essere rilasciati in modo indipendente. I servizi comunicano tramite un bus di servizi, che permette di integrare i servizi in modo semplice.
Il Composed business process si occupa di orchestrare i servizi, e di gestire le transazioni.

- L'obbiettivo è quello di estrarre servizi indipendenti in modo tale da renderli risuabili e da poterli rilasciare in modo indipendente senza dover fare il redeploy di tutta l'applicazione.
- Meno interdipendenze tra i servizi, più facile da mantenere e scalare.
- Meno interconnesioni, ogni servizio ha un db dedicato.

Il layer "Data services" e "Services" può fungere da wrapper per l'integrazione e la comunicaione con i sistemi legacy.

## Web services Soap
