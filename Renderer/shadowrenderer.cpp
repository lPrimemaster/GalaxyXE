#include "shadowrenderer.h"
#include "masterrenderer.h"
#include "../Bitmap.h"
#include "../Gui/gui.h"

#define ONCE(x) \
static int z = 1; \
if(z) { z = 0; x; }


ShadowRenderer::ShadowRenderer()
{
	gui.setPosition(glm::vec2(150.0f, 100.0f));
	gui << 0.2f;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glDrawBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
}


ShadowRenderer::~ShadowRenderer()
{

}

void ShadowRenderer::update(MasterRenderer * renderer, Camera & cam)
{
	gui.update();

	m_shadowshader.bind();
	//Fix shadow bug behind scene
	//Fix shadow map size
	//Fix automatic projections of lights
	static unsigned int staticSize = 0;
	/*if (staticSize == renderer->lights.size())
		return;*/
	staticSize = renderer->lights.size();
	for (auto l : renderer->lights)
	{
		std::map<Light*, Texture*>::iterator found = shadowMaps.find(l);
		if (found == shadowMaps.end())
		{
			shadowMaps.emplace(l, new Texture());
			switch (l->getLightType())
			{
			case GXE_DIRECTIONAL_LIGHT:
				loader.loadShadowTexture(*shadowMaps[l], GXE_ORTHOGONAL_MAP);
				break;
			case GXE_POINT_LIGHT:
				loader.loadShadowTexture(*shadowMaps[l], GXE_CUBE_PERSPECTIVE_MAP);
				break;
			case GXE_SPOT_LIGHT:
				loader.loadShadowTexture(*shadowMaps[l], GXE_PERSPECTIVE_MAP);
				break;
			}
		}

		////Fix this
		//ShadowBox sb(&cam, renderer->lights[0]);
		//sb.update();
		//printf("Sb width %f\n", sb.getWidth());
		//printf("Sb height %f\n", sb.getHeight());
		//printf("Sb lenght %f\n", sb.getLenght());

		nMat = glm::ortho<float>(-10, 10, -10, 10, -10, 40) * glm::lookAt(l->getDirection(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		l->getDepthBiasMatrix() = biasMatrix * nMat;
	}
	m_shadowshader.unbind();
}

void ShadowRenderer::draw(MasterRenderer * renderer)
{
	m_shadowshader.bind();
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto l : renderer->lights)
	{
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMaps[l]->getTexture(), 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "[ShadowRederer] Framebuffer status is incorrect." << std::endl;

		for (auto entID : renderer->entities)
		{
			glBindVertexArray(entID->getModel().getVAO());

			m_shadowshader.setModelMatrix(nMat * entID->getModelMatrix());

			if (entID->getModel().wireframe == GXE_ON) //Skip wireframe objects
				continue;

			if (entID->getModel().modelType == GXE_ALT_MODEL)
				glDrawArrays(entID->getModel().renderType, 0, entID->getModel().getVertexCount());
			else
				glDrawElements(entID->getModel().renderType, entID->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			
			glBindVertexArray(0);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_shadowshader.unbind();

	gui.associateTexture(shadowMaps[renderer->lights[0]]->getTexture());
	gui.draw();

}

std::map<Light*, Texture*>& ShadowRenderer::getShadowMaps()
{
	return shadowMaps;
}
