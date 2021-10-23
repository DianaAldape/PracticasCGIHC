/*
Semestre 2022-1: Pr�ctica 4: Modelado Geom�trico, Color por variable Uniform*/
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
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float PI = 3.14159265f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(1.0, 20, 20);

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);

}


void CrearCilindro(int res, float height, float R) {

	//constantes utilizadas en los ciclos for
	int n, i, coordenada = 0;
	//n�mero de v�rtices ocupados
	int verticesBase = (res + 1) * 6;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	//apuntadores para guardar todos los v�rtices e �ndices generados
	GLfloat* vertices = (GLfloat*)calloc(sizeof(GLfloat*), (verticesBase) * 3);
	unsigned int* indices = (unsigned int*)calloc(sizeof(unsigned int*), verticesBase);

	//ciclo for para crear los v�rtices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el c�rculo
		else {
			x = R * cos((0)*dt);
			z = R * sin((0)*dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices[i + coordenada] = x;
				break;
			case 1:
				vertices[i + coordenada] = y;
				break;
			case 2:
				vertices[i + coordenada] = z;
				break;
			case 3:
				vertices[i + coordenada] = x;
				break;
			case 4:
				vertices[i + coordenada] = 0.5;
				break;
			case 5:
				vertices[i + coordenada] = z;
				break;
			}
		}
		coordenada += 6;
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices[coordenada + i] = x;
				break;
			case 1:
				vertices[coordenada + i] = -0.5f;
				break;
			case 2:
				vertices[coordenada + i] = z;
				break;
			}
		}
		coordenada += 3;
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices[coordenada + i] = x;
				break;
			case 1:
				vertices[coordenada + i] = 0.5;
				break;
			case 2:
				vertices[coordenada + i] = z;
				break;
			}
		}
		coordenada += 3;
	}

	//Se generan los indices de los v�rtices
	for (i = 0; i < verticesBase; i++) {
		indices[i] = i;
	}

	//se genera el mesh del cilindro
	Mesh *cilindro = new Mesh();
	cilindro->CreateMesh(vertices, indices, coordenada, verticesBase);
	meshList.push_back(cilindro);
}

//funci�n para crear un cono
void CrearCono(int res, float height, float R) {

	//constantes utilizadas en los ciclos for
	int n, i, coordenada = 3;
	//n�mero de v�rtices ocupados
	int verticesBase = (res) * 3;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	//apuntadores para guardar todos los v�rtices e �ndices generados
	GLfloat* vertices = (GLfloat*)calloc(sizeof(GLfloat*), (verticesBase)+6);
	unsigned int* indices = (unsigned int*)calloc(sizeof(unsigned int*), res + 1);
	//caso inicial para crear el cono
	vertices[0] = 0.0f;
	vertices[1] = 0.5f;
	vertices[2] = 0.0f;
	//ciclo for para crear los v�rtices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices[i + coordenada] = x;
				break;
			case 1:
				vertices[i + coordenada] = y;
				break;
			case 2:
				vertices[i + coordenada] = z;
				break;
			}
		}
		coordenada += 3;
	}
	//se agregan las coordenadas del �ltimo v�rtice para completar la circunferencia
	vertices[coordenada + 1] = R * cos(0)*dt;
	vertices[coordenada + 2] = -0.5f;
	vertices[coordenada + 3] = R * sin(0)*dt;;

	coordenada += 3;

	//se agregan los �ndices
	for (i = 0; i < res + 2; i++) {
		indices[i] = i;
	}

	//se genera el mesh del cono
	Mesh *cono = new Mesh();
	cono->CreateMesh(vertices, indices, coordenada, res + 2);
	meshList.push_back(cono);
}

//funci�n para crear pir�mide cuadrangular unitaria
void CrearPiramide()
{
	unsigned int piramide_indices[] = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	GLfloat piramide_vertices[] = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh *piramide = new Mesh();
	piramide->CreateMesh(piramide_vertices, piramide_indices, 15, 18);
	meshList.push_back(piramide);
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
	CrearCubo();
	CrearCilindro(5, 3.0f, 2.0f);
	CrearCono(5, 3.0f, 2.0f);
	CrearPiramide();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::vec3 direccion = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));// ya est� indicado, pero todav�a no lo modificaremos
	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		
		glm::mat4 model(1.0); 

		glm::vec3 color = glm::vec3(1.0f, 0.0f, 1.0f);
		//model = glm::mat4(1.0);
		//Traslaci�n
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		//////////////// ROTACI�N //////////////////
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////////////////  ESCALA ////////////////

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		///////////////////// T+R////////////////
		/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		*/
		/////////////R+T//////////
		/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		*/
		model = glm::rotate(model, glm::radians(mainWindow.getrotay() * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//meshList[0]->RenderMesh();
		//meshList[0]->RenderMeshGeometry();
		sp.render(); //Renderiza esfera
		/*
		meshList[0]->RenderMesh();

		//ejercicio : instanciar primitivas para crear su propio objeto
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.75f, -2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMesh();
		*/
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}