#ifndef MECANIQUE_JEU_2D_HPP
#define MECANIQUE_JEU_2D_HPP

void afficheGrille(const std::vector<std::vector<int>>& grille, const int& tailleGrille);
void melangeGrille(std::vector<std::vector<int>>& grille, 
                   const int& tailleGrille, 
                   int& xVide, 
                   int& yVide, 
                   const int& nbMelanges);
void deplacePiece2D(std::vector<std::vector<int>>& grille, 
                  const int& tailleGrille, 
                  int& xVide, 
                  int& yVide, 
                  const int& direction);
bool verifVictoire(const std::vector<std::vector<int>>& grille, const int& tailleGrille);

#endif