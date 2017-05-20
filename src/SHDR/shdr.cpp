

#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include "shdr.h"





Shader::Shader(ShaderSource * shaderSource, GLenum shaderType){

	m_state=SHADER_STATE_INVALID;
	m_shader=glCreateShader(shaderType);
	if (!m_shader){
		return;
	} 

	const GLchar * pShaderCode = shaderSource[0]();
	glShaderSource(m_shader, 1, &pShaderCode, nullptr);
	glCompileShader(m_shader);
	

	GLint success; 
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (!success)
    {	
    	GLchar infoLog[1024];
		glGetShaderInfoLog(m_shader, 1024, NULL, infoLog);
		std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl << shaderSource[0]() << std::endl;
		glDeleteShader(m_shader);
		return;
	}
	m_state = SHADER_STATE_COMPILED;
}

const GLuint Shader::operator()(){
	return m_shader;
}


#ifdef PERFORM_UNIT_TEST

	




#endif