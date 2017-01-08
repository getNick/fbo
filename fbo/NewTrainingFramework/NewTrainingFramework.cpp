// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" 
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <vector>
#include "model.h"
#include "camera.h"


GLuint vboQuad, framebuffer, colorTex;
Shaders myShaders, bwShader;
Matrix m;
float m_time = 0;
model model1;
GLuint texture;
camera cam;

int Init ( ESContext *esContext )
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	m.SetIdentity();

	model1.loadModel("../Resources/Models/Woman1.nfg");

	model1.loadTexture("../Resources/Textures/Woman1.tga", &texture);

	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Globals::screenWidth, Globals::screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Does the GPU support current FBO configuration?
   GLenum status;
   status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   switch(status)
   {
   	case GL_FRAMEBUFFER_COMPLETE: break;
   	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: esLogMessage("FrameBuffer error: incomplete attachment"); break;
   	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: esLogMessage("FrameBuffer error: missing attachment"); break;
   	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS: esLogMessage("FrameBuffer error: incomplete dimensions");     	break;
   	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS: esLogMessage("FrameBuffer error: incomplete formats");        	break;
   	case GL_FRAMEBUFFER_UNSUPPORTED: esLogMessage("FrameBuffer error:unsupported");               	break;
   	default: esLogMessage("FrameBuffer error");
  }
   

	Vertex quadData[6];

	quadData[0].pos.x = -1.0f;  quadData[0].pos.y = 1.0f;  quadData[0].pos.z = 0.0f;
	quadData[1].pos.x = -1.0f;  quadData[1].pos.y = -1.0f;  quadData[1].pos.z = 0.0f;
	quadData[2].pos.x = 1.0f;  quadData[2].pos.y = -1.0f;  quadData[2].pos.z = 0.0f;
	quadData[3].pos.x = -1.0f;  quadData[3].pos.y = 1.0f;  quadData[3].pos.z = 0.0f;
	quadData[4].pos.x = 1.0f;  quadData[4].pos.y = -1.0f;  quadData[4].pos.z = 0.0f;
	quadData[5].pos.x = 1.0f;  quadData[5].pos.y = 1.0f;  quadData[5].pos.z = 0.0f;

	quadData[0].uv.x = 0.0f;	quadData[0].uv.y = 1.0f;
	quadData[1].uv.x = 0.0f;	quadData[1].uv.y = 0.0f;
	quadData[2].uv.x = 1.0f;	quadData[2].uv.y = 0.0f;
	quadData[3].uv.x = 0.0f;	quadData[3].uv.y = 1.0f;
	quadData[4].uv.x = 1.0f;	quadData[4].uv.y = 0.0f;
	quadData[5].uv.x = 1.0f;	quadData[5].uv.y = 1.0f;


	//buffer object
	glGenBuffers(1, &vboQuad); //buffer object name generation
	glBindBuffer(GL_ARRAY_BUFFER, vboQuad); //buffer object binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadData), quadData, GL_STATIC_DRAW); //creation and initializion of buffer onject storage
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//creation of shaders and program 
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	
	return bwShader.Init("../Resources/Shaders/bwShaderVS.vs", "../Resources/Shaders/bwShaderFS.fs");

}

void Draw(ESContext *esContext)
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, model1.m_hVertexBuffer); //binded model's vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model1.m_hIndexBuffer); //binded indices
	glEnable(GL_DEPTH_TEST);
	glUseProgram(myShaders.program);
	
	
	GLfloat* ptr = (GLfloat *)0;
	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr);
	}
	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr+3);
	}
	if (myShaders.matrixTransform != -1) {
		glUniformMatrix4fv(myShaders.matrixTransform, 1, false, (GLfloat *)&m);
	}
	glActiveTexture(GL_TEXTURE0);// bind the texture to the currently active texture unit 
	glBindTexture(GL_TEXTURE_2D, texture);// set the uniform sampler 
	glUniform1i(myShaders.uniformTexture, 0);

	glDrawElements(GL_TRIANGLES, model1.nrIndices, GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(bwShader.program);
	
	
	
	ptr = 0;
	if (bwShader.positionAttribute != -1) //attribute passing to shader, for uniforms use glUniform1f(time, deltaT); glUniformMatrix4fv( m_pShader->matrixWVP, 1, false, (GLfloat *)&rotationMat );
	{
		glEnableVertexAttribArray(bwShader.positionAttribute);
		glVertexAttribPointer(bwShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr);
	}
	if (bwShader.uvAttribute != -1) //attribute passing to shader, for uniforms use glUniform1f(time, deltaT); glUniformMatrix4fv( m_pShader->matrixWVP, 1, false, (GLfloat *)&rotationMat );
	{
		glEnableVertexAttribArray(bwShader.uvAttribute);
		glVertexAttribPointer(bwShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ptr + 3);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glUniform1i(bwShader.uniformTexture, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	m_time += deltaTime;
	m = model1.modelMatrix * cam.getViewM() * cam.getProjectionM();
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	cam.ProcessKeyboard(CameraMovement(key));
}
void Mouse(ESContext *, int posX, int posY) {
	cam.mouseMove(posX, posY);
}

void CleanUp()
{
	glDeleteBuffers(1, &vboQuad);
	glDeleteBuffers(1, &framebuffer);
	glDeleteBuffers(1, &colorTex);
	glDeleteBuffers(1, &model1.m_hIndexBuffer);
	glDeleteBuffers(1, &model1.m_hVertexBuffer);
	glDeleteBuffers(1, &texture);
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("open complite");
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc(&esContext, Mouse);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

