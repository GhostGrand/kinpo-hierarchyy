#include <QCoreApplication>

#include <QtTest/QTest>
#include "header.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    QTest::qExec(new tests, argc, argv);
    return 0;

    QCoreApplication a(argc, argv);

    // Объявление входного .xml файла
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchy\\input.xml";  // расположение входного .xml файла
    QFile inputXml(locationXml);

    // Объявление входного .txt файла
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchy\\input2.txt";  // расположение входного .txt файла
    QFile inputTxt(locationTxt);

    // Объявление выходного .txt файла
    QString locationOutput = QDir::currentPath() + "..\\..\\kinpo-hierarchy\\output.txt";  // расположение входного .txt файла
    QFile outputTxt(locationOutput);

    department rootDepartment;

    // выполнение проверки входных данных
    try {
        testInputDatas(locationXml, inputXml, locationTxt, inputTxt);


    }  catch (int error) {
        outputError(error);
        closeInputDatas(inputXml, inputTxt);
        return 0;
    }

    qDebug() << "work, no input errors";

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

    inputXml.close();   // Закрыть .xml файл
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
    // Входной ID
    int inputID;
    // Объект класса, который хранит получившиеся строки
    QString idDatas;
    if (!inputTxt.open(QIODevice::ReadOnly))    // Проверяем, возможно ли открыть .txt файл для чтения
        return 0;
    idDatas = inputTxt.readAll();   // Записать полученную строку в idDatas
    qDebug() << idDatas;    // Вывести в консоль idDatas

    // Проверить корректность входных данных
    for (int i = 0; i < idDatas.length(); i++)
    {
        if (!idDatas[i].isDigit())  // Если символ не число
        {
            qDebug() << "incorrect ID";
            return 0;   // Вернуть 0 и вывести ошибку
        }
    }

    inputID = idDatas.toInt();
    return inputID;
}

void closeInputDatas(QFile& inputXml, QFile& inputTxt)
{
    inputXml.close();
    inputTxt.close();
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
