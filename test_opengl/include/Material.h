// Material.h
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Material
{
public:
  Material (const char *vertexSource, const char *fragmentSource)
  {
    // 创建并编译着色器
    shader
        = CreateShaderProgram (vertexSource, fragmentSource); // 创建着色器程序
  }

  void
  Use ()
  {
    glUseProgram (shader);
  }

  void
  SetMatrix (const char *name, const glm::mat4 &matrix)
  {
    glUniformMatrix4fv (glGetUniformLocation (shader, name), 1, GL_FALSE,
                        &matrix[0][0]);
  }

  void
  SetVec3 (const std::string &name, const glm::vec3 &value)
  {
    glUniform3fv (glGetUniformLocation (shader, name.c_str ()), 1, &value[0]);
  }

private:
  unsigned int shader;

  unsigned int
  CreateShaderProgram (const char *vertexSource, const char *fragmentSource)
  {
    unsigned int vertexShader = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vertexShader, 1, &vertexSource, NULL);
    glCompileShader (vertexShader);

    unsigned int fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader (fragmentShader);

    unsigned int shaderProgram = glCreateProgram ();
    glAttachShader (shaderProgram, vertexShader);
    glAttachShader (shaderProgram, fragmentShader);
    glLinkProgram (shaderProgram);

    glDeleteShader (vertexShader);
    glDeleteShader (fragmentShader);

    return shaderProgram;
  }
};
