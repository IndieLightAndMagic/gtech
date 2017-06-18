#version 330 core
out vec4 xFragColor;
  
in vec3 ourColor;
in vec2 TexCoord;


//uniform: Storage qualifier, they @onnect our texture outside the GPU as a constant thing that wont change (they're implicitly constant). However uniforms are permitted to be initialized and changed by the user afterwards. 
//sampler2d its is glsl enumeration for GL_TEXTURE_2D. Check https://www.khronos.org/opengl/wiki/Data_Type_(GLSL) for the matter. 
uniform sampler2D ourTexture;

void main()
{
	//Bind the coordinates incoming 
    xFragColor = texture(ourTexture, TexCoord)*vec4(ourColor,1.0f);
}