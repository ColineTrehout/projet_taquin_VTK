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
#include <vtkPolyDataMapper.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStdString.h>
#include <vtkTextActor.h>
#include <vtkTexture.h>
#include <vtkTextProperty.h>
#include <vtkTransformTextureCoords.h>
#include <vtkVectorText.h>

#include <vector>
#include <iostream>
#include <string> 
#include <unistd.h>

#include "creationTexte.hpp"
#include "creationPlateau.hpp"
#include "mecaniqueJeu.hpp"



class Observer : public vtkCommand {
public:
	static Observer* New()
	{
		return new Observer;
	}
	void Execute(vtkObject*, unsigned long, void*);
	void SetPiece0(vtkActor* piece) { _piece0 = piece; }
	void SetPiece1(vtkActor* piece) { _piece1 = piece; }
	void SetPiece2(vtkActor* piece) { _piece2 = piece; }
	void SetPiece3(vtkActor* piece) { _piece3 = piece; }
	void SetPiece4(vtkActor* piece) { _piece4 = piece; }
	void SetPiece5(vtkActor* piece) { _piece5 = piece; }
	void SetPiece6(vtkActor* piece) { _piece6 = piece; }
	void SetPiece7(vtkActor* piece) { _piece7 = piece; }
	void SetPiece8(vtkActor* piece) { _piece8 = piece; }
	void SetPiece9(vtkActor* piece) { _piece9 = piece; }
	void SetPiece10(vtkActor* piece) { _piece10 = piece; }
	void SetPiece11(vtkActor* piece) { _piece11 = piece; }
	void SetPiece12(vtkActor* piece) { _piece12 = piece; }
	void SetPiece13(vtkActor* piece) { _piece13 = piece; }
	void SetPiece14(vtkActor* piece) { _piece14 = piece; }
	void SetPiece15(vtkActor* piece) { _piece15 = piece; }

	int nombreDeplacements() { return _compteurDeplacements;}

	void SetRenderer(vtkRenderer* renderer) { _renderer = renderer; }

    void SetCommandesTexte(vtkTextActor* textCommandes) {_texteCommandes = textCommandes;}

    void SetGrilleJeu(std::vector<std::vector<int>> grille) {_grille = grille;}

    void SetLigneCaseVide2D(int& xVide) {_xVide2D = xVide;}
    void SetColonneCaseVide2D(int& yVide) {_yVide2D = yVide;}

    void SetLigneCaseVide3D(int& xVide) {_xVide3D = xVide;}
    void SetColonneCaseVide3D(int& yVide) {_yVide3D = yVide;}

    void SetPlateau(std::vector<std::vector<vtkSmartPointer<vtkActor>>>  plateau) {_plateau = plateau;}




private:
	vtkActor* _piece0;
	vtkActor* _piece1;
	vtkActor* _piece2;
	vtkActor* _piece3;
	vtkActor* _piece4;
	vtkActor* _piece5;
	vtkActor* _piece6;
	vtkActor* _piece7;
	vtkActor* _piece8;
	vtkActor* _piece9;
	vtkActor* _piece10;
	vtkActor* _piece11;
	vtkActor* _piece12;
	vtkActor* _piece13;
	vtkActor* _piece14;
	vtkActor* _piece15;

    const int _tailleGrille = 4;

    std::vector<std::vector<vtkSmartPointer<vtkActor>>> _plateau;

    int _xVide2D{}; //ligne de la case vide de la grille 2D
    int _yVide2D{}; //colonne de la case vide de la grille 2D

    int _xVide3D{}; //ligne de la case vide de la grille 3D
    int _yVide3D{}; //colonne de la case vide de la grille 3D

    int _compteurDeplacements{}; //nombre de déplacements effectués
    vtkSmartPointer<vtkRenderer> _renderer;
    vtkSmartPointer<vtkTextActor> _texteCommandes;
    std::vector<std::vector<int>> _grille; // grille de jeu (2D)


};


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

    // Presser la touche e quitte automatiquement le jeu
    if (interactor->GetKeyCode() == 'e')
	{
		std::cout << "\nFin du jeu\n";

        exit(0);
	}


	interactor->Render();
}




int main(int, char *[])
{
    std::cout << "Bienvenue dans ce jeu de taquin.\n\n";


    // DÉCLARATIONS

    
    // Définition taille de la grille (4x4 pour le jeu de taquin classique)
    const int tailleGrille = 4; 

    // Épaisseur du plateau de jeu
    const float epaisseurPlateau = 0.4;

    // Couleurs
    vtkNew<vtkNamedColors> colors;

    // Création de la grille dans laquelle on va mettre les pieces du jeu
    std::vector<std::vector <vtkSmartPointer<vtkActor>> >  pieces (tailleGrille, std::vector <vtkSmartPointer<vtkActor>>(tailleGrille));
    //exemple(5, std::vector<int>(5));

    // Création du tableau d'entiers contenant les nombres de 0 à 15 (0 : case vide)

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

    int niveau{};
    int nbMelanges{};
    int direction{};

    // Saisie du niveau de difficulté par le joueur (influence le nombre de
    // déplacements à réaliser pour finir le puzzle)
    std::cout << "Veuillez saisir le niveau de difficulté souhaité :\n"
                 "0 : niveau facile\n"
                 "1 : niveau moyen\n"
                 "2 : niveau difficile\n";

    std::cin >> niveau;

    // check that only one letter was provided and it belongs to the valid options
    while (std::cin.fail() || (niveau != 0 && niveau != 1 && niveau != 2))
    {
        // Nettoyage du buffer d'entrée
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        std::cout << "Saisie invalide, veuillez entrer 0, 1 ou 2\n";
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
        nbMelanges = 10*tailleGrille*tailleGrille;
    }
    else
    {
        std::cout << "Vous avez choisi le niveau difficile.\n";
        nbMelanges = 100*tailleGrille*tailleGrille;
    }



    // MÉLANGE DE LA GRILLE (position initiale du jeu)

    // Mélange de la grille de jeu en opérant nbMelanges déplacements de 
    // pièces à partir de la configuration initiale pour être sûr que 
    // le puzzle soit solvable
    melangeGrille(grille, tailleGrille, xVide2D, yVide2D, nbMelanges);

    //afficheGrille(grille, tailleGrille);


    // Creation du moteur de rendu et de la fenêtre de rendu
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->SetSize(1920,1080);

    // Create a VTK render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderWindowInteractor->SetRenderWindow(renderWindow);





    //std::cout << "Coordonnées case vide : " << xVide << " " << yVide << "\n"; 

    //std::cout << "Victoire ? " << verifVictoire(grille, tailleGrille) << "\n";


    // TESTS DÉPLACEMENTS

    /*
    direction = 0;
    deplacePiece(grille, tailleGrille, xVide, yVide, direction);

    afficheGrille(grille, tailleGrille);

    std::cout << "coordonnées case vide : " << xVide << " " << yVide << "\n"; 

    direction = 2;
    deplacePiece(grille, tailleGrille, xVide, yVide, direction);

    afficheGrille(grille, tailleGrille);

    std::cout << "coordonnées case vide : " << xVide << " " << yVide << "\n"; 

    direction = 3;
    deplacePiece(grille, tailleGrille, xVide, yVide, direction);

    afficheGrille(grille, tailleGrille);

    std::cout << "coordonnées case vide : " << xVide << " " << yVide << "\n"; 

    direction = 0;
    deplacePiece(grille, tailleGrille, xVide, yVide, direction);

    afficheGrille(grille, tailleGrille);

    std::cout << "coordonnées case vide : " << xVide << " " << yVide << "\n"; 
    */

    // CRÉATION DES PIÈCES 3D

    int compteurPiece = 0;
    int numeroPiece = 0;



    // L'origine du repère 3D se trouve en bas à gauche et les lignes et colonnes sont inversées
    for (int j = tailleGrille-1; j >= 0; j--) 
    {
        for (int i{}; i < tailleGrille; i++) 
        {

            // Création d'un cube par case
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

            cubeSource -> SetZLength(epaisseurPlateau);
            //std::cout << cubeSource-> GetXLength() << '\n';

            // Numéro de la grille pour chaque pièce
            numeroPiece = grille[-(j-3)][i];


            // Épaisseur plus faible pour simuler la case vide
            if (numeroPiece == 0)
            {
                cubeSource -> SetZLength(0.1);

                //déplacement du centre du cube
                cubeSource -> SetCenter(0,0,-0.15); 

                //xVide2D = -(j-tailleGrille-1);
                //yVide2D = i;

                xVide3D = j;
                yVide3D = i;
            }

            cubeSource->Update(); // Met à jour la source du cube

            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(cubeSource->GetOutput());


            vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();

            pieces[i][j] = cubeActor;
            pieces[i][j]->SetMapper(mapper);
            //pieces[i][j]->GetProperty()->SetColor(0, color, color); // Couleur 
            pieces[i][j]->SetPosition(i, j, 0.0); // Position de la pièce sur la grille


            // Texture créée à partir d'une image
            vtkNew<vtkImageReader2Factory> readerFactory;
            vtkSmartPointer<vtkImageReader2> imageReader;


            std::string s = "images/bois2/" + std::to_string(numeroPiece) + ".jpg";
            const char * filename = s.c_str();

            imageReader.TakeReference(readerFactory->CreateImageReader2(filename));

            
            imageReader->SetFileName(filename);


            // Création de la texture
            vtkNew<vtkTexture> texture;
            texture->SetInputConnection(imageReader->GetOutputPort());

            // La texture prends la forme du cube
            vtkNew<vtkTransformTextureCoords> transformTexture;
            transformTexture->SetInputConnection(cubeSource->GetOutputPort());

            mapper->SetInputConnection(transformTexture->GetOutputPort());
            
            // Application de la texture sur la pièce
            pieces[i][j]->SetTexture(texture);

            compteurPiece ++;

        }
    }

    

    // Création et personnalisation du texte pour l'affichage des commandes du jeu
    vtkNew<vtkTextActor> textActor;

    textActor = texteCommandes();


    // CRÉATION PLATEAU DE JEU


    // Création des bords du plateau de jeu
    vtkSmartPointer<vtkActor> arriere = vtkSmartPointer<vtkActor>::New();
    arriere = creationBords(4, 4, 0.01, 0, 0, 0, 1.5, 1.5, -epaisseurPlateau/2);

    vtkSmartPointer<vtkActor> gauche = vtkSmartPointer<vtkActor>::New();
    gauche = creationBords(4, epaisseurPlateau, 0.01, 0, 90, 90, -0.5, 1.5, 0);

    vtkSmartPointer<vtkActor> droite = vtkSmartPointer<vtkActor>::New();
    droite = creationBords(4, epaisseurPlateau, 0.01, 0, 90, 90, 3.5, 1.5, 0);

    vtkSmartPointer<vtkActor> haut = vtkSmartPointer<vtkActor>::New();
    haut = creationBords(4, epaisseurPlateau, 0.01, 90, 0, 0, 1.5, 3.5, 0);

    vtkSmartPointer<vtkActor> bas = vtkSmartPointer<vtkActor>::New();
    bas = creationBords(4, epaisseurPlateau, 0.01, 90, 0, 0, 1.5, -0.5, 0);




    // RENDU

    // Ajout des acteurs des pièces au rendu
    for (int i{}; i < tailleGrille; i++) {
        for (int j{}; j < tailleGrille; j++) {
            renderer->AddActor(pieces[i][j]);
        }
    }

    // Ajout au rendu des éléments du plateau de jeu 
    renderer->AddActor(arriere);
    renderer->AddActor(gauche);
    renderer->AddActor(droite);
    renderer->AddActor(haut);
    renderer->AddActor(bas);

    // Ajout du texte au rendu
    renderer->AddActor(textActor);




    // Définissez la couleur de l'arrière plan
    renderer->SetBackground(0.3, 0.3, 0.5); 

    // Définition du nom de la fenêtre de rendu
    renderWindow->SetWindowName("Jeu de taquin");

    renderWindow->AddRenderer(renderer);

    // Commencez la boucle de rendu
    //renderWindow->Render();
    //renderWindowInteractor->Start();


    //sleep(0.25);

    //swap two pieces
    //pieces[0][0]->GetProperty()->SetColor(1, 0, 0); // Couleur (rouge)
    //pieces[0][0]->SetPosition(0,0,0);

	// Création de l'intéracteur
	vtkNew<vtkRenderWindowInteractor> interactor;

    // Supprime les intéractions par défaut
    interactor->SetInteractorStyle(nullptr);
	
    interactor->SetRenderWindow(renderWindow);



	// Création de l'observateur
	vtkNew<Observer> observer;
    
    //définition des cases pour l'intéraction des pièces sur la grille

    //première case (en haut à gauche)
	//observer->SetPiece0(pieces[3][0]);
	//observer->SetPiece1(pieces[2][0]);
	//observer->SetPiece12(pieces[2][3]);

    observer->SetRenderer(renderer);
    observer->SetCommandesTexte( textActor);

    observer->SetGrilleJeu(grille);

    //initialisation des coordonnées de la case vide de la grille 2D
    observer->SetLigneCaseVide2D(xVide2D);
    observer->SetColonneCaseVide2D(yVide2D);

    // Initialisation des coordonnées de la case vide de la grille 3D
    observer->SetLigneCaseVide3D(xVide3D);
    observer->SetColonneCaseVide3D(yVide3D);

    

    observer->SetPlateau(pieces);


	interactor->AddObserver(vtkCommand::KeyPressEvent, observer);


	interactor->Initialize();

    
    //int c = 0;
    //c = observer->nombreDeplacements();
    //std::cout << c << "\n";

	interactor->Start();


    //sleep(3);
    //renderer->RemoveActor(textActor);
    


    //affiche();

    return EXIT_SUCCESS;
}
