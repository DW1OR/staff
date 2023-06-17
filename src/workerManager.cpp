#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <cstddef>
#include <iostream>

using namespace std; // 使用标准命名空间

WorkerManager::WorkerManager() {
  // 初始化属性
  this->m_EmpNum = 0;

  this->m_EMpArray = NULL;
}

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

// 增加职工
void WorkerManager::addEmp() {
  cout << "请输入添加职工数量：" << endl;
  // 保存用户的输入数量
  int addNum = 0;
  cin >> addNum;
  if (addNum > 0) {
    // 计算新空间大小
    int newSize = this->m_EmpNum + addNum;

    // 开辟新空间
    Worker **newSpace = new Worker *[newSize * sizeof(Worker)];

    // 将原来空间下的数据，拷贝到新的空间下
    if (this->m_EMpArray != NULL) {
      for (int i = 0; i < this->m_EmpNum; i++) {
        newSpace[i] = this->m_EMpArray[i];
      }
    }

    // 批量添加新数据
    for (int i = 0; i < addNum; i++) {
      int id;
      string name;
      int deptId;

      cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
      cin >> id;

      cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
      cin >> name;

      cout << "请选择该职工岗位：" << endl;
      cout << "1、普通员工" << endl;
      cout << "2、经理" << endl;
      cout << "3、老板" << endl;
      cin >> deptId;
      while (!(deptId == 1 || deptId == 2 || deptId == 3) || cin.fail()) {
        cout << "输入有误，请重新输入：" << endl;
        // 清空cin缓冲区
        cin.clear();
        cin.ignore();
        cin >> deptId;
      }

      Worker *worker = NULL;
      switch (deptId) {
      case 1:
        worker = new Employee(id, name, 1);
        break;
      case 2:
        worker = new Manager(id, name, 2);
        break;
      case 3:
        worker = new Boss(id, name, 3);
        break;
      default:
        break;
      }

      // 将新建的职工添加到数组中
      newSpace[this->m_EmpNum + 1] = worker;
    }

    // 释放原有的空间
    delete[] this->m_EMpArray;

    // 更新新空间的指向
    this->m_EMpArray = newSpace;

    // 更新新的职工人数
    this->m_EmpNum = newSize;

    cout << "成功添加" << addNum << "名新员工" << endl;
  } else {
    cout << "输入数据有误" << endl;
  }
}

WorkerManager::~WorkerManager() {}