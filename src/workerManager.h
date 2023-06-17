#pragma once // 防止头文件重复包含
#include "worker.h"
#include <iostream> // 包含输入输出流头文件

class WorkerManager {
public:
  WorkerManager();

  // 展示菜单
  void showMenu();

  // 退出系统
  void exitSystem();

  // 增加职工
  void addEmp();

  ~WorkerManager();

  // 记录职工人数
  int m_EmpNum;

  // 职工数组指针
  Worker **m_EMpArray;
};