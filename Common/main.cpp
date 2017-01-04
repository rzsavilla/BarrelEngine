#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "ModelReader.h"
#include "Bitmap.h"
#include "Texture.h"
#include "QuatCamera.h"
#include "MyRobot.h"

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

	//Compile and link shader program
	GLSLProgram shader;
	try {
		shader.compileShader("Source\\Resources\\shader\\basic.frag");
		shader.compileShader("Source\\Resources\\shader\\basic.vert");
		shader.link();
		shader.validate();
		shader.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	GLSLProgram colourShader;
	try {
		colourShader.compileShader("Source\\Resources\\shader\\colour.frag");
		colourShader.compileShader("Source\\Resources\\shader\\colour.vert");
		colourShader.link();
		colourShader.validate();
		colourShader.use();
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	//Delta time
	float dt,time,oldTime = 0;

	QuatCamera cam;

	Mesh bearMesh;
	if (!bearMesh.load("bear.obj")) {
		return 0;
	}

	//Load Texture
	Bitmap bmp = Bitmap::bitmapFromFile("Source\\Resources\\textures\\bear.png");
	bmp.flipVertically();
	Texture* gTexture = new Texture(bmp);

	Model box;
	box.setMesh(&bearMesh,gTexture);
	box.setScale(glm::vec3(1.0, 1.0, 1.0));

	GLuint textureID;
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	//GLint loc = gl::GetUniformLocation(graphics->programHandle,"tex");
	//gl::Uniform1f(loc, 0);

	glfwSetCursorPosCallback(window, mouseMove);
	glfwSetCursorPosCallback(window, mouseStop);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	oldTime = glfwGetTime();
	
	double mX = 0, mY = 0, prevX = 0, prevY = 0;

	Mesh cubeMesh;
	cubeMesh.load("cube.obj");
	MyRobot robot(&cubeMesh);

	gl::Enable(gl::DEPTH_TEST);
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {

		////////////UPDATE//////////////////////

		//Calculate time step
		time = glfwGetTime();
		dt = time - oldTime;
		oldTime = time;
		//std::cout << dt << "\n";


		if (bUp) {
			robot.moveForward();
		}
		else if (bDown) {
			robot.moveBackward();
		}

		if (bLeft) {
			robot.turnLeft();
		}
		else if (bRight) {
			robot.turnRight();
		}

		float fSpeed = 10.0f * dt;
		//Move Camera
		if (bA) {								//Move Left
			cam.pan(-fSpeed,0.0f);
		}
		else if (bD) {							//Move Right
			cam.pan(+fSpeed, 0.0f);
		}
		else if (bS && bLShift) {				//Move UP
			cam.pan(0.0f, fSpeed);
		}
		else if (bW && bLShift) {				//Move Down;
			cam.pan(0.0f, -fSpeed);
		}
		else if (bW) {							//Move Forwards
			
			cam.zoom(fSpeed);
		}
		else if (bS) {							//Move Backwards
			cam.zoom(-fSpeed);
		}

		else if (bSpace) {
			cam.reset();
		}

		robot.update(dt);

		//Mouse//Camera rotation
		double dX, dY;
		float rotateVel = 0.01f;	//Camera rotation velocity
		glfwGetCursorPos(window, &mX, &mY);
		dX = prevX - mX;
		dY = prevY - mY;
		prevX = mX;
		prevY = mY;
		//printf_s("DX: %f Prev: %i Cur: %i\n", dX, prevMousePos[0], mousePos[0]);
		cam.rotate((-dX * rotateVel) * dt, (-dY * rotateVel) * dt);

		//Camera View and Projection matrices to shader
		shader.use();
		shader.setUniform("mView", cam.view());
		shader.setUniform("mProjection", cam.projection());
		colourShader.use();
		colourShader.setUniform("mView", cam.view());
		colourShader.setUniform("mProjection", cam.projection());

		//////////////////RENDER//////////

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		box.draw(&shader);
		robot.draw(&colourShader);

		glfwSwapInterval(1);		//VSYNC
		glfwSwapBuffers(window);
		glfwPollEvents();
		time = glfwGetTime();
	}

	//Close window and terminate GLFW
	glfwTerminate();
	return 0;
}