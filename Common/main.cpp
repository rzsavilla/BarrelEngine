#include "stdafx.h"

#include "Graphics.h"
#include "Model.h"
#include "Camera.h"

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
	//Open window
	GLFWwindow *window = glfwCreateWindow(500, 500, "Barrel Engine" , NULL, NULL);
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

	triangle.set();

	Model triangle2;

	//Vertex top, botL, botR;

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

	Camera camera = Camera(45.0f, 1.0f, 0.1f, 100.0f);
	camera.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera.setFacing(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.setUpVector(glm::vec3(0.0f, 1.0f, 0.0f));

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		gl::Clear(gl::COLOR_BUFFER_BIT);
		gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		graphics->update((float)glfwGetTime());
		triangle.draw(graphics->programHandle,&camera);
		triangle2.draw(graphics->programHandle,&camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Close window and terminate GLFW
	glfwTerminate();
	return 0;
}