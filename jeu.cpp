#include "jeu.h"

void Jeu::Avance(){
	int m = grille.getRow();
	int n = grille.getColumn();
	
	// On doit recopier la grille pour faire des comparaisons 
	Grille prev_grille = grille;
	int nb_voisins = 0;
	
	// On va faire un boucle sur prev_grille et mettre a jour l'etat de chaque cellule dans grille
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			// Si la cellule est vivante, elle reste vivante ssi elle a 2 ou 3 voisines, sinon elle devient morte
			if(prev_grille.estOccupee(i,j)){
				nb_voisins = prev_grille.nbVoisins(i,j);
				if(nb_voisins != 2 && nb_voisins != 3){
					grille.SupprimeCellule(i,j);
				}
			}
			else{
			// Si la grille est morte, elle devient ssi elle a 3 voisines, sinon elle reste morte
				nb_voisins = prev_grille.nbVoisins(i,j);
				if(nb_voisins == 3){
					grille.AjouteCellule(i,j);
				}
			}
		}
	}
}

void Jeu::AjouteCellule(int i, int j){
	grille.AjouteCellule(i,j);
}
void Jeu::SupprimeCellule(int i, int j){
	grille.SupprimeCellule(i,j);
}
void Jeu::afficher(){
	grille.afficher();
}
		
int Jeu::getRow(){
	return grille.getRow();
}

int Jeu::getColumn(){
	return grille.getColumn();
}

int Jeu::estOccupee(int i, int j){
	return grille.estOccupee(i,j);
}
