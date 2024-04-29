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
