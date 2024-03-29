﻿# CMakeList.txt : CMake project for ChemToolKit, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ChemToolKit")
include_directories(include "./include")
set(CMAKE_CXX_STANDARD 20)

# Build as shared libraries 
if (CTK_BUILD_AS_STATIC)
    set(BUILD_SHARED_LIBS False)
else()
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Make the basic maths library 
set(MATHS_SOURCES "src/Maths/Vector3.cpp" "src/Maths/Matrix33.cpp") 
add_library(ctkMaths ${MATHS_SOURCES})

# Make the molecular structure library 
set(MOL_SOURCES "src/Data/Molecule.cpp" "src/Data/Atom.cpp")
add_library(ctkDataObjs ${MOL_SOURCES})
target_link_libraries(ctkDataObjs ctkMaths)

# Make the FileIO library 
set(FILEIO_SOURCES "src/FileIO/FileControl.cpp" "src/FileIO/FileIO_XYZ.cpp" "src/FileIO/FileIO_PDB.cpp" "src/FileIO/FileIO_Mol2.cpp")
add_library(ctkFileIO ${FILEIO_SOURCES})
target_link_libraries(ctkFileIO ctkDataObjs)

# Force Field Library
add_library(ctkForceField "src/ForceField/BondCalc.cpp" "src/ForceField/UFFParams.cpp" "src/ForceField/UFF.cpp" "src/ForceField/AngleCalc.cpp" "src/ForceField/TorsionCalc.cpp" "src/ForceField/NonBondCalc.cpp")
target_link_libraries(ctkForceField ctkMaths)
target_link_libraries(ctkForceField ctkDataObjs)

# Add source to this project's executable.
add_executable (ChemToolKit "main.cpp" )
target_link_libraries(ChemToolKit ctkMaths)
target_link_libraries(ChemToolKit ctkDataObjs)
target_link_libraries(ChemToolKit ctkFileIO)
target_link_libraries(ChemToolKit ctkForceField)

file(GLOB PARAM_FILES "Resources/*.prm")
file(COPY ${PARAM_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/) 
file(GLOB TEST_FILES "tests/*")
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/)



# TODO: Add tests and install targets if needed.



## Python bindings
set(CTK_BIND_PYTHON ON) # -> Auto set to on for now 
if (CTK_BIND_PYTHON)
    # Find python interpreter -> hint Python_ROOT_DIR
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
    set_target_properties(Python::Module PROPERTIES
            MAP_IMPORTED_CONFIG_DEBUG ";RELEASE")
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
endif()
