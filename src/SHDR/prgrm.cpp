#include "shdr.h"

GTech::Program::Program(){
	m_program = glCreateProgram();
	m_state = m_program ? PROGRAM_STATE_VOID : PROGRAM_STATE_INVALID;
}
void GTech::Program::pushShader(Shader*pS){
	if (m_state == PROGRAM_STATE_INVALID || pS->state() != Shader::SHADER_STATE_COMPILED) invalidateProgram();
	else {
		glAttachShader(m_program,pS[0]());
		m_state = (m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) ? m_state : PROGRAM_STATE_SHADERS_ATTACHED;  
	}
}
void GTech::Program::pushShader(ShaderSource* pxSs, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID || pxSs->state() != ShaderSource::SOURCE_STATE_VALID) invalidateProgram();
	else {
		Shader xS(pxSs,eShaderType);
		pushShader(&xS);
	}
}

void GTech::Program::pushShader(const char * pFilename, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID) invalidateProgram();
	else { 
		ShaderSource xSs(pFilename);
		pushShader(&xSs,eShaderType);
	}
}
void GTech::Program::use(){
	if (m_state == PROGRAM_STATE_SHADERS_ATTACHED|| m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) glUseProgram(m_program);
}

void GTech::Program::invalidateProgram(){
	/* TODO: Create a way to admon the shaders more effectively */
	if (m_state != PROGRAM_STATE_INVALID){
		m_state = PROGRAM_STATE_INVALID;
		glDeleteProgram(m_program);		
	}

}
bool GTech::Program::isLinked(){
	return (m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) ? GL_TRUE : GL_FALSE;
}
void GTech::Program::link(){
	int iSuccess;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &iSuccess);
	m_state = iSuccess ? PROGRAM_STATE_LINKED_NOT_USED : PROGRAM_STATE_INVALID;

}
const GLuint GTech::Program::operator()(){return m_program;}

GTech::Program::ProgramState GTech::Program::state(){
	return m_state;
}



void GTech::Program::setInt(const GLchar* pucUniformName, GLint value){
	glUniform1i(glGetUniformLocation(m_program,pucUniformName), value);
}
void GTech::Program::setFloat(const GLchar* pucUniformName, GLfloat value){
	glUniform1f(glGetUniformLocation(m_program,pucUniformName), value);
}
void GTech::Program::setVec2(const GLchar* pucUniformName, const glm::vec2 &value){
	glUniform2fv(glGetUniformLocation(m_program,pucUniformName), 1, &value[0]);
}
void GTech::Program::setVec2(const GLchar* pucUniformName, float x, float y){
	glUniform2f(glGetUniformLocation(m_program,pucUniformName),x,y);
}
void GTech::Program::setVec3(const GLchar* pucUniformName, const glm::vec3 &value){
	glUniform3fv(glGetUniformLocation(m_program,pucUniformName), 1, &value[0]);
}
void GTech::Program::setVec3(const GLchar* pucUniformName, float x, float y, float z){
	glUniform3f(glGetUniformLocation(m_program,pucUniformName), x, y, z);
}
void GTech::Program::setVec4(const GLchar* pucUniformName, const glm::vec4 &value){
	glUniform4fv(glGetUniformLocation(m_program,pucUniformName), 1, &value[0]);
}
void GTech::Program::setVec4(const GLchar* pucUniformName, float x, float y, float z, float w){
	glUniform4f(glGetUniformLocation(m_program,pucUniformName), x, y, z, w);
}
void GTech::Program::setMat2(const GLchar* pucUniformName, const glm::mat2 &value){
	glUniformMatrix2fv(glGetUniformLocation(m_program,pucUniformName), 1, GL_FALSE, &value[0][0]);
}
void GTech::Program::setMat3(const GLchar* pucUniformName, const glm::mat3 &value){
	glUniformMatrix3fv(glGetUniformLocation(m_program,pucUniformName), 1, GL_FALSE, &value[0][0]);
}
void GTech::Program::setMat4(const GLchar* pucUniformName, const glm::mat4 &value){
	glUniformMatrix4fv(glGetUniformLocation(m_program,pucUniformName), 1, GL_FALSE, &value[0][0]);
}

#ifdef PERFORM_UNIT_TEST

	




#endif

