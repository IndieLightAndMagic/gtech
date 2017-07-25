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
	 * Indices to make the triangles. 
	 */
	unsigned int * m_pIndx;
	unsigned int * m_pIndx_TxtrCoords;
public:
	/* Create a Cube of size scale */
	CubeData(float scale=1.0f);
	~CubeData();
	/*!
		\brief Get the cube packed ready for opengl.

		\param pData If pData == null, the function will allocate the memory for you (using new). You are responsible for deleting the memory used for storing the cube. If pData is not null, it should be an address to a memory region with enough capacity to hold the cube. In both cases, whether pData is null or not, the user is responsible for the memory allocated.

		\return A pointer to an address with the cube data in the following format:
		Given vi: [float x, float y, float z, float textcoord_x, float textcoord_y]
		Given a Triangle tj: [v0j, v1j, v2j]
		Given a surface of the cube: Sk:[t0k, t1k]

		The cube has 6 faces (surfaces): C:[S0 S1 S2 S3 S4 S5].

	*/
	float * getCubeDataPack(void * pData);
	float * getCubeDataPackEBO(void * pData, void * pEBO);
};