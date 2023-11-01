#include <vtkActor.h>
#include <vtkSmartPointer.h>

#include "mecaniqueJeu3D.hpp"



// déplace une pièce 3D dans une certaine direction et met à jour les coordonnées de la case vide
void deplacePiece3D(std::vector<std::vector<vtkSmartPointer<vtkActor>>>&  plateau, 
                    int& xVide3D, 
                    int& yVide3D,
                    const int& direction)
{
        vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

        // Déplacement d'une pièce vers le bas
		if (direction == 0) 
		{
            // Déplacement des pièces
            plateau[yVide3D][xVide3D]->SetPosition(yVide3D, xVide3D+1, 0);
            plateau[yVide3D][xVide3D+1]->SetPosition(yVide3D, xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = plateau[yVide3D][xVide3D];
            plateau[yVide3D][xVide3D] = plateau[yVide3D][xVide3D+1];
            plateau[yVide3D][xVide3D+1] = cubeActor;

            // Mise à jour des coordonnées de la case vide
            xVide3D = xVide3D + 1;
		}

        // Déplacement d'une pièce vers le haut
		if (direction == 1) 
		{
            // Déplacement des pièces
            plateau[yVide3D][xVide3D]->SetPosition(yVide3D, xVide3D-1, 0);
            plateau[yVide3D][xVide3D-1]->SetPosition(yVide3D, xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = plateau   [yVide3D][xVide3D];
            plateau   [yVide3D][xVide3D] = plateau   [yVide3D][xVide3D-1];
            plateau   [yVide3D][xVide3D-1] = cubeActor;

            // Mise à jour des coordonnées de la case vide
            xVide3D = xVide3D - 1;
		}

        // Déplacement d'une pièce vers la droite
		if (direction == 2) 
		{
            // Déplacement des pièces
            plateau[yVide3D][xVide3D]->SetPosition(yVide3D-1, xVide3D, 0);
            plateau[yVide3D-1][xVide3D]->SetPosition(yVide3D, xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = plateau[yVide3D][xVide3D];
            plateau[yVide3D][xVide3D] = plateau[yVide3D-1][xVide3D];
            plateau[yVide3D-1][xVide3D] = cubeActor;

            // Mise à jour des coordonnées de la case vide
            yVide3D = yVide3D - 1;
		}

        // Déplacement d'une pièce vers la gauche
		if (direction == 3) 
		{
            // Déplacement des pièces
            plateau[yVide3D][xVide3D]->SetPosition(yVide3D+1, xVide3D, 0);
            plateau[yVide3D+1][xVide3D]->SetPosition(yVide3D, xVide3D, 0);

            // Changement des indices des pièces dans le puzzle en fonction de leur nouvelle position
            cubeActor = plateau[yVide3D][xVide3D];
            plateau[yVide3D][xVide3D] = plateau[yVide3D+1][xVide3D];
            plateau[yVide3D+1][xVide3D] = cubeActor;

            // Mise à jour des coordonnées de la case vide
            yVide3D = yVide3D + 1;
		}
}


