#include "Cam.h"

#ifndef CAM_EPSILON_FOV_DEG
#define CAM_EPSILON_FOV_DEG 1.0
#endif


#ifdef CAM_LOG_DBG
#define CAM_LOG_DBG_V(msg,v) std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << msg << " : " << v << std::endl
#define CAM_LOG_DBG(msg) std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << msg << std::endl
#else
#define CAM_LOG_DBG_V(msg,v) 
#define CAM_LOG_DBG(msg)
#endif

glm::vec3 normalUp(0.0f, 1.0f, 0.0f);

Cam::Cam(glm::vec3 xPosition, glm::vec3 xFront, glm::vec3 xUp, float fFov, float fAspectRatio, float fNearz, float fFarz){
	CAM_LOG_DBG("+ CAM ");

	m_position           = xPosition;
	m_front              = -xFront;
	m_right              = glm::normalize(glm::cross(xUp, m_front));
	m_up                 = glm::cross(m_front, m_right);
	m_fov                = fFov;
	m_nearz              = fNearz;
	m_farz               = fFarz;
	m_aspectRatio        = fAspectRatio;
	m_iUpdateFlags		 = 0x0;
	cbOnProjection       = 0x0;
	cbOnView             = 0x0;

	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearz, m_farz);
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);

}

Cam::~Cam(){
	CAM_LOG_DBG("- CAM ");
}


void Cam::vSetFov(float fFov){

	m_fov = fFov;
	m_iUpdateFlags |= CAM_UPDATE_PROJECTION;

}

void Cam::vSetPosition(glm::vec3 xPosition){

	m_position = xPosition;
	m_iUpdateFlags |= CAM_UPDATE_VIEW;

}

void Cam::vSetFront(glm::vec3 xFront){

	m_front = xFront;
	m_iUpdateFlags |= CAM_UPDATE_VIEW;

}

void Cam::vUpdateCamera(){

		if (!m_iUpdateFlags) return;


		if (m_iUpdateFlags & CAM_UPDATE_VIEW) m_view = glm::lookAt(m_position, m_position + m_front, m_up);
		if (m_iUpdateFlags & CAM_UPDATE_PROJECTION) m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearz, m_farz);

		m_iUpdateFlags = 0x00;

}
glm::mat4 Cam::xGetProjection() { return m_projection; }
glm::mat4 Cam::xGetView()		{ return m_view; }

















