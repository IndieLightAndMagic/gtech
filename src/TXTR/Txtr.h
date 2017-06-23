#ifndef __TXTR_H__
#define __TXTR_H__

class SimpleImageData{
	unsigned char * m_pucData;
public:
	int iWidth, iHeight, iChannels;
	SimpleImageData(const char * imageFilePath);
	~SimpleImageData();
	unsigned char * operator()();
};

class Txtr {
	
	unsigned int m_uiTexture;
	bool m_bValid;
public:
	/*!
		@brief Generate a number of texture handlers.
		@param nTextures The number of handlers to generate;
	*/
	Txtr(unsigned int nTextures);
	Txtr(const char * cpcTextureImagePath);
	virtual ~Txtr();

	/* Select a texture */
	void txtrSelect(unsigned int textureUnitToMakeActive = GL_TEXTURE0);
	/* By default texture config */
	virtual void txtrConfig();
	
	/* Checki if valid */
	bool txtrValid();

};
#endif/*__TXTR_H__*/