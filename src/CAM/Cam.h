#ifndef _CAM_H_
#define _CAM_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#define CAM_UPDATE_PROJECTION	0x1
#define CAM_UPDATE_VIEW			0x2


struct CamProjection {

	float m_fov;
	float m_nearz;
	float m_farz;
	float m_aspectRatio;
	glm::mat4 m_projection;
};
struct CamView{

	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_position;
	glm::mat4 m_view;
};

class Cam{

	int m_iUpdateFlags;

public:	
	glm::mat4 m_projection;
	glm::mat4 m_view;


	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_position;
	
	float m_fov;
	float m_nearz;
	float m_farz;
	float m_aspectRatio;


	Cam(glm::vec3 xPosition, glm::vec3 xFront, glm::vec3 up, float fov, float aspectRatio, float nearz, float farz);
	virtual ~Cam();

	/* Getters and setters */
	void vSetFov(float fFov);
	void vSetPosition(glm::vec3 xPosition);
	void vSetFront(glm::vec3 xFront);



	/* Callbacks when something is dirty (in general a drawing context is a list of shader affected by these changes ) */
	void (*cbOnProjection)(glm::mat4, void * pvDrawingContext);
	void (*cbOnView)(glm::mat4, void * pvDrawingContext);
	void * m_pvDrawingContext;

	void vUpdateCamera();
	glm::mat4 xGetProjection();
	glm::mat4 xGetView();

};


#endif /* __CAM_H__ */
