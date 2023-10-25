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


#include "creationTexte.hpp"


// création du texte pour l'affichage des commandes clavier du jeu
vtkNew<vtkTextActor> texteCommandes()
{
    vtkNew<vtkTextActor> textActor;

    textActor->SetInput("Commandes du jeu de taquin : \n\n" 
                        "z pour déplacer une pièce vers le haut\n"
                        "s pour déplacer une pièce vers le bas\n"
                        "q pour déplacer une pièce vers la gauche\n"
                        "d pour déplacer une pièce vers la droite\n"
                        "e pour quitter le jeu\n"
                        "r pour rejouer une partie\n");

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



// texte qui s'affiche dans la fenêtre lorsque le puzzle est résolu
vtkNew<vtkTextActor> texteVictoire()
{
    vtkNew<vtkTextActor> textActor;

    textActor->SetInput("Félicitations, vous avez résolu le puzzle !\n");

    auto prop = textActor->GetTextProperty();

    //textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetTextScaleModeToViewport();
    textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(6);
    textActor->GetTextProperty()->SetColor(0.9,0.9,0.9);

    // colonne ligne (origine en bas à gauche)
    textActor->SetPosition(700, 900);

    return textActor;
}
