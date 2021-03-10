#include "grille.h"
#include <tuple>

class Jeu{
	private:
		Grille grille;
	public:
		Jeu(Grille  g): grille(g){}
		void Avance();
		void AjouteCellule(int i, int j);
		void SupprimeCellule(int i, int j);
		void afficher();
		int getRow();
		int getColumn();
		int estOccupee(int i, int j);
		
};
