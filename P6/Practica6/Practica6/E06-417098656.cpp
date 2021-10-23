/*
Semestre 2022-1
Pr�ctica 6 Texturizado
Usando librer�a stb_image.h 
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
//clases para dar orden y limpieza al c�digo
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
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";
Sphere sp = Sphere(1, 20, 20);

void CreateObject()
{
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,	0.0f,	0.0f,
		0.0f,-0.5f,0.5f,	1.0f,	0.0f,
		0.5f,-0.5f, 0.0f,	1.0f,	1.0f,
		0.0f,0.5f,0.0f,		0.0f,	1.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10,11, 8,
		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};

	//GLfloat cubo_vertices[] = {
	//	// front
	//	//x		y		z		u		v
	//	-0.5f, -0.5f,  0.5f,	0.26f,	0.34f, //0
	//	 0.5f, -0.5f,  0.5f,	0.49f,	0.34f, //1
	//	 0.5f,  0.5f,  0.5f,	0.49f,	0.66f, //2
	//	-0.5f,  0.5f,  0.5f,	0.26f,	0.66f, //3
	//	//right
	//	0.5f, -0.5f,  0.5f,		0.51f,  0.34f,  //4
	//	0.5f, -0.5f, -0.5f,		0.74f, 0.34f,   //5
	//	0.5f,  0.5f, -0.5f,		0.74f, 0.66f,   //6
	//	0.5f,  0.5f,  0.5f,		0.51f,  0.66f,  //7
	//	// back
	//	-0.5f, -0.5f, -0.5f,	0.99f,	0.34f,  //8
	//	 0.5f, -0.5f, -0.5f,	0.76f,	0.34f,  //9
	//	 0.5f,  0.5f, -0.5f,	0.76f,	0.66f,  //10
	//	-0.5f,  0.5f, -0.5f,	0.99f,	0.66f,  //11
	//	//left
	//	-0.5f, -0.5f, -0.5f,	0.01f,  0.34f,	//12
	//	-0.5f, -0.5f,  0.5f,	0.24f, 0.34f,	//13
	//	-0.5f,  0.5f,  0.5f,	0.24f, 0.66f,	//14
	//	-0.5f,  0.5f, -0.5f,	0.01f,  0.66f,	//15
	//	//Bottom
	//	-0.5f, -0.5f, -0.5f,	0.26f, 0.01f,	//16
	//	 0.5f, -0.5f, -0.5f,	0.49f, 0.01f,	//17
	//	 0.5f, -0.5f,  0.5f,	0.49f, 0.32f,	//18
	//	-0.5f, -0.5f,  0.5f,	0.26f, 0.32f,	//19
	//	//Top
	//	-0.5f, 0.5f,  0.5f,		0.26f,  0.675f,	//20
	//	 0.5f, 0.5f,  0.5f,		0.49f,  0.675f,	//21
	//	 0.5f, 0.5f, -0.5f,		0.49f,  0.99f,	//22
	//	-0.5f, 0.5f, -0.5f,		0.26f,  0.99f,	//23
	//};
	//Mesh *cubo = new Mesh();
	//cubo->CreateMesh(cubo_vertices, cubo_indices, 120, 36);
	//meshList.push_back(cubo);
	//
	//}


	//GLfloat cubo_vertices[] = {
		//	// front
		//	//x		y		z		u		v
		//	-0.5f, -0.5f,  0.5f,	0.26f,	0.34f, //0
		//	 0.5f, -0.5f,  0.5f,	0.49f,	0.34f, //1
		//	 0.5f,  0.5f,  0.5f,	0.49f,	0.66f, //2
		//	-0.5f,  0.5f,  0.5f,	0.26f,	0.66f, //3
		//	//right
		//	0.5f, -0.5f,  0.5f,		0.51f,  0.34f,  //4
		//	0.5f, -0.5f, -0.5f,		0.74f, 0.34f,   //5
		//	0.5f,  0.5f, -0.5f,		0.74f, 0.66f,   //6
		//	0.5f,  0.5f,  0.5f,		0.51f,  0.66f,  //7
		//	// back
		//	-0.5f, -0.5f, -0.5f,	0.99f,	0.34f,  //8
		//	 0.5f, -0.5f, -0.5f,	0.76f,	0.34f,  //9
		//	 0.5f,  0.5f, -0.5f,	0.76f,	0.66f,  //10
		//	-0.5f,  0.5f, -0.5f,	0.99f,	0.66f,  //11
		//	//left
		//	-0.5f, -0.5f, -0.5f,	0.01f,  0.34f,	//12
		//	-0.5f, -0.5f,  0.5f,	0.24f, 0.34f,	//13
		//	-0.5f,  0.5f,  0.5f,	0.24f, 0.66f,	//14
		//	-0.5f,  0.5f, -0.5f,	0.01f,  0.66f,	//15
		//	//Bottom
		//	-0.5f, -0.5f, -0.5f,	0.26f, 0.01f,	//16
		//	 0.5f, -0.5f, -0.5f,	0.49f, 0.01f,	//17
		//	 0.5f, -0.5f,  0.5f,	0.49f, 0.32f,	//18
		//	-0.5f, -0.5f,  0.5f,	0.26f, 0.32f,	//19
		//	//Top
		//	-0.5f, 0.5f,  0.5f,		0.26f,  0.675f,	//20
		//	 0.5f, 0.5f,  0.5f,		0.49f,  0.675f,	//21
		//	 0.5f, 0.5f, -0.5f,		0.49f,  0.99f,	//22
		//	-0.5f, 0.5f, -0.5f,		0.26f,  0.99f,	//23
		//};
		//Mesh *cubo = new Mesh();
		//cubo->CreateMesh(cubo_vertices, cubo_indices, 120, 36);
		//meshList.push_back(cubo);
		//
		//}

		GLfloat cubo_vertices[] = {
			// front
			//x		y		z		u		v
			-0.5f, -0.5f,  0.5f,	
			 0.5f, -0.5f,  0.5f,	
			 0.5f,  0.5f,  0.5f,	
			-0.5f,  0.5f,  0.5f,	
			//right
			0.5f, -0.5f,  0.5f,		
			0.5f, -0.5f, -0.5f,		
			0.5f,  0.5f, -0.5f,		
			0.5f,  0.5f,  0.5f,		
			// back
			-0.5f, -0.5f, -0.5f,	
			 0.5f, -0.5f, -0.5f,	
			 0.5f,  0.5f, -0.5f,	
			-0.5f,  0.5f, -0.5f,	
			//left
			-0.5f, -0.5f, -0.5f,	
			-0.5f, -0.5f,  0.5f,	
			-0.5f,  0.5f,  0.5f,	
			-0.5f,  0.5f, -0.5f,	
			//Bottom
			-0.5f, -0.5f, -0.5f,	
			 0.5f, -0.5f, -0.5f,	
			 0.5f, -0.5f,  0.5f,	
			-0.5f, -0.5f,  0.5f,	
			//Top
			-0.5f, 0.5f,  0.5f,		
			 0.5f, 0.5f,  0.5f,		
			 0.5f, 0.5f, -0.5f,		
			-0.5f, 0.5f, -0.5f,		
		};
		Mesh* cubo = new Mesh();
		cubo->CreateMesh(cubo_vertices, cubo_indices, 72, 36);
		meshList.push_back(cubo);
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
	CreateObject();
	CrearCubo();
	CreateShaders();
	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_ladrillos = Texture("Textures/ladrillos.tga");
	T_ladrillos.LoadTexture();
	T_asfalto = Texture("Textures/dirt.png");
	T_asfalto.LoadTexture();
	T_dado = Texture("Textures/dado2.tga");
	T_dado.LoadTexture();
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
		//ejercicio 1:
		glm::mat4 model(1.0);

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		//T_dado.UseTexture();
		//T_ladrillos.UseTexture();
		meshList[1]->RenderMesh();

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