CMAKE_MINIMUM_REQUIRED(VERSION 3.10) 


PROJECT(taquin) 


find_package(VTK REQUIRED)


if (NOT VTK_FOUND)
  message("Skipping ${PROJECT_NAME}: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()

add_executable(${PROJECT_NAME} MACOSX_BUNDLE)
target_sources(${PROJECT_NAME} PRIVATE
  ${PROJECT_NAME}.cpp 
  creationTexte.cpp
  creationPlateau.cpp
  mecaniqueJeu.cpp
  observateur.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${VTK_LIBRARIES})

message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
else ()
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS ${PROJECT_NAME}
    MODULES ${VTK_LIBRARIES}
    )
endif ()