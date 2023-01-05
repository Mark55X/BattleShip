Readme.txt file
by Anna Albertin, Giulia Selvestrel, Marco Stefani

## Note sulla struttura del progetto
La struttura del progetto si basa su una semplificazione del pattern di progettazione software 
chiamato MVC (Model-View-Controller). 
I ruoli dei file sono:
 - Main (view): ha il ruolo di inviare i dati (ovvero i comandi per l'inserimento delle unit� navali, l'esecuzione
		  di azioni e comandi speciali) al CONTROLLER (GameManager) e di visualizzare le risposte. 
		  E' l'unico file (insieme a replay.cpp) che contiene quindi gestione di stream di input e output. 

 - GameManager (controller): � il controller per la gestione del gioco. Riceve i comandi, li valida e li esegue. 
				 Le sue funzioni restituiscono quasi sempre una GameResponse (vedere game_response.h) 
				 che indica lo stato di esecuzione del comando e altre informazioni (esempio: se � il turno
				 del giocatore successivo oppure � ancora quello del giocatore che ha eseguito l'ultimo comando).
				 Si capisce quindi la netta separazione tra Main e GameManager: � quest'ultimo che tramite
				 la GameResponse comunica cosa verr� fatto successivamente. 
				 
 - Player (model): rappresenta un giocatore e contiene tutti i dati (le griglie e la collezione
				   delle unit� navali) aggiornati del gioco

## Note sull'uso delle eccezioni e GameResponse
Nel progetto � stato fatto un uso ristretto delle eccezioni, privilegiando invece la GameResponse.
In particolare sono state usate solamente nel caso di comando o coordinate della griglia inserite 
dall'utente non valide. Il controller GameManager contiene il blocco try catch per catturarle 
e per creare un oggetto GameResponse appropriato. Non � necessario quindi inserire blocchi try-catch
del main, che giustamente, non conosce le eccezioni gestite internamente dal gioco ma si basa solamente
sulla GameResponse.
Oltre al motivo strutturale, � stata scelto di utilizzare il meno possibile le eccezioni per il fatto 
che sono onerose (computazionalmente) da gestire.
