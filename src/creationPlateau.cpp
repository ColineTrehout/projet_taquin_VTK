#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include "creationPlateau.hpp"



/*
creationBord crée un bord du plateau de jeu

Arguments :
    xLenght : largeur du polyèdre
    yLenght : longueur du polyèdre
    zLength : épaisseur du polyèdre
    xRotate : rotation du polyèdre en x
    yRotate : rotation du polyèdre en y
    zRotate : rotation du polyèdre en z
    xPosition : décalage position en x
    yPosition : décalage position en y
    zPosition : décalage position en z

Retour :
    actor : acteur du polyèdre du bord
*/
vtkSmartPointer<vtkActor> creationBord(const float& xLenght,
                                        const float& yLenght,
                                        const float& zLength,
                                        const float& xRotate,
                                        const float& yRotate,
                                        const float& zRotate,
                                        const float& xPosition,
                                        const float& yPosition,
                                        const float& zPosition)
{
    vtkSmartPointer<vtkCubeSource> plaque = vtkSmartPointer<vtkCubeSource>::New();

    // Dimensions du rectangle
    plaque->SetXLength(xLenght);
    plaque->SetYLength(yLenght);
    plaque->SetZLength(zLength);

    plaque->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

    actor->GetProperty()->SetColor(0.25,0.25,0.25); // marron

    // Rotation
    actor->RotateX(xRotate);
    actor->RotateY(yRotate);
    actor->RotateZ(zRotate);

    // Translation
    actor->SetPosition(xPosition, yPosition, zPosition);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    actor->SetMapper(mapper);

    mapper->SetInputData(plaque->GetOutput());

    return actor;
}



/*
creationActeurPiece crée un acteur cube correspondant à une pièce du jeu et le 
place à sa position sur la grille

Arguments :
    pieces : tableau 2D contenant les pièces 3D du jeu
    mapper : mapper des pièces
    i : ligne
    j : colonne

Retour :
    void
*/
void creationActeurPiece(std::vector<std::vector<vtkSmartPointer<vtkActor>>>& pieces,
                          const vtkSmartPointer<vtkPolyDataMapper>& mapper,
                          const int& i,
                          const int& j)
{

    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

    pieces[i][j] = cubeActor;
    pieces[i][j]->SetMapper(mapper);
    pieces[i][j]->SetPosition(i, j, 0.0); // Position de la pièce sur la grille
}



