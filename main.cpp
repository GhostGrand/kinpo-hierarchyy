#include <QCoreApplication>

#include <QtTest/QTest>
#include "header.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    QTest::qExec(new tests, argc, argv);
}

bool testInputDatas(QString& locationXml, QFile& inputXml, QString& locationTxt, QFile& inputTxt)
{

}

void outputError(int error)
{

}

void getInputDatas()
{

}

int getInputID(QFile& inputTxt)
{

}

void closeInputDatas(QFile& inputXml, QFile& inputTxt)
{

}

void getAllContentFromXml(QFile& inputXml, department &rootDepartment)
{

}

void getInputXmlDatasToStructs(QDomNode record_node, QDomNode root, QList<struct employee> &employeeList, QList<struct department> &departmentList)
{

}

void getDepartmentsLower(int rootEmployeeId, department &rootDepartment, QList<struct department> &lowerDepartments)
{

}

void getOutputStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings)
{

}

void getDepartmentsStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings)
{

}

void writeOutputFile(QString filePath, QList<QString> &outputStrings)
{

}
