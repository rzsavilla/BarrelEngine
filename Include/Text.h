#pragma once

#include "Drawable.h"

/*
	https://learnopengl.com/#!In-Practice/Text-Rendering
*/

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class Text :public Drawable {
private:
	std::string m_string;
	glm::vec2 m_vPos;
	glm::vec3 m_vColour;
	std::shared_ptr<GLSLProgram> m_shader;
	float m_fScale;
	std::map<GLchar, Character>* m_Characters;

	GLuint VAO, VBO;
public:
	Text(std::string string, std::map<GLchar, Character>* characters, float x, float y, glm::vec3 colour, float scale);

	void setString(std::string string);

	void setShader(std::shared_ptr<GLSLProgram> shader);

	void draw();
};