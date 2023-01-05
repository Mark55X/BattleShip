Readme.txt file
by Anna Albertin, Giulia Selvestrel, Marco Stefani

## Note sulla struttura del progetto
La struttura del progetto si basa su una semplificazione del pattern di progettazione software 
chiamato MVC (Model-View-Controller). 
I ruoli dei file sono:
 - Main (view): ha il ruolo di inviare i dati (ovvero i comandi per l'inserimento delle unità navali, l'esecuzione
		  di azioni e comandi speciali) al CONTROLLER (GameManager) e di visualizzare le risposte. 
		  E' l'unico file (insieme a replay.cpp) che contiene quindi gestione di stream di input e output. 

 - GameManager (controller): è il controller per la gestione del gioco. Riceve i comandi, li valida e li esegue. 
				 Le sue funzioni restituiscono quasi sempre una GameResponse (vedere game_response.h) 
				 che indica lo stato di esecuzione del comando e altre informazioni (esempio: se è il turno
				 del giocatore successivo oppure è ancora quello del giocatore che ha eseguito l'ultimo comando).
				 Si capisce quindi la netta separazione tra Main e GameManager: è quest'ultimo che tramite
				 la GameResponse comunica cosa verrà fatto successivamente. 
				 
 - Player (model): rappresenta un giocatore e contiene tutti i dati (le griglie e la collezione
				   delle unità navali) aggiornati del gioco

## Note sull'uso delle eccezioni e GameResponse
Nel progetto è stato fatto un uso ristretto delle eccezioni, privilegiando invece la GameResponse.
In particolare sono state usate solamente nel caso di comando o coordinate della griglia inserite 
dall'utente non valide. Il controller GameManager contiene il blocco try catch per catturarle 
e per creare un oggetto GameResponse appropriato. Non è necessario quindi inserire blocchi try-catch
del main, che giustamente, non conosce le eccezioni gestite internamente dal gioco ma si basa solamente
sulla GameResponse.
Oltre al motivo strutturale, è stata scelto di utilizzare il meno possibile le eccezioni per il fatto 
che sono onerose (computazionalmente) da gestire.
