#include <iostream>
#include <vector>
#include <string>  

#include "mecaniqueJeu.hpp"


/*
// initialise la grille de jeu à l'état final (nombre rangés dans l'ordre croissant
// avec la dernière case vide (0))
void initialiseGrille(std::vector<std::vector<int>> grille, int n)
{
    int i,j,k=1;
    std::cout << "Init\n";

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            grille[i][j]=k; 
            k++;
        }
    }
    grille[n-1][n-1]=0; //dernière case vide
}*/



// affiche la grille de jeu de taille n*n
void afficheGrille(const std::vector<std::vector<int>>& grille, int tailleGrille)
{
    std::cout << "\n";

	for(int i{}; i<tailleGrille; i++)
	{
		for(int j{}; j<tailleGrille; j++)
		{
			std::cout << grille[i][j] << " ";
		}
		printf("\n");
	}
	printf("\n");
}


// mélange la grille à partir de la configuration finale
void melangeGrille(std::vector<std::vector<int>>& grille, 
                   const int& tailleGrille, 
                   int& xVide, 
                   int& yVide, 
                   const int& nbMelanges)
{
	int i{}, direction{}, stock{};

	srand(time(NULL)); // pour générer des valeurs aléatoires

	while (i < nbMelanges) //nbmelange déplacements aléatoires
	{
		direction = rand() % 4; //4 valeurs possibles (de 0 à 3)

        // déplacement d'une pièce vers le bas
		if ((direction == 0) && (xVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide] = grille[xVide - 1][yVide];
			grille[xVide - 1][yVide] = stock;
			xVide += - 1;
		}

        // déplacement d'une pièce vers le haut
		if ((direction == 1) && (xVide < 3)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide + 1][yVide];
			grille[xVide + 1][yVide] = stock;
			xVide += 1;
		}

        // déplacement d'une pièce vers la droite
		if ((direction == 2) && (yVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide-1];
			grille[xVide][yVide-1] = stock;
			yVide += -1;
		}

        // déplacement d'une pièce vers la gauche
		if ((direction == 3) && (yVide < 3)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide+1];
			grille[xVide][yVide+1] = stock;
			yVide += 1;
		}
        i++;
	}
}


// déplace une pièce selon la direction choisie
void deplacePiece(std::vector<std::vector<int>>& grille, 
                  const int& tailleGrille, 
                  int& xVide, 
                  int& yVide, 
                  const int& direction)
{
    int stock{};

        // déplacement d'une pièce vers le bas
		if ((direction == 0) && (xVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide] = grille[xVide - 1][yVide];
			grille[xVide - 1][yVide] = stock;
			xVide += - 1;
		}

        // déplacement d'une pièce vers le haut
		if ((direction == 1) && (xVide < 3)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide + 1][yVide];
			grille[xVide + 1][yVide] = stock;
			xVide += 1;
		}

        // déplacement d'une pièce vers la droite
		if ((direction == 2) && (yVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide-1];
			grille[xVide][yVide-1] = stock;
			yVide += -1;
		}

        // déplacement d'une pièce vers la gauche
		if ((direction == 3) && (yVide < 3)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide+1];
			grille[xVide][yVide+1] = stock;
			yVide += 1;
		}
}



// vérifie si la grille est dans la configuration finale (victoire du jeu)
bool verifVictoire(std::vector<std::vector<int>>& grille, const int& tailleGrille)
{
    bool victoire = true;
    int k = 1;


    for(int i{}; i<tailleGrille; i++)
	{
		for(int j{}; j<tailleGrille; j++)
		{
            // vérifie si les nombres sont ordonnées en ordre croissant (sauf la dernière)
			if(grille[i][j] != k && (i != (tailleGrille-1) || j != (tailleGrille-1))) 
            {
                victoire = false;
            }
			k++;
		}
	}

    // vérifie si la dernière case est vide
	if(grille[tailleGrille-1][tailleGrille-1] != 0) 
    {
        victoire = false;
    }

    return victoire;
}

