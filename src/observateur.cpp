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
            vtkNew<vtkTextActor> textFinJeu;

            textFinJeu = texteVictoire(_compteurDeplacements);
            _renderer->AddActor(textFinJeu);

            std::cout << "\nVous avez gagné ! Vous avez fini le jeu en " 
                      << _compteurDeplacements 
                      << " déplacement(s).\n";
        }
    }

    // Si le puzzle est résolu
    else
    {
        vtkNew<vtkTextActor> textFinJeu;

        textFinJeu = texteVictoire(_compteurDeplacements);

        // Affichage du texte de victoire
        _renderer->AddActor(textFinJeu);
    }

    // Quitter le jeu
    if (interactor->GetKeyCode() == 'e')
	{
		std::cout << "\nFin du jeu\n";

        exit(0);
	}

	interactor->Render();
}