#ifndef __PRMTV_H__
#define __PRMTV_H__

class PrimitiveObj {

protected:
	float m_fScale;


};




/**
 * @brief      Class for cube object. Procure to have one depth on inheritance. Inherit also Protocols / Interfaces. This class inherits GObj and implements the behavior in GOb_Renderable.
 */
class CubeObj:public GOb, GOb_Renderable{
	
	/**
	 * A cube geometry data object. This object has all the vertices and texture coordinates for a cube. 
	 */
	Cube m_cube;

public:
	CubeObj();


}



#endif /*__PRMTV_H__*/
