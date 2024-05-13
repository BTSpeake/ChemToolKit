#pragma once 
#include "GUI/api.h"
#include <vector>
#include <memory>
#include <string>

#include "Data/Model.h"


namespace ctkGraphics {

	class GRAPHICS_API ModelController {
	public:
		//! Contructor 
		ModelController();
		//! Desctructor 
		~ModelController();

		ModelController(const ModelController&) = delete;
		ModelController& operator=(const ModelController&) = delete;

		//! Sets the currently active model index
		bool setCurrentModel(unsigned int i);
		//! Returns a pointer to the currently active model 
		std::shared_ptr<ctkData::Model> getCurrentModel() const;
		//! Returns a list of titles for each model in the list
		std::vector<std::string> getModelListAsStr() const;

	private:
		unsigned int _currentModel{ 0 };
		std::vector<std::shared_ptr<ctkData::Model>> _modelList;

	};

}