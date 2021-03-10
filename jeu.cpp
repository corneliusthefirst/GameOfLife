#include "jeu.h"

void Jeu::Avance()
{
	int m = grille.getRow();
	int n = grille.getColumn();

	// On doit recopier la grille pour faire des comparaisons
	Grille pGrille = grille;
	int nbNeighbour = 0;

	// On va faire un boucle sur prev_grille et mettre a jour l'etat de chaque cellule dans grille
	int i = 0;
	while (i < m)
	{
		int j = 0;
		while (j < n)
		{
			// Si la cellule est vivante, elle reste vivante ssi elle a 2 ou 3 voisines, sinon elle devient morte
			if (pGrille.estOccupee(i, j))
			{
				nbNeighbour = pGrille.nbVoisins(i, j);
				if (nbNeighbour != 2 && nbNeighbour != 3)
				{
					grille.SupprimeCellule(i, j);
				}
			}
			else
			{
				// Si la grille est morte, elle devient ssi elle a 3 voisines, sinon elle reste morte
				nbNeighbour = pGrille.nbVoisins(i, j);
				if (nbNeighbour == 3)
				{
					grille.AjouteCellule(i, j);
				}
			}
			j++;
		}
		i++;
	}
}

void Jeu::AjouteCellule(int i, int j)
{
	grille.AjouteCellule(i, j);
}
void Jeu::SupprimeCellule(int i, int j)
{
	grille.SupprimeCellule(i, j);
}
void Jeu::afficher()
{
	grille.afficher();
}

int Jeu::getRow()
{
	return grille.getRow();
}

int Jeu::getColumn()
{
	return grille.getColumn();
}

int Jeu::estOccupee(int i, int j)
{
	return grille.estOccupee(i, j);
}
