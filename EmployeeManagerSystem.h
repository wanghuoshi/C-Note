#include <iostream>
using namespace std;

class Worker
{
public:
    int m_Id;
    string m_Name;
    int m_DeptId;

    virtual void showInfo() = 0;

    virtual string getDeptName() = 0;
};

class WorkerManager
{
    int m_WorkerNum;
    Worker** m_WorkerArray;

public:
    WorkerManager();
    ~WorkerManager();

    int getArrNum();

    void initArr(Worker** arr);

    void showMenu();

    void exitSystem();

    void addWorker();

    void save();

    void showWorkers();

    int isExist(int id);

    void delWorker();

    void pacthWorker();
};

class Employee :public Worker
{
public:
    Employee(int id, string name, int did);

    virtual void showInfo();

    virtual string getDeptName();
};

class Manager :public Worker
{
public:
    Manager(int id, string name, int idd);

    virtual void showInfo();

    virtual string getDeptName();
};

class Boss :public Worker
{
public:
    Boss(int id, string name, int idd);

    virtual void showInfo();

    virtual string getDeptName();
};