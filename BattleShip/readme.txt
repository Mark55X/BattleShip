Readme.txt file
by Anna Albertin, Giulia Selvestrel, Marco Stefani


## Note sulla struttura del progetto
La struttura del progetto si basa su una semplificazione del pattern di progettazione software 
chiamato MVC (Model-View-Controller). 
I ruoli dei file sono:
 - Main (view): ha il ruolo di inviare i dati (ovvero i comandi per l'inserimento delle unita' navali, l'esecuzione
		di azioni e comandi speciali) al CONTROLLER (GameManager) e di visualizzare le risposte. 
		E' l'unico file (insieme a replay.cpp) che contiene quindi gestione di stream di input e output. 

 - GameManager (controller): e' il controller per la gestione del gioco. Riceve i comandi, li valida e li esegue. 
			     Le sue funzioni restituiscono quasi sempre una GameResponse (vedere game_response.h) 
			     che indica lo stato di esecuzione del comando e altre informazioni (esempio: se e' il turno
			     del giocatore successivo oppure e' ancora quello del giocatore che ha eseguito l'ultimo comando).
			     Si capisce quindi la netta separazione tra Main e GameManager: e' quest'ultimo che tramite
			     la GameResponse comunica cosa verra' fatto successivamente. 
				 
 - Player (model): rappresenta un giocatore e contiene tutti i dati (le griglie e la collezione
		   delle unita' navali) aggiornati del gioco


## Note sull'uso delle eccezioni e GameResponse
Nel progetto e' stato fatto un uso ristretto delle eccezioni, privilegiando invece la GameResponse.
In particolare sono state usate solamente nel caso di comando o coordinate della griglia inserite 
dall'utente non valide. Il controller GameManager contiene il blocco try catch per catturarle 
e per creare un oggetto GameResponse appropriato. Non e' necessario quindi inserire blocchi try-catch
del main, che giustamente, non conosce le eccezioni gestite internamente dal gioco ma si basa solamente
sulla GameResponse.
Oltre al motivo strutturale, e' stata scelto di utilizzare il meno possibile le eccezioni per il fatto 
che sono onerose (computazionalmente) da gestire.
