#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <unistd.h>
#include <vtkCommand.h>
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
#include <vtkTextProperty.h>
#include <vtkNamedColors.h>
#include <vtkTexture.h>
#include <vtkJPEGReader.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader.h>
#include <vtkTransformTextureCoords.h>
#include <vtkCylinderSource.h>
#include <vtkVectorText.h>
#include <vtkTextActor.h>

#include "affichageTexte.hpp"



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

};


void Observer::Execute(vtkObject* caller, unsigned long, void*)
{
	auto* interactor{ vtkRenderWindowInteractor::SafeDownCast(caller) };

	//if r is pressed

    
	if (interactor->GetKeyCode() == 'r')
	{
		std::cout << "r is pressed\n";

		//auto res{_coneSource->GetResolution()};

        _piece0->GetProperty()->SetColor(1, 0, 0); // Couleur (rouge)
        _piece1->GetProperty()->SetColor(0, 1, 0); // Couleur (vert)
        


	}

    if (interactor->GetKeyCode() == 'e')
	{
		std::cout << "Fin du jeu\n";

        exit(0);
	}


	interactor->Render();
}





int main(int, char *[])
{

    // Couleurs
    vtkNew<vtkNamedColors> colors;


    // Create a VTK render window and renderer
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();


    // Create a VTK render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Définition taille de la grille (4x4 pour le jeu de taquin classique)
    const int gridSize = 4; 

    // Création de la grille de jeu
    vtkSmartPointer<vtkActor> pieces[gridSize][gridSize];

    float color = 0.0;



    // Read texture file
    vtkNew<vtkImageReader2Factory> readerFactory;
    vtkSmartPointer<vtkImageReader2> imageReader;
    imageReader.TakeReference(readerFactory->CreateImageReader2("logo.png"));
    imageReader->SetFileName("logo.png");


    // L'origine du repère se trouve en bas à gauche
    for (int j = 3; j >= 0; j--) 
    {
        for (int i = 0; i < gridSize; i++) 
        {

            // Création d'un cube par case
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
            cubeSource -> SetZLength(0.6);

            // Le dernier cube a une épaisseur plus faible pour simuler la case vide
            if (i == 3 && j == 0)
            {
                cubeSource -> SetZLength(0.2);

                //déplacement du centre du cube
                cubeSource -> SetCenter(0,0,-0.2); 
            }

            cubeSource->Update(); // Met à jour la source du cube

            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(cubeSource->GetOutput());


            pieces[i][j] = vtkSmartPointer<vtkActor>::New();
            pieces[i][j]->SetMapper(mapper);
            pieces[i][j]->GetProperty()->SetColor(0, color, color); // Couleur (rouge)
            pieces[i][j]->SetPosition(i, j, 0.0); // Position de la pièce sur la grille


            // Create texture
            vtkNew<vtkTexture> texture;
            texture->SetInputConnection(imageReader->GetOutputPort());

            vtkNew<vtkTransformTextureCoords> transformTexture;
            transformTexture->SetInputConnection(cubeSource->GetOutputPort());

            mapper->SetInputConnection(transformTexture->GetOutputPort());
            pieces[i][j]->SetTexture(texture);


            //dégradé de couleur
            color += 0.05;
        }
    }
    





    
    // derrière du plateau 

    vtkSmartPointer<vtkCubeSource> flatRectangle = vtkSmartPointer<vtkCubeSource>::New();

    // Dimensions du rectangle
    flatRectangle->SetXLength(4);
    flatRectangle->SetYLength(4);
    flatRectangle->SetZLength(0.01);

    flatRectangle->Update();

    vtkSmartPointer<vtkActor> plateau = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    plateau->SetMapper(mapper);

    plateau->GetProperty()->SetColor(0.5,0.2,0.05); // marron

    plateau->SetPosition(1.5, 1.5, -0.3);

    mapper->SetInputData(flatRectangle->GetOutput());




    // texte

    vtkNew<vtkTextActor> textActor;
    textActor->SetInput("Hello World !! \n yea");

    auto prop = textActor->GetTextProperty();

    textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetTextScaleModeToViewport();
    textActor->SetPosition(130, 800);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(20);
    textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    textActor->GetTextProperty()->SetColor(1,0,0);


    renderer->AddActor(textActor);


    //ajoute le fond du plateau
    renderer->AddActor(plateau);


    // Ajoutez les acteurs des pièces à la scène
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
	observer->SetPiece0(pieces[0][3]);
	observer->SetPiece1(pieces[3][0]);
	//observer->SetPiece12(pieces[2][3]);



	interactor->AddObserver(vtkCommand::KeyPressEvent, observer);

	interactor->Initialize();
	interactor->Start();


    affiche();

    return EXIT_SUCCESS;
}
