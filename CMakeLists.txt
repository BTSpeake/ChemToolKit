# CMakeList.txt : CMake project for ChemToolKit, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("ChemToolKit")
include_directories(include "./include")

# Some compiler and environment specific controls 
if (MSVC) 
    if (WITH_OMP)
        add_compile_options(/openmp)
    endif()
else() 
    if (WITH_OMP)
        add_compile_options(-fopenmp)
    endif()
endif() 

# Make the basic maths library 
set(MATHS_SOURCES "src/Maths/Vector3.cpp" "src/Maths/Matrix33.cpp") 
add_library(ctkMaths SHARED ${MATHS_SOURCES})

# Make the molecular structure library 
set(MOL_SOURCES "src/Data/Model.cpp" "src/Data/Atom.cpp" "src/Data/VolumeData.cpp" "src/Data/Surface.cpp" "include/Data/HalfEdge.h" "include/Data/Vertex.h" "include/Data/Face.h")
add_library(ctkDataObjs SHARED ${MOL_SOURCES})
target_link_libraries(ctkDataObjs ctkMaths)

# Make the FileIO library 
set(FILEIO_SOURCES "src/FileIO/FileControl.cpp" "src/FileIO/FileIO_XYZ.cpp" "src/FileIO/FileIO_PDB.cpp" "src/FileIO/FileIO_Mol2.cpp" "src/FileIO/FileIO_DLP.cpp")
add_library(ctkFileIO SHARED ${FILEIO_SOURCES})
target_link_libraries(ctkFileIO ctkDataObjs)

# Force Field Library
add_library(ctkForceField SHARED "src/ForceField/BondCalc.cpp" "src/ForceField/UFFParams.cpp" "src/ForceField/UFF.cpp" "src/ForceField/AngleCalc.cpp" "src/ForceField/TorsionCalc.cpp" "src/ForceField/NonBondCalc.cpp")
target_link_libraries(ctkForceField ctkMaths)
target_link_libraries(ctkForceField ctkDataObjs)

# Make the graphics library using VTK as a base 
if (WITH_CTK_GRAPHICS)  
    add_compile_definitions(WITH_CTK_GRAPHICS)
    # Find VTK 
    find_package(VTK REQUIRED)
    if (VTK_FOUND)
        include_directories(include ${VTK_INCLUDE_DIRS})
    endif()
    # Graphics library 
    add_library(ctkGraphics SHARED "src/GUI/ModelController.cpp" "src/GUI/RenderWindow.cpp")
    target_link_libraries(ctkGraphics ctkDataObjs)
    target_link_libraries(ctkGraphics ${VTK_LIBRARIES})
    # vtk_module_autoinit is needed
    vtk_module_autoinit(
      TARGETS ctkGraphics
      MODULES ${VTK_LIBRARIES}
    )
endif()



# Dummy executable (for now)
add_executable (ChemToolKit "main.cpp" )
if(WITH_CTK_GRAPHICS)
    target_link_libraries(ChemToolKit ctkDataObjs ctkGraphics ${VTK_LIBRARIES})
endif()

# Global resource data files 
file(GLOB PARAM_FILES "Resources/*.prm")
file(COPY ${PARAM_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/) 



# CTests for C++ testing 
if (WITH_TESTING)
    file(GLOB TEST_FILES "tests/Resources/*")
    file(COPY ${TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_files/)
    include(tests/CMakeLists.txt)
endif()


## Python bindings
if (CTK_BIND_PYTHON)
    # Find python interpreter -> hint Python_ROOT_DIR
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
    set_target_properties(Python::Module PROPERTIES MAP_IMPORTED_CONFIG_DEBUG ";RELEASE")
    include_directories(${Python_INCLUDE_DIRS})
    # Find pybind11 -> hint pybind11_DIR
    find_package(pybind11 REQUIRED)
    include_directories(include pybind11_INCLUDE_DIRS)

    pybind11_add_module(ctkPyMaths "Bindings/Python/Maths.cpp")
    target_link_libraries(ctkPyMaths PRIVATE ctkMaths)

    pybind11_add_module(ctkPyDataObjs "Bindings/Python/DataObjs.cpp")
    target_link_libraries(ctkPyDataObjs PRIVATE ctkDataObjs ctkMaths)

    pybind11_add_module(ctkPyFileIO "Bindings/Python/FileIO.cpp")
    target_link_libraries(ctkPyFileIO PRIVATE ctkFileIO ctkDataObjs)

    pybind11_add_module(ctkPyForceField "Bindings/Python/ForceField.cpp")
    target_link_libraries(ctkPyForceField PRIVATE ctkForceField ctkDataObjs)

    if(WITH_CTK_GRAPHICS)
        pybind11_add_module(ctkPyGraphics "Bindings/Python/Graphics.cpp")
        target_link_libraries(ctkPyGraphics PRIVATE ctkGraphics)
    endif()

    # TODO: Add tests for python bindings 
endif()
