#ifndef __PRMTV_H__
#define __PRMTV_H__

#include "CubeData.h"


class PrimitiveObj {

protected:
	float m_fScale;


};




/**
 * @brief      Class for cube object. Procure to have one depth on inheritance. Inherit also Protocols / Interfaces. This class inherits GObj and implements the behavior in GOb_Renderable.
 */
class CubeObj:public {
	
	/**
	 * A cube geometry data object. This object has all the vertices and texture coordinates for a cube. 
	 */
	float * m_pCubeDataPack;

	struct {
	/**
	 * Pointer to a Matrix translation Model.
	 */
		glm::mat4 * m_pModelTrx;

	/**
	 * Ponter to a Matrix rotational Model.
	 */
		glm::mat4 * m_pModelRtx;

		
		/**
		 * @brief      Sets the rotation.
		 *
		 * @param[in]  xAxis  The axis the rotation will take place around acis
		 * @param[in]  fDeg   The amount of rotation.
		 */
		void setRotation(glm::vec3 xAxis, float fDeg);

		/**
		 * @brief      Sets the position.
		 *
		 * @param[in]  xPos  The x position
		 */
		void setPosition(glm::vec3 xPos);	
		
		/**
		 * @brief      Set a scale for the object.
		 *
		 * @param[in]  fScale  The f scale
		 */
		void setScale(float fScale);


	}affineTransformations;


public:
	CubeObj();


}



#endif /*__PRMTV_H__*/
