#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>


#include "creationPlateau.hpp"


// creation des bords du plateau de jeu
vtkSmartPointer<vtkActor> creationBords(float xLenght,
                                                float yLenght,
                                                float zLength,
                                                float xRotate,
                                                float yRotate,
                                                float zRotate,
                                                float xPosition,
                                                float yPosition,
                                                float zPosition)
{
    vtkSmartPointer<vtkCubeSource> plaque = vtkSmartPointer<vtkCubeSource>::New();

    // Dimensions du rectangle
    plaque->SetXLength(xLenght);
    plaque->SetYLength(yLenght);
    plaque->SetZLength(zLength);

    plaque->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

    actor->GetProperty()->SetColor(0.25,0.25,0.25); // marron

    actor->RotateX(xRotate);
    actor->RotateY(yRotate);
    actor->RotateZ(zRotate);

    actor->SetPosition(xPosition, yPosition, zPosition);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    actor->SetMapper(mapper);

    mapper->SetInputData(plaque->GetOutput());

    return actor;
}



