#include <shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

Shader::Shader(std::string_view vertex_path, std::string_view fragment_path) {
    auto const ex_bits = std::ifstream::failbit | std::ifstream::badbit;
    auto const vert_path = fs::path(vertex_path);
    auto const frag_path = fs::path(fragment_path);

    auto vert_file = std::ifstream(vert_path);
    auto frag_file = std::ifstream(frag_path);

    auto vertex_shader = std::string{};
    auto fragment_shader = std::string{};

    try {
        vert_file.exceptions(ex_bits);
        frag_file.exceptions(ex_bits);

        auto vert_stream = std::stringstream{};
        auto frag_stream = std::stringstream{};

        vert_stream << vert_file.rdbuf();
        frag_stream << frag_file.rdbuf();

        vert_file.close();
        frag_file.close();

        vertex_shader = vert_stream.str();
        fragment_shader = frag_stream.str();
    } catch (std::ifstream::failure const& ex) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char *vert_shader_cstr = vertex_shader.c_str();
    const char *frag_shader_cstr = fragment_shader.c_str();
    char info_log[512] = {0};
    int success = 0;

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vert_shader_cstr, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << info_log
                  << "\n";
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &frag_shader_cstr, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << info_log
                  << "\n";
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << info_log
                  << "\n";
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() {
    glUseProgram(ID);
}

template <>
void Shader::set_uniform<bool>(std::string const& name, bool const& value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

template <>
void Shader::set_uniform<int>(std::string const& name, int const& value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

template <>
void Shader::set_uniform<float>(std::string const& name, float const& value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

template <>
void Shader::set_uniform<glm::vec2>(
    std::string const& name,
    glm::vec2 const& vec
) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

template <>
void Shader::set_uniform<float>(
    std::string const& name,
    float const x,
    float const y
) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

template <>
void Shader::set_uniform<glm::vec3>(
    std::string const& name,
    glm::vec3 const& vec
) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

template <>
void Shader::set_uniform<float>(
    std::string const& name,
    float const x,
    float const y,
    float const z
) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

template <>
void Shader::set_uniform<glm::vec4>(
    std::string const& name,
    glm::vec4 const& vec)
const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

template <>
void Shader::set_uniform<float>(
    std::string const& name,
    float const x,
    float const y,
    float const z,
    float const w
) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

template <>
void Shader::set_uniform<glm::mat2>(
    std::string const& name,
    glm::mat2 const& matrix
) const {
    glUniformMatrix2fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(matrix)
    );
}

template <>
void Shader::set_uniform<glm::mat3>(std::string const& name, glm::mat3 const& matrix) const {
    glUniformMatrix3fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(matrix)
    );
}

template <>
void Shader::set_uniform<glm::mat4>(std::string const& name, glm::mat4 const& matrix) const {
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(matrix)
    );
}

