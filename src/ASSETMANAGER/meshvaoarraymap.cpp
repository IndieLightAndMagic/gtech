#include "meshvaoarraymap.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/


void UnbindVertexArray(){

    glBindVertexArray(0);

}

void BindVertexData(const GTech::Mesh& rMesh){
        
    //Get raw pointer   
    auto meshdataptr = reinterpret_cast<const GLvoid*>(rMesh.floatVector.data()) ;

    //Ok Create VBOs and EBOs
    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);

    //Source VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rMesh.floatVector.size(), meshdataptr, GL_STATIC_DRAW);

}

void UnbindVertexData(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BindVertexIndexData(const GTech::Mesh& rMesh, unsigned int triangleArrayIndex){

    //Source EBo
    unsigned int ebo;
    
    auto triangleheaderptr = rMesh.triangleArray[triangleArrayIndex];

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangleheaderptr->indexArray.size(), triangleheaderptr->indexArray.data(), GL_STATIC_DRAW);


}

void UnbindVertexIndexData(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SetVertexAttribPointers(const GTech::Mesh& rMesh, int triangleArrayIndex){

    auto meshsourcemap    = rMesh.meshSourceMap;
    auto meshdataptr      = reinterpret_cast<const GLvoid*>(rMesh.floatVector.data());
    auto& triangledataptr = rMesh.triangleArray[triangleArrayIndex];
    
    for (auto& trianglesemantic : triangledataptr->meshTrianglesInput){
        
        const auto& semantictype    = (unsigned int)trianglesemantic.semanticType;
        const auto& meshsourceptr   = meshsourcemap[trianglesemantic.source];
        auto* const offsetaddress   = &(reinterpret_cast<const float*>(meshdataptr))[meshsourceptr->index];
        const auto triangledatasize = (int)(meshsourceptr->pointsCount * 3 *sizeof(float));
        glVertexAttribPointer(semantictype, triangledatasize, GL_FLOAT, GL_FALSE, 0, offsetaddress);
    
    }

}

std::shared_ptr<unsigned int> GTech::MeshVaoArrayMap::LoadVaoArrayForMeshNode(std::string meshnodename, GTech::Scene& scene){

    //Get Mesh data and the number of vaos
    auto [pmesh, trianglearraysz] = GTech::MeshDataTuple(meshnodename, scene);
    if (pmesh == nullptr || trianglearraysz == 0) return nullptr;


    //Allocate memory. If no memory return nullptr.
    auto ptr = std::shared_ptr<unsigned int>(new unsigned int[trianglearraysz], std::default_delete<unsigned int[]>());
    if (!ptr) return nullptr;

    //OPENGL
    //Generate the vertexes array
    auto rawvaoptr = ptr.get();
    glGenVertexArrays(trianglearraysz, rawvaoptr);

    //Loop through triangle array
    for (int triangleArrayIndex = 0; triangleArrayIndex < trianglearraysz; ++triangleArrayIndex){
        
        glBindVertexArray(rawvaoptr[triangleArrayIndex]);
        
        BindVertexData(*pmesh);
        SetVertexAttribPointers(*pmesh, triangleArrayIndex);
        UnbindVertexData();

        BindVertexIndexData(*pmesh, triangleArrayIndex);
        UnbindVertexIndexData();

        UnbindVertexArray();
    }

    return ptr;

}
bool GTech::MeshVaoArrayMap::SetScenePtr(std::shared_ptr<GTech::Scene> pscene){
    
    if (pscene) return false;
    sp_context = pscene;
    return true;

}
GTech::MeshVaoArrayMap::MeshVaoArrayMap(std::shared_ptr<GTech::Scene> pscene){

    sp_context  = pscene;
    fresolution = LoadVaoArrayForMeshNode;

}