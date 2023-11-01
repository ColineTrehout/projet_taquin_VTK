#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextActor.h>

#include "creationTexte.hpp"
#include "mecaniqueJeu2D.hpp"
#include "mecaniqueJeu3D.hpp"
#include "observateur.hpp"




int Observer::nombreDeplacements() 
{ 
    return _compteurDeplacements;
}

void Observer::SetRenderer(vtkRenderer* renderer) 
{ 
    _renderer = renderer; 
}

void Observer::SetCommandesTexte(vtkTextActor* textCommandes) 
{
    _texteCommandes = textCommandes;
}

void Observer::SetGrilleJeu(const std::vector<std::vector<int>>& grille) 
{
    _grille = grille;
}

void Observer::SetLigneCaseVide2D(const int& xVide) 
{
    _xVide2D = xVide;
}

void Observer::SetColonneCaseVide2D(const int& yVide) 
{
    _yVide2D = yVide;
}

void Observer::SetLigneCaseVide3D(const int& xVide) 
{
    _xVide3D = xVide;
}

void Observer::SetColonneCaseVide3D(const int& yVide) 
{
    _yVide3D = yVide;
}

void Observer::SetNbMelanges(const int& nbMelanges)
{
    _nbMelanges = nbMelanges;
}

void Observer::SetPlateau(const std::vector<std::vector<vtkSmartPointer<vtkActor>>>&  plateau) 
{
    _plateau = plateau;
}



void Observer::Execute(vtkObject* caller, unsigned long, void*)
{
	auto* interactor{ vtkRenderWindowInteractor::SafeDownCast(caller) };
    int direction{};


    // Déplacement des pièces uniquement possible si le jeu n'est pas déjà résolu
    if (!(verifVictoire(_grille, _tailleGrille)))
    {
        _renderer-> RemoveActor(_texteNouvellePartie);

        // Déplacement d'une pièce vers le bas
        if (interactor->GetKeyCode() == 's' && _xVide3D < 3)
        {
            direction = 0;

            // Mise à jour de la grille 3D et des coordonnées de la case vide
            deplacePiece3D(_plateau, _xVide3D, _yVide3D, direction);

            // Mise à jour de la grille 2D et des coordonnées de la case vide
            deplacePiece2D(_grille, _tailleGrille, _xVide2D, _yVide2D, 0);

            _compteurDeplacements++;

        }

        // Déplacement d'une pièce vers le haut
        if (interactor->GetKeyCode() == 'z' && _xVide3D > 0)
        {
            direction = 1;

            // Mise à jour de la grille 3D et des coordonnées de la case vide
            deplacePiece3D(_plateau, _xVide3D, _yVide3D, direction);

            // Mise à jour de la grille 2D et des coordonnées de la case vide
            deplacePiece2D(_grille, _tailleGrille, _xVide2D, _yVide2D, 1);

            _compteurDeplacements++;
        }

        // Déplacement d'une pièce vers la droite
        if (interactor->GetKeyCode() == 'd' && _yVide3D > 0)
        {
            direction = 2;

            // Mise à jour de la grille 3D et des coordonnées de la case vide
            deplacePiece3D(_plateau, _xVide3D, _yVide3D, direction);

            // Mise à jour de la grille 2D et des coordonnées de la case vide
            deplacePiece2D(_grille, _tailleGrille, _xVide2D, _yVide2D, 2);

            _compteurDeplacements++;
        }
        
        // Déplacement d'une pièce vers la gauche
        if (interactor->GetKeyCode() == 'q' && _yVide3D < 3)
        {
            direction = 3;

            // Mise à jour de la grille 3D et des coordonnées de la case vide
            deplacePiece3D(_plateau, _xVide3D, _yVide3D, direction);

            // Mise à jour de la grille 2D et des coordonnées de la case vide
            deplacePiece2D(_grille, _tailleGrille, _xVide2D, _yVide2D, 3);

            _compteurDeplacements++;
        }

        if (verifVictoire(_grille, _tailleGrille))
        {
            _texteFinJeu = texteVictoire(_compteurDeplacements);
            _renderer->AddActor(_texteFinJeu);

            std::cout << "\nVous avez gagné ! Vous avez fini le jeu en " 
                      << _compteurDeplacements 
                      << " déplacement(s).\n";
        }
    }

    // Rejouer une partie
    if (verifVictoire(_grille, _tailleGrille) and interactor->GetKeyCode() == 'r')
    {

        int i{};

        _renderer-> RemoveActor(_texteFinJeu);

        _texteNouvellePartie = texteNouvellePartie();
        _renderer->AddActor(_texteNouvellePartie);


        srand(time(NULL)); // Pour générer des valeurs aléatoires

        while (i < _nbMelanges) // _nbMelanges déplacements aléatoires
        {
            direction = rand() % 4; //4 valeurs possibles (de 0 à 3)

            deplacePiece2D(_grille, _tailleGrille, _xVide2D, _yVide2D, direction);

            deplacePiece3D(_plateau, _xVide3D, _yVide3D, direction);

            _compteurDeplacements = 0;

            i++;
        }

    }


    // Quitter le jeu
    if (interactor->GetKeyCode() == 'e')
	{
		std::cout << "\nFin du jeu.\n";

        exit(0);
	}

	interactor->Render();
}