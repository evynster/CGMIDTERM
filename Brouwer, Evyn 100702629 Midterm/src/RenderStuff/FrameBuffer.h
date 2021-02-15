#pragma once

#include <RenderStuff/ShaderStuff/Shader.h>

namespace mte {
	
	struct DepthTarget
	{
		DepthTarget() {};
		~DepthTarget();
		void unload();

		GLuint _texture;

	};

	struct ColourTarget
	{
		ColourTarget() {};
		~ColourTarget();
		void unload();

		std::vector<GLuint> _textures;
		std::vector<GLenum> _formats;
		std::vector<GLenum> _buffers;
		unsigned int _attachCount = 0;
	};


	class FrameBuffer {
	public:
		FrameBuffer();
		~FrameBuffer();

		virtual void init(unsigned width,unsigned height);

		void init();

		void unload();

		void addDepthTarget();

		void addColourTarget(GLenum format);


		void bindDepthAsTexture(int index) const;

		void bindColourAsTexture(unsigned colourBuffer, int index) const;

		void unBindTexture(int index);

		void resize(unsigned width, unsigned height);

		void setSize(unsigned width, unsigned height);

		void setViewPort()const;


		void bind()const;

		void unBind()const;

		void renderFSQ()const;

		void drawBackBuffer();

		void clear();

		bool checkFBO();

		static void initFSQ();
		static void drawFSQ();

		unsigned int _width = 0;
		unsigned int _height = 0;


		GLuint texture;


	private:
		GLuint _FBO;

		DepthTarget _depth;

		ColourTarget _colour;

		GLenum _filter = GL_NEAREST;

		GLenum _wrap = GL_CLAMP_TO_EDGE;

		GLbitfield _clearFlag = 0;

		bool _isInit = false;

		bool _depthActive = false;

		static GLuint _FSQVBO;

		static GLuint _FSQVAO;

		static int _maxColourAttaches;

		static bool _isInitFSQ;

	};



}