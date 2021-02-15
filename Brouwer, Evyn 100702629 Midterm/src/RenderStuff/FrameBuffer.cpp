#include "FrameBuffer.h"

GLuint mte::FrameBuffer::_FSQVBO = 0;
GLuint mte::FrameBuffer::_FSQVAO = 0;

int mte::FrameBuffer::_maxColourAttaches = 0;
bool mte::FrameBuffer::_isInitFSQ = false;

void mte::ColourTarget::unload()
{
	glDeleteTextures(_attachCount,&_textures[0]);
}



mte::ColourTarget::~ColourTarget()
{
	unload();
}

void mte::DepthTarget::unload()
{
	glDeleteTextures(1,&_texture);
}


mte::DepthTarget::~DepthTarget()
{
	unload();
}

mte::FrameBuffer::FrameBuffer()
{

}

mte::FrameBuffer::~FrameBuffer()
{
	unload();
}


void mte::FrameBuffer::unload()
{
	glDeleteFramebuffers(1,&_FBO);

	_isInit = false;
}

void mte::FrameBuffer::init(unsigned width, unsigned height)
{
	setSize(width,height);

	init();
}

void mte::FrameBuffer::init()
{
	glGenFramebuffers(1,&_FBO);

	glBindFramebuffer(GL_FRAMEBUFFER,_FBO);

	if (_depthActive) {
		_clearFlag |= GL_DEPTH_BUFFER_BIT;

		glGenTextures(1,&_depth._texture);

		glBindTexture(GL_TEXTURE_2D,_depth._texture);

		glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24,_width,_height);

		glTextureParameteri(_depth._texture, GL_TEXTURE_MIN_FILTER, _filter);
		glTextureParameteri(_depth._texture, GL_TEXTURE_MAG_FILTER, _filter);
		glTextureParameteri(_depth._texture, GL_TEXTURE_WRAP_S, _wrap);
		glTextureParameteri(_depth._texture,GL_TEXTURE_WRAP_T, _wrap);

		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_depth._texture,0);		

		glBindTexture(GL_TEXTURE_2D,GL_NONE);
	}

	if (_colour._attachCount) {
		_clearFlag |= GL_COLOR_BUFFER_BIT;

		GLuint* textureHandles = new GLuint[_colour._attachCount];

		glGenTextures(_colour._attachCount, textureHandles);

		for (unsigned i = 0; i < _colour._attachCount; i++) {
			_colour._textures[i] = textureHandles[i];

			glBindTexture(GL_TEXTURE_2D, _colour._textures[i]);

			glTexStorage2D(GL_TEXTURE_2D, 1, _colour._formats[i], _width, _height);

			glTextureParameteri(_colour._textures[i], GL_TEXTURE_MIN_FILTER, _filter);
			glTextureParameteri(_colour._textures[i], GL_TEXTURE_MAG_FILTER, _filter);
			glTextureParameteri(_colour._textures[i], GL_TEXTURE_WRAP_S, _wrap);
			glTextureParameteri(_colour._textures[i], GL_TEXTURE_WRAP_T, _wrap);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _colour._textures[i], 0);

		}

		delete[] textureHandles;

	}
	checkFBO();

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

	_isInit = true;

}

void mte::FrameBuffer::addDepthTarget()
{
	if (_depth._texture) {
		_depth.unload();
	}
	_depthActive = true;

}

void mte::FrameBuffer::addColourTarget(GLenum format)
{
	_colour._textures.resize(_colour._attachCount+1);
	_colour._formats.push_back(format);
	_colour._buffers.push_back(GL_COLOR_ATTACHMENT0 + _colour._attachCount);

	_colour._attachCount++;
}

void mte::FrameBuffer::bindDepthAsTexture(int index) const
{
	if (_depth._texture != 0) {
		//glActiveTexture(GL_TEXTURE0 + slot);
		glBindTextureUnit(index, _depth._texture);
	}
}

void mte::FrameBuffer::bindColourAsTexture(unsigned colourBuffer, int index) const
{
	if (_colour._textures[colourBuffer] != 0) {
		//glActiveTexture(GL_TEXTURE0 + slot);
		glBindTextureUnit(index, _colour._textures[colourBuffer]);
	}
}

void mte::FrameBuffer::unBindTexture(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D,GL_NONE);
}

void mte::FrameBuffer::resize(unsigned width, unsigned height)
{
	setSize(width,height);
	unload();

	_depth.unload();

	_colour.unload();
	init();
}

void mte::FrameBuffer::setSize(unsigned width, unsigned height)
{
	_width = width;
	_height = height;
}

void mte::FrameBuffer::setViewPort() const
{
	glViewport(0,0,_width,_height);
}

void mte::FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER,_FBO);

	if (_colour._attachCount) {
		glDrawBuffers(_colour._attachCount,&_colour._textures[0]);
	}
}

void mte::FrameBuffer::unBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER,GL_NONE);
}

void mte::FrameBuffer::renderFSQ() const
{
	setViewPort();
	bind();
	drawFSQ();
	unBind();
}

void mte::FrameBuffer::drawBackBuffer()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER,_FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,GL_NONE);

	glBlitFramebuffer(0,0,_width,_height,0,0,_width,_height,GL_COLOR_BUFFER_BIT,GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER,GL_NONE);
}

void mte::FrameBuffer::clear()
{
	glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
	glClear(_clearFlag);
	glBindFramebuffer(GL_FRAMEBUFFER,GL_NONE);
}

bool mte::FrameBuffer::checkFBO()
{
	bind();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER != GL_FRAMEBUFFER_COMPLETE)) {
		return false;
	}
	return true;
}

void mte::FrameBuffer::initFSQ()
{
	//A vbo with Uvs and verts from
   //-1 to 1 for verts
   //0 to 1 for UVs
	float VBO_DATA[]
	{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		-1.f, 1.f, 0.f,

		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f,
		1.f, -1.f, 0.f,

		0.f, 0.f,
		1.f, 0.f,
		0.f, 1.f,

		1.f, 1.f,
		0.f, 1.f,
		1.f, 0.f
	};
	//Vertex size is 6pts * 3 data points * sizeof (float)
	int vertexSize = 6 * 3 * sizeof(float);
	//texcoord size = 6pts * 2 data points * sizeof(float)
	int texCoordSize = 6 * 2 * sizeof(float);

	//Generates vertex array
	glGenVertexArrays(1, &_FSQVAO);
	//Binds VAO
	glBindVertexArray(_FSQVAO);

	//Enables 2 vertex attrib array slots
	glEnableVertexAttribArray(0); //Vertices
	glEnableVertexAttribArray(1); //UVS

	//Generates VBO
	glGenBuffers(1, &_FSQVBO);

	//Binds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, _FSQVBO);
	//Buffers the vbo data
	glBufferData(GL_ARRAY_BUFFER, vertexSize + texCoordSize, VBO_DATA, GL_STATIC_DRAW);

#pragma warning(push)
#pragma warning(disable : 4312)
	//Sets first attrib array to point to the beginning of the data
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	//Sets the second attrib array to point to an offset in the data
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(vertexSize));
#pragma warning(pop)

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void mte::FrameBuffer::drawFSQ()
{
	glBindVertexArray(_FSQVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(GL_NONE);
}
