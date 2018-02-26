#include "masterrenderer.h"
#include "../camera.h"
#include "../Bitmap.h"

MasterRenderer::MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : m_sshader(vertexShaderFile, fragmentShaderFile)
{

}

void MasterRenderer::update(Camera & camera)
{
	m_shadowrenderer.update(this, camera);

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

	m_sshader.bind();

	GLuint samplerLoc = glGetUniformLocation(m_sshader.getID(), "sampler");
	glUniform1i(samplerLoc, 0);
	GLuint shadowLoc = glGetUniformLocation(m_sshader.getID(), "shadow");
	glUniform1i(shadowLoc, 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 3);
	glActiveTexture(GL_TEXTURE0);

	for (auto entID : entities)
	{
		glBindVertexArray(entID->getModel().getVAO());

		if (&entID->getTexture() != NULL) entID->getTexture().bind();

		m_sshader.setModelMatrix(entID->getModelMatrix()); //Use further methods

		glDrawElements(GL_TRIANGLES, entID->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);

		if (&entID->getTexture() != NULL) entID->getTexture().unbind(); //Use further methods

		glBindVertexArray(0);
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

	m_sshader.unbind();
}
