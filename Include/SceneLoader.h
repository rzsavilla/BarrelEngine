#pragma once

/** Factory pattern
	https://sourcemaking.com/design_patterns/factory_method
*/

#include "ResourceManager.h"
#include "GLSLProgram.h"
#include "Light.h"
#include "Model.h"
#include "GameScene.h"

#include "tinyxml2.h"

class SceneLoader {
private:
	ResourceManager* m_res;
	std::vector<std::pair<std::string,std::shared_ptr<Scene>>>* m_scenes;
	std::vector<std::pair<std::string,Model>> m_vModels;			//!< Store Models
	std::vector<std::pair<std::string,Light>> m_vLights;			//!< Store Lights
	std::vector<std::pair<std::string, QuatCamera>> m_vCamera;		//!< Store Cameras

	void loadMesh(tinyxml2::XMLElement* e);
	void loadTexture(tinyxml2::XMLElement* e);
	void loadMaterial(tinyxml2::XMLElement* e);
	void loadShader(tinyxml2::XMLElement* e);

	std::pair<std::string, Model> loadModel(tinyxml2::XMLElement* e);
	std::pair<std::string, Light> loadLight(tinyxml2::XMLElement* e);
	std::pair<std::string, QuatCamera> loadCamera(tinyxml2::XMLElement* e);

	void readScene(tinyxml2::XMLNode* node);
	void readResources(tinyxml2::XMLNode* node);

	bool m_bDebug = true;

	//! Checks whether element text exists
	bool readElementText(tinyxml2::XMLElement* e,char*& data);
	
	//! Read X,Y,Z elements
	glm::vec3 parseVec3(tinyxml2::XMLElement*e);
public:
	SceneLoader(std::string sFilename,ResourceManager* res, std::vector<std::pair<std::string, std::shared_ptr<Scene>>>*);							//!< Default constructor
	~SceneLoader();							//!< Destructor

	/*! Loads scene
		Can load resources directly to ResourceManager and 
		load scene directly into Scene;
	*/
	int load(std::string sFilename); 
};