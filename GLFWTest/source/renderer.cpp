#define GLEW_STATIC
#define GLM_FORCE_RADIANS

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "math.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>
#include <common/shader.hpp>
#include <common/texture.hpp>

#include "common/renderer.h"
#include "common/vertexshader.h"
#include <common\controls.hpp>
#include <common\objloader.hpp>
#include <common\text2D.hpp>
namespace {
	GLFWwindow* window;
	glm::vec2 wh;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint indexbuffer;
	GLuint N_vertex;
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint uvBuffer;
	int kkk;
};

void renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	wh = glm::vec2(width, height);
}
void InitDraw()
{

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);
	programID = LoadShaders("Texture.vertexshader", "Texture.fragmentshader");
	MatrixID = glGetUniformLocation(programID, "MVP");
	//Ladataan kuva obj::lle
	Texture = loadDDS("./textures/uvmap.DDS");
	TextureID = glGetUniformLocation(programID,"myTextureSampler");
	//Obj loader käyttöön:

	 std::vector< glm::vec3 > vertices;
	 std::vector< glm::vec2 > uvs;
	 std::vector< glm::vec3 > normals; 
	 bool res = loadOBJ("./textures/cube.obj", vertices, uvs, normals);
	//static const GLfloat g_vertex_buffer_data[] =
	//{
	//	-1.0f, -1.0f, -1.0f,//0
	//	-1.0f, -1.0f, 1.0f, //1
	//	-1.0f, 1.0f, 1.0f, //2
	//	1.0f, 1.0f, -1.0f, //3
	//	-1.0f, -1.0f, -1.0f, //4
	//	-1.0f, 1.0f, -1.0f, //5
	//	1.0f, -1.0f, 1.0f, //6
	//	-1.0f, -1.0f, -1.0f, //7
	//	1.0f, -1.0f, -1.0f, //8
	//	1.0f, 1.0f, -1.0f, //9
	//	1.0f, -1.0f, -1.0f, //10
	//	-1.0f, -1.0f, -1.0f, //11
	//	-1.0f, -1.0f, -1.0f, //12
	//	-1.0f, 1.0f, 1.0f, //13
	//	-1.0f, 1.0f, -1.0f, //14
	//	1.0f, -1.0f, 1.0f, //15
	//	-1.0f, -1.0f, 1.0f, //16
	//	-1.0f, -1.0f, -1.0f, //17
	//	-1.0f, 1.0f, 1.0f, //18
	//	-1.0f, -1.0f, 1.0f, //19
	//	1.0f, -1.0f, 1.0f, //20
	//	1.0f, 1.0f, 1.0f, //21
	//	1.0f, -1.0f, -1.0f, //22
	//	1.0f, 1.0f, -1.0f, //23
	//	1.0f, -1.0f, -1.0f, //24
	//	1.0f, 1.0f, 1.0f, //25
	//	1.0f, -1.0f, 1.0f, //26
	//	1.0f, 1.0f, 1.0f, //27
	//	1.0f, 1.0f, -1.0f, //28
	//	-1.0f, 1.0f, -1.0f, //29
	//	1.0f, 1.0f, 1.0f, //30
	//	-1.0f, 1.0f, -1.0f, //31
	//	-1.0f, 1.0f, 1.0f, //32
	//	1.0f, 1.0f, 1.0f, //33
	//	-1.0f, 1.0f, 1.0f, //34
	//	1.0f, -1.0f, 1.0f //35
	//};
	//Huom! tänne obj loaderin vertices:it
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3),&vertices[0], GL_STATIC_DRAW);

	/*static const GLfloat g_color_buffer_data[] = {
		0.583f, 0.771f, 0.014f,1.0f,
		0.609f, 0.115f, 0.436f,1.0f,
		0.327f, 0.483f, 0.844f,1.0f,
		0.822f, 0.569f, 0.201f,1.0f,
		0.435f, 0.602f, 0.223f,1.0f,
		0.310f, 0.747f, 0.185f,1.0f,
		0.597f, 0.770f, 0.761f,1.0f,
		0.559f, 0.436f, 0.730f,1.0f,
		0.359f, 0.583f, 0.152f,1.0f,
		0.483f, 0.596f, 0.789f, 1.0f,
		0.559f, 0.861f, 0.639f, 1.0f,
		0.195f, 0.548f, 0.859f, 1.0f,
		0.014f, 0.184f, 0.576f, 1.0f,
		0.771f, 0.328f, 0.970f, 1.0f,
		0.406f, 0.615f, 0.116f, 1.0f,
		0.676f, 0.977f, 0.133f, 1.0f,
		0.971f, 0.572f, 0.833f, 1.0f,
		0.140f, 0.616f, 0.489f, 1.0f,
		0.997f, 0.513f, 0.064f, 1.0f,
		0.945f, 0.719f, 0.592f, 1.0f,
		0.543f, 0.021f, 0.978f, 1.0f,
		0.279f, 0.317f, 0.505f, 1.0f,
		0.167f, 0.620f, 0.077f, 1.0f,
		0.347f, 0.857f, 0.137f, 1.0f,
		0.055f, 0.953f, 0.042f, 1.0f,
		0.714f, 0.505f, 0.345f, 1.0f,
		0.783f, 0.290f, 0.734f, 1.0f,
		0.722f, 0.645f, 0.174f, 1.0f,
		0.302f, 0.455f, 0.848f, 1.0f,
		0.225f, 0.587f, 0.040f, 1.0f,
		0.517f, 0.713f, 0.338f, 1.0f,
		0.053f, 0.959f, 0.120f, 1.0f,
		0.393f, 0.621f, 0.362f, 1.0f,
		0.673f, 0.211f, 0.457f, 1.0f,
		0.820f, 0.883f, 0.371f, 1.0f,
		0.982f, 0.099f, 0.879f, 1.0f,

	};*/
	//Huom! tänne obj loaderin uvs:it
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	//Draw tarvii verticesin koon:

	kkk = vertices.size();
	
}
void Draw()
{
	//Matriisi hiirelle ja näppäimistölle:

	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	//Matriisi ilman hiirtä/näppäimistöä:

/*	glm::mat4 Projection = glm::perspective(
		45.0f, 
		4.0f / 3.0f, 
		0.1f,
		100.0f
		);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), 
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0) 
		);
	glm::mat4 Model = glm::mat4(1.0f);
	*/
	glUseProgram(programID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	
	glUniform1i(TextureID, 0);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer
		(
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,       // must match the layout in the shader.
		2,       // size
		GL_FLOAT,// type
		GL_FALSE,// normalized?
		0,       // stride
		(void*)0 // array buffer offset
		);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, kkk);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void renderer::Init(GLFWwindow* w)
{
	window = w;
	InitDraw();
}

void renderer::Render(void) 
{
	Draw();
	glfwSwapBuffers(window);
}




void renderer::Uninit(void) 
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}