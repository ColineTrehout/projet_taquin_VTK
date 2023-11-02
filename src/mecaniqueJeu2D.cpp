#include <iostream>
#include <vector>
#include <string>  

#include "mecaniqueJeu2D.hpp"



/*
afficheGrille affiche la grille de jeu 2D dans le terminal

Arguments :
    grille : grille de jeu 2D (contient les entiers de 0 à 15, 0 étant la case vide)
	tailleGrille : taille de la grille 2D

Retour :
    void
*/
void afficheGrille(const std::vector<std::vector<int>>& grille, const int& tailleGrille)
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



/*
afficheGrille mélange la grille 2D avec un nombre maximum de déplacements égal
à nbMelanges à partir de la configuration finale

Arguments :
    grille : grille de jeu 2D (contient les entiers de 0 à 15, 0 étant la case vide)
	xVide : ligne de la case vide
	yVide : colonne de la case vide
	nbMelanges : nombre maximum de déplacements effectués pour mélanger la grille

Retour :
    void
*/
void melangeGrille(std::vector<std::vector<int>>& grille, 
                   const int& tailleGrille, 
                   int& xVide, 
                   int& yVide, 
                   const int& nbMelanges)
{
	int i{}, direction{};

	srand(time(NULL)); // Pour générer des valeurs aléatoires

	while (i < nbMelanges) // nbMelanges déplacements aléatoires
	{
		direction = rand() % 4; // 4 valeurs possibles (de 0 à 3)

		deplacePiece2D(grille, tailleGrille, xVide, yVide, direction);

        ++i;
	}
}



/*
deplacePiece2D déplace une pièce selon la direction choisie et met à jour les 
coordonnées de la case vide (si le mouvement n'est pas valide car en bordure
de la grille aucune action n'est faite)

Arguments :
    grille : grille de jeu 2D (contient les entiers de 0 à 15, 0 étant la case vide)
	tailleGrille : taille de la grille
	xVide : ligne de la case vide
	yVide : colonne de la case vide
	direction : direction dans laquelle la pièce est déplacée

Retour :
    void
*/
void deplacePiece2D(std::vector<std::vector<int>>& grille, 
                  const int& tailleGrille, 
                  int& xVide, 
                  int& yVide, 
                  const int& direction)
{
    int stock{};

        // Déplacement d'une pièce vers le bas
		if ((direction == 0) && (xVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide] = grille[xVide - 1][yVide];
			grille[xVide - 1][yVide] = stock;
			--xVide;
		}

        // Déplacement d'une pièce vers le haut
		if ((direction == 1) && (xVide < tailleGrille-1)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide + 1][yVide];
			grille[xVide + 1][yVide] = stock;
			++xVide;
		}

        // Déplacement d'une pièce vers la droite
		if ((direction == 2) && (yVide > 0)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide-1];
			grille[xVide][yVide-1] = stock;
			--yVide;
		}

        // Déplacement d'une pièce vers la gauche
		if ((direction == 3) && (yVide < tailleGrille-1)) 
		{
			stock = grille[xVide][yVide];
			grille[xVide][yVide]  = grille[xVide][yVide+1];
			grille[xVide][yVide+1] = stock;
			++yVide;
		}
}



/*
verifVictoire vérifie si la grille 2D est dans la configuration finale 
(victoire du jeu)

Arguments :
    grille : grille de jeu 2D (contient les entiers de 0 à 15, 0 étant la case vide)
	tailleGrille : taille de la grille

Retour :
    victoire : booléen indiquant la victoire du joueur
*/
bool verifVictoire(const std::vector<std::vector<int>>& grille, const int& tailleGrille)
{
    bool victoire = true;
    int k = 1;

    for(int i{}; i < tailleGrille; i++)
	{
		for(int j{}; j < tailleGrille; j++)
		{
            // Vérifie si les nombres sont ordonnées par ordre croissant (sauf la dernière)
			if(grille[i][j] != k && (i != (tailleGrille-1) || j != (tailleGrille-1))) 
            {
                victoire = false;
            }
			++k;
		}
	}

    // Vérifie si la dernière case est vide
	if(grille[tailleGrille-1][tailleGrille-1] != 0) 
    {
        victoire = false;
    }

    return victoire;
}

