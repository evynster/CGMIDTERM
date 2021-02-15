#pragma once

#include "Resources/ResourceManager.h"

namespace mte {
	class PostEffect {
	public:
		virtual void init(unsigned width, unsigned height);

		virtual void applyEffect(PostEffect* previousBuffer);

		virtual void drawToScreen();

		virtual void Reshape(unsigned width, unsigned height);

		void clear();

		void unload();

		void bindBuffer(int index);

		void unbindBuffer();

		void bindColourAsTexture(int index, int colourBuffer, int textureSlot);
		void bindDepthAsTexture(int index, int textureslot);
		void unbindTexture(int textureSlot);

		void bindShader(int index);
		void unbindShader();

	protected:

		std::vector<std::shared_ptr<FrameBuffer>> _buffers;
		
		std::vector<std::shared_ptr<Shader>> _shaders;
		


	private:



	};


}