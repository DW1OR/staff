#pragma once // 防止头文件重复包含
#include "worker.h"
#include <fstream>
#include <iostream> // 包含输入输出流头文件

#define FILENAME "empFile.txt"

class WorkerManager {
public:
  WorkerManager();

  // 保存文件
  void saveFile();

  // 统计文件中人数
  int getEmpNum();

  // 初始化员工
  void initEmp();

  // 展示菜单
  void showMenu();

  // 退出系统
  void exitSystem();

  // 增加职工
  void addEmp();

  // 显示职工
  void showEmp();

  // 判断职工是否存在
  int isExist(int id);

  // 删除职工
  void delEmp();

  ~WorkerManager();

  // 记录职工人数
  int m_EmpNum;

  // 职工数组指针
  Worker **m_EmpArray;

  // 标识文件是否为空
  bool m_FileIsEmpty;
};