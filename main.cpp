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
    // Проверка наличия входного файла .xml
    if (!inputXml.exists())
    {
        //puts("error: no input .xml");
        throw 1;
    }

    // Проверка корректности входного .xml файла
    if (!inputXml.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //puts("invalid input data: unable to read .xml file");
        throw 2;

    }

    // Проверка наличия входного файла .txt
    if (!inputTxt.exists())
    {
        //puts("error: no input .txt");
        throw 3;
    }

    // Проверка наличия ID во входном .txt файле
    if(inputTxt.size() == 0)
    {
        //puts("invalid input data: .txt file is empty");
        throw 4;
    }

    inputXml.close();   // закрыть .xml файл
}

void outputError(int error)
{
    if(error == 1)
        qDebug() << "error: no input .xml";
    if(error == 2)
        qDebug() << "invalid input data: unable to read .xml file";
    if(error == 3)
        qDebug() << "error: no input .txt";
    if(error == 4)
        qDebug() << "invalid input data: .txt file is empty";
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
