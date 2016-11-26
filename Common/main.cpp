#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "Camera.h"
#include "Robot.h"


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

	Model triangle;

	Vertex top, botL, botR;

	top.Position = glm::vec3(0.0f, 0.5f, 0.0f);
	botL.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
	botR.Position = glm::vec3(0.5f, -0.5f, 0.0f);

	top.Colour = glm::vec3(0.0f, 0.0f, 1.0f);
	botL.Colour = glm::vec3(1.0f, 0.0f, 0.0f);
	botR.Colour = glm::vec3(1.0f, 0.0f, 0.0f);

	triangle.vertices.push_back(top);
	triangle.vertices.push_back(botL);
	triangle.vertices.push_back(botR);

	triangle.indices.push_back(0);
	triangle.indices.push_back(1);
	triangle.indices.push_back(2);
	triangle.indices.push_back(2);

	triangle.set();

	Model triangle2;


	top.Position = glm::vec3(0.0f, 0.f, 0.0f);
	botL.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
	botR.Position = glm::vec3(0.5f, -0.5f, 0.0f);

	triangle2.vertices.push_back(top);
	triangle2.vertices.push_back(botL);
	triangle2.vertices.push_back(botR);

	top.Colour = glm::vec3(1.0f, 1.0f, 0.0f);
	botL.Colour = glm::vec3(1.0f, 0.0f, 0.0f);
	botR.Colour = glm::vec3(1.0f, 0.0f, 0.0f);

	triangle2.indices.push_back(0);
	triangle2.indices.push_back(1);
	triangle2.indices.push_back(2);

	triangle2.set();

	Graphics* graphics = new Graphics();
	graphics->init();

	Camera camera = Camera(90.0f, 1.0f, 0.1f, 100.0f);
	glm::vec3 CameraPos(0.0f, 5.0f, 20.0f);
	glm::vec3 CameraFace(0.0f, 0.0f, 0.0f);
	glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
	camera.setPosition(CameraPos);
	camera.setFacing(CameraFace);
	camera.setUpVector(CameraUp);
	


	Robot robot;
	robot.setCamera(&camera);
	robot.setShader(graphics->programHandle);

	

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
		//Change camera facing /*Broken*/
		if (bLeft) {
			CameraFace.x -= fSpeed;
		}
		else if (bRight) {
			CameraFace.x += fSpeed;
		}
		else if (bUp) {
			CameraFace.y += fSpeed;
		}
		else if (bDown) {
			CameraFace.y -= fSpeed;
		}
		//Move Camera
		if (bA) {								//Move Left
			//CameraPos.x -= fSpeed;
			//CameraFace.x -= fSpeed;
			robot.moveLeft();
		}
		else if (bD) {							//Move Right
			//CameraPos.x += fSpeed;
			//CameraFace.x += fSpeed;
			robot.moveRight();
		}
		else if (bW && bLShift) {							//Move UP
			CameraPos.y += fSpeed;
			CameraFace.y += fSpeed;
		}
		else if (bS && bLShift) {							//Move DOWN
			CameraPos.y -= fSpeed;
			CameraFace.y -= fSpeed;
		}
		else if (bW) {							//Move Forward
			//CameraPos.z -= fSpeed;
			//CameraFace.z -= fSpeed;
			robot.moveForward();
		}
		else if (bS) {							//Move Backwards
			//CameraPos.z += fSpeed;
			//CameraFace.z += fSpeed;
			robot.moveBackward();
		}

		else if (bSpace) {
			CameraPos = glm::vec3 (0.0f, 0.0f, 20.0f);
			CameraFace = glm::vec3(0.0f, 0.0f, 0.0f);
			CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		camera.setPosition(CameraPos);
		camera.setFacing(CameraFace);
		camera.setUpVector(CameraUp);

		robot.DrawRobot(0.0f, 0.0f, 0.0f, 0.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwSetTime(0.0f);
	}

	//Close window and terminate GLFW
	glfwTerminate();
	return 0;
}