#ifndef CREATION_TEXTE_HPP
#define CREATION_TEXTE_HPP

vtkNew<vtkTextActor> texteCommandes();

vtkNew<vtkTextActor> texteVictoire(const int& compteurDeplacements);

vtkNew<vtkTextActor> texteNouvellePartie();

#endif
