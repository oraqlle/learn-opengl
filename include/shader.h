#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <string_view>

class Shader {
public:
    unsigned int ID;

    Shader(std::string_view vertex_path, std::string_view frag_path);

    ~Shader();

    void cleanup();

    // activate shader
    void use();

    // set uniforms in shaders
    template <typename T>
    void set_uniform(std::string const&, T const&) const;

    template <typename T>
    void set_uniform(std::string const&, T const, T const) const;

    template <typename T>
    void set_uniform(std::string const&, T const, T const, T const) const;

    template <typename T>
    void set_uniform(std::string const&, T const, T const, T const, T const) const;
};


#endif // SHADER_H

