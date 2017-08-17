#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
//Fragment Shader Input TexCoord.
out vec2 TexCoord;


//Object Model-------
struct ObjModel{ 
	mat4 tx;
	mat4 rt;
};
mat4 ObjModel_txrt(ObjModel objModel) { return objModel.tx * objModel.rt; }
mat4 ObjModel_rttx(ObjModel objModel) { return objModel.rt * objModel.tx; }

uniform ObjModel objModel;
mat4 objModelMatrix;
//-------------------


//Camera Model-------
struct CamModel{
	mat4 pr;
	mat4 vw;
};
mat4 CamModel_prvw(CamModel camModel) { return camModel.pr * camModel.vw; }

uniform CamModel camModel;
mat4 camModelMatrix;
//-------------------




void main()
{
	//Calculate Object Model.
	objModelMatrix = ObjModel_txrt(objModel);
	
	//Calculate Camera Model.
	camModelMatrix = CamModel_prvw(camModel);

	//Vertex Shader final pi position.
	gl_Position = camModelMatrix * objModelMatrix * vec4(aPos, 1.0f);
	
	//Texture Coordinate (0,1)-(0,1)
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);


}