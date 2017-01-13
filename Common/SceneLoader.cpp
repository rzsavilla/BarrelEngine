#include <stdafx.h>
#include "SceneLoader.h"
#include <cstdlib>

void SceneLoader::loadMesh(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	Mesh mesh;
	char* c = "";
	std::string s;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set mesh ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));		//Mesh ID
			}
		}
		else if (strcmp(childValue, "File") == 0) {
			//Load mesh
			if (readElementText(Child, c)) {
				std::string sFile(c, strlen(c));
				mesh.load(sFile);
			};
		}
		else if (strcmp(childValue, "Texture") == 0) {

		}
	}
	m_res->addMesh(s,mesh);	//Add mesh to resource manager;
	if (m_bDebug) std::cout << " Mesh Loaded: " << s << "\n";
}

void SceneLoader::loadTexture(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;
	Texture* texture = NULL;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set texture ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));
			}
		}
		else if (strcmp(childValue, "File") == 0) {
			
			if (readElementText(Child, c)) {
				std::string sFile(c, strlen(c));
				//Load image
				Bitmap bmp = Bitmap::bitmapFromFile(sFile);
				bmp.flipVertically();
				//Create texture
				texture = new Texture(bmp);
			};
		}
	}
	m_res->addTexture(s,texture);
	if (m_bDebug) std::cout << " Texture Loaded: " << s << "\n";
}

void SceneLoader::loadMaterial(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* c = "";
	std::string s;
	Material material;
	glm::vec3 v;
	for (XMLElement* Child = e->FirstChildElement(); Child != NULL; Child = Child->NextSiblingElement()) {
		const char* childValue = Child->Value();
		if (strcmp(childValue, "ID") == 0) {
			//Set texture ID
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));
			}
		}
		else if (strcmp(childValue, "AmbientReflect") == 0) {
			v = parseVec3(Child);
			material.setAmbient(v);
		}
		else if (strcmp(childValue, "DiffuseReflect") == 0) {
			v = parseVec3(Child);
			material.setDiffuse(v);
		}
		else if (strcmp(childValue, "SpecularReflect") == 0) {
			v = parseVec3(Child);
			material.setSpecular(v);
		}
		else if (strcmp(childValue, "Shininess")) {
			if (readElementText(Child, c)) {
				s = std::string(c, strlen(c));
				material.setShininess(atof(c));
			}
		}
	}
	m_res->addMaterial(s, material);
	if (m_bDebug) std::cout << " Material Loaded: " << s << "\n";
}

void SceneLoader::loadShader(tinyxml2::XMLElement * e)
{

}

std::pair<std::string, Model> SceneLoader::loadModel(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;

	char* cData = "";			//Temporary storage for element data

	if (m_bDebug) std::cout << "Loading Model \n  ";

	Model model;
	std::string sID;
	//Look at Model Element
	for (XMLElement* modelChild = e->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()) {
		const char* childValue = modelChild->Value();
		if (strcmp(childValue, "ID") == 0) {
			if (readElementText(modelChild, cData)) {
				sID = std::string(cData, strlen(cData));
			}
		}
		else if (strcmp(childValue, "Mesh") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setMesh(m_res->getMesh(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Shader") == 0) {
			if (readElementText(modelChild, cData)) {
				model.setShader(m_res->getShader(std::string(cData, strlen(cData))));
			}
		}
		else if (strcmp(childValue, "Position") == 0) {
			glm::vec3 v = parseVec3(modelChild);
			model.setPosition(v);

			if (m_bDebug) std::cout << "Position Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Scale") == 0) {
			//Set model scale
			glm::vec3 v = parseVec3(modelChild);
			model.setScale(v);
			if (m_bDebug) std::cout << "Scale Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
		else if (strcmp(childValue, "Origin") == 0) {
			//Set model origin
			glm::vec3 v = parseVec3(modelChild);
			model.setOrigin(v);
			if (m_bDebug) std::cout << "Origin Set : " << v.x << ", " << v.y << ", " << v.z << "\n  ";
		}
	}

	return std::pair<std::string, Model>();
}

std::pair<std::string, Light> SceneLoader::loadLight(tinyxml2::XMLElement * e)
{
	return std::pair<std::string, Light>();
}

QuatCamera SceneLoader::loadCamera(tinyxml2::XMLElement * e)
{
	return QuatCamera();
}

void SceneLoader::readScene(tinyxml2::XMLNode * node)
{
	bool bTypeFound = false;
	m_vModels.clear();
	m_vLights.clear();
	m_vCamera.clear();
	char* c = "";
	std::string str;
	if (readElementText(node->FirstChildElement("Type"), c)) {
		str = std::string(c, strlen(c));
	}

	std::string sID;
	if (str == "Game") {
		std::shared_ptr<GameScene> gameScene = std::make_unique<GameScene>();	//Create scene

		if (m_bDebug) std::cout << "Loading Scene elements\n ";
		using namespace tinyxml2;
		for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
		{
			if (strcmp(element->Value(), "ID") == 0) {
				if (readElementText(element, c)) {
					sID = std::string(c, strlen(c));		//ID
				}
			}
			else if (strcmp(element->Value(), "Model") == 0) {
				gameScene->addModel(loadModel(element));
			}
			else if (strcmp(element->Value(), "Light") == 0) {
				gameScene->addLight(loadLight(element));
			}
			else if (strcmp(element->Value(), "Camera") == 0) {
				loadCamera(element);
			}
			else if (strcmp(element->Value(), "Robot") == 0) {

			}
		}
		m_scenes->push_back(std::pair<std::string, std::shared_ptr<Scene>>(sID,gameScene));
	}
	else {

	}
}

void SceneLoader::readResources(tinyxml2::XMLNode* node)
{
	using namespace tinyxml2;
	std::cout << "Reading Resources\n";
	for (XMLElement* element = node->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		const char* c = element->Value();
		if (strcmp(c, "Mesh") == 0) {
			loadMesh(element);
		}
		else if (strcmp(c, "Texture") == 0) {
			loadTexture(element);
		}
		else if (strcmp(c, "Material") == 0) {

		}
		else if (strcmp(c, "Shader") == 0) {

		}

	}
}

bool SceneLoader::readElementText(tinyxml2::XMLElement* e,char*& data)
{
	data = (char*)e->GetText();
	if (data != nullptr) {
		//Text exists
		return true;
	}
	//Text does not exist
	data = nullptr;
	return false;
}

glm::vec3 SceneLoader::parseVec3(tinyxml2::XMLElement * e)
{
	using namespace tinyxml2;
	char* cData = "";		//Temp data storage

	glm::vec3 v(0.0f,0.0f,0.0f);

	for (XMLElement* childElement = e->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		const char* c = childElement->Value();
		if ((strcmp(c, "X")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.x = atof(cData);	//Convert to float and place into float array
			}
		}
		else if ((strcmp(c, "Y")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.y = atof(cData);	//Convert to float and place into float array
			}
		}
		else if ((strcmp(c, "Z")) == 0) {
			if (readElementText(childElement, cData)) {	//Check if text exists
				v.z = atof(cData);	//Convert to float and place into float array
			}
		}
	}

	return v;		//Return vector
}

SceneLoader::SceneLoader(std::string sFilename, ResourceManager * res, std::vector<std::pair<std::string, std::shared_ptr<Scene>>>* scenes)
{
	m_res = res;		//Pointer to Resource manager
	m_scenes = scenes;	//Pointer to vector of scenes
	load(sFilename);
}

SceneLoader::~SceneLoader()
{

}

int SceneLoader::load(std::string sFilename)
{
	using namespace tinyxml2;
	//Load xml scene file
	XMLDocument doc;
	if (doc.LoadFile(sFilename.c_str()) != XML_SUCCESS) {
		//Failed to load
		std::cout << "Could not load file: " << sFilename << "\n";
		return false;
	}

	if (m_bDebug) std::cout << "Reading scene file: " << sFilename << "\n";

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
