# Kubernetes

_Kubernetes fornisce un framework per far funzionare i sistemi distribuiti in modo resiliente, si occupa della scalabilità, failover, distribuzione delle applicazioni._

_Quindi Kubernetes è di fatto un Orchestratore di container (Docker)._

## Benefici

- **Orchestratore di container**: Kubernetes permette di gestire i container in modo efficiente
- **Zero downtime**: Kubernetes permette di aggiornare le applicazioni senza downtime
- **Self-healing**: Kubernetes si occupa di riavviare i container in caso di crash
- **Scalabilità**: Kubernetes permette di scalare orizzontalmente le applicazioni

## Componenti

- **Cluster**: insieme di nodi che eseguono applicazioni containerizzate
  - un cluster ha almeno un Worker Node
- **Worker Node**: componente che ospita i Pod
- **Pod**: unità minima di esecuzione in Kubernetes, contiene uno o più container (generalmente uno) (guscio esterno del container)
  - Network: ogni Pod ha un indirizzo IP univoco
  - Storage: ogni Pod ha un filesystem condiviso tra i container all'interno del Pod
  - Status: un Pod è in uno dei seguenti stati: Pending, Running, Succeeded, Failed
- **Kubelet**: agente che gira su ogni Worker Node e si occupa di inizializzare i Pod e ne controlla lo stato
- **Kube-proxy**: componente che si occupa di gestire il networking tra i Pod
- **Services**: fungono da singolo punto di accesso per uno o più Pod
  - Risolvono il problema dei pod che cambiano indirizzo IP ogni volta che vengono riavviati
  - Un Service ha un indirizzo IP fisso
  - Possono funzionare da Load Balancer e da API Gateway

## File di Configurazione
