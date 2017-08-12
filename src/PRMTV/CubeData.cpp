#include "CubeData.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif
#include <GLM/glm.hpp>

CubeData * pSingleton = 0;
CubeData* CubeData::CreateCubeData(){
	if (!pSingleton) pSingleton = new CubeData;
	return pSingleton;
}
void CubeData::FinishCubeData(){
	if (pSingleton) delete pSingleton;
}
CubeData::CubeData():
	m_fScale(1.0f),
	m_pVrtx(0x0),
	m_pVrtx_TxtrCoord(0x0),
	m_pIndx(0x0),
	m_pIndx_TxtrCoords(0x0),
	m_fData(0x0)
{
	m_pVrtx = new float[24];
	m_pVrtx_TxtrCoord = new float[8];
	m_pVrtx_Normals = new float [18];

	m_pIndx = new unsigned int[36];
	m_pIndx_TxtrCoords = new unsigned int[36];


    m_pIndx[0]=7;
    m_pIndx[1]=3;
    m_pIndx[2]=1;
    m_pIndx[3]=1;
    m_pIndx[4]=5;
    m_pIndx[5]=7;
    m_pIndx[6]=6;
    m_pIndx[7]=2;
    m_pIndx[8]=0;
    m_pIndx[9]=0;
    m_pIndx[10]=4;
    m_pIndx[11]=6;
    m_pIndx[12]=4;
    m_pIndx[13]=5;
    m_pIndx[14]=7;
    m_pIndx[15]=7;
    m_pIndx[16]=6;
    m_pIndx[17]=4;
    m_pIndx[18]=0;
    m_pIndx[19]=1;
    m_pIndx[20]=3;
    m_pIndx[21]=3;
    m_pIndx[22]=2;
    m_pIndx[23]=0;
    m_pIndx[24]=7;
    m_pIndx[25]=3;
    m_pIndx[26]=2;
    m_pIndx[27]=2;
    m_pIndx[28]=6;
    m_pIndx[29]=7;
    m_pIndx[30]=5;
    m_pIndx[31]=1;
    m_pIndx[32]=0;
    m_pIndx[33]=0;
    m_pIndx[34]=4;
    m_pIndx[35]=5;
    
    
    m_pIndx_TxtrCoords[0] = 0;
    m_pIndx_TxtrCoords[1] = 2;
    m_pIndx_TxtrCoords[2] = 3;
    m_pIndx_TxtrCoords[3] = 3;
    m_pIndx_TxtrCoords[4] = 1;
    m_pIndx_TxtrCoords[5] = 0;
    m_pIndx_TxtrCoords[6] = 0;
    m_pIndx_TxtrCoords[7] = 2;
    m_pIndx_TxtrCoords[8] = 3;
    m_pIndx_TxtrCoords[9] = 3;
    m_pIndx_TxtrCoords[10] = 1;
    m_pIndx_TxtrCoords[11] = 0;
    m_pIndx_TxtrCoords[12] = 2;
    m_pIndx_TxtrCoords[13] = 3;
    m_pIndx_TxtrCoords[14] = 1;
    m_pIndx_TxtrCoords[15] = 1;
    m_pIndx_TxtrCoords[16] = 0;
    m_pIndx_TxtrCoords[17] = 2;
    m_pIndx_TxtrCoords[18] = 2;
    m_pIndx_TxtrCoords[19] = 3;
    m_pIndx_TxtrCoords[20] = 1;
    m_pIndx_TxtrCoords[21] = 1;
    m_pIndx_TxtrCoords[22] = 0;
    m_pIndx_TxtrCoords[23] = 2;
    m_pIndx_TxtrCoords[24] = 1;
    m_pIndx_TxtrCoords[25] = 3;
    m_pIndx_TxtrCoords[26] = 2;
    m_pIndx_TxtrCoords[27] = 2;
    m_pIndx_TxtrCoords[28] = 0;
    m_pIndx_TxtrCoords[29] = 1;
    m_pIndx_TxtrCoords[30] = 1;
    m_pIndx_TxtrCoords[31] = 3;
    m_pIndx_TxtrCoords[32] = 2;
    m_pIndx_TxtrCoords[33] = 2;
    m_pIndx_TxtrCoords[34] = 0;
    m_pIndx_TxtrCoords[35] = 1;

	/* Build 8 cube vertices */
	for (auto index0 = 0; index0 <8; ++index0){
		auto indexprob = index0;
		for (int index1 = 0; index1<=2; index1++){
			m_pVrtx[index0*3+index1] = 0.5f*m_fScale;
			m_pVrtx[index0*3+index1] *= indexprob & 0x1 ? -1.0f : 1.0f;
			indexprob = indexprob >> 1;
		}
	}

	/* Build 4 texture coordinates */
	for (auto index0 = 0; index0 <4; ++index0){
		m_pVrtx_TxtrCoord[index0*2+0] = index0<2		? 0.0f : 1.0f;
		m_pVrtx_TxtrCoord[index0*2+1] = index0&0x1	? 1.0f : 0.0f; 	
	}
	
	/* Build 6 normals */
	for (auto index0 = 0; index0 <6; ++index0){
		
		glm::vec3 p[3];
		glm::vec3 p0p1,p1p2;

		for (auto index1 = 0; index1 < 3; ++index1){

			int vertexIdx = m_pIndx[index0*6 + index1];
			p[index1] = glm::vec3 ( m_pVrtx[vertexIdx*3 + 0], m_pVrtx[vertexIdx*3 + 1], m_pVrtx[vertexIdx*3 + 2] ); 

		}

		/* triang borders */
		p0p1 = glm::vec3(p[1] - p[0]);
		p1p2 = glm::vec3(p[2] - p[1]);
		
		/* calc normal */
		glm::vec3 normal = glm::normalize(glm::cross(p0p1,p1p2));
		m_pVrtx_Normals[index0*3 + 0] = normal.x;
		m_pVrtx_Normals[index0*3 + 1] = normal.y;
		m_pVrtx_Normals[index0*3 + 2] = normal.z;		
	
	}

	
	unsigned int uiComponentsCount = 8*3*2*6;
	m_fData = new float[8*3*2*6]; /* 6 faces, 2 triangles per face, 3 vertices per triangle, 8 components per vertex */ 

	for (auto index = 0; index < uiComponentsCount ; ++index)
	{
		int modIndex = index%8;
		int divIndex = index/8;
		int vertexIndex;
		if (modIndex<3) {
			vertexIndex = m_pIndx[divIndex];
			vertexIndex *= 3;
			m_fData[index] = m_pVrtx[ vertexIndex + modIndex ]; 
		} else if (modIndex<5) {
			vertexIndex = m_pIndx_TxtrCoords[ divIndex ];
			vertexIndex *= 2;
			m_fData[index] = m_pVrtx_TxtrCoord[ vertexIndex + modIndex - 3];
		} else {
			vertexIndex = divIndex / 6;
			m_fData[index] = m_pVrtx_Normals[ vertexIndex + modIndex - 5];
		}
	}
}

void CubeData::Gen(){

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_fData), m_fData, GL_STATIC_DRAW);

	/* Vertices (Location 0) */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Texture Coordinates (Location 1) */
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	/* Normals (Location 2) */
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(5*sizeof(float)));
	glEnableVertexAttribArray(2);


}
void CubeData::Bind(){
	glBindVertexArray(m_vao);
}
void CubeData::Draw(){
	glDrawArrays(GL_TRIANGLES, 0, 36);
}



CubeData::~CubeData(){

	if (m_pIndx_TxtrCoords) delete m_pIndx_TxtrCoords;
	if (m_pVrtx_TxtrCoord) delete m_pVrtx_TxtrCoord;
	if (m_pIndx) delete m_pIndx;
	if (m_pVrtx) delete m_pVrtx;
	if (m_fData) delete m_fData;
}
