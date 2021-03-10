#include "grille.h"

int Grille::getRow(){
	return _m;
}
int Grille::getColumn(){
	return _n;
}

void Grille::afficher(){
	for (int i = 0; i < grille.size(); i++) { 
        for (int j = 0; j < grille[i].size(); j++){ 
            	if(grille[i][j]){
					std::cout << "0" << " ";
				}
				else{
					std::cout << "_" << " ";
				}
		}
	std::cout << std::endl;
  	}
   	std::cout << "______________________"<<std::endl; 	
}

void Grille::AjouteCellule(int i, int j){
	grille[i][j] = 1;
}

void Grille::SupprimeCellule(int i, int j){
	grille[i][j] = 0;
}

int Grille::estOccupee(int i, int j){
	return grille[i][j];
}

int Grille::nbVoisins(int i, int j){
	int sum = 0;
	for(int k = i-1;k<=i+1;k++){
		for(int l = j-1;l<=j+1;l++){
			if((k == i && l == j) || (k<0) || (k>=_m) || (l<0) || (l>=_n)){}
			else{
				if(grille[k][l]){
				 	sum++;
				}
			}
		}
	}
	return sum;
}
