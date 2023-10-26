#ifndef CREATION_PLATEAU_HPP
#define CREATION_PLATEAU_HPP

vtkSmartPointer<vtkActor> creationBords(const float& xLenght,
                                        const float& yLenght,
                                        const float& zLength,
                                        const float& xRotate,
                                        const float& yRotate,
                                        const float& zRotate,
                                        const float& xPosition,
                                        const float& yPosition,
                                        const float& zPosition);

#endif