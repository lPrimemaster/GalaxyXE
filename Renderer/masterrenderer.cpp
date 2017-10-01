#include "masterrenderer.h"
#include "../camera.h"

MasterRenderer::MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : m_sshader(vertexShaderFile, fragmentShaderFile)
{

}

void MasterRenderer::update(Camera & camera)
{
	m_sshader.bind();
	m_sshader.setProjViewMatrix(camera.getProjViewMatrix());
	m_sshader.unbind();
}

void MasterRenderer::draw()
{
	m_sshader.bind();
	static int count = 0;
	//glActiveTexture(GL_TEXTURE0);

	static bool once = true;
	for (auto* entID : entities)
	{
		if (once)
		{
			printf("Pcount: %d\n", entID->getModel().getPrimitiveCount());
		}

		//entID->getModel().getTex()->bind(); //Use further methods
		glBindVertexArray(entID->getModel().getVAO());

		m_sshader.setModelMatrix(entID->getModelMatrix()); //Use further methods

		glDrawElements(GL_TRIANGLES, entID->getModel().getPrimitiveCount() * 3, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		//entID->getModel().getTex()->unbind(); //Use further methods
	}

	once = false;
	m_sshader.unbind();
}

StaticShader * MasterRenderer::getShader()
{
	return &m_sshader;
}
