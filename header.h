#ifndef HEADER_H
#define HEADER_H

#endif // HEADER_H
#include <QString>
#include <QList>
#include <QFile>
#include <QDomDocument>



struct employee
{
   QString fioEmployee;
   int idEmployee;
   QString departmentAffiliation;
};

struct department
{
    int idHead;
    QString departmentName;
    QList<employee> employeesOfDepartment;
    QList<department> childDepartments;
};


bool testInputDatas(QString& locationXml, QFile& inputXml, QString& locationTxt, QFile& inputTxt);

int outputError(int error);

void getInputDatas();

int getInputID(QFile& inputTxt);

void getInputXmlDatasToStructs(QDomNode record_node, QDomNode root, QList<struct employee> &employeeList, QList<struct department> &departmentList);    // сюда заносить ноду

void getAllContentFromXml(QFile& inputXml, department &rootDepartment);

QString getFIOEmployee(int idEmployee, QList<struct employee> &employeeList);

void closeInputDatas(QFile& inputXml, QFile& inputTxt);

void getDepartmentsLower(int rootEmployeeId, department &rootDepartment, QList<struct department> &lowerDepartments);

void getOutputStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings);

void getDepartmentsStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings);

void writeOutputFile(QString filePath, QList<QString> &outputStrings);
