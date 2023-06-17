#include "manager.h"

using namespace std;

Manager::Manager(int id, string name, int deptId) {
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = deptId;
}

// 显示个人信息
void Manager::showInfo() {
  cout << "职工编号：" << this->m_Id << endl;
  cout << "职工姓名：" << this->m_Name << endl;
  cout << "岗位：" << this->getDeptName() << endl;
  cout << "岗位职责：完成老板交给的任务，下发任务给普通员工" << endl;
}

// 获取岗位名称
string Manager::getDeptName() { return string("经理"); }