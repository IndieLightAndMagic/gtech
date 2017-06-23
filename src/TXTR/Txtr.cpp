#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <STB/stb_image.h>
#include "Txtr.h"

SimpleImageData::SimpleImageData(const char * pucFilePath){
	m_pucData = stbi_load(pucFilePath,&iWidth, &iHeight, &iChannels, 0);
	if (!m_pucData){
		std::cout << "[+]SimpleImageData: Failed...." << std::endl;
		return;
	} 

	char rpath[1024];
	realpath(pucFilePath,rpath);
	std::cout << "[+]SimpleImageData: @ "<<rpath<<" : " << iWidth << " x " << iHeight << "[" << iChannels << "]" << std::endl;

}
SimpleImageData::~SimpleImageData(){
	stbi_image_free(m_pucData);
}
unsigned char * SimpleImageData::operator()(){ return m_pucData; }

Txtr::Txtr(const char * cpcImageTexture){

	SimpleImageData xSimpleImage(cpcImageTexture);
	
	m_bValid = false;
	m_puiTextures = 0x00;
	
	if (xSimpleImage() == 0x00 ) return;
	m_bValid = true;
	
	glGenTextures(1,&m_uiTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	

	txtrConfig();

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, xSimpleImage.iWidth, xSimpleImage.iHeight, 0, xSimpleImage.iChannels ==  3 ? GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, xSimpleImage());
	glGenerateMipmap(GL_TEXTURE_2D);
	

}

Txtr::Txtr(unsigned int uiNtextures){
	
	m_bValid = false;
	m_puiTextures = new unsigned int [uiNtextures];
	
	if (!m_puiTextures) return;
	

	m_uiNtextures = uiNtextures;
	glGenTextures(uiNtextures,m_puiTextures);

	m_bValid = true;
}
void Txtr::txtrSelect(){
	
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);

}
Txtr::~Txtr(){
	if (m_puiTextures) delete m_puiTextures;
}
void Txtr::txtrSelect(unsigned int uiTextureIndex){

	if (uiTextureIndex >= m_uiNtextures) return;
	glBindTexture(GL_TEXTURE_2D, m_puiTextures[uiTextureIndex]);
	m_uiActiveTextureIndex =  uiTextureIndex;

}
void Txtr::txtrConfig(){
 	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Txtr::txtrImage(SimpleImageData * pxImage){
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, pxImage->iWidth, pxImage->iHeight, 0, pxImage -> iChannels ==  3 ? GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, pxImage->operator()());
	glGenerateMipmap(GL_TEXTURE_2D);
}
bool Txtr::txtrValid(){
	return m_bValid;
}

