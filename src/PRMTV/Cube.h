#ifndef __CUBE_H__
#define __CUBE_H__

#ifdef __APPLE__
#include <OpenGl/gl3.h>
#include <OpenGl/glext.h>
#else
#include <OpenGl/gl.h>
#endif


#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SHDR/shdr.h>

#include "CubeData.h"
/**
 * @brief      The Object in the Scene.
 */
class CubeObj{
	
protected:

	/* Static Data loadel in the GPU(By OpenGl means) */
	CubeData m_cube;

	/* The position matrix */
	glm::mat4 m_tx;
	glm::vec3 m_pos;
	/**
	 * The local rotation matrix
	 */
	glm::mat4 m_rt;
	float m_fDeg;

	/**
	 * The renderer.
	 */
	Program * m_pShaderProgram;


	bool m_bRedraw;

public:
	CubeObj();
	~CubeObj(){}
	void SetPosition(glm::vec3 xPosition);
	void SetRotation(glm::vec3 xAxis, float fDeg);

	/**
	 * @brief      Assign the program shader who will "paint" the object.
	 *
	 * @param[in]  m_pShaderProgram  Weak reference to the ShaderProgram.
	 */
	void AssignProgramRenderer(Program * m_pShaderProgram);

	/**
	 * @brief      Calculate new positions, orientations.
	 *  
	 */
	virtual void Update();


	/*! Draw the object */
	void Draw();


};

#endif /*__CUBE_H__*/
