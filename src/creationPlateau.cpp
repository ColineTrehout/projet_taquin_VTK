#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>


#include "creationPlateau.hpp"


// Création des bords du plateau de jeu
vtkSmartPointer<vtkActor> creationBords(const float& xLenght,
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



