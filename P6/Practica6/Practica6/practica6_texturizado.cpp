/*
Semestre 2022-1
Práctica 6 Texturizado
Usando librería stb_image.h 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>

//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include "Sphere.h"
#include"Window.h"
#include "Camera.h"
#include"Texture.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float codo = 0.0f;

Texture T_ladrillos;
Texture T_asfalto;
Texture T_dado;
Texture T_caras;
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";
Sphere sp = Sphere(1, 20, 20);

//ejercicio 1 para hacer en clase, el cubo
void CrearDodecaedro()
{
	unsigned int dodecaedro_indices[] = {
		// front
		0,1,2,
		2,3,0,
		3,4,0,

		5,6,7,
		7,8,5,
		8,9,5,

		10,14,13,
		13,10,11,
		11,12,13,

		15,19,18,
		18,15,16,
		16,17,18,

		20,24,23,
		23,20,21,
		21,22,23,
		
		25,29,28,
		28,25,26,
		26,27,28,

		30,34,33,
		33,30,31,
		31,32,33,

		35,39,38,
		38,35,36,
		36,37,38,

		40,44,43,
		43,40,41,
		41,42,43,

		45,49,48,
		48,45,46,
		46,47,48,

		50,54,53,
		53,50,51,
		51,52,53,

		55,59,58,
		58,55,56,
		56,57,58,

	};

	GLfloat dodecaedro_vertices[] = {
		// front
		//x		y		z				u		v
		 //Bottom
		  0.0f,  0.0f,  -1.0f, 			0.65094f, 0.3972f, //0		A
		  1.0f,  0.0f,  -1.0f,			0.73546f, 0.28048f, //1		B
		  1.31f, 0.0f,  -0.05f,			0.81596f, 0.3972f,//2		C
		  0.5f,  0.0f,   0.54f,			0.7851f, 0.59039f,//3		D
		 -0.31f, 0.0f,  -0.05f,			0.68448f, 0.59575f,//4		E

		 //PRIMERAS 5
		  1.31f, 0.0f, -0.05f,			0.8f, 0.6f, 			//5 
		  0.5f,  0.0f,  0.54f,			0.83743f, 0.41732f, 			//6
		  0.5f,  0.85f, 1.06f,			0.93805f, 0.41195f,	//H		//7
		  1.31f, 1.38f, 0.8f,			0.9689f, 0.60783f,	//M		//8
		  1.81f, 0.85f, 0.1f,			0.88975f, 0.71516f,	//G		//9

		  0.5f,  0.0f,  0.54f,			0.68314f, 0.63734f,	//10
		 -0.31f, 0.0f, -0.05f,			0.78376f, 0.63064f,	//11
		 -0.81f, 0.85f, 0.11f,			0.81328f, 0.82383f,	//I		//12
		 -0.31f, 1.38f, 0.8f,			0.73278f, 0.94055f,	//N		//13
		  0.5f,  0.85f, 1.06f,			0.65228f, 0.82383f,	//14

		 -0.31f, 0.0f,  -0.05f,			0.53422f, 0.41061f,			//15
		  0.0f,  0.0f,  -1.0f,			0.62411f, 0.40525f,			//16
		 -0.31f, 0.85f, -1.43f,			0.65497f, 0.59844f,	//J		//17
		 -0.81f, 1.38f, -0.74f,			0.57447f, 0.72857f,	//O		//18
		 -0.81f, 0.85f,  0.11f,			0.5f, 0.6f,			//19

		  0.0f,  0.0f,  -1.0f,			0.59191f, 0.06314f,			//20
		  1.0f,  0.0f,  -1.0f,			0.68314f, 0.06314f,			//21
		  1.31f, 0.85f, -1.43f,			0.71131f, 0.24425f,	//F		//22
		  0.5f,  1.38f, -1.69f,			0.63216f, 0.36232f,	//K		//23
		 -0.31f, 0.85f, -1.43f,			0.56374f, 0.24023f,			//24

		  1.0f,  0.0f,  -1.0f,			0.78108f, 0.04838f,	//B		//25
		  1.31f, 0.0f,  -0.05f,			0.87365f, 0.05509f,	//C
		  1.81f, 0.85f,  0.1f,			0.90853f, 0.25365f,	//G
		  1.81f, 1.38f, -0.74f,			0.83206f, 0.35829f,	//L
		  1.31f, 0.85f, -1.43f,			0.74888f, 0.2523f,//F		//29
		  
		  //SEGUNDAS 5
		   0.5f,  1.38f, -1.69f,		0.37055f, 0.59039f,	//K		//30
		   1.31f, 0.85f, -1.43f,		0.33835f, 0.3972f,	//F
		   1.81f, 1.38f, -0.74f,		0.42153f, 0.27645f,	//L
		   1.31f, 2.23f, -0.57f,		0.5f, 0.4f,	//Q
		   0.5F, 2.23f, -1.16F,			0.46714f, 0.59039f,//P		  34

		   1.81f, 1.38f, -0.74f,		0.3142f, 0.36902f,			//35
		   1.81f, 0.85f,  0.1f,			0.21761f, 0.37036f,	//G
		   1.31f, 1.38f,  0.8f,			0.18004f, 0.17583f,
		   1.0f,  2.23f,  0.38f,		0.2659f, 0.0618f,	//R
		   1.31f, 2.23f, -0.57f,		0.34908f, 0.18522f,	//Q		  39

		   1.31f, 1.38f, 0.8f,			0.2f, 0.4f,	//M		  40
		   0.5f,  0.85f, 1.06f,			0.15992f, 0.59039f,	//H
		  -0.31f, 1.38f, 0.8f,			0.0593f, 0.59575f,//N
		   0.0f,  2.23f, 0.38f,			0.03112f, 0.40122f,//S
		   1.0f,  2.23f, 0.38f,			0.11296f, 0.29255f,	//R

		  -0.31f, 1.38f, 0.8f,			0.16797f, 0.63466f,	//N		  45
		  -0.81, 0.85f, 0.11f,			0.25383f, 0.75138f,	//I
		  -0.81f, 1.38f, -0.74f,		0.21761f, 0.94457f,//O
		  -0.31f, 2.23f, -0.57f,		0.12503f, 0.94323f,//T
		   0.0f, 2.23f, 0.38f,			0.08849f, 0.74683f,	//S		  49

		  -0.81f, 1.38f, -0.74f,		0.282f, 0.74735f,	//O		  50
		  -0.31f, 0.85f, -1.43f,		0.36518f, 0.636f,
		   0.5f,  1.38f, -1.69f,		0.44118f, 0.7441f,
		   0.5F, 2.23f, -1.16F,			0.4112f, 0.94782f,	//P
		  -0.31f, 2.23f, -0.57f,		0.31282f, 0.94782f,	//T		  54

		   //Top
			0.5F, 2.23f, -1.16F,		0.22029f, 0.4133f,//P		  55
			1.31f, 2.23f, -0.57f,		0.31688f, 0.41464f,	//Q
			1.0f, 2.23f, 0.38f,			0.34908f, 0.60246f,	//R
			0.0f, 2.23f, 0.38f,			0.2659f, 0.72455f,//S
		  -0.31f, 2.23f, -0.57f,		0.19058f, 0.60498f,	//T		  59



};
Mesh *dodecaedro = new Mesh();
dodecaedro ->CreateMesh(dodecaedro_vertices, dodecaedro_indices,300 , 108 );   //180, 108
meshList.push_back(dodecaedro);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearDodecaedro();
	CreateShaders();

	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_ladrillos = Texture("Textures/ladrillos.tga");
	T_ladrillos.LoadTexture();
	T_asfalto = Texture("Textures/dirt.png");
	T_asfalto.LoadTexture();
	T_dado = Texture("Textures/dado2.tga");
	T_dado.LoadTexture();
	T_caras = Texture("Textures/carasDode.tga");
	T_caras.LoadTexture();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		//uniformColor = shaderList[0].getColorLocation();
		//ejercicio 1:
		glm::mat4 model(1.0);

		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T_caras.UseTexture();
		//T_ladrillos.UseTexture();
		meshList[0]->RenderMesh();

		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_asfalto.UseTexture();
		meshList[1]->RenderMesh();*/

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}