#include <iostream>
#include "Data/Model.h"#
#ifdef WITH_CTK_GRAPHICS
#include "GUI/RenderWindow.h"
#endif

int main() {
#ifdef WITH_CTK_GRAPHICS
	ctkData::Model model;
	model.addAtom(1, 0, 0, 0);
	model.addAtom(1, 0, 0, 1);
	ctkGraphics::RenderWindow rw;
	rw.setModel(model);
	rw.render();
#else
	std::cout << "Command line interface has not yet been implemented\n"; 
	std::cout << "Check back soon..." << std::endl;
#endif 
}

