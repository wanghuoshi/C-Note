#include <iostream>
#include <fstream>
#include "unistd.h"
#include "EmployeeManagerSystem.h"
using namespace std;
#define FILENAME "./第4阶段实战-基于多态的企业职工系统/empFIle.txt"

WorkerManager::WorkerManager()
{
    int num = this->getArrNum();
    if(num > 0)
    {
        this->m_WorkerNum = num;
        this->m_WorkerArray = new Worker* [this->m_WorkerNum];
        this->initArr(this->m_WorkerArray);
    }
    else
    {
        this->m_WorkerNum = 0;
        this->m_WorkerArray = NULL;
    }
    
}

WorkerManager::~WorkerManager()
{
    if(this->m_WorkerArray != NULL)
    {
        delete[] this->m_WorkerArray;
    }
    
}

int WorkerManager::getArrNum()
{
    int id, dId, arrNum=0;
    string name;
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if(ifs.is_open())
    {
        

        while(ifs >> id && ifs >> name &&  ifs >> dId)
        {
            arrNum++;
        }
    }
    ifs.close();

    return arrNum;
}

void WorkerManager::initArr(Worker** arr)
{
    int id, dId, index = 0;
    string name;

    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if(ifs.is_open())
    {
        Worker* worker = NULL;
        while(ifs >> id && ifs >> name && ifs >> dId)
        {
            if(dId == 1)
            {
                worker = new Employee(id, name, dId);
            }
            else if(dId == 2)
            {
                worker = new Manager(id, name, dId);
            }
            else
            {
                worker = new Boss(id, name, dId);
            }
            arr[index] = worker;
            index++;
        }
    }
    ifs.close();
}

void WorkerManager::showMenu()
{
    cout << "**********  Welcome!!! **********" << endl;
    cout << "***********  0.EXIT   ***********" << endl;
    cout << "***********  1.ADD    ***********" << endl;
    cout << "***********  2.SHOW   ***********" << endl;
    cout << "***********  3.DELETE ***********" << endl;
    cout << "***********  4.PATCH  ***********" << endl;
    cout << "***********  5.FIND   ***********" << endl;
    cout << "***********  6.SORT   ***********" << endl;
    cout << "***********  7.CLEAN  ***********" << endl;
    cout << endl;
}

void WorkerManager::exitSystem()
{
    cout << "Thanks!" <<endl;
}

void WorkerManager::addWorker()
{
    cout << "Please input adding workers number." << endl;
    int addNum = 0;
    cin >> addNum;

    if(addNum > 0)
    {
        int newSize = this->m_WorkerNum + addNum;
        Worker** newArray = new Worker* [newSize];

        if(m_WorkerArray != NULL)
        {
           for(int i=0; i < addNum; i++)
            {
                newArray[i] = this->m_WorkerArray[i];
            } 
        }
        
        for(int i=0; i<addNum; i++)
        {
            int id, dSelect;
            string name;
            cout << "Please input new worker's Id." << endl;
            cin >> id;
            cout << "Please input new worker's name." << endl;
            cin >> name;
            cout << "Please select new worker's department." << endl;
            cout << "1: Employee, 2: Manager, 3: Boss." << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3:
                    worker = new Boss(id, name, 3);
                    break;
            }

            newArray[this->m_WorkerNum + i] = worker; 
        }

        delete[] this->m_WorkerArray;
        this->m_WorkerArray = newArray;
        this->m_WorkerNum = newSize;

        cout << "Successfully add." << endl;
    }
    else
    {
        cout << "Error input." << endl;
    }
    this->save();

    cout << endl;
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for(int i=0; i < this->m_WorkerNum; i++)
    {
        ofs << this->m_WorkerArray[i]->m_Id
        <<" "<< this->m_WorkerArray[i]->m_Name
        <<" "<< this->m_WorkerArray[i]->m_DeptId << endl;
    }
    ofs.close();
}

void WorkerManager::showWorkers()
{
    for(int i=0; i < this->m_WorkerNum; i++)
    {
        this->m_WorkerArray[i]->showInfo();
    }
    cout << endl;
}

int WorkerManager::isExist(int id)
{
    int i;
    for(i = 0; i < this->m_WorkerNum; i++)
    {
        if(this->m_WorkerArray[i]->m_Id == id)
        {
            return i;
        }
        else
        {
            return -1;
        }
        
    }
}

void WorkerManager::delWorker()
{
    int id;
    cout << "Please input the id which you want to delete." << endl;
    cin >> id;
    int index = this->isExist(id);
    if(index == -1)
    {
        cout << "There is no this id." << endl;
    }
    else
    {
        for(int i = index; i < this->m_WorkerNum; i++)
        {
            this->m_WorkerArray[i] = this->m_WorkerArray[i+1];
        }
        this->m_WorkerNum--;
        this->save();
        cout << "Successfully Delete." << endl;
        cout << endl;
    }
}

void WorkerManager::pacthWorker()
{
    int id;
    cout << "Please input the id which you want to patch." << endl;
    cin >> id;
    int index = this->isExist(id);
    if(index != -1)
    {
        cout << "Please input new name." << endl;
        string name;
        cin >> name;
        cout << "Please input new department id." << endl;
        int dId;
        cin >> dId;
        Worker* worker;
        switch(dId)
        {
            case 1:
                worker = new Employee(id, name, dId);
                break;
            case 2:
                worker = new Manager(id, name, dId);
                break;
            case 3:
                worker = new Boss(id, name, dId);
                break;
        }        
        this->m_WorkerArray[index] = worker;
        this->save();
        cout << "Successfully patch the worker." << endl;
    }
    else
    {
        cout << "There is no this worker." << endl;
    }
    cout << endl;  
}

Employee::Employee(int id, string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void Employee::showInfo()
{
    cout << "Employee's Id: " << this->m_Id << ", Name: "
    << this->m_Name << ", DeptId: " << this->m_DeptId <<
    ", Task: Complete what manager give" << endl;
}

string Employee::getDeptName()
{
    return "Employee";
}

Manager::Manager(int id, string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void Manager::showInfo()
{
    cout << "Manager's Id: " << this->m_Id << ", Name: "
    << this->m_Name << ", DeptId: " << this->m_DeptId <<
    ", Task: Complete what boss give, and give to employee" << endl;
}

string Manager::getDeptName()
{
    return "Manager";
}

Boss::Boss(int id, string name, int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void Boss::showInfo()
{
    cout << "Boss's Id: " << this->m_Id << ", Name: "
    << this->m_Name << ", DeptId: " << this->m_DeptId <<
    ", Task: Give tasks to managers" << endl;
}

string Boss::getDeptName()
{
    return "Boss";
}

int main()
{
    WorkerManager ems;
    int choice = 0;

    while(true)
    {
        ems.showMenu();
        cout << "Please input your choice." << endl;
        cin >> choice;
        switch (choice)
        {
            case 0: //退出系统
                ems.exitSystem();
                return 0;
            case 1: //添加职工t
                ems.addWorker();
                break;
            case 2: //显示职工
                ems.showWorkers();
                break;
            case 3: //删除职工
                ems.delWorker();
                break;
            case 4: //修改职工
                ems.pacthWorker();
                break;
            case 5: //查找职工
                break;
            case 6: //排序职工
                break;
            case 7: //清空文件
                break;
            default:
                break;
        }
    }

    return 0;
}

