#ifndef OBSERVATEUR_HPP
#define OBSERVATEUR_HPP

class Observer : public vtkCommand {
public:
	static Observer* New()
	{
		return new Observer;
	}
	void Execute(vtkObject*, unsigned long, void*);
	int nombreDeplacements();
	void SetRenderer(vtkRenderer* renderer);
    void SetCommandesTexte(vtkTextActor* textCommandes);
    void SetGrilleJeu(const std::vector<std::vector<int>>& grille);
    void SetLigneCaseVide2D(const int& xVide);
    void SetColonneCaseVide2D(const int& yVide);
    void SetLigneCaseVide3D(const int& xVide);
    void SetColonneCaseVide3D(const int& yVide);
    void SetPlateau(const std::vector<std::vector<vtkSmartPointer<vtkActor>>>&  plateau);


private:

    const int _tailleGrille = 4;
    std::vector<std::vector<int>> _grille; // Grille de jeu (2D)
    std::vector<std::vector<vtkSmartPointer<vtkActor>>> _plateau; // Plateau 3D
    int _xVide2D{}; // Ligne de la case vide de la grille 2D
    int _yVide2D{}; // Colonne de la case vide de la grille 2D
    int _xVide3D{}; // Ligne de la case vide de la grille 3D
    int _yVide3D{}; // Colonne de la case vide de la grille 3D
    int _compteurDeplacements{}; // Nombre de déplacements effectués
    vtkSmartPointer<vtkTextActor> _texteCommandes; // Texte pour l'affichage des commandes
    vtkSmartPointer<vtkRenderer> _renderer;
};

#endif