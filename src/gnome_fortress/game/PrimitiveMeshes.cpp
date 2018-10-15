/*0.0
 * Copyright (c) 2018 Nathan Marshall <Nathagnome_fortress@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 */


#include "gnome_fortress/game/PrimitiveMeshes.h"

namespace gnome_fortress {
namespace game {

using namespace gnome_fortress::model;

Mesh *CreateCube(void) {
    // Each face of the cube is defined by four vertices (with the same normal) and two triangles

    // Vertices that form the cube
    // 9 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3)
    GLfloat vertices[] = {
        // First cube face
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f, 0.0f,
        // Second cube face
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f, 1.0f,
        // Third cube face
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f, 0.0f,
        // Fourth cube face
        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f, 0.0f,
        // Fifth cube face
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f, 0.0f,
        // Sixth cube face
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f, 0.0f,
    };

    GLuint elements[] = {
        // First cube face
        0, 1, 2,
        0, 2, 3,
        // Second cube face
        4, 5, 6,
        4, 6, 7,
        // Third cube face
        8, 9, 10,
        8, 10, 11,
        // Fourth cube face
        12, 13, 14,
        12, 14, 15,
        // Fifth cube face
        16, 17, 18,
        16, 18, 19,
        // Sixth cube face
        20, 21, 22,
        20, 22, 23
    };

    // Create mesh 
    return new Mesh(vertices, sizeof(vertices), sizeof(GLfloat) * 9, elements, sizeof(elements), GL_TRIANGLES);
}


Mesh *CreateCylinder(void) {
	// The top and bottom faces of the cylinder are each defined by n vertices and (n - 2) triangles, where n is circle_resolution
	// The side (curved) face is defined by 2n vertices and 2n triangles

	// the circle will have this many vertices/edges
	const int circle_resolution = 24;

	const int num_vertices = circle_resolution * 4;
	const int num_triangles = (circle_resolution - 2) * 2 + circle_resolution * 2;

	// 9 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3)
	const int attr_count = 9;

	// Vertices that form the cylinder
	GLfloat vertices[num_vertices * attr_count];
	GLuint elements[num_triangles * 3];

	int attr_index = 0;
	int vertex_index = 0;
	int bottom_face_vertex_offset = vertex_index;

	// vertices for bottom face
	for (int i = 0; i < circle_resolution; i++) {
        float angle = 2 * glm::pi<float>() / circle_resolution * i;

        float vertex_x = cos(angle) * 0.5f;
        float vertex_z = sin(angle) * 0.5f;

        // bottom face vertex position
        vertices[attr_index + 0] = vertex_x;
        vertices[attr_index + 1] = -0.5f;
        vertices[attr_index + 2] = vertex_z;
        // bottom face vertex normal
        vertices[attr_index + 3] = 0.0f;
        vertices[attr_index + 4] = -1.0f;
        vertices[attr_index + 5] = 0.0f;
        // bottom face vertex color
        vertices[attr_index + 6] = 0.5f + 0.5f * sin(angle + glm::pi<float>());
        vertices[attr_index + 7] = 0.5f + 0.5f * cos(angle + glm::pi<float>());
        vertices[attr_index + 8] = 1.0f;

        attr_index += attr_count;
        vertex_index++;
	}

	int side_face_lower_vertex_offset = vertex_index;

	// lower vertices for side face
	for (int i = 0; i < circle_resolution; i++) {
        float angle = 2 * glm::pi<float>() / circle_resolution * i;

        float vertex_x = cos(angle) * 0.5f;
        float vertex_z = sin(angle) * 0.5f;

        // vertex normal for side face vertices
        glm::vec3 vertex_norm = glm::normalize(glm::vec3(vertex_x, 0.0f, vertex_z));

        // side face lower vertex position
        vertices[attr_index + 0] = vertex_x;
        vertices[attr_index + 1] = -0.5f;
        vertices[attr_index + 2] = vertex_z;
        // side face lower vertex normal
        vertices[attr_index + 3] = vertex_norm.x;
        vertices[attr_index + 4] = vertex_norm.y;
        vertices[attr_index + 5] = vertex_norm.z;
        // side face lower vertex color
        vertices[attr_index + 6] = 0.5f + 0.5f * sin(static_cast<float>(i) / circle_resolution * 2 * glm::pi<float>());
        vertices[attr_index + 7] = 1.0f;
        vertices[attr_index + 8] = 0.5f + 0.5f * cos(static_cast<float>(i) / circle_resolution * 2 * glm::pi<float>());

        attr_index += attr_count;
        vertex_index++;
	}

	int side_face_upper_vertex_offset = vertex_index;

	// upper vertices for side face
	for (int i = 0; i < circle_resolution; i++) {
        float angle = 2 * glm::pi<float>() / circle_resolution * i;

        float vertex_x = cos(angle) * 0.5f;
        float vertex_z = sin(angle) * 0.5f;

        // vertex normal for side face vertices
        glm::vec3 vertex_norm = glm::normalize(glm::vec3(vertex_x, 0.0f, vertex_z));

        // side face upper vertex position
        vertices[attr_index + 0] = vertex_x;
        vertices[attr_index + 1] = 0.5f;
        vertices[attr_index + 2] = vertex_z;
        // side face upper vertex normal
        vertices[attr_index + 3] = vertex_norm.x;
        vertices[attr_index + 4] = vertex_norm.y;
        vertices[attr_index + 5] = vertex_norm.z;
        // side face upper vertex color
        vertices[attr_index + 6] = 0.5f + 0.5f * cos(static_cast<float>(i) / circle_resolution * 2 * glm::pi<float>());
        vertices[attr_index + 7] = 0.5f + 0.5f * sin(static_cast<float>(i) / circle_resolution * 2 * glm::pi<float>());
        vertices[attr_index + 8] = 1.0f;

        attr_index += attr_count;
        vertex_index++;
	}

	int top_face_vertex_offset = vertex_index;

	// vertices for top face
	for (int i = 0; i < circle_resolution; i++) {
        float angle = 2 * glm::pi<float>() / circle_resolution * i;

        float vertex_x = cos(angle) * 0.5f;
        float vertex_z = sin(angle) * 0.5f;

        // top face vertex position
        vertices[attr_index + 0] = vertex_x;
        vertices[attr_index + 1] = 0.5f;
        vertices[attr_index + 2] = vertex_z;
        // top face vertex normal
        vertices[attr_index + 3] = 0.0f;
        vertices[attr_index + 4] = 1.0f;
        vertices[attr_index + 5] = 0.0f;
        // top face vertex color
        vertices[attr_index + 6] = 0.5f + 0.5f * sin(angle + glm::pi<float>());
        vertices[attr_index + 7] = 1.0f;
        vertices[attr_index + 8] = 0.5f + 0.5f * cos(angle + glm::pi<float>());

        attr_index += attr_count;
        vertex_index++;
	}

	int element_attr_offset = 0;

	// populate elements array for bottom face
	for (int i = 0; i < circle_resolution - 2; i++) {
        elements[element_attr_offset + 0] = bottom_face_vertex_offset;
        elements[element_attr_offset + 1] = bottom_face_vertex_offset + i + 1;
        elements[element_attr_offset + 2] = bottom_face_vertex_offset + i + 2;

        element_attr_offset += 3;
	}

	// populate elements array for side face
	for (int i = 0; i < circle_resolution; i++) {
        elements[element_attr_offset + 0] = side_face_lower_vertex_offset + i;
        elements[element_attr_offset + 1] = side_face_upper_vertex_offset + i;
        elements[element_attr_offset + 2] = side_face_lower_vertex_offset + (i + 1) % circle_resolution;

        element_attr_offset += 3;

        elements[element_attr_offset + 0] = side_face_upper_vertex_offset + i;
        elements[element_attr_offset + 1] = side_face_upper_vertex_offset + (i + 1) % circle_resolution;
        elements[element_attr_offset + 2] = side_face_lower_vertex_offset + (i + 1) % circle_resolution;

        element_attr_offset += 3;
	}

	// populate elements array for top face
	for (int i = 0; i < circle_resolution - 2; i++) {
        elements[element_attr_offset + 0] = top_face_vertex_offset;
        elements[element_attr_offset + 1] = top_face_vertex_offset + i + 2;
        elements[element_attr_offset + 2] = top_face_vertex_offset + i + 1;

        element_attr_offset += 3;
	}

	return new Mesh(vertices, sizeof(vertices), sizeof(GLfloat) * attr_count, elements, sizeof(elements), GL_TRIANGLES);
}

}
}