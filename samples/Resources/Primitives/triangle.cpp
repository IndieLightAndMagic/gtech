#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <SHDR/shdr.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const unsigned int elements{24};
const unsigned int elemenstperrow{8};

glm::mat4 locationMatrix;
glm::mat4 rotationMatrix;
float cube_vertices[] = 
{

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

};



void getCubeData(unsigned int *pCubeVBO, unsigned int *pCubeVAO)
{
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    glGenVertexArrays(1, pCubeVAO);
    glGenBuffers(1, pCubeVBO);

    cubeVAO = *pCubeVAO;
    cubeVBO = *pCubeVBO;

    auto szcube = sizeof(cube_vertices);
    
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, szcube, cube_vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
 	// texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);


    for (unsigned int index = 0; index < elements; ++index)
    {
    	if (index%8)
    	{
    		std::cout << cube_vertices[index] << " ";
    	}
    	else
    	{
    		std::cout << "\n\n[ " << index / elemenstperrow << " ] " << cube_vertices[index] << " ";
    	}
    }
    std::cout << "\n";


       
}
void drawCube(Program &shaderProgram, unsigned int vao)
{
    
    shaderProgram.setMat4("objModel.tx", locationMatrix);
    shaderProgram.setMat4("objModel.rt", rotationMatrix);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, elements/elemenstperrow);
}
void setCubeLocation(glm::vec3 &locationVector)
{
    locationMatrix = glm::mat4(1.0f);
    locationMatrix = glm::translate(locationMatrix, locationVector);

}
void setCubeRotation(glm::vec3 &rotationalAxis, float &radians)
{
    rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, float(radians), rotationalAxis);  
}
