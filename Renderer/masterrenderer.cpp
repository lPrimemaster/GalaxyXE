#include "masterrenderer.h"
#include "../camera.h"

MasterRenderer::MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : m_sshader(vertexShaderFile, fragmentShaderFile)
{

}

void MasterRenderer::update(Camera & camera)
{
	m_sshader.bind();
	m_sshader.setProjViewMatrix(camera.getProjViewMatrix());
	t = camera.getProjViewMatrix();
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
			printf("MVP matrix\n");
			glm::mat4 mvp = t * entID->getModelMatrix();
			for (int i = 0; i < 4; i++)
				printf("%f %f %f %f\n", t[i][0], t[i][1], t[i][2], t[i][3]);
			printf("Model matrix\n");
			for (int i = 0; i < 4; i++)
				printf("%f %f %f %f\n", entID->getModelMatrix()[i][0], entID->getModelMatrix()[i][1], entID->getModelMatrix()[i][2], entID->getModelMatrix()[i][3]);
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
