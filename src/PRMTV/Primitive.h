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
	
	
	CubeData m_glData;
	

public:
	CubeObj();


}



#endif /*__PRMTV_H__*/
