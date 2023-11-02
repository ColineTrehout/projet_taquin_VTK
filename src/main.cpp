#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkCubeSource.h>
#include <vtkFreeTypeTools.h>
#include <vtkImageActor.h>
#include <vtkImageBlend.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageReader.h>
#include <vtkImageReader2Factory.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStdString.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTexture.h>
#include <vtkTransformTextureCoords.h>
#include <vtkVectorText.h>

#include <iostream>
#include <string> 
#include <unistd.h>
#include <vector>

#include "creationPlateau.hpp"
#include "creationTexte.hpp"
#include "mecaniqueJeu2D.hpp"
#include "observateur.hpp"



int main()
{
    std::cout << "Bienvenue dans ce jeu de taquin !\n\nPour résoudre le puzzle,"
                 " vous devez replacer les pièces dans l'ordre croissant en"
                 " partant du coin supérieur gauche. Le coin inférieur droit"
                 " doit rester vide.\n\n";


    //-------------------------------------------------------------------------
    // DÉCLARATIONS

    
    // Définition taille de la grille (4x4 pour le jeu de taquin classique)
    const int tailleGrille = 4; 

    // Épaisseur du plateau de jeu
    const float epaisseurPlateau = 0.4;

    // Création de la grille dans laquelle on va mettre les pieces 3D du jeu
    std::vector<std::vector<vtkSmartPointer<vtkActor>>> pieces(tailleGrille, std::vector <vtkSmartPointer<vtkActor>>(tailleGrille));

    // Création de la grille 2D (tableau d'entiers contenant les nombres de 0 à 15 (0 : case vide))
    std::vector<std::vector<int>> grille
    { 
        {1, 2, 3, 4}, 
        {5, 6, 7, 8}, 
        {9, 10, 11, 12},
        {13, 14, 15, 0} 
    };

    // Coordonnées de la case vide pour la grille 2D (origine en haut à gauche)
    int xVide2D = 3;
    int yVide2D = 3;

    // Coordonnées de la case vide pour le jeu 3D (origine en bas à gauche)
    int xVide3D = 0;
    int yVide3D = 3;

    // Niveau du jeu allant de facile à expert
    int niveau{};

    // Nombre de mélanges de la grille déterminant la difficulté du jeu
    int nbMelanges{};


    //-------------------------------------------------------------------------
    
    // SAISIE DU NIVEAU DE DIFFICULTÉ


    // Saisie du niveau de difficulté par le joueur (influence le nombre de
    // déplacements à réaliser pour finir le puzzle)
    std::cout << "Veuillez saisir le niveau de difficulté souhaité :\n"
                 "0 : niveau facile\n"
                 "1 : niveau moyen\n"
                 "2 : niveau difficile\n"
                 "3 : niveau expert\n";

    std::cin >> niveau;

    // Vérification de la validité de la saisie
    while (std::cin.fail() || (niveau != 0 && niveau != 1 && niveau != 2 && niveau != 3))
    {
        // Nettoyage du buffer d'entrée
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Saisie invalide, veuillez entrer 0, 1, 2 ou 3\n";
        std::cin >> niveau;
    }

    if (niveau == 0)
    {
        std::cout << "Vous avez choisi le niveau facile.\n";
        nbMelanges = tailleGrille*tailleGrille;
    }
    else if(niveau == 1)
    {
        std::cout << "Vous avez choisi le niveau moyen.\n";
        nbMelanges = 5*tailleGrille*tailleGrille;
    }
    else if(niveau == 2)
    {
        std::cout << "Vous avez choisi le niveau difficile.\n";
        nbMelanges = 100*tailleGrille*tailleGrille;
    }
    else
    {
        std::cout << "Vous avez choisi le niveau expert. Bonne chance.\n";
        nbMelanges = 200*tailleGrille*tailleGrille;
    }

    //-------------------------------------------------------------------------

    // MÉLANGE DE LA GRILLE (position initiale du jeu)


    // Mélange de la grille de jeu en opérant un certain nombre de déplacements 
    // à partir de la configuration initiale pour être sûr que 
    // le puzzle soit solvable
    melangeGrille(grille, tailleGrille, xVide2D, yVide2D, nbMelanges);

    //-------------------------------------------------------------------------
    
    // FENÊTRE DE RENDU


    // Création du moteur de rendu et de la fenêtre de rendu
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    // Réglage de la taille de la fenêtre
    renderWindow->SetSize(1920,1080);

    // Création d'un window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderWindowInteractor->SetRenderWindow(renderWindow);

    //-------------------------------------------------------------------------

    // CRÉATION DES PIÈCES 3D


    int numeroPiece = 0;


    // L'origine du repère 3D se trouve en bas à gauche et les lignes et colonnes sont inversées
    for (int j = tailleGrille-1; j >= 0; j--) 
    {
        for (int i{}; i < tailleGrille; i++) 
        {

            // Création d'un cube par case
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

            cubeSource -> SetZLength(epaisseurPlateau);

            // Numéro de la grille 2D pour chaque pièce 3D
            numeroPiece = grille[-(j-3)][i];

            // Simulation de la case vide
            if (numeroPiece == 0)
            {
                // Épaisseur plus faible pour simuler la case vide
                cubeSource -> SetZLength(0.1);

                // Déplacement du centre du cube
                cubeSource -> SetCenter(0,0,-0.15); 

                // Coordonnées de la case vide au début du jeu
                xVide3D = j;
                yVide3D = i;
            }

            // Met à jour la source du cube
            cubeSource->Update(); 

            mapper->SetInputData(cubeSource->GetOutput());

            // Crée un acteur par pièce et les ajoute dans pieces
            creationActeurPiece(pieces, mapper, i, j);

            //-------------------------------------------------------------------------

            //  TEXTURE


            vtkNew<vtkImageReader2Factory> readerFactory;
            vtkSmartPointer<vtkImageReader2> imageReader;
            std::string imagePath;
            vtkNew<vtkTexture> texture;

            // Chemin pour accéder aux images contenant la texture de chaque pièce
            if (niveau == 3)
            {
                imagePath = "images/wood/" + std::to_string(numeroPiece) + ".jpg";
            }
            else
            {
                imagePath = "images/numbers/" + std::to_string(numeroPiece) + ".jpg";
            }

            // Application de la texture sur la pièce
            imageReader.TakeReference(readerFactory->CreateImageReader2(imagePath.c_str()));
            imageReader->SetFileName(imagePath.c_str());
            texture->SetInputConnection(imageReader->GetOutputPort());
            pieces[i][j]->SetTexture(texture);
        }
    }
    
    //-------------------------------------------------------------------------
    
    // TEXTE POUR LES COMMANDES DU JEU


    // Configuration du texte pour l'affichage des commandes du jeu
    vtkNew<vtkTextActor> textActor;
    textActor = texteCommandes();

    //-------------------------------------------------------------------------

    // CRÉATION PLATEAU DE JEU


    // Création des bords du plateau de jeu
    vtkSmartPointer<vtkActor> bordArriere = vtkSmartPointer<vtkActor>::New();
    bordArriere = creationBord(4, 4, 0.01, 0, 0, 0, 1.5, 1.5, -epaisseurPlateau/2);

    vtkSmartPointer<vtkActor> bordGauche = vtkSmartPointer<vtkActor>::New();
    bordGauche = creationBord(4, epaisseurPlateau, 0.01, 0, 90, 90, -0.5, 1.5, 0);

    vtkSmartPointer<vtkActor> bordDroit = vtkSmartPointer<vtkActor>::New();
    bordDroit = creationBord(4, epaisseurPlateau, 0.01, 0, 90, 90, 3.5, 1.5, 0);

    vtkSmartPointer<vtkActor> bordHaut = vtkSmartPointer<vtkActor>::New();
    bordHaut = creationBord(4, epaisseurPlateau, 0.01, 90, 0, 0, 1.5, 3.5, 0);

    vtkSmartPointer<vtkActor> bordBas = vtkSmartPointer<vtkActor>::New();
    bordBas = creationBord(4, epaisseurPlateau, 0.01, 90, 0, 0, 1.5, -0.5, 0);

    //-------------------------------------------------------------------------

    // RENDU


    // Ajout des acteurs des pièces au rendu
    for (int i{}; i < tailleGrille; i++) 
    {
        for (int j{}; j < tailleGrille; j++) 
        {
            renderer->AddActor(pieces[i][j]);
        }
    }

    // Ajout au rendu des éléments du plateau de jeu 
    renderer->AddActor(bordArriere);
    renderer->AddActor(bordGauche);
    renderer->AddActor(bordDroit);
    renderer->AddActor(bordHaut);
    renderer->AddActor(bordBas);

    // Ajout du texte au rendu
    renderer->AddActor(textActor);

    // Définition de la couleur de l'arrière plan
    renderer->SetBackground(0.3, 0.3, 0.5); 

    // Définition du nom de la fenêtre de rendu
    renderWindow->SetWindowName("Jeu de taquin");

    renderWindow->AddRenderer(renderer);

    //-------------------------------------------------------------------------

    // INTÉRACTEUR


	// Création de l'intéracteur
	vtkNew<vtkRenderWindowInteractor> interactor;

    // Supprime les intéractions par défaut
    interactor->SetInteractorStyle(nullptr);
	
    interactor->SetRenderWindow(renderWindow);

    //-------------------------------------------------------------------------

    // OBSERVATEUR


	// Création de l'observateur
	vtkNew<Observer> observer;

    observer->SetRenderer(renderer);
    observer->SetCommandesTexte(textActor);

    observer->SetNbMelanges(nbMelanges);

    // Configuration des plateaux de jeu
    observer->SetGrilleJeu(grille);
    observer->SetPlateau(pieces);

    // Configuration des coordonnées de la case vide de la grille 2D
    observer->SetLigneCaseVide2D(xVide2D);
    observer->SetColonneCaseVide2D(yVide2D);

    // Configuration des coordonnées de la case vide de la grille 3D
    observer->SetLigneCaseVide3D(xVide3D);
    observer->SetColonneCaseVide3D(yVide3D);

	interactor->AddObserver(vtkCommand::KeyPressEvent, observer);

	interactor->Initialize();

	interactor->Start();


    return EXIT_SUCCESS;
}
