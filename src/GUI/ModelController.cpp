#include "GUI/ModelController.h"

ModelController::ModelController() {}

ModelController::~ModelController() {
	_modelList.clear();
}

bool ModelController::setCurrentModel(unsigned int i) {
	if (i >= _modelList.size()) {
		return false;
	}
	else {
		_currentModel = i;
	}
	return true;
}

std::shared_ptr<ctkData::Model> ModelController::getCurrentModel() const {
	if (_modelList.size() > 0) {
		return _modelList[_currentModel];
	}
	else {
		return nullptr;
	}
}

std::vector<std::string> ModelController::getModelListAsStr() const {
	std::vector<std::string> titles;
	for (auto model : _modelList) {
		titles.push_back(model->getTitle());
	}
	return titles;
}