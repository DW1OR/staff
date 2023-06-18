#include "workerManager.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  // 实例化管理者对象
  WorkerManager wm;

  int flag = -1;
  while (flag != 0) {
    // 显示菜单
    wm.showMenu();
    cin >> flag;

    switch (flag) {
    case 0: // 0、推出管理程序
      wm.exitSystem();
      break;
    case 1: // 1、增加职工信息
      wm.addEmp();
      break;
    case 2: // 2、显示职工信息
      wm.showEmp();
      break;
    case 3: // 3、删除离职职工
      wm.delEmp();
      break;
    case 4: // 4、修改职工信息
      wm.updateEmp();
      break;
    case 5: // 5、查找职工信息
      break;
    case 6: // 6、按照偏好排序
      break;
    case 7: // 7、清空所有文档
      break;
    default:
      cout << "输入的选择有误！" << endl;
      break;
    }

    system("pause");
    system("cls");
  }

  return 0;
}
