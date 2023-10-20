#ifndef MECANIQUE_JEU_HPP
#define MECANIQUE_JEU_HPP

void afficheGrille(const std::vector<std::vector<int>>& grille, int tailleGrille);
void melangeGrille(std::vector<std::vector<int>>& grille, 
                   const int& tailleGrille, 
                   int& xVide, 
                   int& yVide, 
                   const int& nbMelanges);

bool deplacePiece(std::vector<std::vector<int>>& grille, 
                  const int& tailleGrille, 
                  int& xVide, 
                  int& yVide, 
                  const int& direction);

bool verifVictoire(std::vector<std::vector<int>>& grille, const int& tailleGrille);

#endif