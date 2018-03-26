#include "masterrenderer.h"
#include "../camera.h"
#include "../Bitmap.h"

MasterRenderer::MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : m_sshader(vertexShaderFile, fragmentShaderFile)
{

}

void MasterRenderer::update(Camera & camera)
{
	m_shadowrenderer.update(this, camera);
	m_skyrenderer.update(camera);

	m_sshader.bind();
	m_sshader.setEyeDir(math::normalize(camera.getEye()));
	m_sshader.setProjViewMatrix(camera.getProjViewMatrix());
	for(auto light : lights)
	{
		m_sshader.setDepthBiasMatrix(light->getDepthBiasMatrix());
		m_sshader.setLight(light);
	}

	m_sshader.unbind();

}

void MasterRenderer::draw()
{
	if (entities.empty())
		return;

	m_shadowrenderer.draw(this);
	m_skyrenderer.draw();

	m_sshader.bind();
	glActiveTexture(GL_TEXTURE1); //Fix this -- clean this
	glBindTexture(GL_TEXTURE_2D, m_shadowrenderer.getShadowMaps().at(lights[0])->getTexture());
	glActiveTexture(GL_TEXTURE0);
	for (auto entID : entities)
	{
		glBindVertexArray(entID->getModel().getVAO());

		if (&entID->getTexture() != NULL) entID->getTexture().bind();

		m_sshader.setModelMatrix(entID->getModelMatrix()); //Use further methods

		if (entID->getModel().wireframe == GXE_ON)
		{
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (entID->getModel().modelType == GXE_ALT_MODEL)
			glDrawArrays(entID->getModel().renderType, 0, entID->getModel().getVertexCount());
		else
			glDrawElements(entID->getModel().renderType, entID->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);

		if (entID->getModel().wireframe == GXE_ON)
		{
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (&entID->getTexture() != NULL) entID->getTexture().unbind(); //Use further methods

		glBindVertexArray(0);
	}
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

	m_sshader.unbind();
}
