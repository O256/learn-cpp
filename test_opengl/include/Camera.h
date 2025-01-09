// Camera.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
 public:
  Camera(float fov = 45.0f, float aspect = 1.33f) {
    projection = glm::perspective(glm::radians(fov), aspect, 0.1f,
                                  100.0f);   // 设置投影矩阵
    position = glm::vec3(0.0f, 0.0f, 3.0f);  // 设置相机位置
    view = glm::lookAt(position, glm::vec3(0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));  // 设置视图矩阵
  }

  glm::mat4 GetViewMatrix() const {
    return view;  // 返回视图矩阵
  }

  glm::mat4 GetProjectionMatrix() const {
    return projection;  // 返回投影矩阵
  }

 private:
  glm::mat4 view;
  glm::mat4 projection;
  glm::vec3 position;
};
