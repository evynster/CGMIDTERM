#include "PostEffect.h"

void mte::PostEffect::init(unsigned width, unsigned height)
{
	int index = int(_buffers.size());
	_buffers.push_back(std::make_shared<FrameBuffer>());
	_buffers[index]->addColourTarget(GL_RGBA8);
	_buffers[index]->addDepthTarget();
	_buffers[index]->init(width,height);

	index = int(_shaders.size());
	ResourceManager manager;

	_shaders.push_back(manager.createShader("","",""));

}

void mte::PostEffect::applyEffect(PostEffect* previousBuffer)
{
}

void mte::PostEffect::drawToScreen()
{
}

void mte::PostEffect::Reshape(unsigned width, unsigned height)
{
}

void mte::PostEffect::clear()
{
}

void mte::PostEffect::unload()
{
}

void mte::PostEffect::bindBuffer(int index)
{
}

void mte::PostEffect::unbindBuffer()
{
}

void mte::PostEffect::bindColourAsTexture(int index, int colourBuffer, int textureSlot)
{
}

void mte::PostEffect::bindDepthAsTexture(int index, int textureslot)
{
}

void mte::PostEffect::unbindTexture(int textureSlot)
{
}

void mte::PostEffect::bindShader(int index)
{
}

void mte::PostEffect::unbindShader()
{
}
