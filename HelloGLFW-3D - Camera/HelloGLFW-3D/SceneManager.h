#include <iostream>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>


struct color
{
	int R,G,B;
};

struct vec3
{
	float x, y, z;
	vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class SceneManager {
public:
	SceneManager() {}
	~SceneManager() {}
	//void drawCube();
	void drawGround();
	void renderWireCube(GLdouble dSize);
	void renderSolidCube(GLdouble dSize);
	void drawTri(vec3 p1, vec3 p2, vec3 p3);
	void drawPoint(vec3 p, vec3 color = vec3(0,255,255));
	void drawCube(vec3 dims, vec3 pos, vec3 color, GLint mode = GL_QUADS);
};