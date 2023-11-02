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



/*
texteCommandes crée un acteur de texte correspondant aux commandes clavier
du jeu

Arguments :
    void

Retour :
    textActor : acteur texte des commandes
*/
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

    textActor->SetPosition(30, 700);

    return textActor;
}



/*
texteVictoire crée un acteur de texte correspondant au message qui s'affiche
en cas de victoire

Arguments :
    compteurDeplacements : nombre de déplacements qui ont été effectués pour
                           résoudre le puzzle

Retour :
    textActor : acteur texte du message de victoire
*/
vtkNew<vtkTextActor> texteVictoire(const int& compteurDeplacements)
{
    const std::string s = "Félicitations, vous avez résolu le puzzle en " 
                    + std::to_string(compteurDeplacements) + 
                    " coup(s) !\n";

    vtkNew<vtkTextActor> textActor;

    textActor->SetInput(s.c_str());

    auto prop = textActor->GetTextProperty();

    //textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetTextScaleModeToViewport();
    textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(8);
    textActor->GetTextProperty()->SetColor(0.9,0.9,0.9);

    // Position du texte : (colonne, ligne) avec origine en bas à gauche
    textActor->SetPosition(510, 900);

    return textActor;
}



/*
texteNouvellePartie crée un acteur de texte correspondant au démarrage d'une
nouvelle partie

Arguments :
    void

Retour :
    textActor : acteur texte du message pour le redémarrrage d'une partie
*/
vtkNew<vtkTextActor> texteNouvellePartie()
{
    vtkNew<vtkTextActor> textActor;

    textActor->SetInput("Nouvelle partie");

    auto prop = textActor->GetTextProperty();

    //textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetTextScaleModeToViewport();
    textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(8);
    textActor->GetTextProperty()->SetColor(0.9,0.9,0.9);

    // Position du texte : (colonne, ligne) avec origine en bas à gauche
    textActor->SetPosition(800, 910);

    return textActor;
}
