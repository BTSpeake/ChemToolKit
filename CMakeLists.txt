# CMakeList.txt : CMake project for ChemToolKit, include source and define
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

# Build as shared libraries 
# set (BUILD_SHARED_LIBS TRUE)  ::TODO::

# Make the basic maths library 
set(MATHS_SOURCES "src/Maths/Vector3.cpp") 
add_library(ctkMaths ${MATHS_SOURCES} "src/Maths/Matrix33.cpp")

# Make the molecular structure library 
set(MOL_SOURCES "src/Molecule/Molecule.cpp" "src/Molecule/Atom.cpp")
add_library(ctkMolecule ${MOL_SOURCES})
target_link_libraries(ctkMolecule ctkMaths)


# Add source to this project's executable.
add_executable (ChemToolKit "main.cpp" "src/ForceField/BondCalc.cpp" "src/ForceField/UFFParams.cpp" "src/ForceField/UFF.cpp" "src/ForceField/AngleCalc.cpp" "src/FileIO/FileIO_XYZ.cpp" "src/FileIO/FileIO_PDB.cpp" "src/FileIO/FileControl.cpp" "src/Python/Molecule.cpp"  "src/FileIO/FileIO_Mol2.cpp" )
target_link_libraries(ChemToolKit ctkMaths)
target_link_libraries(ChemToolKit ctkMolecule)

file(GLOB PARAM_FILES "Resources/*.prm")
file(COPY ${PARAM_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/) 
file(GLOB TEST_FILES "tests/*")
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ChemToolKit PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
