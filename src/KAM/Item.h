#ifndef _ITEM_H_
#define _ITEM_H_

#include <glm/glm.hpp>





typedef struct ItemMatrix {

	glm::mat4 m;
	ItemMatrix(){
		m = glm::mat4(1.0f);
	}

}ItemMatrix;




#endif /* _ITEM_H_ */