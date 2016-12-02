#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "Camera.h"
#include "Robot.h"
#include "ModelReader.h"
#include "Bitmap.h"
#include "Texture.h"


bool bW, bS, bA, bD,
bUp, bDown, bLeft, bRight,
bSpace, bLShift;

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
	glfwWindowHint(GLFW_DEPTH_BITS, 32);								//Enable Depth buffer

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
	ModelReader loader;	//Object loader

	Model loadedCube = loader.ReadModelObjData("Source\\Resources\\models\\cube.obj");
	loadedCube.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	loadedCube.setPosition(glm::vec3(-10.0f, 5.0f, 3.0f));

	Model loadedSphere = loader.ReadModelObjData("Source\\Resources\\models\\sphere.obj");
	loadedSphere.setColour(glm::vec3(0.0f, 1.0f, 1.0f));
	loadedSphere.setPosition(glm::vec3(10.0f, 5.0f, 5.0f));

	Model loadedCylinder = loader.ReadModelObjData("Source\\Resources\\models\\cylinder.obj");
	loadedCylinder.setColour(glm::vec3(1.0f, 0.0f, 1.0f));
	loadedCylinder.setPosition(glm::vec3(5.0f, 10.0f, -5.0f));

	Model loadedPlane = loader.ReadModelObjData("Source\\Resources\\models\\plane.obj");
	loadedPlane.setColour(glm::vec3(0.0f, 0.7f, 0.3f));
	loadedPlane.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	loadedPlane.setScale(glm::vec3(10.f, 1.0f, 10.0f));

	Graphics* graphics = new Graphics();
	graphics->init();

	Camera camera = Camera(90.0f, 1.0f, 0.1f, 100.0f);
	glm::vec3 CameraPos(0.0f, 10.0f, 20.0f);
	glm::vec3 CameraFace(0.0f, 10.0f, 0.0f);
	glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
	camera.setPosition(CameraPos);
	camera.setFacing(CameraFace);
	camera.setUpVector(CameraUp);
	
	Robot robot;
	robot.setCamera(&camera);
	robot.setShader(graphics->programHandle);
	robot.setPosition(0.0f, 10.0f, 0.0f);

	//Load Texture
	Bitmap bmp = Bitmap::bitmapFromFile("Source\\Resources\\textures\\red.bmp");
	Texture* gTexture = new Texture(bmp);
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	GLint loc = gl::GetUniformLocation(graphics->programHandle,"tex");
	gl::Uniform1f(loc, 0);

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		float dt = glfwGetTime();
		//triangle.rotate(1.0f, yAxis);
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		gl::Enable(gl::DEPTH_TEST);			//Enable depth buffer
		robot.Prepare(0.1f);
		//graphics->update((float)glfwGetTime());
		//triangle.draw(graphics->programHandle,&camera);
		//triangle2.draw(graphics->programHandle,&camera);
		glfwSetKeyCallback(window, key_callback);

		float fSpeed = 1.0f;
		///////Move Camera///////////////
		if (bUp && bLShift) {		//Move Camera forward
			CameraPos.z -= fSpeed;
			CameraFace.z -= fSpeed;
		}
		else if (bDown && bLShift) {	//Move Camera backwward
			CameraPos.z += fSpeed;
			CameraFace.z += fSpeed;
		}
		else if (bLeft && bLShift) {	//Move Camera left
			CameraPos.x -= fSpeed;
			CameraFace.x -= fSpeed;
		}
		else if (bRight && bLShift) {	//Move Camera right
			CameraPos.x += fSpeed;
			CameraFace.x += fSpeed;
		}
		else if (bW && bLShift) {		//Move UP
			CameraPos.y += fSpeed;
			CameraFace.y += fSpeed;
		}
		else if (bS && bLShift) {		//Move DOWN
			CameraPos.y -= fSpeed;
			CameraFace.y -= fSpeed;
		}
		//Change camera facing /*Broken*/
		else if (bLeft) {					//Camera turn left
			CameraFace.x -= fSpeed;
		}
		else if (bRight) {				//Camera turn right
			CameraFace.x += fSpeed;
		}
		else if (bUp) {					//Camera look up		
			CameraFace.y += fSpeed;
		}
		else if (bDown) {				//Camera look down
			CameraFace.y -= fSpeed;
		}
		
		/////////////Move Robot//////////////
		if (bA) {								//Move Left
			robot.moveLeft();
		}
		else if (bD) {							//Move Right
			//CameraPos.x += fSpeed;
			//CameraFace.x += fSpeed;
			robot.moveRight();
		}
		else if (bW) {							//Move Forward
			robot.moveForward();
		}
		else if (bS) {							//Move Backwards
			robot.moveBackward();
		}

		else if (bSpace) {
			CameraPos = glm::vec3 (0.0f, 10.0f, 20.0f);
			CameraFace = glm::vec3(0.0f, 10.0f, 0.0f);
			CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			robot.setPosition(0.0f, 10.0f, 0.0f);
		}

		camera.setPosition(CameraPos);
		camera.setFacing(CameraFace);
		camera.setUpVector(CameraUp);

		loadedCube.draw(graphics->programHandle, &camera);
		loadedSphere.draw(graphics->programHandle, &camera);
		loadedCylinder.draw(graphics->programHandle, &camera);
		loadedPlane.draw(graphics->programHandle, &camera);
		robot.DrawRobot(0.0f, 0.0f, 0.0f, 0.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwSetTime(0.0f);
	}

	//Close window and terminate GLFW
	glfwTerminate();
	return 0;
}