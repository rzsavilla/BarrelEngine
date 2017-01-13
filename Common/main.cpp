#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "ModelReader.h"
#include "Bitmap.h"
#include "Texture.h"
#include "QuatCamera.h"
#include "MyRobot.h"

#include "Light.h"
#include "Material.h"

#include <Engine.h>


bool bW, bS, bA, bD,
bUp, bDown, bLeft, bRight,
bSpace, bLShift, bLeftMouse, bRightMouse;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		bW = action;
		break;
	case GLFW_KEY_S:
		bS = action;
		break;
	case GLFW_KEY_A:
		bA = action;
		break;
	case GLFW_KEY_D:
		bD = action;
		break;
	case GLFW_KEY_UP:
		bUp = action;
		break;
	case GLFW_KEY_DOWN:
		bDown = action;
		break;
	case GLFW_KEY_LEFT:
		bLeft = action;
		break;
	case GLFW_KEY_RIGHT:
		bRight = action;
		break;
	case GLFW_KEY_SPACE:
		bSpace = action;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		bLShift = action;
		break;
	default:
		break;
	};
}

float mousePos[] = { 0.0f,0.0f };
float prevMousePos[] = { 0.0f,0.0f };

void mouseButtonPress(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

	}
}

static void mouseMove(GLFWwindow* window, double xpos, double ypos)
{
	mousePos[0] = (float)xpos;
	mousePos[1] = (float)ypos;
}

static void mouseStop(GLFWwindow* window, double xpos, double ypos) {
	prevMousePos[0] = mousePos[0];
	prevMousePos[1] = mousePos[1];
}

void updateLight(GLSLProgram& prog, Light light,Material material , QuatCamera cam) {
	//Camera
	prog.use();
	prog.setUniform("mView", cam.view());					//View matrix
	prog.setUniform("mProjection", cam.projection());		//Projection matrix
	prog.setUniform("viewPos", cam.position());

	//Light
	prog.setUniform("lightPosition", light.getPosition());
	prog.setUniform("lightRadius", light.getRadius());

	//Material reflectivity
	prog.setUniform("Ka", material.getAmbient());		//Ambient material reflection
	prog.setUniform("Kd", material.getDiffuse());		//Diffuse
	prog.setUniform("Ks", material.getSpecular());		//Specular
	prog.setUniform("shininess", material.getShininess());
	//Light intensity
	prog.setUniform("La", light.getAmbient());	//Ambient light
	prog.setUniform("Ld", light.getDiffuse());	//Diffuse light
	prog.setUniform("Ls", light.getSpecular());	//Specular light
}

#include "SceneLoader.h";

int main() {

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);

	//Open window
	GLFWwindow *window = glfwCreateWindow(1024, 768, "Barrel Engine" , NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to load window\n";
		system("pause");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//Load OpenGL functions
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if (!didLoad) {
		//Clean up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	std::vector<std::pair<std::string, std::shared_ptr<Scene>>> m_scenes;
	ResourceManager m_res;
	std::string sFile = "Source\\Resources\\scenes\\test.xml";

	SceneLoader sceneLoader(sFile, &m_res, &m_scenes);


	gl::Enable(gl::DEPTH_TEST);
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {

		////////////UPDATE//////////////////////
		//Calculate time step

		float fS = 10.0f;

		
		for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
			(*it).second->update(0.1);	//Update Scene
			(*it).second->render(window);
		}

		//////////////////LIGHTS//////////

		//////////////////RENDER//////////


		//gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		//gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		//glfwSwapInterval(1);		//VSYNC OFF
		//glfwSwapBuffers(window);
		//glfwPollEvents();
	}
	//Close window and terminate GLFW
	glfwTerminate();


	int w = 0;
	//XMLDocument doc;
	//doc.LoadFile("Source\\Resources\\scenes\\test.xml");

	//const char* title = doc.FirstChildElement("Scenes")->FirstChildElement("Scene")->Attribute("type");

	////const char* type = doc.FirstChildElement("Scenes)
	//int i = 0;

	//unsigned int uiWidth = 1024;
	//unsigned int uiHeight = 768;

	//// Initialize GLFW
	//if (!glfwInit()) exit(EXIT_FAILURE);
	//
	//// Select OpenGL 4.3 with a forward compatible core profile.
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, FALSE);
	//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
	//glfwWindowHint(GLFW_DEPTH_BITS, 32);								//Enable Depth buffer
	//
	////Open window
	//GLFWwindow *window = glfwCreateWindow(1024, 768, "Barrel Engine" , NULL, NULL);
	//if (window == NULL) {
	//	std::cout << "Failed to load window\n";
	//	system("pause");
	//	glfwTerminate();
	//	exit(EXIT_FAILURE);
	//}
	//glfwMakeContextCurrent(window);
	////Load OpenGL functions
	//gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	//if (!didLoad) {
	//	//Clean up and abort
	//	glfwTerminate();
	//	exit(EXIT_FAILURE);
	//}

	////Compile and link shader program
	//GLSLProgram shader;
	//try {
	//	shader.compileShader("Source\\Resources\\shader\\basic.frag");
	//	shader.compileShader("Source\\Resources\\shader\\basic.vert");
	//	shader.link();
	//	shader.validate();
	//	shader.use();
	//}
	//catch (GLSLProgramException & e) {
	//	cerr << e.what() << endl;
	//	exit(EXIT_FAILURE);
	//}

	//GLSLProgram colourShader;
	//try {
	//	colourShader.compileShader("Source\\Resources\\shader\\colour.frag");
	//	colourShader.compileShader("Source\\Resources\\shader\\colour.vert");
	//	colourShader.link();
	//	colourShader.validate();
	//	colourShader.use();
	//}
	//catch (GLSLProgramException & e) {
	//	cerr << e.what() << endl;
 //		exit(EXIT_FAILURE);
	//}

	//GLSLProgram phongShader;
	//try {
	//	phongShader.compileShader("Source\\Resources\\shader\\phong.frag");
	//	phongShader.compileShader("Source\\Resources\\shader\\phong.vert");
	//	phongShader.link();
	//	phongShader.validate();
	//	phongShader.use();
	//}
	//catch (GLSLProgramException & e) {
	//	cerr << e.what() << endl;
	//	exit(EXIT_FAILURE);
	//}

	///////////////Create Lights/////////////
	//Light roomLight;
	//roomLight.setIntensity(
	//	glm::vec3(0.7f, 0.7f, 0.7f),	//Ambient
	//	glm::vec3(0.8f, 0.8f, 0.8f),	//Diffuse
	//	glm::vec3(1.0f, 1.0f, 1.0f),	//Specular
	//	100.0f							//Light radius
	//);

	//roomLight.setPosition(0.0f, 30.0f, 0.0f);

	//////////////Create Material//////////
	//Material material;
	//material.setReflectivity(
	//	glm::vec3(0.7f, 0.7f, 0.7f),
	//	glm::vec3(0.8f, 0.8f, 0.8f),
	//	glm::vec3(1.0f, 1.0f, 1.0f),
	//	200.0f							//Specular highlight
	//);

	//QuatCamera cam;

	//Mesh roomMesh;
	//if (!roomMesh.load("room.obj")) {
	//	return 0;
	//}

	//Mesh bearMesh;
	//if (!bearMesh.load("bear.obj")) {
	//	return 0;
	//}

	//Bitmap cubeBMP = Bitmap::bitmapFromFile("Source\\Resources\\textures\\cube.bmp");
	//cubeBMP.flipVertically();

	//Bitmap bearBMP = Bitmap::bitmapFromFile("Source\\Resources\\textures\\bear.png");
	//bearBMP.flipVertically();

	////Load Texture
	//Bitmap bmp = Bitmap::bitmapFromFile("Source\\Resources\\textures\\room.png");
	//bmp.flipVertically();
	//Texture* gTexture = new Texture(bmp);
	//Texture* cubeTexture = new Texture(cubeBMP);
	//Texture* bearTexture = new Texture(bearBMP);

	//Model box;
	//box.setMesh(&roomMesh,gTexture);
	//box.setScale(glm::vec3(1.0, 1.0, 1.0));
	//box.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//Model bear;
	//bear.setMesh(&bearMesh, bearTexture);
	////bear.setScale(glm::vec3(1.0, 1.0, 1.0));
	//bear.setPosition(glm::vec3(0.0f, -1.0f, 75.0f));
	//bear.setRotation(180,Axis::yAxis);

	//glfwSetCursorPosCallback(window, mouseMove);
	//glfwSetCursorPosCallback(window, mouseStop);
	//
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//
	//double mX = 0, mY = 0, prevX = 0, prevY = 0;


	//Mesh cubeMesh;
	//cubeMesh.load("cube.obj");
	//MyRobot robot(&cubeMesh);
	//robot.setPosition(0.0f, 7.8f, 0.0f);

	////Delta time
	//float dt, time, oldTime = 0;
	//oldTime = glfwGetTime();

	//std::shared_ptr<Engine> engine = Engine::getInstance();

	//gl::Enable(gl::DEPTH_TEST);
	//while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {

	//	////////////UPDATE//////////////////////
	//	//Calculate time step
	//	time = glfwGetTime();
	//	dt = time - oldTime;
	//	oldTime = time;
	//	//std::cout << dt << "\n";

	//	float fS = 10.0f;

	//	if (bUp) {
	//		robot.moveForward();
	//		//box.translate(glm::vec3(fS * dt, 0.0f, 0.0f));
	//	}
	//	else if (bDown) {
	//		robot.moveBackward();
	//		//box.translate(glm::vec3(-fS * dt, 0.0f, 0.0f));
	//	}

	//	if (bLeft) {
	//		robot.turnLeft();
	//	}
	//	else if (bRight) {
	//		robot.turnRight();
	//	}

	//	float fSpeed = 10.0f * dt;
	//	//Move Camera
	//	if (bA) {								//Move Left
	//		cam.pan(-fSpeed,0.0f);
	//	}
	//	else if (bD) {							//Move Right
	//		cam.pan(+fSpeed, 0.0f);
	//	}
	//	else if (bS && bLShift) {				//Move UP
	//		cam.pan(0.0f, fSpeed);
	//	}
	//	else if (bW && bLShift) {				//Move Down;
	//		cam.pan(0.0f, -fSpeed);
	//	}
	//	else if (bW) {							//Move Forwards
	//		
	//		cam.zoom(fSpeed);
	//	}
	//	else if (bS) {							//Move Backwards
	//		cam.zoom(-fSpeed);
	//	}

	//	else if (bSpace) {
	//		cam.reset();
	//		cam.setPosition(glm::vec3(3.0, 5.0f, 5.0f));
	//		cam.rotate(glm::radians(-25.0f), glm::radians(45.0f));
	//	}
	//	//cam.lookAt(robot.getPosition());
	//	robot.update(dt);

	//	//Mouse//Camera rotation
	//	double dX, dY;
	//	float rotateVel = 0.1f;	//Camera rotation velocity
	//	glfwGetCursorPos(window, &mX, &mY);
	//	dX = prevX - mX;
	//	dY = prevY - mY;
	//	prevX = mX;
	//	prevY = mY;
	//	cam.rotate((-dX * rotateVel) * (1 / 60.0f), (-dY * rotateVel) * (1 / 60.0f));

	//	//////////////////LIGHTS//////////
	//	updateLight(phongShader, roomLight, material, cam);
	//	updateLight(colourShader, roomLight, material, cam);

	//	//////////////////RENDER//////////
	//	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	//	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	//	bear.draw(&phongShader);
	//	box.draw(&phongShader);
	//	robot.draw(&colourShader);

	//	glfwSwapInterval(1);		//VSYNC OFF
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//	time = glfwGetTime();
	//}
	//delete gTexture;
	////Close window and terminate GLFW
	//glfwTerminate();

	return 0;
}