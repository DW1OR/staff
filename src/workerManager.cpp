#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <process.h>

using namespace std; // 使用标准命名空间

WorkerManager::WorkerManager() {
  ifstream ifs;
  // 读文件
  ifs.open(FILENAME, ios::in);

  if (!ifs.is_open()) {
    // cout << "文件不存在" << endl;
    //  初始化属性
    this->m_EmpNum = 0;
    this->m_EmpArray = NULL;
    this->m_FileIsEmpty = true;
    ifs.close();
    return;
  }

  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    // cout << "文件为空" << endl;
    //  初始化属性
    this->m_EmpNum = 0;
    this->m_EmpArray = NULL;
    this->m_FileIsEmpty = true;
    ifs.close();
    return;
  }

  // 读取文件中数据
  int num = this->getEmpNum();
  cout << "职工人数为：" << num << endl;
  this->m_EmpNum = num;
  this->m_EmpArray = new Worker *[this->m_EmpNum];
  this->initEmp();
}

// 保存文件
void WorkerManager::saveFile() {
  ofstream ofs;
  ofs.open(FILENAME, ios::out | ios::trunc);

  // 将每个人数据写入文件中
  for (int i = 0; i < this->m_EmpNum; i++) {
    ofs << this->m_EmpArray[i]->m_Id << " " << this->m_EmpArray[i]->m_Name
        << " " << this->m_EmpArray[i]->m_DeptId << " " << endl;
  }

  ofs.close();
}

// 统计文件中人数
int WorkerManager::getEmpNum() {
  ifstream ifs;
  ifs.open(FILENAME, ios::in);

  int id;
  string name;
  int deptId;

  int num = 0;
  // ifs遇到空格会停止读取
  while (ifs >> id && ifs >> name && ifs >> deptId) {
    num++;
  }

  return num;
}

// 初始化员工
void WorkerManager::initEmp() {
  ifstream ifs;
  ifs.open(FILENAME, ios::in);

  int id;
  string name;
  int deptId;

  int index = 0;
  while (ifs >> id && ifs >> name && ifs >> deptId) {
    Worker *worker = NULL;
    switch (deptId) {
    case 1:
      worker = new Employee(id, name, deptId);
      break;
    case 2:
      worker = new Manager(id, name, deptId);
      break;
    case 3:
      worker = new Boss(id, name, deptId);
      break;
    default:
      break;
    }

    this->m_EmpArray[index++] = worker;
  }

  ifs.close();
}

// 展示菜单
void WorkerManager::showMenu() {
  cout << "欢迎使用职工管理系统" << endl;
  cout << "0、退出管理程序" << endl;
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
    if (this->m_EmpArray != NULL) {
      for (int i = 0; i < this->m_EmpNum; i++) {
        newSpace[i] = this->m_EmpArray[i];
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
      newSpace[this->m_EmpNum + i] = worker;
    }

    // 释放原有的空间
    delete[] this->m_EmpArray;

    // 更新新空间的指向
    this->m_EmpArray = newSpace;

    // 更新新的职工人数
    this->m_EmpNum = newSize;

    // 更新职工不为空标志
    this->m_FileIsEmpty = false;

    // 保存数据到文件中
    this->saveFile();

    cout << "成功添加" << addNum << "名新员工" << endl;
  } else {
    cout << "输入数据有误" << endl;
  }
}

// 显示职工
void WorkerManager::showEmp() {
  if (this->m_FileIsEmpty) {
    cout << "文件不存在或记录为空" << endl;
  } else {
    for (int i = 0; i < m_EmpNum; i++) {
      this->m_EmpArray[i]->showInfo();
    }
  }
}

// 判断职工是否存在
int WorkerManager::isExist(int id) {
  for (int i = 0; i < this->m_EmpNum; i++) {
    if (this->m_EmpArray[i]->m_Id == id) {
      return i;
    }
  }

  return -1;
}

// 删除职工
void WorkerManager::delEmp() {
  if (this->m_FileIsEmpty) {
    cout << "文件不存在或者记录为空" << endl;
  } else {
    cout << "请输入想要删除的职工编号:" << endl;
    int id = 0;
    cin >> id;

    int index = this->isExist(id);
    if (index != -1) {
      for (int i = index; i < this->m_EmpNum - 1; i++) {
        this->m_EmpArray[i] = this->m_EmpArray[i + 1];
      }

      // 职工人数同步
      this->m_EmpNum--;
      this->saveFile();

      cout << "删除成功" << endl;
    } else {
      cout << "删除失败，未找到对应职工" << endl;
    }
  }
}

// 修改职工
void WorkerManager::updateEmp() {
  if (this->m_FileIsEmpty) {
    cout << "文件不存在或者记录为空" << endl;
  } else {
    cout << "请输入修改职工编号：" << endl;
    int id;
    cin >> id;

    int updateIndex = this->isExist(id);
    if (updateIndex != -1) {
      int newId;
      string newName;
      int newDeptId;

      cout << "请输入职工的新编号：" << endl;
      cin >> newId;

      cout << "请输入职工的新姓名：" << endl;
      cin >> newName;

      cout << "请选择该职工的新岗位：" << endl;
      cout << "1、普通员工" << endl;
      cout << "2、经理" << endl;
      cout << "3、老板" << endl;
      cin >> newDeptId;
      while (!(newDeptId == 1 || newDeptId == 2 || newDeptId == 3) ||
             cin.fail()) {
        cout << "输入有误，请重新输入：" << endl;
        // 清空cin缓冲区
        cin.clear();
        cin.ignore();
        cin >> newDeptId;
      }

      Worker *worker = NULL;
      switch (newDeptId) {
      case 1:
        worker = new Employee(newId, newName, 1);
        break;
      case 2:
        worker = new Manager(newId, newName, 2);
        break;
      case 3:
        worker = new Boss(newId, newName, 3);
        break;
      default:
        break;
      }

      // 更新数据到数组中
      this->m_EmpArray[updateIndex] = worker;

      // 保存数据到文件中
      this->saveFile();

      cout << "修改成功" << endl;
    } else {
      cout << "修改失败，没有查找到对应员工" << endl;
    }
  }
}

// 查找职工
void WorkerManager::findEmp() {
  if (this->m_FileIsEmpty) {
    cout << "文件不存在或者记录为空" << endl;
  } else {
    cout << "请输入查找的方式：" << endl;
    cout << "1、按职工编号查找" << endl;
    cout << "2、按职工姓名查找" << endl;

    int select = 0;
    cin >> select;
    while (!(select == 1 || select == 2) || cin.fail()) {
      cout << "输入有误，请重新输入：" << endl;
      // 清空cin缓冲区
      cin.clear();
      cin.ignore();
      cin >> select;
    }

    if (select == 1) {
      int id;
      cout << "请输入查找的职工编号：" << endl;
      cin >> id;

      int index = this->isExist(id);
      if (index != -1) {
        cout << "查找成功，该职工信息如下：" << endl;
        this->m_EmpArray[index]->showInfo();
        return;
      }
    } else if (select == 2) {
      string name;
      cout << "请输入查找的职工姓名：" << endl;
      cin >> name;

      for (int i = 0; i < m_EmpNum; i++) {
        if (this->m_EmpArray[i]->m_Name == name) {
          cout << "查找成功，该职工信息如下：" << endl;
          this->m_EmpArray[i]->showInfo();
          return;
        }
      }
    }

    cout << "查找失败" << endl;
  }
}

// 员工排序
void WorkerManager::sortEmp() {
  if (this->m_FileIsEmpty) {
    cout << "文件不存在或者记录为空" << endl;
  } else {
    cout << "请输入排序的方式：" << endl;
    cout << "1、按职工编号进行升序" << endl;
    cout << "2、按职工编号进行降序" << endl;

    int select = 0;
    cin >> select;
    while (!(select == 1 || select == 2) || cin.fail()) {
      cout << "输入有误，请重新输入：" << endl;
      // 清空cin缓冲区
      cin.clear();
      cin.ignore();
      cin >> select;
    }

    for (int i = 0; i < m_EmpNum; i++) {
      int minOrMax = i;
      for (int j = i + 1; j < this->m_EmpNum; j++) {
        if (select == 1) { // 升序
          if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
            minOrMax = j;
          }
        } else { // 降序
          if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
            minOrMax = j;
          }
        }
      }

      if (i != minOrMax) {
        Worker *temp = this->m_EmpArray[i];
        this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
        this->m_EmpArray[minOrMax] = temp;
      }
    }

    this->saveFile();
    
    cout << "排序成功！排序后的结果为：" << endl;
    this->showEmp();
  }
}

WorkerManager::~WorkerManager() { delete[] m_EmpArray; }