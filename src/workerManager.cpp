#include "workerManager.h"
#include <iostream>

using namespace std; // 使用标准命名空间

WorkerManager::WorkerManager() {}

// 展示菜单
void WorkerManager::showMenu() {
  cout << "欢迎使用职工管理系统" << endl;
  cout << "0、推出管理程序" << endl;
  cout << "1、增加职工信息" << endl;
  cout << "2、显示职工信息" << endl;
  cout << "3、删除离职职工" << endl;
  cout << "4、修改职工信息" << endl;
  cout << "5、查找职工信息" << endl;
  cout << "6、按照偏好排序" << endl;
  cout << "7、清空所有文档" << endl;
  cout << endl;
  cout << "请输入你的选择：" << endl;
}

// 退出系统
void WorkerManager::exitSystem() {
  cout << "欢迎下次使用" << endl;
  system("pause");
  exit(0);
}

WorkerManager::~WorkerManager() {}