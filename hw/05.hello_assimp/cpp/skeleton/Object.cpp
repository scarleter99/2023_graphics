#include "Object.h"

void Object::init_buffer_objects() 
{
    // TODO
    // VBO
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * pmesh_->mNumVertices, pmesh_->mVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * pmesh_->mNumVertices, pmesh_->mColors[0], GL_STATIC_DRAW);

    // IBO
    faces.resize(pmesh_->mNumFaces);

    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i)
    {
        const aiFace& face = pmesh_->mFaces[i];
        Face& currentFace = faces[i];

        glGenBuffers(1, &currentFace.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentFace.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * face.mNumIndices, face.mIndices, GL_STATIC_DRAW);
        
        currentFace.num_indices = face.mNumIndices;
    }
}

glm::mat4 Object::get_model_matrix() const
{
    glm::mat4 mat_model = glm::mat4(1.0f);
    
    // TODO
    mat_model = mat_model * glm::translate(glm::mat4(1.0f), vec_translate_);
    mat_model = mat_model * glm::mat4_cast(quat_rotate_);
    mat_model = mat_model * glm::scale(glm::mat4(1.0f), vec_scale_);

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    // TODO
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, sizeof(aiColor4D), (void*)0);

    // IBO를 이용해 물체 그리기
    for (const Face& face : faces)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glDrawElements(GL_TRIANGLES, face.num_indices, GL_UNSIGNED_INT, (void*)0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // 정점 attribute 배열 비활성화
    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);
}
    
void Object::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << pmesh_->mNumVertices << std::endl;
    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
    {
        aiVector3D vertex = pmesh_->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (pmesh_->mColors[0] != NULL)
        {
            aiColor4D color = pmesh_->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}