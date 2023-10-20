#include <vtkFreeTypeTools.h>
#include <vtkImageActor.h>
#include <vtkImageBlend.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkStdString.h>
#include <vtkNamedColors.h>
#include <vtkTexture.h>
#include <vtkJPEGReader.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader.h>
#include <vtkTransformTextureCoords.h>
#include <vtkCylinderSource.h>
#include <vtkTextProperty.h>
#include <vtkVectorText.h>
#include <vtkTextActor.h>

#include <iostream>


#include "affichageTexte.hpp"


vtkNew<vtkTextActor> creationTexteCommandes()
{
    vtkNew<vtkTextActor> textActor;

    textActor->SetInput("Commandes du jeu de taquin : \n\n" 
                        "pressez 'z' pour déplacer une pièce vers le haut\n"
                        "pressez 's' pour déplacer une pièce vers le bas\n"
                        "pressez 'q' pour déplacer une pièce vers la gauche\n"
                        "pressez 'd' pour déplacer une pièce vers la droite\n"
                        "pressez 'e' pour quitter le jeu\n"
                        "pressez 'r' pour rejouer une partie\n");

    auto prop = textActor->GetTextProperty();

    //textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetTextScaleModeToViewport();
    textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(5);
    textActor->GetTextProperty()->SetColor(0.9,0.9,0.9);

    textActor->SetPosition(30, 800);

    return textActor;
}

