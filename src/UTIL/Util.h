#ifndef __UTIL__H__
#define __UTIL__H__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class OSWindowWrapper {

protected:
	bool m_bValid;
	std::string m_sAppTitle;
	int m_iWidth, m_iHeight;
public:
	OSWindowWrapper(int iAppWidth, int iAppHeight, std::string sAppTitle);
	virtual ~OSWindowWrapper();

};


class OSWindowWrapperSDL: public OSWindowWrapper {
	SDL_Window * m_pxWindow;
	SDL_GLContext m_xContext;
public:
	OSWindowWrapperSDL(int iWidth, int iHeight, std::string rsAppName = "Unnamed");
	~OSWindowWrapperSDL();
	SDL_Window * operator()();

	bool bOSWWCloseEventReceived();
	void vOSWWSwap();
	void vOSWWRaiseCloseEvent();
};

class OGLManager {
	OGLManager();
	~OGLManager();
	static OGLManager * s_instance;
public:
	static OGLManager* init();
	static void reset();


};






/* COLOR LIST as in http://cloford.com/resources/colours/namedcol.htm*/
#define LIGHTPINK				255.0f/255.0f,	182.0f/255.0f,	193.0f/255.0f
#define PINK					255.0f/255.0f,	192.0f/255.0f,	203.0f/255.0f
#define CRIMSON					220.0f/255.0f,	20.0f/255.0f,	60.0f/255.0f
#define LAVENDERBLUSH			255.0f/255.0f,	240.0f/255.0f,	245.0f/255.0f
#define PALEVIOLETRED			219.0f/255.0f,	112.0f/255.0f,	147.0f/255.0f
#define HOTPINK					255.0f/255.0f,	105.0f/255.0f,	180.0f/255.0f
#define DEEPPINK				255.0f/255.0f,	20.0f/255.0f,	147.0f/255.0f
#define MEDIUMVIOLETRED			199.0f/255.0f,	21.0f/255.0f,	133.0f/255.0f
#define ORCHID					218.0f/255.0f,	112.0f/255.0f,	214.0f/255.0f
#define THISTLE					216.0f/255.0f,	191.0f/255.0f,	216.0f/255.0f
#define PLUM					221.0f/255.0f,	160.0f/255.0f,	221.0f/255.0f
#define VIOLET					238.0f/255.0f,	130.0f/255.0f,	238.0f/255.0f
#define FUCHSIA					255.0f/255.0f,	0.0f/255.0f,	255.0f/255.0f
#define DARKMAGENTA				139.0f/255.0f,	0.0f/255.0f,	139.0f/255.0f
#define PURPLE					128.0f/255.0f,	0.0f/255.0f,	128.0f/255.0f
#define MEDIUMORCHID			186.0f/255.0f,	85.0f/255.0f,	211.0f/255.0f
#define DARKVIOLET				148.0f/255.0f,	0.0f/255.0f,	211.0f/255.0f
#define DARKORCHID				153.0f/255.0f,	50.0f/255.0f,	204.0f/255.0f
#define INDIGO					75.0f/255.0f,	0.0f/255.0f,	130.0f/255.0f
#define BLUEVIOLET				138.0f/255.0f,	43.0f/255.0f,	226.0f/255.0f
#define MEDIUMPURPLE			147.0f/255.0f,	112.0f/255.0f,	219.0f/255.0f
#define MEDIUMSLATEBLUE			123.0f/255.0f,	104.0f/255.0f,	238.0f/255.0f
#define SLATEBLUE				106.0f/255.0f,	90.0f/255.0f,	205.0f/255.0f
#define DARKSLATEBLUE			72.0f/255.0f,	61.0f/255.0f,	139.0f/255.0f
#define GHOSTWHITE				248.0f/255.0f,	248.0f/255.0f,	255.0f/255.0f
#define LAVENDER				230.0f/255.0f,	230.0f/255.0f,	250.0f/255.0f
#define BLUE					0.0f/255.0f,	0.0f/255.0f,	255.0f/255.0f
#define MEDIUMBLUE				0.0f/255.0f,	0.0f/255.0f,	205.0f/255.0f
#define DARKBLUE				0.0f/255.0f,	0.0f/255.0f,	139.0f/255.0f
#define NAVY					0.0f/255.0f,	0.0f/255.0f,	128.0f/255.0f
#define MIDNIGHTBLUE			25.0f/255.0f,	25.0f/255.0f,	112.0f/255.0f
#define ROYALBLUE				65.0f/255.0f,	105.0f/255.0f,	225.0f/255.0f
#define CORNFLOWERBLUE			100.0f/255.0f,	149.0f/255.0f,	237.0f/255.0f
#define LIGHTSTEELBLUE			176.0f/255.0f,	196.0f/255.0f,	222.0f/255.0f
#define LIGHTSLATEGRAY			119.0f/255.0f,	136.0f/255.0f,	153.0f/255.0f
#define SLATEGRAY				112.0f/255.0f,	128.0f/255.0f,	144.0f/255.0f
#define DODGERBLUE				30.0f/255.0f,	144.0f/255.0f,	255.0f/255.0f
#define ALICEBLUE				240.0f/255.0f,	248.0f/255.0f,	255.0f/255.0f
#define STEELBLUE				70.0f/255.0f,	130.0f/255.0f,	180.0f/255.0f
#define LIGHTSKYBLUE			135.0f/255.0f,	206.0f/255.0f,	250.0f/255.0f
#define SKYBLUE					135.0f/255.0f,	206.0f/255.0f,	235.0f/255.0f
#define DEEPSKYBLUE				0.0f/255.0f,	191.0f/255.0f,	255.0f/255.0f
#define LIGHTBLUE				173.0f/255.0f,	216.0f/255.0f,	230.0f/255.0f
#define POWDERBLUE				176.0f/255.0f,	224.0f/255.0f,	230.0f/255.0f
#define CADETBLUE				95.0f/255.0f,	158.0f/255.0f,	160.0f/255.0f
#define DARKTURQUOISE			0.0f/255.0f,	206.0f/255.0f,	209.0f/255.0f
#define AZURE					240.0f/255.0f,	255.0f/255.0f,	255.0f/255.0f
#define LIGHTCYAN				224.0f/255.0f,	255.0f/255.0f,	255.0f/255.0f
#define PALETURQUOISE			175.0f/255.0f,	238.0f/255.0f,	238.0f/255.0f
#define AQUA					0.0f/255.0f,	255.0f/255.0f,	255.0f/255.0f
#define DARKCYAN				0.0f/255.0f,	139.0f/255.0f,	139.0f/255.0f
#define TEAL					0.0f/255.0f,	128.0f/255.0f,	128.0f/255.0f
#define DARKSLATEGRAY			47.0f/255.0f,	79.0f/255.0f,	79.0f/255.0f
#define MEDIUMTURQUOISE			72.0f/255.0f,	209.0f/255.0f,	204.0f/255.0f
#define LIGHTSEAGREEN			32.0f/255.0f,	178.0f/255.0f,	170.0f/255.0f
#define TURQUOISE				64.0f/255.0f,	224.0f/255.0f,	208.0f/255.0f
#define AQUAMARINE				127.0f/255.0f,	255.0f/255.0f,	212.0f/255.0f
#define MEDIUMAQUAMARINE		102.0f/255.0f,	205.0f/255.0f,	170.0f/255.0f
#define MEDIUMSPRINGGREEN		0.0f/255.0f,	250.0f/255.0f,	154.0f/255.0f
#define MINTCREAM				245.0f/255.0f,	255.0f/255.0f,	250.0f/255.0f
#define SPRINGGREEN				0.0f/255.0f,	255.0f/255.0f,	127.0f/255.0f
#define MEDIUMSEAGREEN			60.0f/255.0f,	179.0f/255.0f,	113.0f/255.0f
#define SEAGREEN				46.0f/255.0f,	139.0f/255.0f,	87.0f/255.0f
#define HONEYDEW				240.0f/255.0f,	255.0f/255.0f,	240.0f/255.0f
#define DARKSEAGREEN			143.0f/255.0f,	188.0f/255.0f,	143.0f/255.0f
#define PALEGREEN				152.0f/255.0f,	251.0f/255.0f,	152.0f/255.0f
#define LIGHTGREEN				144.0f/255.0f,	238.0f/255.0f,	144.0f/255.0f
#define LIMEGREEN				50.0f/255.0f,	205.0f/255.0f,	50.0f/255.0f
#define LIME					0.0f/255.0f,	255.0f/255.0f,	0.0f/255.0f
#define FORESTGREEN				34.0f/255.0f,	139.0f/255.0f,	34.0f/255.0f
#define GREEN					0.0f/255.0f,	128.0f/255.0f,	0.0f/255.0f
#define DARKGREEN				0.0f/255.0f,	100.0f/255.0f,	0.0f/255.0f
#define LAWNGREEN				124.0f/255.0f,	252.0f/255.0f,	0.0f/255.0f
#define CHARTREUSE				127.0f/255.0f,	255.0f/255.0f,	0.0f/255.0f
#define GREENYELLOW				173.0f/255.0f,	255.0f/255.0f,	47.0f/255.0f
#define DARKOLIVEGREEN			85.0f/255.0f,	107.0f/255.0f,	47.0f/255.0f
#define YELLOWGREEN				154.0f/255.0f,	205.0f/255.0f,	50.0f/255.0f
#define OLIVEDRAB				107.0f/255.0f,	142.0f/255.0f,	35.0f/255.0f
#define IVORY					255.0f/255.0f,	255.0f/255.0f,	240.0f/255.0f
#define BEIGE					245.0f/255.0f,	245.0f/255.0f,	220.0f/255.0f
#define LIGHTYELLOW				255.0f/255.0f,	255.0f/255.0f,	224.0f/255.0f
#define LIGHTGOLDENRODYELLOW	250.0f/255.0f,	250.0f/255.0f,	210.0f/255.0f
#define YELLOW					255.0f/255.0f,	255.0f/255.0f,	0.0f/255.0f
#define OLIVE					128.0f/255.0f,	128.0f/255.0f,	0.0f/255.0f
#define DARKKHAKI				189.0f/255.0f,	183.0f/255.0f,	107.0f/255.0f
#define PALEGOLDENROD			238.0f/255.0f,	232.0f/255.0f,	170.0f/255.0f
#define LEMONCHIFFON			255.0f/255.0f,	250.0f/255.0f,	205.0f/255.0f
#define KHAKI					240.0f/255.0f,	230.0f/255.0f,	140.0f/255.0f
#define GOLD					255.0f/255.0f,	215.0f/255.0f,	0.0f/255.0f
#define CORNSILK				255.0f/255.0f,	248.0f/255.0f,	220.0f/255.0f
#define GOLDENROD				218.0f/255.0f,	165.0f/255.0f,	32.0f/255.0f
#define DARKGOLDENROD			184.0f/255.0f,	134.0f/255.0f,	11.0f/255.0f
#define FLORALWHITE				255.0f/255.0f,	250.0f/255.0f,	240.0f/255.0f
#define OLDLACE					253.0f/255.0f,	245.0f/255.0f,	230.0f/255.0f
#define WHEAT					245.0f/255.0f,	222.0f/255.0f,	179.0f/255.0f
#define ORANGE					255.0f/255.0f,	165.0f/255.0f,	0.0f/255.0f
#define MOCCASIN				255.0f/255.0f,	228.0f/255.0f,	181.0f/255.0f
#define PAPAYAWHIP				255.0f/255.0f,	239.0f/255.0f,	213.0f/255.0f
#define BLANCHEDALMOND			255.0f/255.0f,	235.0f/255.0f,	205.0f/255.0f
#define NAVAJOWHITE				255.0f/255.0f,	222.0f/255.0f,	173.0f/255.0f
#define ANTIQUEWHITE			250.0f/255.0f,	235.0f/255.0f,	215.0f/255.0f
#define TAN						210.0f/255.0f,	180.0f/255.0f,	140.0f/255.0f
#define BURLYWOOD				222.0f/255.0f,	184.0f/255.0f,	135.0f/255.0f
#define DARKORANGE				255.0f/255.0f,	140.0f/255.0f,	0.0f/255.0f
#define BISQUE					255.0f/255.0f,	228.0f/255.0f,	196.0f/255.0f
#define LINEN					250.0f/255.0f,	240.0f/255.0f,	230.0f/255.0f
#define PERU					205.0f/255.0f,	133.0f/255.0f,	63.0f/255.0f
#define PEACHPUFF				255.0f/255.0f,	218.0f/255.0f,	185.0f/255.0f
#define SANDYBROWN				244.0f/255.0f,	164.0f/255.0f,	96.0f/255.0f
#define CHOCOLATE				210.0f/255.0f,	105.0f/255.0f,	30.0f/255.0f
#define SADDLEBROWN				139.0f/255.0f,	69.0f/255.0f,	19.0f/255.0f
#define SEASHELL				255.0f/255.0f,	245.0f/255.0f,	238.0f/255.0f
#define SIENNA					160.0f/255.0f,	82.0f/255.0f,	45.0f/255.0f
#define LIGHTSALMON				255.0f/255.0f,	160.0f/255.0f,	122.0f/255.0f
#define CORAL					255.0f/255.0f,	127.0f/255.0f,	80.0f/255.0f
#define ORANGERED				255.0f/255.0f,	69.0f/255.0f,	0.0f/255.0f
#define DARKSALMON				233.0f/255.0f,	150.0f/255.0f,	122.0f/255.0f
#define TOMATO					255.0f/255.0f,	99.0f/255.0f,	71.0f/255.0f
#define SALMON					250.0f/255.0f,	128.0f/255.0f,	114.0f/255.0f
#define MISTYROSE				255.0f/255.0f,	228.0f/255.0f,	225.0f/255.0f
#define LIGHTCORAL				240.0f/255.0f,	128.0f/255.0f,	128.0f/255.0f
#define SNOW					255.0f/255.0f,	250.0f/255.0f,	250.0f/255.0f
#define ROSYBROWN				188.0f/255.0f,	143.0f/255.0f,	143.0f/255.0f
#define INDIANRED				205.0f/255.0f,	92.0f/255.0f,	92.0f/255.0f
#define RED						255.0f/255.0f,	0.0f/255.0f,	0.0f/255.0f
#define BROWN					165.0f/255.0f,	42.0f/255.0f,	42.0f/255.0f
#define FIREBRICK				178.0f/255.0f,	34.0f/255.0f,	34.0f/255.0f
#define DARKRED					139.0f/255.0f,	0.0f/255.0f,	0.0f/255.0f
#define MAROON					128.0f/255.0f,	0.0f/255.0f,	0.0f/255.0f
#define WHITE					255.0f/255.0f,	255.0f/255.0f,	255.0f/255.0f
#define WHITESMOKE				245.0f/255.0f,	245.0f/255.0f,	245.0f/255.0f
#define GAINSBORO				220.0f/255.0f,	220.0f/255.0f,	220.0f/255.0f
#define LIGHTGREY				211.0f/255.0f,	211.0f/255.0f,	211.0f/255.0f
#define SILVER					192.0f/255.0f,	192.0f/255.0f,	192.0f/255.0f
#define DARKGRAY				169.0f/255.0f,	169.0f/255.0f,	169.0f/255.0f
#define GRAY					128.0f/255.0f,	128.0f/255.0f,	128.0f/255.0f
#define DIMGRAY					105.0f/255.0f,	105.0f/255.0f,	105.0f/255.0f
#define BLACK					0.0f/255.0f,	0.0f/255.0f,	0.0f/255.0f





#endif /* __util__h__ */



