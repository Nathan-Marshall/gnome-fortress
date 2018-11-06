#include "gnome_fortress/model/OBJParser.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "resources_config.h"

namespace gnome_fortress {
namespace model {

void ParseOBJFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Unable to open \"" << filename << "\"!" << std::endl;
        return;
    } else {
        std::cout << "Parsing OBJ file, \"" << filename << "\":" << std::endl;
    }

    OBJParserState state;

    std::string line;
    while (std::getline(file, line)) {
        std::string command = line.substr(0, line.find(" "));
        std::string args = line.substr(line.find(" ") + 1);

        if (command == "o") {
            CreateObject(state, args);
        } else if (command == "g") {
            CreateObject(state, args);
        } else if (command == "v") {
            CreateVertex(state, args);
        } else if (command == "vt") {
            VertexTexturePosition(state, args);
        } else if (command == "vn") {
            VertexNormal(state, args);
        } else if (command == "f") {
            CreateFace(state, args);
        } else if (command == "mtllib") {
            CreateMaterial(state, args);
        } else if (command == "usemtl") {
            UseMaterial(state, args);
        } else if (command == "#") {
            // this is a commment, do nothing
        } else {
            std::cout << "Ignoring line \"" << line << "\"." << std::endl;
        }
    }

    std::cout << "Finished parsing \"" << filename << "\"." << std::endl;
    file.close();
}

void CreateObject(OBJParserState &state, const std::string &args) {

}

void CreateVertex(OBJParserState &state, const std::string &args) {
    
}

void VertexTexturePosition(OBJParserState &state, const std::string &args) {
    
}

void VertexNormal(OBJParserState &state, const std::string &args) {
    
}

void CreateFace(OBJParserState &state, const std::string &args) {
    
}

void CreateMaterial(OBJParserState &state, const std::string &args) {

}

void UseMaterial(OBJParserState &state, const std::string &args) {

}















Mesh LoadMesh(const std::string &partial_filename){
    std::string filename = std::string(RESOURCES_DIRECTORY) + partial_filename;

    // First load model into memory. If that goes well, we transfer the
    // mesh to an OpenGL buffer
    TriMesh mesh;

    // Parse file
    // Open file
    std::ifstream f;
    f.open(filename);
    if (f.fail()){
        throw(std::ios_base::failure(std::string("Error opening file ")+std::string(filename)));
    }

    // Parse lines
    std::string line;
    std::string ignore(" \t\r\n");
    std::string part_separator(" \t");
    std::string face_separator("/");
    bool added_normal = false;
    while (std::getline(f, line)){
        // Clean extremities of the string
        string_trim(line, ignore);
        // Ignore comments
        if ((line.size() <= 0) ||
            (line[0] == '#')){
            continue;
        }
        // Parse string
        std::vector<std::string> part = string_split(line, part_separator);
        // Check commands
        if (!part[0].compare(std::string("v"))){
            if (part.size() >= 4){
                glm::vec3 position(str_to_num<float>(part[1].c_str()), str_to_num<float>(part[2].c_str()), str_to_num<float>(part[3].c_str()));
                mesh.position.push_back(position);
            } else {
                throw(std::ios_base::failure(std::string("Error: v command should have exactly 3 parameters")));
            }
        } else if (!part[0].compare(std::string("vn"))){
            if (part.size() >= 4){
                glm::vec3 normal(str_to_num<float>(part[1].c_str()), str_to_num<float>(part[2].c_str()), str_to_num<float>(part[3].c_str()));
                mesh.normal.push_back(normal);
                added_normal = true;
            } else {
                throw(std::ios_base::failure(std::string("Error: vn command should have exactly 3 parameters")));
            }
        } else if (!part[0].compare(std::string("vt"))){
            if (part.size() >= 3){
                glm::vec2 tex_coord(str_to_num<float>(part[1].c_str()), str_to_num<float>(part[2].c_str()));
                mesh.tex_coord.push_back(tex_coord);
            } else {
                throw(std::ios_base::failure(std::string("Error: vt command should have exactly 2 parameters")));
            }
        } else if (!part[0].compare(std::string("f"))){
            if (part.size() >= 4){
                if (part.size() > 5){
                    throw(std::ios_base::failure(std::string("Error: f commands with more than 4 vertices not supported")));
                } else if (part.size() == 5){
                    // Break a quad into two triangles
                    Quad quad;
                    for (int i = 0; i < 4; i++){
                        std::vector<std::string> fd = string_split_once(part[i+1], face_separator);
                        if (fd.size() == 1){
                            quad.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            quad.t[i] = -1;
                            quad.n[i] = -1;
                        } else if (fd.size() == 2){
                            quad.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            quad.t[i] = str_to_num<float>(fd[1].c_str())-1;
                            quad.n[i] = -1;
                        } else if (fd.size() == 3){
                            quad.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            if (std::string("").compare(fd[1]) != 0){
                                quad.t[i] = str_to_num<float>(fd[1].c_str())-1;
                            } else {
                                quad.t[i] = -1;
                            }
                            quad.n[i] = str_to_num<float>(fd[2].c_str())-1;
                        } else {
                            throw(std::ios_base::failure(std::string("Error: f parameter should have 1 or 3 parameters separated by '/'")));
                        }
                    }
                    Face face1, face2;
                    face1.i[0] = quad.i[0]; face1.i[1] = quad.i[1]; face1.i[2] = quad.i[2];
                    face1.n[0] = quad.n[0]; face1.n[1] = quad.n[1]; face1.n[2] = quad.n[2];
                    face1.t[0] = quad.t[0]; face1.t[1] = quad.t[1]; face1.t[2] = quad.t[2];
                    face2.i[0] = quad.i[0]; face2.i[1] = quad.i[2]; face2.i[2] = quad.i[3];
                    face2.n[0] = quad.n[0]; face2.n[1] = quad.n[2]; face2.n[2] = quad.n[3];
                    face2.t[0] = quad.t[0]; face2.t[1] = quad.t[2]; face2.t[2] = quad.t[3];
                    mesh.face.push_back(face1);
                    mesh.face.push_back(face2);
                } else if (part.size() == 4){
                    Face face;
                    for (int i = 0; i < 3; i++){
                        std::vector<std::string> fd = string_split_once(part[i+1], face_separator);
                        if (fd.size() == 1){
                            face.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            face.t[i] = -1;
                            face.n[i] = -1;
                        } else if (fd.size() == 2){
                            face.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            face.t[i] = str_to_num<float>(fd[1].c_str())-1;
                            face.n[i] = -1;
                        } else if (fd.size() == 3){
                            face.i[i] = str_to_num<float>(fd[0].c_str())-1;
                            if (std::string("").compare(fd[1]) != 0){
                                face.t[i] = str_to_num<float>(fd[1].c_str())-1;
                            } else {
                                face.t[i] = -1;
                            }
                            face.n[i] = str_to_num<float>(fd[2].c_str())-1;
                        } else {
                            throw(std::ios_base::failure(std::string("Error: f parameter should have 1, 2, or 3 parameters separated by '/'")));
                        }
                    }
                    mesh.face.push_back(face);
                }
            } else {
                throw(std::ios_base::failure(std::string("Error: f command should have 3 or 4 parameters")));
            }
        }
        // Ignore other commands
    }

    // Close file
    f.close();

    // Check if vertex references are correct
    for (unsigned int i = 0; i < mesh.face.size(); i++){
        for (int j = 0; j < 3; j++){
            if (mesh.face[i].i[j] >= mesh.position.size()){
                throw(std::ios_base::failure(std::string("Error: index for triangle ")+num_to_str<int>(mesh.face[i].i[j])+std::string(" is out of bounds")));
            }
        }
    }

    // Compute degree of each vertex
    std::vector<int> degree(mesh.position.size(), 0);
    for (unsigned int i = 0; i < mesh.face.size(); i++){
        for (int j = 0; j < 3; j++){
            degree[mesh.face[i].i[j]]++;
        }
    }

    // Compute vertex normals if no normals were ever added
    if (!added_normal){
        mesh.normal = std::vector<glm::vec3>(mesh.position.size(), glm::vec3(0.0, 0.0, 0.0));
        for (unsigned int i = 0; i < mesh.face.size(); i++){
            // Compute face normal
            glm::vec3 vec1, vec2;
            vec1 = mesh.position[mesh.face[i].i[0]] -
                        mesh.position[mesh.face[i].i[1]];
            vec2 = mesh.position[mesh.face[i].i[0]] -
                        mesh.position[mesh.face[i].i[2]];
            glm::vec3 norm = glm::cross(vec1, vec2);
            norm = glm::normalize(norm);
            // Add face normal to vertices
            mesh.normal[mesh.face[i].i[0]] += norm;
            mesh.normal[mesh.face[i].i[1]] += norm;
            mesh.normal[mesh.face[i].i[2]] += norm;
        }
        for (unsigned int i = 0; i < mesh.normal.size(); i++){
            if (degree[i] > 0){
                mesh.normal[i] /= degree[i];
            }
        }
    }

    // Debug
    //print_mesh(mesh);

    // If we got to this point, the file was parsed successfully and the
    // mesh is in memory
    // Now, transfer the mesh to OpenGL buffers
    // Create three new vertices for each face, in case vertex
    // normals/texture coordinates are not consistent over the mesh

    // Number of attributes for vertices and faces
    const int vertex_att = 11;
    const int face_att = 3;

    // Create OpenGL buffers and copy data
    GLuint vbo, ebo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.face.size() * 3 * vertex_att * sizeof(GLuint), 0, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.face.size() * face_att * sizeof(GLuint), 0, GL_STATIC_DRAW);

    unsigned int vertex_index = 0;
    for (unsigned int i = 0; i < mesh.face.size(); i++){
        // Add three vertices and their attributes
        GLfloat att[3 * vertex_att] = { 0 };
        for (int j = 0; j < 3; j++){
            // Position
            att[j*vertex_att + 0] = mesh.position[mesh.face[i].i[j]][0];
            att[j*vertex_att + 1] = mesh.position[mesh.face[i].i[j]][1];
            att[j*vertex_att + 2] = mesh.position[mesh.face[i].i[j]][2];
            // Normal
            if (!added_normal){
                att[j*vertex_att + 3] = mesh.normal[mesh.face[i].i[j]][0];
                att[j*vertex_att + 4] = mesh.normal[mesh.face[i].i[j]][1];
                att[j*vertex_att + 5] = mesh.normal[mesh.face[i].i[j]][2];
            } else {
                if (mesh.face[i].n[j] >= 0){
                    att[j*vertex_att + 3] = mesh.normal[mesh.face[i].n[j]][0];
                    att[j*vertex_att + 4] = mesh.normal[mesh.face[i].n[j]][1];
                    att[j*vertex_att + 5] = mesh.normal[mesh.face[i].n[j]][2];
                }
            }
            // No color in (6, 7, 8)
            // Texture coordinates
            if (mesh.face[i].t[j] >= 0){
                att[j*vertex_att + 9] = mesh.tex_coord[mesh.face[i].t[j]][0];
                att[j*vertex_att + 10] = mesh.tex_coord[mesh.face[i].t[j]][1];
            }
        }

        // Copy attributes to buffer
        glBufferSubData(GL_ARRAY_BUFFER, i * 3 * vertex_att * sizeof(GLfloat), 3 * vertex_att * sizeof(GLfloat), att);

        // Add triangle
        GLuint findex[face_att] = { 0 };
        findex[0] = vertex_index;
        findex[1] = vertex_index + 1;
        findex[2] = vertex_index + 2;
        vertex_index += 3;

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * face_att * sizeof(GLuint), face_att * sizeof(GLuint), findex);
    }

    // Create resource
    return Mesh(vbo, ebo, mesh.position.size(), mesh.face.size() * face_att, GL_TRIANGLES);
}


void string_trim(std::string str, std::string to_trim){

    // Trim any character in to_trim from the beginning of the string str
    while ((str.size() > 0) && 
           (to_trim.find(str[0]) != std::string::npos)){
        str.erase(0);
    }

    // Trim any character in to_trim from the end of the string str
    while ((str.size() > 0) && 
           (to_trim.find(str[str.size()-1]) != std::string::npos)){
        str.erase(str.size()-1);
    }
}


std::vector<std::string> string_split(std::string str, std::string separator){

    // Initialize output
    std::vector<std::string> output;
    output.push_back(std::string(""));
    int string_index = 0;

    // Analyze string
    unsigned int i = 0;
    while (i < str.size()){
        // Check if character i is a separator
        if (separator.find(str[i]) != std::string::npos){
            // Split string
            string_index++;
            output.push_back(std::string(""));
            // Skip separators
            while ((i < str.size()) && (separator.find(str[i]) != std::string::npos)){
                i++;
            }
        } else {
            // Otherwise, copy string
            output[string_index] += str[i];
            i++;
        }
    }

    return output;
}


std::vector<std::string> string_split_once(std::string str, std::string separator){

    // Initialize output
    std::vector<std::string> output;
    output.push_back(std::string(""));
    int string_index = 0;

    // Analyze string
    unsigned int i = 0;
    while (i < str.size()){
        // Check if character i is a separator
        if (separator.find(str[i]) != std::string::npos){
            // Split string
            string_index++;
            output.push_back(std::string(""));
            // Skip single separator
            i++;
        } else {
            // Otherwise, copy string
            output[string_index] += str[i];
            i++;
        }
    }

    return output;
}


template <typename T> std::string num_to_str(T num){

    std::ostringstream ss;
    ss << num;
    return ss.str();
}


template <typename T> T str_to_num(const std::string &str){

    std::istringstream ss(str);
    T result;
    ss >> result;
    if (ss.fail()){
        throw(std::ios_base::failure(std::string("Invalid number: ")+str));
    }
    return result;
}

}
}