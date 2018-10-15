#include "gnome_fortress/renderer/Technique.h"

#include <exception>

namespace gnome_fortress {
namespace renderer {

Technique::Technique(GLuint program)
    : shader_program(program),
      uniforms(),
      attributes(),
      stride(0) {

}

Technique::UniformEntry::UniformEntry(const Uniform &uni, const GLfloat *fvalues)
    : uni(uni),
      fvalues(fvalues),
      ivalues(nullptr),
      uivalues(nullptr) {
    if (uni.getType() != GL_FLOAT) {
        throw std::exception("Invalid data type. Uniform is not of type GL_FLOAT.");
    }
}

Technique::UniformEntry::UniformEntry(const Uniform &uni, const GLint *ivalues)
    : uni(uni),
      fvalues(nullptr),
      ivalues(ivalues),
      uivalues(nullptr) {
    if (uni.getType() != GL_INT) {
        throw std::exception("Invalid data type. Uniform is not of type GL_INT.");
    }
}

Technique::UniformEntry::UniformEntry(const Uniform &uni, const GLuint *uivalues)
    : uni(uni),
      fvalues(nullptr),
      ivalues(nullptr),
      uivalues(uivalues) {
    if (uni.getType() != GL_UNSIGNED_INT) {
        throw std::exception("Invalid data type. Uniform is not of type GL_UNSIGNED_INT.");
    }
}

Technique::AttributeEntry::AttributeEntry(const VertexAttribute &attr, GLvoid *offset)
    : attr(attr),
    offset(offset) {
}

GLuint Technique::getShader() const {
    return shader_program;
}

void Technique::addUniform(const Uniform &uni, const GLfloat *fvalues) {
    uniforms.push_back(UniformEntry(uni, fvalues));
}

void Technique::addUniform(const Uniform &uni, const GLint *ivalues) {
    uniforms.push_back(UniformEntry(uni, ivalues));
}

void Technique::addUniform(const Uniform &uni, const GLuint *uivalues) {
    uniforms.push_back(UniformEntry(uni, uivalues));
}

void Technique::addVertexAttribute(const VertexAttribute &attr) {
    attributes.push_back(AttributeEntry(attr, reinterpret_cast<GLvoid *>(stride)));
    stride += attr.getTotalSize();
}

void Technique::activate() const {
    //shader
    glUseProgram(shader_program);

    // uniforms
    for (const UniformEntry &entry : uniforms) {
        if (entry.uni.getType() == GL_FLOAT) {
            // floats
            if (entry.uni.getRows() == 1) {
                if (entry.uni.getColumns() == 1) {
                    glUniform1fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniform2fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniform3fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniform4fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                }
            } else if (entry.uni.getRows() == 2) {
                if (entry.uni.getColumns() == 1) {
                    glUniform2fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniformMatrix2fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniformMatrix2x3fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniformMatrix2x4fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                }
            } else if (entry.uni.getRows() == 3) {
                if (entry.uni.getColumns() == 1) {
                    glUniform3fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniformMatrix3x2fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniformMatrix3fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniformMatrix3x4fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                }
            } else if (entry.uni.getRows() == 4) {
                if (entry.uni.getColumns() == 1) {
                    glUniform4fv(entry.uni.getLocation(), entry.uni.getCount(), entry.fvalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniformMatrix4x2fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniformMatrix4x3fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniformMatrix4fv(entry.uni.getLocation(), entry.uni.getCount(), false, entry.fvalues);
                }
            }
        } else if (entry.uni.getType() == GL_INT) {
            // integers
            if (entry.uni.getRows() == 1) {
                if (entry.uni.getColumns() == 1) {
                    glUniform1iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniform2iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniform3iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniform4iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
                }
            } else if (entry.uni.getRows() == 2) {
                glUniform2iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
            } else if (entry.uni.getRows() == 3) {
                glUniform3iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
            } else if (entry.uni.getRows() == 4) {
                glUniform4iv(entry.uni.getLocation(), entry.uni.getCount(), entry.ivalues);
            }
        } else if(entry.uni.getType() == GL_UNSIGNED_INT) {
            // unsigned integers
            if (entry.uni.getRows() == 1) {
                if (entry.uni.getColumns() == 1) {
                    glUniform1uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
                } else if (entry.uni.getColumns() == 2) {
                    glUniform2uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
                } else if (entry.uni.getColumns() == 3) {
                    glUniform3uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
                } else if (entry.uni.getColumns() == 4) {
                    glUniform4uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
                }
            } else if (entry.uni.getRows() == 2) {
                glUniform2uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
            } else if (entry.uni.getRows() == 3) {
                glUniform3uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
            } else if (entry.uni.getRows() == 4) {
                glUniform4uiv(entry.uni.getLocation(), entry.uni.getCount(), entry.uivalues);
            }
        }
    }

    // attributes
    for (const AttributeEntry &entry : attributes) {
        glEnableVertexAttribArray(entry.attr.getIndex());
        glVertexAttribPointer(
                entry.attr.getIndex(),
                entry.attr.getComponentCount(),
                entry.attr.getType(),
                entry.attr.isNormalized(),
                stride,
                entry.offset);
    }
}

void Technique::deactivate() const {
    // uniforms

    //attributes
    for (const AttributeEntry &entry : attributes) {
        glDisableVertexAttribArray(entry.attr.getIndex());
    }
}

}
}