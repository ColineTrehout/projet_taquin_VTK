#ifndef MECANIQUE_JEU_HPP
#define MECANIQUE_JEU_HPP

//void initialiseGrille(std::vector<std::vector<int>> grille, int tailleGrille);
void afficheGrille(const std::vector<std::vector<int>>& grille, int tailleGrille);
void melangeGrille(std::vector<std::vector<int>>& grille, 
                   const int& tailleGrille, 
                   int& xVide, 
                   int& yVide, 
                   const int& nbMelanges);



#endif