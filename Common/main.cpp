#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "Robot.h"
#include "ModelReader.h"
#include "Bitmap.h"
#include "Texture.h"
#include "QuatCamera.h"

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
	prevMousePos[0] = mousePos[0];
	prevMousePos[1] = mousePos[1];

	mousePos[0] = (float)xpos;
	mousePos[1] = (float)ypos;
}

int main() {

	unsigned int uiWidth = 1024;
	unsigned int uiHeight = 768;

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

	//Load Shader program
	Graphics* graphics = new Graphics();
	graphics->init();

	QuatCamera cam;

	Mesh CubeMesh;
	if (!CubeMesh.load("bear.obj")) {
		return 0;
	}

	//Load Texture
	Bitmap bmp = Bitmap::bitmapFromFile("Source\\Resources\\textures\\bear.png");
	bmp.flipVertically();
	Texture* gTexture = new Texture(bmp);

	Model box;
	box.setMesh(&CubeMesh,gTexture);
	box.setScale(glm::vec3(1.0, 1.0, 1.0));
	//box.setTexture(gTexture);

	GLuint textureID;
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	GLint loc = gl::GetUniformLocation(graphics->programHandle,"tex");
	gl::Uniform1f(loc, 0);

	glfwSetCursorPosCallback(window, mouseMove);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		//Handle Inputs

		float dt = glfwGetTime();
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		gl::Enable(gl::DEPTH_TEST);			//Enable depth buffer

		glfwSetKeyCallback(window, key_callback);

		float fSpeed = 0.1f;
		//Move Camera
		if (bA) {								//Move Left
			cam.pan(-fSpeed,0.0f);
		}
		else if (bD) {							//Move Right
			cam.pan(+fSpeed, 0.0f);
		}
		else if (bS && bLShift) {				//Move Forwards
			cam.pan(0.0f, -fSpeed);
		}
		else if (bW && bLShift) {				//Move Backwards;
			cam.pan(0.0f, fSpeed);
		}
		else if (bS) {							//Move Down
			cam.zoom(-fSpeed);
		}
		else if (bW) {							//Move Up
			
			cam.zoom(fSpeed);
		}
		else if (bSpace) {
			cam.reset();
		}

		float dX = prevMousePos[0] - mousePos[0];
		float dY = prevMousePos[1] - mousePos[1];
		//printf_s("DX: %f Prev: %i Cur: %i\n", dX, prevMousePos[0], mousePos[0]);

		float rotateVel = 0.001f;
		
		printf_s("%f\t %f\t %f\n",dX, dX * rotateVel, dY * rotateVel);
		if (dX != 0 && dY != 0) {
			
		}
		cam.rotate(dX * rotateVel, dY * rotateVel);

		box.draw(graphics->programHandle, &cam);

		glfwSwapBuffers(window);
		glfwWaitEvents();
		glfwSetTime(0.0f);
	}

	//Close window and terminate GLFW
	glfwTerminate();
	return 0;
}