#pragma once

/** Factory pattern
	https://sourcemaking.com/design_patterns/factory_method
*/

#include "ResourceManager.h"
#include "GLSLProgram.h";
#include "Light.h"
#include "Model.h"

#include "tinyxml2.h"

class SceneLoader {
private:
	ResourceManager* m_res;
	Scene* m_scene;
	std::vector<Model> m_vModels;			//!< Store Models
	std::vector<Light> m_vLights;			//!< Store Lights
	std::vector<QuatCamera> m_vCamera;		//!< Store Cameras
	std::vector<GLSLProgram> m_vShaders;	//!< Store Shaders

	void loadMesh(tinyxml2::XMLElement* e);
	void loadTexture(tinyxml2::XMLElement* e);
	void loadMaterial(tinyxml2::XMLElement* e);

	void loadModel(tinyxml2::XMLElement* e);
	void loadLight(tinyxml2::XMLElement* e);
	void loadCamera(tinyxml2::XMLElement* e);

	void readScene(tinyxml2::XMLNode* node);
	void readResources(tinyxml2::XMLNode* node);
public:
	SceneLoader();							//!< Default constructor
	SceneLoader(std::string sFilename);		//!< Constructor loads file
	~SceneLoader();							//!< Destructor

	/*! Loads scene
		Can load resources directly to ResourceManager and 
		load scene directly into Scene;
	*/
	int load(std::string sFilename, ResourceManager* res = nullptr, Scene* scene = nullptr); 
};