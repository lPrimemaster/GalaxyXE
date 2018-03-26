#include "skyrenderer.h"



SkyRenderer::SkyRenderer()
{

}


SkyRenderer::~SkyRenderer()
{
}

void SkyRenderer::update(Camera & cam)
{
	m_skyshader.bind();
	glm::mat4 out = cam.getViewMatrix();
	out[3][0] = 0;
	out[3][1] = 0;
	out[3][2] = 0;
	m_skyshader.setProjViewMatrix(cam.getProjectMatrix() * out);
	m_skyshader.unbind();
}

void SkyRenderer::draw()
{
	m_skyshader.bind();

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_skybox.getModel().getVAO());
	GLint pol;
	glGetIntegerv(GL_POLYGON_MODE, &pol);
	if(pol == GL_LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Optimize this

	m_skybox.getTexture().bind();

	glDrawArrays(GL_TRIANGLES, 0, m_skybox.getModel().getVertexCount());
	glDepthMask(GL_TRUE);

	m_skybox.getTexture().unbind();

	if (pol == GL_LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Optimize this

	glBindVertexArray(0);

	m_skyshader.unbind();
}
