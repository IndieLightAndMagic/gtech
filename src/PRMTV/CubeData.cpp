#include "CubeData.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif
#include <GLM/glm.hpp>

#include <iostream>

CubeData * pCubeArcheType = 0;
CubeData* CubeData::CreateCubeData(){
	if (!pCubeArcheType) pCubeArcheType = new CubeData;
	return pCubeArcheType;
}
void CubeData::FinishCubeData(){
	if (pCubeArcheType) delete pCubeArcheType;
}
CubeData::CubeData()
{
	//6 face x 2 triangles/face x 3 vertex/triangle x 8 comp/vertex
	m_pfData = new float[6*2*3*8];
	m_uiDataSize = sizeof(float)*6*2*3*8;
	for (auto faceIndex = 0; faceIndex < 6; ++faceIndex)
	for (auto triangleIndex = 0; triangleIndex < 2; ++triangleIndex)
	for (auto vertexIndex = 0; vertexIndex < 3; ++vertexIndex)
	for (auto vertexComponentIndex = 0; vertexComponentIndex < 8; ++vertexComponentIndex){

		int index = faceIndex*48 + triangleIndex*24 + vertexIndex*8 + vertexComponentIndex;

		if 		(vertexComponentIndex<3)m_pfData[index] = vertices[faces[faceIndex][triangleIndex][vertexIndex]][vertexComponentIndex];
		else if	(vertexComponentIndex<6)m_pfData[index] = normals[faceIndex][vertexComponentIndex-3];
		else if	(vertexComponentIndex<8)m_pfData[index] = texture[triangleIndex][vertexIndex][vertexComponentIndex-6];
		
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_uiDataSize, m_pfData, GL_STATIC_DRAW);

	/* Vertices (Location 0) */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Normal Coordinates (Location 1) */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	/* Texture (Location 2) */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

}
void CubeData::Bind(){
	glBindVertexArray(m_vao);
}
void CubeData::Draw(){
	glDrawArrays(GL_TRIANGLES, 0, 36);
}



CubeData::~CubeData(){
	delete m_pfData;
}
