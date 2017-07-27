#ifndef __G_H__
#define __G_H__


/* This is an interface which defines a protocol/behavior of how to get ids */
class Id_Iface{
protected:
	/* This will be inherited to derived classes, the m_id */
	unsigned long int m_id;
	virtual void initId() = 0; 
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