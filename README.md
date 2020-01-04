# Server-MultiThread
<ul>
  <li>Scrivere un programma basato su comunicazione client/server con socket</li>
  <li>Il client invia un carattere al server</li>
  <li>Il server incrementa il carattere (in modo casuale) e lo invia al client,che lo stampa a video </li>
</ul>

<p>
Il Server appena sviluppato gestisce i client in sequenza.<br>
E' possibile migliorare la gestione del Server tramite l'uso dei threads
<ul>
  <li>Per ogni client che fa richiesta di connessione, viene creato un thread che gestisce la comunicazione con un client</li>
  <li>Quando il client si disconnette, il relativo thread finisce.</li>
  <li>Il programma principale rimane per gestire le richieste di connessioni</li>
  <li>Per evitare che il Server debba invocare la pthread_join, per ogni thread che termina, si deve cambiare lo stato di ciascun thread in modo detached.</li>
  <li>in questo modo le risorse del thread vengono rilasciate dal SO alla terminazione del thread.</li>  
</ul>
</p>
