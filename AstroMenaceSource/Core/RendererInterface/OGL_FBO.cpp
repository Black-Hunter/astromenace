/******************************************************************************

	This source file is part of Viewizard Game Engine
	For the latest info, see http://www.viewizard.com/

	File name: OGL_FBO.cpp

	Copyright (c) 2012 Michael Kurinnoy, Viewizard
	All Rights Reserved.

	File Version: 3.1

******************************************************************************

	AstroMenace game source code available under "dual licensing" model.
	The licensing options available are:

	* Commercial Licensing. This is the appropriate option if you are
	  creating proprietary applications and you are not prepared to
	  distribute and share the source code of your application.
	  Contact us for pricing at viewizard@viewizard.com

	* Open Source Licensing. This is the appropriate option if you want
	  to share the source code of your application with everyone you
	  distribute it to, and you also want to give them the right to share
	  who uses it. You should have received a copy of the GNU General Public
	  License version 3 with this source codes.
	  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/


#include "RendererInterface.h"


// текущий работающий буфер, если 0 - фрейм буфер
eFBO *CurrentFBO = 0;

/*
// данные для буферов, чтобы сделать MSAA
GLuint ColorRenderbufferName = 0;
GLuint DepthRenderbufferName = 0;
GLuint ColorTextureName = 0;
GLuint FramebufferRenderName = 0;
GLuint FramebufferResolveName = 0;
GLuint FBO_Width, FBO_Height;
*/
// указатели на функии
PFNGLGENRENDERBUFFERSEXTPROC				glGenRenderbuffersEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC				glBindRenderbufferEXT = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC	glRenderbufferStorageMultisampleEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC				glGenFramebuffersEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC					glBindFramebufferEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC			glFramebufferRenderbufferEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC			glCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC			glFramebufferTexture2DEXT = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC				glDeleteRenderbuffersEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC				glDeleteFramebuffersEXT = NULL;
PFNGLBLITFRAMEBUFFEREXTPROC					glBlitFramebufferEXT = NULL;
PFNGLISFRAMEBUFFEREXTPROC					glIsFramebufferEXT = NULL;
PFNGLGENERATEMIPMAPPROC 					glGenerateMipmapEXT = NULL;
// GL_NV_framebuffer_multisample_coverage, не обязательный
PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC	glRenderbufferStorageMultisampleCoverageNV = NULL;




//------------------------------------------------------------------------------------
// Инициализация работы с FBO
//------------------------------------------------------------------------------------
bool vw_Internal_InitializationFBO()
{
	// GL_ARB_framebuffer_object
	glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glGenRenderbuffers");
	glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) SDL_GL_GetProcAddress("glBindRenderbuffer");
	glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) SDL_GL_GetProcAddress("glRenderbufferStorageMultisample");
	glGenFramebuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glGenFramebuffers");
	glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glBindFramebuffer");
	glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) SDL_GL_GetProcAddress("glFramebufferRenderbuffer");
	glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) SDL_GL_GetProcAddress("glCheckFramebufferStatus");
	glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) SDL_GL_GetProcAddress("glFramebufferTexture2D");
	glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glDeleteRenderbuffers");
	glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC) SDL_GL_GetProcAddress("glDeleteFramebuffers");
	glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glBlitFramebuffer");
	glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glIsFramebuffer");
	glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPPROC) SDL_GL_GetProcAddress("glGenerateMipmap");


	if (glGenRenderbuffersEXT == NULL || glBindRenderbufferEXT == NULL ||
		glRenderbufferStorageMultisampleEXT == NULL || glGenFramebuffersEXT == NULL ||
		glBindFramebufferEXT == NULL || glFramebufferRenderbufferEXT == NULL ||
		glCheckFramebufferStatusEXT == NULL || glFramebufferTexture2DEXT == NULL ||
		glDeleteRenderbuffersEXT == NULL || glDeleteFramebuffersEXT == NULL ||
		glBlitFramebufferEXT == NULL || glIsFramebufferEXT == NULL ||
		glGenerateMipmapEXT == NULL)
	{
		// GL_EXT_framebuffer_object+GL_EXT_framebuffer_multisample+GL_EXT_framebuffer_blit
		glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glGenRenderbuffersEXT");
		glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) SDL_GL_GetProcAddress("glBindRenderbufferEXT");
		glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) SDL_GL_GetProcAddress("glRenderbufferStorageMultisampleEXT");
		glGenFramebuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glGenFramebuffersEXT");
		glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glBindFramebufferEXT");
		glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) SDL_GL_GetProcAddress("glFramebufferRenderbufferEXT");
		glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) SDL_GL_GetProcAddress("glCheckFramebufferStatusEXT");
		glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) SDL_GL_GetProcAddress("glFramebufferTexture2DEXT");
		glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC) SDL_GL_GetProcAddress("glDeleteRenderbuffersEXT");
		glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC) SDL_GL_GetProcAddress("glDeleteFramebuffersEXT");
		glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glBlitFramebufferEXT");
		glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC) SDL_GL_GetProcAddress("glIsFramebufferEXT");
		glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPPROC) SDL_GL_GetProcAddress("glGenerateMipmapEXT");
	}


	if (glGenRenderbuffersEXT == NULL || glBindRenderbufferEXT == NULL ||
		glRenderbufferStorageMultisampleEXT == NULL || glGenFramebuffersEXT == NULL ||
		glBindFramebufferEXT == NULL || glFramebufferRenderbufferEXT == NULL ||
		glCheckFramebufferStatusEXT == NULL || glFramebufferTexture2DEXT == NULL ||
		glDeleteRenderbuffersEXT == NULL || glDeleteFramebuffersEXT == NULL ||
		glBlitFramebufferEXT == NULL || glIsFramebufferEXT == NULL ||
		glGenerateMipmapEXT == NULL)
	{
		glGenRenderbuffersEXT = NULL;
		glBindRenderbufferEXT = NULL;
		glRenderbufferStorageMultisampleEXT = NULL;
		glGenFramebuffersEXT = NULL;
		glBindFramebufferEXT = NULL;
		glFramebufferRenderbufferEXT = NULL;
		glCheckFramebufferStatusEXT = NULL;
		glFramebufferTexture2DEXT = NULL;
		glDeleteRenderbuffersEXT = NULL;
		glDeleteFramebuffersEXT = NULL;
		glBlitFramebufferEXT = NULL;
		glIsFramebufferEXT = NULL;
		glGenerateMipmapEXT = NULL;

		return false;
	}

	// инициализируем GL_NV_framebuffer_multisample_coverage, как не обязательный
	glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC) SDL_GL_GetProcAddress("glRenderbufferStorageMultisampleCoverageNV");


	return true;
}








//------------------------------------------------------------------------------------
// Создаем FBO с заданными параметрами (FBO - уже заранее подготовленный объект, в функции память не выделяем)
//------------------------------------------------------------------------------------
bool vw_BuildFBO(eFBO *FBO, int Width, int Height, bool NeedColor, bool NeedDepth, int MSAA, int *CSAA)
{
	if (FBO == 0) return false;
	if (glGenRenderbuffersEXT == NULL) return false;
	if (glBindRenderbufferEXT == NULL) return false;
	if (glRenderbufferStorageMultisampleEXT == NULL) return false;
	if (glGenFramebuffersEXT == NULL) return false;
	if (glBindFramebufferEXT == NULL) return false;
	if (glFramebufferRenderbufferEXT == NULL) return false;
	if (glCheckFramebufferStatusEXT == NULL) return false;
	// если не поддерживаем ковередж - просто ставим MSAA
	if (glRenderbufferStorageMultisampleCoverageNV == NULL) *CSAA = MSAA;

	FBO->Width = Width;
	FBO->Height = Height;
	FBO->ColorBuffer = 0;
	FBO->DepthBuffer = 0;
	FBO->ColorTexture = 0;
	FBO->DepthTexture = 0;
	FBO->FrameBufferObject = 0;


	glGenFramebuffersEXT(1, &FBO->FrameBufferObject);
	glBindFramebufferEXT(GL_FRAMEBUFFER, FBO->FrameBufferObject);


	if (NeedColor)
	{
		// если есть мультисемплы - делаем буфером, если нет - текстурой
		if (MSAA >= 2)
		{
			glGenRenderbuffersEXT(1, &FBO->ColorBuffer);
			glBindRenderbufferEXT(GL_RENDERBUFFER, FBO->ColorBuffer);
			if ((*CSAA == MSAA) | (CSAA == 0))
				glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER, MSAA, GL_RGBA, FBO->Width, FBO->Height);
			else
				glRenderbufferStorageMultisampleCoverageNV(GL_RENDERBUFFER, *CSAA, MSAA, GL_RGBA, FBO->Width, FBO->Height);
			glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, FBO->ColorBuffer);
			if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				fprintf(stderr, "Can't create FRAMEBUFFER.\n\n");
				return false;
			}
		}
		else
		{
			glGenTextures(1, &FBO->ColorTexture);
			glBindTexture(GL_TEXTURE_2D, FBO->ColorTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FBO->Width, FBO->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO->ColorTexture, 0);
			if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				fprintf(stderr, "Can't create FRAMEBUFFER.\n\n");
				return false;
			}
		}
	}


	if (NeedDepth)
	{
		// если есть мультисемплы - делаем буфером, если нет - текстурой
		if (MSAA >= 2)
		{
			glGenRenderbuffersEXT(1, &FBO->DepthBuffer);
			glBindRenderbufferEXT(GL_RENDERBUFFER, FBO->DepthBuffer);
			if ((*CSAA == MSAA) | (CSAA == 0))
				// Ставим "GL_DEPTH_COMPONENT" (No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available ...)
				glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER, MSAA, GL_DEPTH_COMPONENT, FBO->Width, FBO->Height);
			else
				// Ставим "GL_DEPTH_COMPONENT" (No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available ...)
				glRenderbufferStorageMultisampleCoverageNV(GL_RENDERBUFFER, *CSAA, MSAA, GL_DEPTH_COMPONENT, FBO->Width, FBO->Height);
			glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, FBO->DepthBuffer);
			if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				fprintf(stderr, "Can't create FRAMEBUFFER.\n\n");
				return false;
			}
		}
		else
		{
			glGenTextures(1, &FBO->DepthTexture);
			glBindTexture(GL_TEXTURE_2D, FBO->DepthTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// Ставим "GL_DEPTH_COMPONENT" (No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available ...)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, FBO->Width, FBO->Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, FBO->DepthTexture, 0);
			if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				fprintf(stderr, "Can't create FRAMEBUFFER.\n\n");
				return false;
			}
		}
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

	return true;
}







//------------------------------------------------------------------------------------
// Установка FBO
//------------------------------------------------------------------------------------
void vw_BindFBO(eFBO *FBO)
{
	if (glBindFramebufferEXT == NULL) return;
	if (FBO != 0)
		if (FBO->FrameBufferObject == 0) return;

	// проверяем текущий
	if (CurrentFBO != 0)// если текущий был с мультисемплами - надо их выключить
		if ((CurrentFBO->ColorBuffer != 0) | (CurrentFBO->DepthBuffer != 0)) glDisable(GL_MULTISAMPLE);

	if (FBO != 0)
	{
		if ((FBO->ColorBuffer != 0) | (FBO->DepthBuffer != 0)) glEnable(GL_MULTISAMPLE);
		glBindFramebufferEXT(GL_FRAMEBUFFER, FBO->FrameBufferObject);
	}
	else
	{
		// ставим основной фрейм буфер
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}

	CurrentFBO = FBO;
}







//------------------------------------------------------------------------------------
// получаем текущий установленный FBO, 0 - если фрейм буфер
//------------------------------------------------------------------------------------
eFBO *vw_GetCurrentFBO()
{
	return CurrentFBO;
}








//------------------------------------------------------------------------------------
// Блит FBO
//------------------------------------------------------------------------------------
void vw_BlitFBO(eFBO *SourceFBO, eFBO *TargetFBO)
{
	if (glBindFramebufferEXT == NULL) return;
	if (glBlitFramebufferEXT == NULL) return;
	if (SourceFBO == 0) return;
	if (SourceFBO->FrameBufferObject == 0) return;
	if (TargetFBO == 0) return;
	if (TargetFBO->FrameBufferObject == 0) return;

	glBindFramebufferEXT(GL_READ_FRAMEBUFFER, SourceFBO->FrameBufferObject);
	glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER, TargetFBO->FrameBufferObject);
	glBlitFramebufferEXT(
		0, 0, SourceFBO->Width, SourceFBO->Height,
		0, 0, TargetFBO->Width, TargetFBO->Height,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);
}










//------------------------------------------------------------------------------------
// Рисуем FBO в указанный FBO
//------------------------------------------------------------------------------------
void vw_DrawColorFBO(eFBO *SourceFBO, eFBO *TargetFBO)
{
	if (SourceFBO == 0) return;
	if (SourceFBO->ColorTexture == 0) return;


	vw_BindFBO(TargetFBO);
	glViewport(0, 0, SourceFBO->Width, SourceFBO->Height);


	// рисуем текстуру на весь экран

    // запоминаем состояние флагов
	glPushAttrib(GL_ENABLE_BIT);
    // и выключаем "ненужные"
	glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);								//select the projection matrix
	glPushMatrix();												//store the projection matrix
	glLoadIdentity();											//reset the projection matrix

	glOrtho(0, SourceFBO->Width, 0, SourceFBO->Height, -1, 1);

	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix
	glPushMatrix();
	glLoadIdentity();


		float *buff = 0;
		// RI_2f_XY | RI_1_TEX
		buff = new float[4*4]; if (buff == 0) return;

		int k=0;

		buff[k++] = 0.0f;
		buff[k++] = 0.0f;
		buff[k++] = 0.0f;
		buff[k++] = 0.0f;

		buff[k++] = 0.0f;
		buff[k++] = SourceFBO->Height;
		buff[k++] = 0.0f;
		buff[k++] = 1.0f;

		buff[k++] = SourceFBO->Width;
		buff[k++] = 0.0f;
		buff[k++] = 1.0f;
		buff[k++] = 0.0f;

		buff[k++] = SourceFBO->Width;
		buff[k++] = SourceFBO->Height;
		buff[k++] = 1.0f;
		buff[k++] = 1.0f;


		vw_BindTexture(0, SourceFBO->ColorTexture);

		vw_SendVertices(RI_TRIANGLE_STRIP, 4, RI_2f_XY | RI_1_TEX, buff, 4*sizeof(float));

		vw_BindTexture(0, 0);
		if (buff != 0){delete [] buff; buff = 0;}


	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);			//select the projection matrix
	glPopMatrix();							//restore the old projection matrix

	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix

    // восстанавливаем флаги
	glPopAttrib();

}











//------------------------------------------------------------------------------------
// Удаление данных FBO
//------------------------------------------------------------------------------------
void vw_DeleteFBO(eFBO *FBO)
{
	if (FBO == 0) return;
	if (glDeleteRenderbuffersEXT == NULL) return;
	if (glDeleteFramebuffersEXT == NULL) return;


	if (FBO->ColorTexture != 0) {glDeleteTextures(1, &FBO->ColorTexture); FBO->ColorTexture=0;};
	if (FBO->DepthTexture != 0) {glDeleteTextures(1, &FBO->DepthTexture); FBO->DepthTexture=0;};

	if (FBO->ColorBuffer != 0) {glDeleteRenderbuffersEXT(1, &FBO->ColorBuffer); FBO->ColorBuffer=0;};
	if (FBO->DepthBuffer != 0) {glDeleteRenderbuffersEXT(1, &FBO->DepthBuffer); FBO->DepthBuffer=0;};

	if (FBO->FrameBufferObject != 0) {glDeleteFramebuffersEXT(1, &FBO->FrameBufferObject); FBO->FrameBufferObject=0;};
}
