#pragma once        // 防止头文件重复包含
#include <iostream> // 包含输入输出流头文件

class WorkerManager {
public:
  WorkerManager();

  // 展示菜单
  void showMenu();

  // 退出系统
  void exitSystem();

  ~WorkerManager();
};