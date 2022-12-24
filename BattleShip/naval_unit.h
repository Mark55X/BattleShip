// NavalUnit Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef naval_unit_h
#define naval_unit_h

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe virtuale pura NavalUnit
	// Rappresenta un unità navale all'interno del gioco
	// Possiede :
	//   1. Una grandezza (size), ovvero il numero di caselle nella griglia di gioco
	//   2. Scuda (shield), ovvero il numero di celle non ancora colpite 
	//		(inizialmente uguale a Size)
	//	 3. ???
	class NavalUnit {

	public:

		// getters
		int size() const;
		int shield() const;
		
		// Una Unità navale può compiere un'azione in base
		// al tipo di unità. Non è possibile definire tale comportamento
		// in questa classe
		virtual bool Action() const = 0;

	private:
		int size_;
		int shield_;

	};


} // namespace battle_ships

#endif // naval_unit_h
