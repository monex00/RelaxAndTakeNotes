# Lezione 2 29/04

## Task e approcci dell'nlp

Ultimamente si è passato all'uso di reti neurali per risolvere questi tipi di task.
Invece di analizzare il linguaggio dal punto di vista umano, questi dati si danno in pasto ad una rete neurale che impara a fare il task.

Solitamente venivano usati tanto per gli speech, ma tramite l'uso dei transformer si è passati a usarli anche per il nlp.
Attraverso task di masking le reti neurali fanno l'encoding dell'input capendo cosa va con cosa. Queste reti neurali sanno completare la frase, dire che cosa manca.

Questa evoluzione, nella ricerca scientifica, ha portato che tutti i generici task di nlp si possano fare con le reti neurali, in particolare con i large language model.

- strategie di prompting
- strategie di fine tuning
- strategie di rug (?): si fa information retrieval e si usa il risultato direttamente nel prompt

## Significato del significato

Nlp studia i fenomeni del linguaggio in maniera tale da approcciarli in maniera computazionale.

Definizioni di base:

- **Lessico**: insieme delle parole di una lingua
- **Sintaassi**: regole che governano la combinazione delle parole
- **Semantica**: significato delle parole e delle frasi
- **Pragmatica**: significato in contesto, significato inteso: "ti muovi come un elefante"
- **Polisemia**: una parola può avere più significati
- **Omonimia**: due parole diverse con lo stesso suono
- **Ontologia**: studio delle categorie di entità e delle relazioni tra di esse, creare un ontologia significa creare un significato condiviso tra termini

## Teorie sul significato

- **Basate su Primitive**: basato su concetti primitivi, il significato è divisibile in primitive universali riconoscibili da tutti indipendentemente dalla lingua, dalla cultura, ecc.
- **Basate sulle relazioni**: il significato nasce quando si mettono insime le parole, ad un termine risco a dare un significato solo se lo metto in relazione con altri termini
- Si basano tanto sulla sintassi e inferenza
- **Basate su Composizioni**: Posso creare nuovi significati andando a combinare parole più o meno ingegnosamente
  - si basa su strutture profonde

## Basate sulle primitive

- Markers:
-

## Triangolo semiotico

Un concetto astratto per poter essere comunicato va lessicalizzato, deve essere portato ad un livello simbolico. Ci sono legami molto deboli tra parola e simbolo (rappresentazione -> concetto -> referente)

- concept: il concetto di gatto
- referent: un gatto preciso
- sign/rappresentazione: la parola "gatto"

Nel mondo ai, le macchine devono partire dal livello simbolico, sono i dati da cui partono per poter astrarre il concetto.
Si cerca di andare verso sia il concetto, sia il referente. Quando parliamo di vision abbiamo ad esempio immagini di "gatto", questi sono referenti.

## Multilingual word meaning

Avere un contesto multilingua è avere della barriere, la comprensione avviene solo e soltatando quando si comprende anche l'altra lingua.

Tuttavia, puo' essre una opportunità. Se noi apprendiamo da una lingua, in realtà apprendiamo dei concetti universali su tutte le lingue. Apprendere un'altra lingua dopo averne già imparata una è più facile e veloce. Inoltre il contenunto lessicale di un'altra lingua può arrichire la nostra lingua, perchè si ha lo stesso concentto espresso in modi diversi.

Inoltre diminuesce l'ambiguità sullo stesso termine, in quanto mangari in una lingua lo stesso concentto è molto meno ambiguo, ha meno significati.
Lingue diverse offrono significati diversi e la combinazione di queste può aggiungere funzionalità.

Lingue rare: è difficile avere materiale lessicale che permettono di allenare i modelli.

Concentti comunque diversi: se ho la traduzione di un termine in un'altra lingua in realtà non sempre, anche a livello culturale, si intendo lo stesso significato. Ad esempio nel polo nord esistono tanti termini per i diversi tipi di bianco, mentre in Italia ne esistono pochi.

# Lezione 5 06/05

## Text mining e applicazioni

Nlp prima era molto rulebased, adesso è nato un sottoramo del data mining chiamato text mining in cui si usano techiche statistiche e di machine learning per analizzare il testo.

- approcci top-down
- approcci bottom-up

### vector space model

Una informazione testuale rappresentata attraverso un vettore.
formule:

- TF IDF
- COSINE SIMILARITY

- COSINE SIMILARITY: calcola l'angolo dei due vettori che rappresentano le features nello spazio multidimensionale

  - funziona meglio della distanza euclidea perchè prende in considerazione la direzione dei vettori

- TF IDF: permette di popolare i vettori senza tecniche specifiche di machine learning:

  - TF: time frequency, conta quante volte una parola compare in un documento
  - IDF: inverse document frequency, calcola quanto una parola è rara (sparsa) in un corpus, più è comune più è basso

- Co-occurrence matrix: conta quante volte due parole compaiono insieme in un contesto, calcola quanto le parole siano legate una all'altra.

### diversi tipi di task del text mining

- Summarization
  - estrattiva
  - atrattiva
- Document clustering: separe in maniera non supervisionata i documenti in cluster
- Document classification/categorization: assegna una categoria/etichette ad un documento
  - le etichette possono essere organizzate in tassonomie
- Document segmentation: divide un documento in segmenti
  - Individua gli elementi diversi di un discorso
  - Text tiling: divide il testo in blocchi di testo
    - permette di indivuduare come shifta un discorso sui diversi argomenti andando a vedere come cambia la frequenza delle parole nelle varie frasi

### Document summarization

ruduzione del testo mantenendo le informazioni più importanti
due diversi metodi:

- estrattivo: seleziona le frasi più importanti
- astrattivo: crea un riassunto nuovo, implica NGL(natural language generation, reti neurali)

valutazione Rouge: misura la qualità del riassunto comparando la similarità tra il riassunto e il testo originale usando n-grammi (bigrammi, trigrammi, ecc.)

## Orienteering and Browsing

Navigare attraverso un testo in maniera iterativa, cercando di trovare informazioni specifiche.

### Information retrieval

Ottenimento delle informazioni attraverso query

## Semantica documentale

Topic modeling e Dynamic topic modeling.
Text visualization

### Topic modeling

Task che permette di, dati una collezioni di testi in input, trovare i topic che sono presenti in questi testi.
Topic: lista pesata di parole
Il problema principale riguarda problemi di calcolabilità, perchè non si sa quanti topic ci siano e quali siano.
Solitamente i topic sono le parole che co-occorono, non tutte sono utili.

- **Latent Semantic Analysis**: effettua una fattorizzazione matriciale.
  Di fatto crea uno spazio latente a partire dal testo, questo spazio oggi esiste nei Large Language Model.
  Crea una matrice termine-documento, e ho per ogni documento un vettore che rappresenta quale termine è presente nel documento. In grigio quelle parole positive (che sono presenti).

  Si crea un contesto indiretto tramite la co-occorrenza delle parole nei documenti che ci sono in mezzo. (le prime parole del dizionario sono co-occorenti con le ultime)
  Questo va a creare uno spazio latente, uno spazio in cui le parole hanno un significato diverso, un significato di co-occurrenza.
  Gli stessi documenti vengono proiettati in questo spazio latente, con meno dimensioni in cui le features aggreano le features dello spazio originale. (aggregano sia il valore lessicale che il valore semantico)

  Se applichiamo la **latent semantic analysis** in uno spazio a due dimensioni, allora i punti vengono proiettati su un asse che cerca di massimizzare la varianze, cioè il distanziamneto tra i punti.
  La differenza tra la varianza espressa nel primo spazio e la varianza espressa nel secondo spazio è indice di quanto l'informazione sia stata mantenuta.

  Questo è un metodo di riduzione della dimensionalità, che permette di avere una rappresentazione più compatta dei dati.

### text visualization

Proietta i testi in spazi visualizzabili, ad esempio in 2D o 3D.
Utilizza tecniche come PCA, SOM, multidimensional scaling.

Approcci grafici:

- **parallel coordinates**: le dimensioni vengono proittare in maniera sequenziale in modo tale da poter rappresentare dimensioni molto grandi, ogni elemento è rappresentato da un segmento che collega i punti delle varie dimensioni
- **radial visualization**: il cerchio rappresenta le features che fungono da atrattori, i punti all'interno viene identificato con un calcolo delle forze attrattive. (dipende dall'ordine delle features)
- **heatmap**: le features sono rappresentate in una matrice e le features sono rappresentate in una scala di colori
- **correlation circle**

### Perchè usare matrici

é una approssimazione, è questo non è un problema, perchè il nostro cervello è abituato a fare approssimazioni sul linguaggio.

Esiste un rapporto tra spazi concettuali e prototype theory, cioè il nostro cervello raggruppa le cose in base a prototipi, cioè in base a come le cose sono simili a un prototipo.

Nel momento in cui costruisco una matrice applico tecniche di nlp più o meno statistico, esisto dei parametri:

- stategie di pesatura
- transformazioni matriciali
- meccanismi di clustering

### normalizzazione

Il testo puo' essere normalizzato, solitamtente sul livello lessicale/sintattico.
Con la denormalizzazione si fa una normalizzazione a livello semantico.
Associo ad un termine un significato, e questo termine può avere più significati.

### Configurazioni matriciali

- **Term-document matrix**
  - granularità dei documenti
  - elenco task
- **Term-context matrix**
  - granularità delle parole, come le parole sono distribuite nei contesti
- **Term-pattern matrix**
  - tuple di parole realazionate con un pattern(pattern che legano le parole delle tuple)
  - task di relational similarity o search
  - clustering: accorpare pattern diversi che indicano lo stesso significato
  - relation search: es. lista tutte le x tale che x causa il cancro
  - granularità intermedia rispetto alle prime due, granularità a livello di frasi

### Similarità, ruolo

A livello cognitivo, l'uomo lavora molto con la similarità, cioè raggruppa le cose in base a quanto sono simili. Fondamentale quindi nel pensiero e nell'apprendimento umano.

Ne esistono diversi tipi:

- semantic similarity: o sono sinonimi o sono quasi-sinonimi, stesso concetto o quasi!
- relatedness similiarity: due concetti sono legati, ma non sono sinonimi. Ad esempio "gatto" e "topo" sono legati, ma non sono sinonimi. o antonimi, ad esempio "luce" e "buio".
- Attributional similarity: due concetti sono simili perchè condividono delle proprietà, ad esempio "gatto" e "cane" sono simili perchè sono animali domestici.
-
- Relational Similarity: similarity tra coppie diverse di parole, il gatto miagola come il cane abbaia
- Semantic association: co-occorrono frequentemente insieme, ad esempio "caffè" e "zucchero"

Dataset: simlex999

### problemi principali nella rappresentazione matriciale

-

### arricchimento matriciale

tipicamente esistono due approcci al problema:

- ottenere conoscenza da dati: statistcal knowledge
- : semantic knowledge
