#include "shadowrenderer.h"
#include "masterrenderer.h"
#include "../Bitmap.h"

#define ONCE(x) \
static int z = 1; \
if(z) { z = 0; x; }


ShadowRenderer::ShadowRenderer() : m_sshader2("test", "test")
{
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

	m_shadowshader.bind();

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
			loader.loadShadowTexture(*shadowMaps[l], GXE_ORTHOGONAL_MAP);
		}

		nMat = glm::ortho<float>(-10, 10, -10, 10, -10, 20) * glm::lookAt(l->getDirection(), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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

			glDrawElements(GL_TRIANGLES, entID->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			
			glBindVertexArray(0);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_shadowshader.unbind();

	m_sshader2.bind();
	GLuint vao, vbo;

	std::vector<glm::vec3> vertices = 
	{
		glm::vec3(-1, 1, 0),
		glm::vec3(-1, -1, 0),
		glm::vec3(1, 1, 0),
		glm::vec3(1, -1, 0)
	};

	m_sshader2.setModelMatrix(glm::translate(glm::vec3(0.5f, 0.5f, 0.0f)) * glm::scale(glm::vec3(0.25f, 0.25f, 1.0f)));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 3);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	m_sshader2.unbind();

}
