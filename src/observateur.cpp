#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextActor.h>

#include "creationTexte.hpp"
#include "mecaniqueJeu.hpp"
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


void Observer::SetGrilleJeu(std::vector<std::vector<int>> grille) 
{
    _grille = grille;
}

void Observer::SetLigneCaseVide2D(int& xVide) 
{
    _xVide2D = xVide;
}

void Observer::SetColonneCaseVide2D(int& yVide) 
{
    _yVide2D = yVide;
}

void Observer::SetLigneCaseVide3D(int& xVide) 
{
    _xVide3D = xVide;
}

void Observer::SetColonneCaseVide3D(int& yVide) 
{
    _yVide3D = yVide;
}

void Observer::SetPlateau(std::vector<std::vector<vtkSmartPointer<vtkActor>>>  plateau) 
{
    _plateau = plateau;
}

void Observer::Execute(vtkObject* caller, unsigned long, void*)
{
	auto* interactor{ vtkRenderWindowInteractor::SafeDownCast(caller) };


    // Déplacement des pièces uniquement possible si le jeu n'est pas déjà résolu
    if (!(verifVictoire(_grille, _tailleGrille)))
    {

        // Déplacement d'une pièce vers la droite
        if (interactor->GetKeyCode() == 'd' && _yVide3D > 0)
        {
            vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

            // Déplacement des pièces
            _plateau[_yVide3D][_xVide3D]->SetPosition(_yVide3D-1, _xVide3D, 0);
            _plateau[_yVide3D-1][_xVide3D]->SetPosition(_yVide3D, _xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = _plateau[_yVide3D][_xVide3D];
            _plateau[_yVide3D][_xVide3D] = _plateau[_yVide3D-1][_xVide3D];
            _plateau[_yVide3D-1][_xVide3D] = cubeActor;

            // Mise à jour de la grille 2D et des coordonnées 2D de la case vide
            deplacePiece(_grille, _tailleGrille, _xVide2D, _yVide2D, 2);

            _yVide3D = _yVide3D - 1;

            _compteurDeplacements++;
        }
        
        // Déplacement d'une pièce vers la gauche
        if (interactor->GetKeyCode() == 'q' && _yVide3D < 3)
        {
            vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

            // Déplacement des pièces
            _plateau[_yVide3D][_xVide3D]->SetPosition(_yVide3D+1, _xVide3D, 0);
            _plateau[_yVide3D+1][_xVide3D]->SetPosition(_yVide3D, _xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = _plateau[_yVide3D][_xVide3D];
            _plateau[_yVide3D][_xVide3D] = _plateau[_yVide3D+1][_xVide3D];
            _plateau[_yVide3D+1][_xVide3D] = cubeActor;

            // Mise à jour de la grille 2D et des coordonnées 2D de la case vide
            deplacePiece(_grille, _tailleGrille, _xVide2D, _yVide2D, 3);

            _yVide3D = _yVide3D + 1;

            _compteurDeplacements++;
        }

        // Déplacement d'une pièce vers le haut
        if (interactor->GetKeyCode() == 'z' && _xVide3D > 0)
        {
            vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

            // Déplacement des pièces
            _plateau[_yVide3D][_xVide3D]->SetPosition(_yVide3D, _xVide3D-1, 0);
            _plateau[_yVide3D][_xVide3D-1]->SetPosition(_yVide3D, _xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = _plateau[_yVide3D][_xVide3D];
            _plateau[_yVide3D][_xVide3D] = _plateau[_yVide3D][_xVide3D-1];
            _plateau[_yVide3D][_xVide3D-1] = cubeActor;

            // Mise à jour de la grille 2D et des coordonnées 2D de la case vide
            deplacePiece(_grille, _tailleGrille, _xVide2D, _yVide2D, 1);

            _xVide3D = _xVide3D - 1;

            _compteurDeplacements++;
        }

        // Déplacement d'une pièce vers le bas
        if (interactor->GetKeyCode() == 's' && _xVide3D < 3)
        {
            vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

            // Déplacement des pièces
            _plateau[_yVide3D][_xVide3D]->SetPosition(_yVide3D, _xVide3D+1, 0);
            _plateau[_yVide3D][_xVide3D+1]->SetPosition(_yVide3D, _xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = _plateau[_yVide3D][_xVide3D];
            _plateau[_yVide3D][_xVide3D] = _plateau[_yVide3D][_xVide3D+1];
            _plateau[_yVide3D][_xVide3D+1] = cubeActor;

            // Mise à jour de la grille 2D et des coordonnées 2D de la case vide
            deplacePiece(_grille, _tailleGrille, _xVide2D, _yVide2D, 0);

            _xVide3D = _xVide3D + 1;

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

    else
    {
        vtkNew<vtkTextActor> textFinJeu;

        textFinJeu = texteVictoire(_compteurDeplacements);
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