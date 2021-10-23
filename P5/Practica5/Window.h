#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getcodo() { return codo; }
	GLfloat gethombro() { return hombro; }
	GLfloat getmuneca() { return muneca; }
	GLfloat getfalange_indice() { return falange_indice; }
	GLfloat getfalangina_indice() { return falangina_indice; }
	GLfloat getfalangeta_indice() { return falangeta_indice; }

	GLfloat getfalange_2() { return falange_indice; }
	GLfloat getfalangina_2() { return falangina_indice; }
	GLfloat getfalangeta_2() { return falangeta_indice; }

	GLfloat getfalange_3() { return falange_indice; }
	GLfloat getfalangina_3() { return falangina_indice; }
	GLfloat getfalangeta_3() { return falangeta_indice; }

	GLfloat getfalange_4() { return falange_indice; }
	GLfloat getfalangina_4() { return falangina_indice; }
	GLfloat getfalangeta_4() { return falangeta_indice; }

	GLfloat getfalange_5() { return falange_indice; }
	GLfloat getfalangina_5() { return falangina_indice; }
	GLfloat getfalangeta_5() { return falangeta_indice; }

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotay, codo, hombro, muneca, falange_indice, falangina_indice, falangeta_indice, falange_2, falangina_2, falangeta_2,
		falange_3, falangina_3, falangeta_3, falange_4, falangina_4, falangeta_4, rotax,
		falange_5, falangina_5, falangeta_5;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
};

