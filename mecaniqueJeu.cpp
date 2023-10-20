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



bool deplacePiece(std::vector<std::vector<int>>& grille, 
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



/*

// la case choisie est déplacée
void deplacePiece(int **M, int n, int *x, int *y, int x2, int y2)
{
    int sauv;
    sauv=M[*x][*y];
    M[*x][*y]=M[x2][y2];
    M[x2][y2]=sauv;
}



//le joueur choisit la case à déplacer
void choixDeplacement(int **M, int n, int *i, int *j)
{
    char choix;
    int coord;
   //menu pour le déplacement d'une case
	printf("Veuillez choisir une option de déplacement d'une case :\n\n");
	printf("g : déplacement d'une case vers la gauche\n");
	printf("d : déplacement d'une case vers la droite\n");
    printf("h : déplacement d'une case vers le haut\n");
    printf("b : déplacement d'une case vers le bas\n");
    printf("q : quitter le jeu\n");
	printf("\nVotre choix : ");

    choix=getchar(); //saisie du déplacement
	switch(choix)
	{

		case 'g': //déplacer la case vers la gauche
        coord=*j+1; //coord est la colonne de la case à déplacer
        if(coord<n && coord>=0) //si on peut déplacer la case vers la gauche
        {
            deplacePiece(M,n,i,j,*i,coord);
            *j=coord; //mise à jour du j de la case vide
        }
        else
        {
            printf(" /!\\ impossible de déplacer une case vers la gauche\n");
        }
		break;
		case 'd': //déplacer la case vers la droite
        coord=*j-1; //coord est la colonne de la case à déplacer 
        if(coord<n && coord>=0) //si on peut déplacer la case vers la droite
        {
            deplacePiece(M,n,i,j,*i,coord);
            *j=coord; //mise à jour du j de la case vide
        }
        else
        {
            printf(" /!\\ impossible de déplacer une case vers la droite\n");
        }
		break;
        case 'h': //déplacer la case vers le haut
        coord=*i+1; //coord est la ligne de la case à déplacer
        if(coord<n && coord>=0) //si on peut déplacer la case vers le haut
        {
            deplacePiece(M,n,i,j,coord,*j);
            *i=coord; //mise à jour du i de la case vide
        }
        else
        {
            printf(" /!\\ impossible de déplacer une case vers le haut\n");
        }
		break;
        case 'b': //déplacer la case vers le bas
        coord=*i-1; //coord est la ligne de la case à déplacer
        if(coord<n && coord>=0) //si on peut déplacer la case vers le bas
        {
            deplacePiece(M,n,i,j,coord,*j);
            *i=coord; //mise à jour du i de la case vide
        }
        else
        {
            printf(" /!\\ impossible de déplacer une case vers le bas\n");
        }
        break;
        case 'q': //pour quitter le jeu
        printf("Fin du jeu\n");
        exit(0);
        break;
		default: //autre cas
		printf("Erreur de saisie\n");
		exit(0);
		break;
	} 
}
*/
