// Mesh.h
#pragma once
#include <glad/glad.h>

#include <vector>

class Mesh {
 public:
  Mesh(const std::vector<float>& vertices) {
    // 创建并绑定VAO和VBO
    glGenVertexArrays(1, &VAO);  // 创建VAO
    glGenBuffers(1, &VBO);       // 创建VBO

    glBindVertexArray(VAO);              // 绑定VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // 绑定VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);  // 设置VBO数据

    // 假设顶点数据格式为：位置(3) + 法线(3) + UV(2)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);  // 设置顶点属性指针
    glEnableVertexAttribArray(0);     // 启用顶点属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));  // 法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));  // 纹理坐标
    glEnableVertexAttribArray(2);

    vertexCount = vertices.size() / 8;  // 设置顶点数量
  }

  void Draw() {
    glBindVertexArray(VAO);  // 绑定VAO
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  }

 private:
  unsigned int VAO, VBO;
  int vertexCount;
};
