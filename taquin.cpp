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





class Observer : public vtkCommand {
public:
	static Observer* New()
	{
		return new Observer;
	}
	void Execute(vtkObject*, unsigned long, void*);
	void SetFirstPiece(vtkActor* piece) { _piece1 = piece; }
	void SetSecondPiece(vtkActor* piece) { _piece2 = piece; }


private:
	vtkActor* _piece1;
	vtkActor* _piece2;

};


void Observer::Execute(vtkObject* caller, unsigned long, void*)
{
	auto* interactor{ vtkRenderWindowInteractor::SafeDownCast(caller) };

	//if r is pressed

    
	if (interactor->GetKeyCode() == 'r')
	{
		std::cout << "r is pressed\n";

		//auto res{_coneSource->GetResolution()};

        _piece1->GetProperty()->SetColor(1, 0, 0); // Couleur (rouge)
        _piece2->GetProperty()->SetColor(0, 1, 0); // Couleur (vert)
        


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
    // Create a VTK render window and renderer
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    renderWindow->AddRenderer(renderer);

    // Create a VTK render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    const int gridSize = 4; // Taille de la grille (4x4 pour le jeu de taquin classique)
    vtkSmartPointer<vtkActor> pieces[gridSize][gridSize];

    float color = 0.0;

    // L'origine du repère se trouve en bas à gauche
    for (int j = 3; j >= 0; j--) 
    {
        for (int i = 0; i < gridSize; i++) 
        {
            vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
            cubeSource->Update(); // Met à jour la source du cube

            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(cubeSource->GetOutput());

            //condition pour ne pas créer la dernière case de la grille
            if (i != 3 || j != 0)
            {
            pieces[i][j] = vtkSmartPointer<vtkActor>::New();
            pieces[i][j]->SetMapper(mapper);
            pieces[i][j]->GetProperty()->SetColor(0, color, color); // Couleur (rouge)
            pieces[i][j]->SetPosition(i, j, 0.0); // Position de la pièce sur la grille
            }

            //dégradé de couleur
            color += 0.05;
        }
    }



    // Ajoutez les acteurs des pièces à la scène
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            renderer->AddActor(pieces[i][j]);
        }
    }

    // Définissez la couleur de fond du renderer
    renderer->SetBackground(0.3, 0.3, 0.5); 


    // Définir le nom de la fenêtre de rendu
    renderWindow->SetWindowName("Jeu de taquin");

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
	observer->SetFirstPiece(pieces[0][3]);
	observer->SetSecondPiece(pieces[3][3]);

	interactor->AddObserver(vtkCommand::KeyPressEvent, observer);

	interactor->Initialize();
	interactor->Start();



    return 0;
}
