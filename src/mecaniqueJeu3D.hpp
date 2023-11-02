#ifndef MECANIQUE_JEU_3D_HPP
#define MECANIQUE_JEU_3D_HPP

void deplacePiece3D(std::vector<std::vector<vtkSmartPointer<vtkActor>>>&  plateau,
                    const int& tailleGrille,  
                    int& _xVide3D, 
                    int& _yVide3D,
                    const int& direction);

#endif