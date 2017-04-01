#include "SceneManager.h"

#include <fstream>
#include <string>

#include <vector>

using namespace std;


//void SceneManager::drawCube()
//{
//	//glPushMatrix();	
//	glColor3ub(255,0,0);
//	renderSolidCube(1.0);
//	glColor3ub(0,0,0);
//	renderWireCube(1.0);
//	//glPopMatrix();
//	
//}

void SceneManager::drawTri(vec3 p1, vec3 p2, vec3 p3)
{
	glPointSize(15);
	glLineWidth(3);

	// Desenha um triângulo no centro da janela
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);
	//glVertex3f(-0.5, -0.5);
	glVertex3f(p1.x, p1.y, p1.z);
	glColor3ub(0, 255, 0);
	//glVertex3f(0.0, 0.5, 0);
	glVertex3f(p2.x, p2.y, p2.z);
	glColor3ub(0, 0, 255);
	glVertex3f(p3.x, p3.y, p3.z);
	//glVertex3f(0.5, -0.5, 0);
	glEnd();

	glColor3ub(150,150,150);
	glBegin(GL_LINE_LOOP);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_POINTS);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

	glPointSize(1);
	glLineWidth(1);
}

void SceneManager::drawPoint(vec3 p, vec3 color)
{
	glPointSize(15);
	glColor3ub(color.x, color.y, color.z);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();

}

void SceneManager::drawCube(vec3 dims, vec3 pos, vec3 color, GLint mode)
{
	vec3 v[8] = {
	vec3(-0.5, -0.5, -0.5),
	vec3(-0.5, -0.5, 0.5),
	vec3(-0.5, 0.5, -0.5),
	vec3(-0.5, 0.5, 0.5),
	vec3(0.5, -0.5, -0.5),
	vec3(0.5, -0.5, 0.5),
	vec3(0.5, 0.5, -0.5),
	vec3(0.5, 0.5, 0.5), };

	int f[6][4]=
	{
		0, 2, 6, 4,
		5, 7, 6, 4,
		7, 3, 2, 6,
		5, 1, 0, 4,
		1, 3, 7, 5,
		1, 3, 2, 0
	};

	glColor3ub(color.x, color.y, color.z);
	glLineWidth(3);

	for (int i = 0; i < 6; i++) //numero de faces
	{
		glBegin(mode);
		for (int j = 0; j < 4; j++) //numero de vertices
		{
			glVertex3f(pos.x+v[f[i][j]].x, pos.y+v[f[i][j]].y, pos.z+v[f[i][j]].z);	
		}
		glEnd();
	}
	glLineWidth(1);
}

void SceneManager::drawGround()
{
	float y = -0.0;
	// Draw ground
	int count = 0;
	for (int i = -100; i <= 100; i += 1) //linhas
		for (int j = -100; j <= 100; j += 1) //colunas
		{
			if (count % 2)
				glColor3f(0.5f, 0.5f, 0.5f);
			else glColor3f(1.0f, 1.0f, 1.0f);
			count++;
			glBegin(GL_QUADS);
			glVertex3f(j, y, i);
			glVertex3f(j, y, i + 1);
			glVertex3f(j + 1, y, i + 1);
			glVertex3f(j + 1, y, i);
			glEnd();
		}
}

/*
* Draws a wireframed cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
*/
void SceneManager::renderWireCube(GLdouble dSize)
{
	double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	/*
	* PWO: I dared to convert the code to use macros...
	*/
	glBegin(GL_LINE_LOOP); N(1.0, 0.0, 0.0); V(+, -, +); V(+, -, -); V(+, +, -); V(+, +, +); glEnd();
	glBegin(GL_LINE_LOOP); N(0.0, 1.0, 0.0); V(+, +, +); V(+, +, -); V(-, +, -); V(-, +, +); glEnd();
	glBegin(GL_LINE_LOOP); N(0.0, 0.0, 1.0); V(+, +, +); V(-, +, +); V(-, -, +); V(+, -, +); glEnd();
	glBegin(GL_LINE_LOOP); N(-1.0, 0.0, 0.0); V(-, -, +); V(-, +, +); V(-, +, -); V(-, -, -); glEnd();
	glBegin(GL_LINE_LOOP); N(0.0, -1.0, 0.0); V(-, -, +); V(-, -, -); V(+, -, -); V(+, -, +); glEnd();
	glBegin(GL_LINE_LOOP); N(0.0, 0.0, -1.0); V(-, -, -); V(-, +, -); V(+, +, -); V(+, -, -); glEnd();

#   undef V
#   undef N
}

/*
* Draws a solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
*/
void SceneManager::renderSolidCube(GLdouble dSize)
{
	double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	/*
	* PWO: Again, I dared to convert the code to use macros...
	*/
	glBegin(GL_QUADS);
	N(1.0, 0.0, 0.0); V(+, -, +); V(+, -, -); V(+, +, -); V(+, +, +);
	N(0.0, 1.0, 0.0); V(+, +, +); V(+, +, -); V(-, +, -); V(-, +, +);
	N(0.0, 0.0, 1.0); V(+, +, +); V(-, +, +); V(-, -, +); V(+, -, +);
	N(-1.0, 0.0, 0.0); V(-, -, +); V(-, +, +); V(-, +, -); V(-, -, -);
	N(0.0, -1.0, 0.0); V(-, -, +); V(-, -, -); V(+, -, -); V(+, -, +);
	N(0.0, 0.0, -1.0); V(-, -, -); V(-, +, -); V(+, +, -); V(+, -, -);
	glEnd();

#   undef V
#   undef N
}

