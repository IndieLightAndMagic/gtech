

#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include "shdr.h"





Shader::Shader(ShaderSource * shaderSource, GLenum shaderType){

	m_state=SHADER_STATE_INVALID;
	try {

		m_shader=glCreateShader(shaderType);
		if (!m_shader){
			throw 1;
		} 
		m_state=Shader::SHADER_STATE_CREATED;
	}
	catch (int error){

		std::cout << "ERROR::SHADER::SHADER_NOT_SUCCESFULLY_CREATED" << std::endl;
		return;
	
	}
	if ( shaderSource != 0x00 && m_state == Shader::SHADER_STATE_CREATED) {
		try {

			const GLchar * pShaderCode = shaderSource[0]();
			glShaderSource(m_shader, 1, &pShaderCode, nullptr);
			glCompileShader(m_shader);
			GLint success; 
			glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
			if (!success)
	    	{	
	    		throw 1;
			}
			m_state = SHADER_STATE_COMPILED;
		}
		catch (int error){

	    		GLchar infoLog[1024];
				glGetShaderInfoLog(m_shader, 1024, NULL, infoLog);
				std::cout<< "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl << shaderSource[0]() << std::endl;
				glDeleteShader(m_shader);
				return;
		
		}	
	}

	
	

}

const GLuint Shader::operator()(){
	return m_shader;
}

Shader::ShaderState Shader::state(){ return m_state; }


#ifdef TEST_BENCH
#include <TEST/tbench.h>

unsigned int shaderTest(GLenum shaderType){

	
	Shader s(nullptr,shaderType);
	if (s.state()==Shader::SHADER_STATE_CREATED){

		std::cout << s() << std::endl;
		return UINT_TEST_OK;

	}
	return UINT_TEST_FAIL;

}

int main (int argc, char ** argv){

	bool _0k = true;
	TEST_INT(_0k, shaderTest(GL_VERTEX_SHADER));
	TEST_INT(_0k, shaderTest(GL_FRAGMENT_SHADER));
	TEST_INT(_0k, shaderTest(GL_GEOMETRY_SHADER));
	
	TEST_RESULT(_0k);

}
#endif

