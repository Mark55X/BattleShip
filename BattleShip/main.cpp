// Main
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "game_manager.h";

#include <iostream>

using std::cout;
using std::endl;
using battle_ships::GameManager;

/*
* Pensieri miei abbastanza profondi da scrivere nel readme.TXT
* 
* Secondo me � ESSENZIALE dividere il MAIN dal resto del progetto
* tale che si possono creare molti modi per fare il main
* senza che influisca DIRETTAMENTE nella logica del gioco.
* 
* Mi spiego meglio: perch� il main dovrebbe fare i controlli di validit� dei comandi?
* Per me non deve farli, non � il suo ruolo. Lui sa solo che � un comando, non sa 
* nemmeno cosa fa, perch� la descrizione di tale esecuzione deve essere descritta dal
* CORE del gioco che mi invier� un oggetto di tipo RESPONSE
* 
* Attenzione, parte importante perch� il RESPONSE sar� una risponsa GENERICA (non � un template attenzione :) )
* Response{
	StatusExecution : bool  -> Se avvenuto con successo o meno
	Content : string        -> Contenuto (pu� essere la string aformattata per il comando XX XX 
										  o la descrizione tipo 'Eseguito FUOCO su cella nemica A1 ')
	NextShift : bool        -> False se il turno � ancora del giocatore che ha eseguito il comando
  }
  
  QUESTO PERCHE' giustamente se io avessi i metodi che restituiscono bool cosa capirei?
  Se � false, per quale motivo � false? Coordiante fuori? Entrambe? O solo una? Oppure sono giste
  ma l'origin riguarda nessun unit� navale e per me QUESTO NON FA LO SWITCH DEL TURNO!!

  Ok quindi ha senso usare un oggetto pi� descrittivo, si ok per� perch� non usare le eccezioni?
  Tipo: InvalidCellException con la DESCRIZIONE interna di cosa � sbagliato?

  Se siamo nel caso di Logger/Replay � palese l'uso delle eccezioni: il file non esiste, problemi di scrittura
  ecc,... MA NEL GIOCO?? Forse si, forse no: bloccare l'esecuzione di colpo mi implicherebbe che non serve pi�
  la Response descritta qui sopra perch� so che se c'e un ecezzione TEORICAMENTE devo rifare il turno...
  ma se tipo mi parte un ecezzione per il Logger? Quella viene catturata da s� e quindi non influenzerebbe 
  l'andamento della partita...dovrebbe bloccare la partita? Come ? Vado a lavarmi, buon Natale a tutti.

  Abbiamo quindi: Eccezioni ->  PRO: Dati che si passano pi� leggeri(o cos� si crede)  
								CONTRO:blocco dell'esecuzione improvviso 

				  Response ->   PRO: Non c'� interruzione del flusso (forse un p� stile retro?)
								CONTRO: La gran parte delle funzioni resituiscono la response

  Attenzione che... XX XX SUCEESFUL ma non cambia turno..come faccio con ecezzioni?
					A1 B2 SUCESFUL fantastico...nesusna ecezzione ma come stampo che � avvenuta l'azione
	Quello che sto dicendo � che: io ho lo stesso risultato di Response SOLO se avviene l'eccezione. Ma 
	io magari vorrei avere il risultato anche quando non accade. OVVERO dare pi� potere al main,
	fargli capire cosa significano tali comandi... (impossibile capire l'AZIONE in s�)


*/
int main(void) 
{
	cout << "-------------------------------" << endl;
	cout << "        BATTAGLIA NAVALE       " << endl;
	cout << " Albertin, Selvestrel, Stefani " << endl;
	cout << "-------------------------------" << endl << endl << endl;

	GameManager game;
	game.ExecCommand("XX XX", GameManager::PlayerOne);

}