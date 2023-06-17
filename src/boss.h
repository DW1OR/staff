// 老板文件
#pragma once
#include "worker.h"
#include <iostream>

using namespace std;

class Boss : public Worker {
public:
  Boss(int id, string name, int deptId);

  // 显示个人信息
  virtual void showInfo();

  // 获取岗位名称
  virtual string getDeptName();
};