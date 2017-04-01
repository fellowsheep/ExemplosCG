//*****************************************************
//
// PrimeiroProjeto - OpenGL2 + GLFW
//
// Finalmente, removendo a GLUT da história :D
//
// Adaptado do projeto com GLUT por Rossana B. Queiroz 08/2011
// Este projeto também possui fortes influências do
// Tutorial de GLUT do LightHouse3D - http://www.lighthouse3d.com/tutorials/glut-tutorial/
// com a implementação da câmera (Moving the Camera I)
//
// Última modificação: 31/03/2017
//*****************************************************

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "SceneManager.h" //é a SceneManager que está incluindo a glfw!


//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------

// actual vector representing the camera's direction 
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, y = 0.5f, z = 5.0f;
// the key states. These variables will be zero

// angle of rotation for the camera direction
float angle = 0.0f;

//displacement when key is pressed
float deltaMove = 0.5;

//Objeto gerenciador da cena
SceneManager *scene;


using namespace std;

//-----------------------------------------------------------------------------
// CALLBACK DE RENDERING
//-----------------------------------------------------------------------------

void RenderScene()
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
		x + lx , y, z + lz,
		0.0f, 1.0, 0.0f);

	//Chama o método para desenhar o chão quadriculado
	scene->drawGround();

	//Desenho de alguns pontos para debug - didático apenas
	scene->drawPoint(vec3(0.0, 0.0, 0.0));
	scene->drawPoint(vec3(0.0, 0.0, -2.0), vec3(255,0,255));
	scene->drawPoint(vec3(0.0, 0.0, 2.0));
	
	//Desenha um triângulo passando as coordenadas de 3 pontos 
	scene->drawTri(vec3(-1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 2.0, 0.0));

	//Desenha um cubo passando por parâmetro as dimensões, pos do centro, cor e modo de desenho
	scene->drawCube(vec3(1,1,1),vec3(0.0, 0.5, 0.0),vec3(0,255,255),GL_QUADS);
	scene->drawCube(vec3(1, 1, 1), vec3(0.0, 0.5, 0.0), vec3(100, 100, 100), GL_LINE_LOOP);

}


//------ GLFW Callbacks
//Callback de erro 
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

//Callback de teclado
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W)
	{ 
		x += deltaMove * lx ;
		z += deltaMove * lz ;
	}
	if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S)
	{
		x -= deltaMove * lx ;
		z -= deltaMove * lz ;
	}
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A)
	{
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
	{
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
	}
}

//Callback de redimensionamento
void reshape(GLFWwindow* window, int width, int height)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (height == 0)
		height = 1;
	float ratio = width * 1.0 / height;

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	
}

// Programa Principal 
int main(void)
{
	
	//Inicialização da janela da aplicação
	GLFWwindow* window;

	//Setando a callback de erro
	glfwSetErrorCallback(error_callback);

	//Inicializando a lib
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Criando a janela
	window = glfwCreateWindow(640, 480, "HELLO GLFW!! BYE BYE GLUT!!! :D", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Colocando a janela criada como sendo o contexto atual
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Setando a callback de teclado
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de reshape
	glfwSetFramebufferSizeCallback(window, reshape);
	
	//Criação do objeto que gerencia a cena
	scene = new SceneManager;
	

	reshape(window, 640, 480);

	while (!glfwWindowShouldClose(window)) //loop da aplicação :)
	{
		int width, height;

		//aqui recupera o tamanho atual da janela, para correção do aspect ratio mais tarde
		glfwGetFramebufferSize(window, &width, &height);
		
		//Função que renderiza a cena
		RenderScene();

		//trocando os buffers 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}
