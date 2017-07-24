#ifndef __G_H__
#define __G_H__


/* This is an interface which defines a protocol/behavior of how to get ids */
class Id_Iface{
protected:
	/* This will be inherited to derived classes, the m_id */
	unsigned long int m_id;
	virtual void initId() = 0; 
};

/**
 * @brief      This abstract class defines a renderable object.
 */
class GOb_Renderable_Iface{

protected:
	/**
	 * Pointer to a Matrix translation Model.
	 */
	glm::mat4 * m_pModelTrx;

	/**
	 * Ponter to a Matrix rotational Model.
	 */
	glm::mat4 * m_pModelRtx;

	/**
	 * @brief      Derived classes must implement this. Rotate the object around an axis.  
	 *
	 * @param[in]  rotAxis  The rot axis by means of a x,y,z vector.
	 * @param[in]  deg      The degrees
	 */
	virtual void setRotation(glm::v3 rotAxis, float deg) = 0;
	/**
	 * @brief      Derived classes must implement this. Sets the object's position.
	 *
	 * @param[in]  position	The object's position
	 */
	virtual void setPosition(glm::v3 position) = 0;

};

class GOb:public Id_Iface{

	/* We have to complain with the Id_Iface protocol */	
	void initId();
public:
	GOb() {
		initId();
		std::cout << "+GOb [@ 0x" << std::hex << m_id << " ]"<<std::endl;
		initOb();
	}
	virtual void initOb(){
		std::cout << "Obj [@ 0x" << std::hex << m_id << " ] default initialized."<<std::endl;
	}
};




#endif/*__G_H__*/