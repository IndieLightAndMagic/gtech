#ifndef __TXTR_H__
#define __TXTR_H__

class SimpleImageData{
	bool m_bValid;
	unsigned char * m_pucData;
public:
	int iWidth, iHeight, iChannels;
	SimpleImageData(const char * imageFilePath);
	~SimpleImageData();
	unsigned char * operator()();
};

class Txtr {
	
	unsigned int m_uiTexture;
	unsigned int m_uiActiveTextureIndex;
	unsigned int m_uiNtextures;

	bool m_bValid;
	unsigned int * m_puiTextures;
public:
	/*!
		@brief Generate a number of texture handlers.
		@param nTextures The number of handlers to generate;
	*/
	Txtr(unsigned int nTextures);
	Txtr(const char * cpcTextureImagePath);
	virtual ~Txtr();

	/* Select a texture */
	void txtrSelect();
	void txtrSelect(unsigned int uiTextureIndex);
	/* By default texture config */
	void txtrConfig();
	/* Assign Data for the texture */
	void txtrImage(SimpleImageData * pxImg);

	/* Checki if valid */
	bool txtrValid();
};
#endif/*__TXTR_H__*/