#include <stdafx.h>
#include "SceneLoader.h"
#include <cstdlib>

void SceneLoader::loadMesh(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	for (XMLElement* meshChild = e->FirstChildElement(); meshChild != NULL; meshChild = meshChild->NextSiblingElement()) {
		std::cout << " " << meshChild->Value() << "\n";
		const char* childValue = meshChild->Value();
		if (strcmp(childValue, "File") == 0) {
			//Add mesh to model
			std::cout << "  " << "MeshChild" << "\n";
		}
		else if (strcmp(childValue, "Id") == 0) {

		}
	}
}

void SceneLoader::loadTexture(tinyxml2::XMLElement * e)
{

}

void SceneLoader::loadMaterial(tinyxml2::XMLElement * e)
{

}

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
			std::cout << vec.x << "\n";
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

void SceneLoader::readScene(tinyxml2::XMLNode * node)
{
	using namespace tinyxml2;
	for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (strcmp(element->Value(), "Model") == 0) {
			loadModel(element);
		}
		else if (strcmp(element->Value(), "Light") == 0) {
			loadLight(element);
		}
		else if (strcmp(element->Value(), "Camera") == 0) {
			loadCamera(element);
		}
		else if (strcmp(element->Value(), "Robot") == 0) {

		}
	}
}

void SceneLoader::readResources(tinyxml2::XMLNode* node)
{
	using namespace tinyxml2;
	for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (strcmp(element->Value(), "Mesh") == 0) {

		}
		else if (strcmp(element->Value(), "Texture") == 0) {

		}
		else if (strcmp(element->Value(), "Material") == 0) {

		}

	}
}

SceneLoader::SceneLoader()
{
}

SceneLoader::SceneLoader(std::string sFilename)
{
	load(sFilename);
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
	XMLNode *ptrRoot = doc.FirstChild();
	if (ptrRoot == nullptr) {
		std::cout << "No root: " << sFilename << "\n";
		return false;
	}

	for (XMLNode* node = ptrRoot; node != NULL; node = node->NextSiblingElement()) {
		const char* value = node->Value();

		if (strcmp(node->Value(), "Resources") == 0) {
			readResources(node);
		}
		else if (strcmp(node->Value(), "Scene") == 0) {
			readScene(node);
		}
	}

	return XML_SUCCESS;
}
