#include <stdafx.h>
#include "SceneLoader.h"
#include <cstdlib>

void SceneLoader::loadModel(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	m_vModels.push_back(Model());	//Add empty model
									//Look at Model Element
	std::cout << e->Value() << "\n ";
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		std::cout << " " << modelChild->Value() << "\n";
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "Mesh") == 0) {
			//Add mesh to model
			std::cout << "  " << "MeshChild" << "\n";
		}
		else if (strcmp(childValue, "Position") == 0) {
			//Set model position
			glm::vec3 vec(
				atof(modelChild->FirstChildElement("posX")->GetText()),
				atof(modelChild->FirstChildElement("posY")->GetText()),
				atof(modelChild->FirstChildElement("posZ")->GetText())
			);
			m_vModels.back().setPosition(vec);
		}
		else if (strcmp(childValue, "Scale") == 0) {
			//Set model scale
			glm::vec3 vec(
				atof(modelChild->FirstChildElement("scaleX")->GetText()),
				atof(modelChild->FirstChildElement("scaleY")->GetText()),
				atof(modelChild->FirstChildElement("scaleZ")->GetText())
			);
			m_vModels.back().setScale(vec);
		}
		else if (strcmp(childValue, "Origin") == 0) {
			//Set model scale
			glm::vec3 vec(
				atof(modelChild->FirstChildElement("originX")->GetText()),
				atof(modelChild->FirstChildElement("originY")->GetText()),
				atof(modelChild->FirstChildElement("originZ")->GetText())
			);
			m_vModels.back().setOrigin(vec);
		}
	}
}

void SceneLoader::loadLight(tinyxml2::XMLElement * e)
{
}

void SceneLoader::loadCamera(tinyxml2::XMLElement * e)
{
}

void SceneLoader::readScene(tinyxml2::XMLElement * e)
{
}

void SceneLoader::readResources(tinyxml2::XMLElement * e)
{
}

SceneLoader::SceneLoader()
{
}

SceneLoader::SceneLoader(std::string sFilename)
{
}

SceneLoader::~SceneLoader()
{
	delete m_res;
	delete m_scene;
}

int SceneLoader::load(std::string sFilename, ResourceManager * res, Scene * scene)
{
	if (!res) {
		res = new ResourceManager;
	}

	using namespace tinyxml2;
	//Load xml scene file
	XMLDocument doc;
	if (doc.LoadFile(sFilename.c_str()) != XML_SUCCESS) {
		//Failed to load
		std::cout << "Could not load file: " << sFilename << "\n";
		return false;
	}
	XMLElement *ptrRoot = doc.FirstChildElement("Scene");
	if (ptrRoot == nullptr) {
		std::cout << "No root: " << sFilename << "\n";
		return false;
	}

	const char *rootValue = ptrRoot->Value();

	for (XMLElement* element = ptrRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (strcmp(element->Value(), "Model") == 0) {
			loadModel(element);
		}
		else if (strcmp(element->Value(), "Light") == 0) {

		}
		else if (strcmp(element->Value(), "Camera") == 0) {

		}
		else if (strcmp(element->Value(), "Robot") == 0) {

		}
	}

	return XML_SUCCESS;
}
