#include "masterrenderer.h"
#include "../camera.h"

MasterRenderer::MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : m_sshader(vertexShaderFile, fragmentShaderFile)
{

}

void MasterRenderer::update(Camera & camera)
{
	m_sshader.bind();
	m_sshader.setEyeDir(camera.getEye());
	m_sshader.setProjViewMatrix(camera.getProjViewMatrix());
	static float time = 0.0f;
	m_sshader.setTime(time);
	for (auto l : lights)
	{
		if (l->getType() == GXE_DIRECTIONAL_LIGHT)
		{
			l->computeHalfVector(camera);
		}
		if (l->isChanged())
		{
			m_sshader.setLight(l);
		}
	}
	m_sshader.unbind();
}

void MasterRenderer::draw()
{
	if (entities.empty())
		return;

	m_sshader.bind();
	for (auto entID : entities)
	{
		glBindVertexArray(entID->getModel().getVAO());

		if (&entID->getTexture() != NULL) entID->getTexture().bind();

		m_sshader.setModelMatrix(entID->getModelMatrix()); //Use further methods

		glDrawElements(GL_TRIANGLES, entID->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);

		if (&entID->getTexture() != NULL) entID->getTexture().unbind(); //Use further methods

		glBindVertexArray(0);
	}
	m_sshader.unbind();
}
