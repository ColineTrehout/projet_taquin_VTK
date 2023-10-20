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

#include <iostream>
#include <string> 
#include <unistd.h>

#include "affichageTexte.hpp"
#include "creationPlateau.hpp"


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

    int _xVide = 0; //ligne de la case vide
    int _yVide = 3; //colonne de la case vide
    int _compteurDeplacements = 0; //nombres de déplacements effectués

};


void Observer::Execute(vtkObject* caller, unsigned long, void*)
{
	auto* interactor{ vtkRenderWindowInteractor::SafeDownCast(caller) };


    
	if (interactor->GetKeyCode() == 'd')
	{
		std::cout << "d is pressed\n";

		//auto res{_coneSource->GetResolution()};

        //_piece0->GetProperty()->SetColor(1, 0, 0); // Couleur (rouge)
        //_piece1->GetProperty()->SetColor(0, 1, 0); // Couleur (vert)
        _piece0->SetPosition(_yVide-1,_xVide,0);
        _piece1->SetPosition(_yVide,_xVide,0);
        _yVide += -1;

        _compteurDeplacements++;
	}

    if (interactor->GetKeyCode() == 'e')
	{
		std::cout << "Fin du jeu\n";

        exit(0);
	}

    std::cout << _compteurDeplacements << "\n";
	interactor->Render();
}





int main(int, char *[])
{
    std::cout << "Bienvenue dans ce jeu de taquin\n";


    // déclarations

    float epaisseurPlateau = 0.4;

    // Couleurs
    vtkNew<vtkNamedColors> colors;


    // Create a VTK render window and renderer
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->SetSize(1920,1080);


    // Create a VTK render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Définition taille de la grille (4x4 pour le jeu de taquin classique)
    const int gridSize = 4; 

    // Création de la grille de jeu
    vtkSmartPointer<vtkActor> pieces[gridSize][gridSize];

    float color = 0.0;


    // TEXTURE  




    // CRÉATION DES PIÈCES

    int compteur = 0;

    // L'origine du repère se trouve en bas à gauche
    for (int j = 3; j >= 0; j--) 
    {
        for (int i = 0; i < gridSize; i++) 
        {

            // Création d'un cube par case
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

            cubeSource -> SetZLength(epaisseurPlateau);
            //std::cout << cubeSource-> GetXLength() << '\n';

            // Le dernier cube a une épaisseur plus faible pour simuler la case vide
            if (i == 3 && j == 0)
            {
                cubeSource -> SetZLength(0.1);

                //déplacement du centre du cube
                cubeSource -> SetCenter(0,0,-0.15); 
            }

            cubeSource->Update(); // Met à jour la source du cube

            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(cubeSource->GetOutput());


            pieces[i][j] = vtkSmartPointer<vtkActor>::New();
            pieces[i][j]->SetMapper(mapper);
            //pieces[i][j]->GetProperty()->SetColor(0, color, color); // Couleur 
            pieces[i][j]->SetPosition(i, j, 0.0); // Position de la pièce sur la grille


            // Read texture file
            vtkNew<vtkImageReader2Factory> readerFactory;
            vtkSmartPointer<vtkImageReader2> imageReader;

            std::string s = "images/pieces/" + std::to_string(compteur) + ".png";
            const char * filename = s.c_str();

            imageReader.TakeReference(readerFactory->CreateImageReader2(filename));

            
            imageReader->SetFileName(filename);


            // Create texture
            vtkNew<vtkTexture> texture;
            texture->SetInputConnection(imageReader->GetOutputPort());

            // application de la texture sur la pièce
            vtkNew<vtkTransformTextureCoords> transformTexture;
            transformTexture->SetInputConnection(cubeSource->GetOutputPort());

            mapper->SetInputConnection(transformTexture->GetOutputPort());
            pieces[i][j]->SetTexture(texture);

            compteur ++;

        }
    }
    


    // CRÉATION PLATEAU DE JEU
    


    // Création et personnalisation de l'acteur texte pour l'affichage des commandes du jeu
    vtkNew<vtkTextActor> textActor;

    textActor = creationTexteCommandes();


    // ajoute le texte au rendu
    renderer->AddActor(textActor);


    // création des bords du plateau de jeu
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


    // ajoute au rendu les éléments du plateau de jeu 
    renderer->AddActor(arriere);
    renderer->AddActor(gauche);
    renderer->AddActor(droite);
    renderer->AddActor(haut);
    renderer->AddActor(bas);


    // Ajoute les acteurs des pièces au rendu
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            renderer->AddActor(pieces[i][j]);
        }
    }




    // Définissez la couleur de l'arrière plan
    renderer->SetBackground(0.3, 0.3, 0.5); 


    // Définir le nom de la fenêtre de rendu
    renderWindow->SetWindowName("Jeu de taquin");

    renderWindow->AddRenderer(renderer);

    // Commencez la boucle de rendu
    //renderWindow->Render();
    //renderWindowInteractor->Start();


    //sleep(0.25);

    //swap two pieces
    //pieces[0][0]->GetProperty()->SetColor(1, 0, 0); // Couleur (rouge)
    //pieces[0][0]->SetPosition(0,0,0);

	//create renderer window interactor
	vtkNew<vtkRenderWindowInteractor> interactor;
	interactor->SetRenderWindow(renderWindow);



	//create an observer attached to window interactor
	vtkNew<Observer> observer;
    
    //définition des cases pour l'intéraction des pièces sur la grille

    //première case (en haut à gauche)
	observer->SetPiece0(pieces[3][0]);
	observer->SetPiece1(pieces[2][0]);
	//observer->SetPiece12(pieces[2][3]);

    int c = 0;

	interactor->AddObserver(vtkCommand::KeyPressEvent, observer);

	interactor->Initialize();
    c = observer->nombreDeplacements();
    std::cout << c << "\n";
	interactor->Start();


    //affiche();

    return EXIT_SUCCESS;
}
