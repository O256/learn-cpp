#pragma once

#include "render_components.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

// 渲染对象结构体
struct RenderObject
{
  std::shared_ptr<Mesh> mesh;         // 网格
  std::shared_ptr<Material> material; // 材质
  glm::mat4 transform;                // 变换矩阵
};

// 简单渲染管线类
class SimplePipeline
{
public:
  SimplePipeline () { camera = std::make_shared<Camera> (); }

  // 设置相机
  void
  SetCamera (std::shared_ptr<Camera> cam)
  {
    camera = cam;
  }

  // 设置投影矩阵
  void
  SetProjection (glm::mat4 proj)
  {
    projection = proj;
  }

  // 设置视图矩阵
  void
  SetView (glm::mat4 v)
  {
    this->view = v;
  }

  // 设置模型矩阵
  void
  SetModel (glm::mat4 model)
  {
    model = model;
  }

  // 渲染场景中的所有对象
  void
  Render (const std::vector<RenderObject> &objects)
  {
    // 清除缓冲
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓冲

    // 获取相机矩阵
    glm::mat4 view = camera->GetViewMatrix ();
    glm::mat4 projection = camera->GetProjectionMatrix ();

    // 启用深度测试
    glEnable (GL_DEPTH_TEST);

    // 渲染所有对象
    for (const auto &obj : objects)
      {
        obj.material->Use (); // 使用材质

        // 设置变换矩阵
        obj.material->SetMatrix ("view", view); // 设置视图矩阵
        obj.material->SetMatrix ("projection", projection); // 设置投影矩阵
        obj.material->SetMatrix ("model", obj.transform); // 设置模型矩阵

        // 绘制网格
        obj.mesh->Draw (); // 绘制网格
      }
  }

private:
  std::shared_ptr<Camera> camera; // 相机
  glm::mat4 projection;           // 投影矩阵
  glm::mat4 view;                 // 视图矩阵
  glm::mat4 model;                // 模型矩阵
};