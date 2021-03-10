#include "grille.h"

int Grille::getRow()
{
	return _m;
}
int Grille::getColumn()
{
	return _n;
}

void Grille::afficher()
{
	int i = 0;
	while (i < grille.size())
	{
		int j = 0;
		while (j < grille[i].size())
		{
			if (grille[i][j])
			{
				std::cout << "0"
									<< " ";
			}
			else
			{
				std::cout << "_"
									<< " ";
			}
			j++;
		}
		std::cout << std::endl;
		i++;
	}
	std::cout << "______________________" << std::endl;
}

void Grille::AjouteCellule(int i, int j)
{
	grille[i][j] = 1;
}

void Grille::SupprimeCellule(int i, int j)
{
	grille[i][j] = 0;
}

int Grille::estOccupee(int i, int j)
{
	return grille[i][j];
}

int Grille::nbVoisins(int i, int j)
{
	int sumCount = 0;
	int counter = i - 1;
	while (counter <= i + 1)
	{
		counter++;
		int follower = j - 1;
		while (follower <= j + 1)
		{
			bool condition = (counter == i && follower == j) ||
											 (counter < 0) || (counter >= _m) ||
											 (follower < 0) || (follower >= _n);
			if (!condition)
			{
				if (grille[counter][follower])
				{
					sumCount++;
				}
			}
			follower++;
		}
	}
	return sumCount;
}
