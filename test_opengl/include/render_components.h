#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include <sstream>

// 简化的相机类
class Camera
{
public:
  Camera (float fov = 45.0f, float aspect = 1.33f)
  {
    projection = glm::perspective (glm::radians (fov), aspect, 0.1f, 100.0f); // 设置投影矩阵
    position = glm::vec3 (0.0f, 0.0f, 3.0f); // 设置相机位置
    view = glm::lookAt (position, glm::vec3 (0.0f), // 设置视图矩阵
                        glm::vec3 (0.0f, 1.0f, 0.0f)); // 设置相机方向
  }

  glm::mat4
  GetViewMatrix () const
  {
    return view; // 返回视图矩阵
  }
  glm::mat4
  GetProjectionMatrix () const
  {
    return projection; // 返回投影矩阵
  }

private:
  glm::mat4 view;
  glm::mat4 projection;
  glm::vec3 position;
};

// 简化的网格类
class Mesh
{
public:
  Mesh (const std::vector<float> &vertices)
  {
    // 创建并绑定VAO和VBO
    glGenVertexArrays (1, &VAO); // 创建VAO
    glGenBuffers (1, &VBO); // 创建VBO

    glBindVertexArray (VAO); // 绑定VAO
    glBindBuffer (GL_ARRAY_BUFFER, VBO); // 绑定VBO
    glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof (float),
                  vertices.data (), GL_STATIC_DRAW); // 设置VBO数据

    // 假设顶点数据格式为：位置(3) + 法线(3) + UV(2)
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float),
                           (void *)0); // 设置顶点属性指针
    glEnableVertexAttribArray (0); // 启用顶点属性

    vertexCount = vertices.size () / 8; // 设置顶点数量
  }

  // 添加新的构造函数，接受顶点数据和索引数据
  Mesh (const std::vector<float> &vertices,
        const std::vector<unsigned int> &indices)
  {
    // 创建并绑定VAO
    glGenVertexArrays (1, &VAO);
    glBindVertexArray (VAO); // 绑定VAO

    // 创建并绑定VBO
    glGenBuffers (1, &VBO); // 创建VBO
    glBindBuffer (GL_ARRAY_BUFFER, VBO); // 绑定VBO
    glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof (float),
                  vertices.data (), GL_STATIC_DRAW); // 设置VBO数据

    // 创建并绑定EBO
    glGenBuffers (1, &EBO);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  indices.size () * sizeof (unsigned int), indices.data (),
                  GL_STATIC_DRAW);

    // 设置顶点属性指针
    // 位置属性
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float),
                           (void *)0);
    glEnableVertexAttribArray (0);

    // 法线属性
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float),
                           (void *)(3 * sizeof (float)));
    glEnableVertexAttribArray (1);

    // 纹理坐标属性
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float),
                           (void *)(6 * sizeof (float)));
    glEnableVertexAttribArray (2);

    size_t indexCount = indices.size ();
  }

  void
  Draw ()
  {
    glBindVertexArray (VAO);
    glDrawArrays (GL_TRIANGLES, 0, vertexCount);
  }

private:
  unsigned int VAO, VBO, EBO;
  int vertexCount;
};

// 简化的材质类
class Material
{
public:
  Material (const char *vertexPath, const char *fragmentPath)
  {
    // 创建并编译着色器
    shader = CreateShaderProgram (vertexPath, fragmentPath); // 创建着色器程序
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

  void SetVec3(const std::string& name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(shader, name.c_str()), 1, &value[0]);
  }

private:
  unsigned int shader;
  std::string
  LoadShaderCode (const char *path)
  {
    std::ifstream file (path);
    std::string code ((std::istreambuf_iterator<char> (file)),
                      std::istreambuf_iterator<char> ());
    return code;
  }

  unsigned int
  CreateShaderProgram (const char *vertexPath, const char *fragmentPath)
  {
    std::string vertexCode = LoadShaderCode (vertexPath);
    std::string fragmentCode = LoadShaderCode (fragmentPath);

    // Store the C-string pointers
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader (GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);

    // Use the stored pointers
    glShaderSource (vertexShader, 1, &vertexSource, NULL);
    glCompileShader (vertexShader);
    glShaderSource (fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader (fragmentShader);

    // 创建着色器程序
    unsigned int shaderProgram = glCreateProgram (); // 创建着色器程序
    glAttachShader (shaderProgram, vertexShader); // 附加顶点着色器
    glAttachShader (shaderProgram, fragmentShader); // 附加片段着色器
    glLinkProgram (shaderProgram); // 链接着色器程序

    return shaderProgram; // 返回着色器程序
  }
};