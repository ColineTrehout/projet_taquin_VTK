#ifndef CREATION_PLATEAU_HPP
#define CREATION_PLATEAU_HPP

vtkSmartPointer<vtkActor> creationBord(const float& xLenght,
                                        const float& yLenght,
                                        const float& zLength,
                                        const float& xRotate,
                                        const float& yRotate,
                                        const float& zRotate,
                                        const float& xPosition,
                                        const float& yPosition,
                                        const float& zPosition);

void creationActeursCubes(std::vector<std::vector<vtkSmartPointer<vtkActor>>>& pieces,
                  const vtkSmartPointer<vtkPolyDataMapper>& mapper,
                  const int& i,
                  const int& j);

#endif