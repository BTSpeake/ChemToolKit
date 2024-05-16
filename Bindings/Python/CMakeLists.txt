
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