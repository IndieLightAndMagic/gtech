#ifndef __CUBE_DATA_H__
#define __CUBE_DATA_H__

/* This class is only to calculate the geometry of a cube of m_fScale * [W=1,H=1,D=1]. */
class CubeData final {
	
	
	
	float m_fScale;
	/**
	 * Local space coordinates array for the cube vertices.
	 */
	float * m_pVrtx;

	/**
	 * Texture coordinates for each vertex.
	 */
	float * m_pVrtx_TxtrCoord;

	/**
	 * Normals. 
	 */
	float * m_pVrtx_Normals;
	/**
	 * Indices to make the triangles. 
	 */
	unsigned int * m_pIndx;
	unsigned int * m_pIndx_TxtrCoords;

	/* GL OBJECTS */ 
	unsigned int m_vbo,m_vao;
	float * m_fData;

	/* Create a Cube and GEN VAO & VBO for it. */
	CubeData();
	void Gen();
	
public:
	static CubeData * CreateCubeData();
	/* Dangerous */
	static void FinishCubeData();
	~CubeData();
	
	void Bind();
	void Draw();
};


#endif /*__CUBE_DATA_H__*/