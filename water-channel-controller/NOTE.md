# Procedura lettura su seriale tra server e client (comunicazione):

1. Sto zitto e leggo messaggio(i) da server.
2. Fino a quando non ho conferma (con apposito carattere $"END"$) sto zitto e leggo ciò che mi scrive il server sulla seriale.
3. Quando l'ultimo messaggio che ho ricevuto dal server corrisponde a $"END"$ allora posso iniziare posso inziare a scrivere io (client) sulla seriale.
4. Inizio  a scrivere i due messaggi da recapitare come conferma al server.
5. Come ultimo messaggio per comunicare che ho finito di parlare, mando un messaggio di $"END"$.
6. Ora il server capisce che può tornare a scrivere, dato che ha ricevuto il messaggio che comunica l'inizio del silenzio da parte del client.

#### Nota: La comunicazione su seriale può avvenire in una sola direzione, quindi Client e Server non possono comunicare in contemporanea (uno ascolta, l'altro parla).

# Formattazione del messaggio - Server -> Client 
### Ordine dei messaggi: 
- Stringa 1: "valveValue:25" , "status:NORMAL"
- Stringa 2: "END"


