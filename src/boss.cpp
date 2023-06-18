#include "boss.h"

using namespace std;

Boss::Boss(int id, string name, int deptId) {
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = deptId;
}

// 显示个人信息
void Boss::showInfo() {
  cout << "职工编号：" << this->m_Id << "\t职工姓名：" << this->m_Name
       << "\t岗位：" << this->getDeptName() << "\t岗位职责：管理公司所有事务"
       << endl;
}

// 获取岗位名称
string Boss::getDeptName() { return string("老板"); }