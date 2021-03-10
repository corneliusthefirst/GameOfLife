#include <iostream>
#include <vector>
 
class Grille{
	private:
		// taille de la grille
		int _m;
		int _n;
		
		//la grille est un vecteur des vecteurs(0-cellule morte, 1-cellule vivante)
		std::vector<std::vector<int>> grille;
	public:
		Grille(int m,int n): _m(m),_n(n){
			std::vector<int> v(n,0);
			for(int i = 0;i<m;i++){
				grille.push_back(v);
			}
		}
		
		Grille(std::vector<std::vector<int>> g): grille(g){
			_m = g.size();
			_n = g[0].size();
		}
		
		int  getRow();
		int  getColumn();
		void afficher();
		void AjouteCellule(int i, int j);
		void SupprimeCellule(int i, int j);
		int  estOccupee(int i, int j);
		int  nbVoisins(int i, int j);
};
