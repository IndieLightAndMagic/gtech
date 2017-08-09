#include "CubeData.h"
#include "Cube.h"

CubeObj::CubeObj(){
	/* Generate Vao */
	m_cube.Gen();
	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	SetRotation(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f);
	m_pShaderProgram = 0;
	m_bRedraw = true;

}
void CubeObj::SetPosition(glm::vec3 xPosition){

	m_pos = xPosition;
	m_tx = glm::translate(m_tx, xPosition);

}
void CubeObj::SetRotation(glm::vec3 xAxis, float fDeg){

	m_fDeg = fDeg;
	m_rt = glm::rotate(m_rt, glm::radians(fDeg), xAxis);

}
void CubeObj::Update(){}

void CubeObj::AssignProgramRenderer(Program * pShaderProgram){

	m_pShaderProgram = pShaderProgram;
}

void CubeObj::Draw(){
	
	m_pShaderProgram->use();
	m_cube.Bind();
	m_pShaderProgram->setMat4("objModel.tx", m_tx);
	m_pShaderProgram->setMat4("objModel.rt", m_rt);
	m_cube.Draw();

}

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float CubeObjVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//70
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	//32
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//51
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//70

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	//03
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	//03
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	//41
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//42
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//53
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//42

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//31
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//31
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//20
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	//33
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//51
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	//40
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0		//51	
	
	};