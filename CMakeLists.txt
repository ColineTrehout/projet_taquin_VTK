CMAKE_MINIMUM_REQUIRED(VERSION 3.10) 


PROJECT(taquin) 


find_package(VTK REQUIRED)


if (NOT VTK_FOUND)
  message("Skipping ${PROJECT_NAME}: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()

add_executable(main MACOSX_BUNDLE)
target_sources(main PRIVATE
  src/main.cpp 
  src/creationTexte.cpp
  src/creationPlateau.cpp
  src/mecaniqueJeu2D.cpp
  src/mecaniqueJeu3D.cpp
  src/observateur.cpp
)

target_link_libraries(main PRIVATE ${VTK_LIBRARIES})

message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
else ()
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS main
    MODULES ${VTK_LIBRARIES}
    )
endif ()