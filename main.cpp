#include <QCoreApplication>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDomDocument>
#include <QDir>
#include "header.h"
#include <QtTest/QTest>
#include "tests.h"
int main(int argc, char *argv[])
{
//    QTest::qExec(new tests, argc, argv);
//    return 0;

    QCoreApplication a(argc, argv);

    // Объявление входного .xml файла
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\input.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    // Объявление входного .txt файла
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\input2.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    // Объявление выходного .txt файла
    QString locationOutput = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\output.txt";  // Расположение входного .txt файла
    QFile outputTxt(locationOutput);

    department rootDepartment;

    // Выполнение проверки входных данных
    try {
        testInputDatas(locationXml, inputXml, locationTxt, inputTxt);


    }  catch (int error) {
        outputError(error);
        closeInputDatas(inputXml, inputTxt);
        return 0;
    }

    qDebug() << "work, no input errors";

    // Получить ID пользователя
    int rootEmployeeId = getInputID(inputTxt);
    if (rootEmployeeId == 0)  // Если ID отсутствует - завершить программу и вернуть ошибку
    {
        return 0;
    }

    // Запарсить .xml файл
    getAllContentFromXml(inputXml, rootDepartment);

    // Получить подразделения, подчиняющиеся данному сотруднику
    QList<QString> outputStrings;
    getOutputStrings(rootEmployeeId, rootDepartment, outputStrings);


    // Записать получившийся список строк в выходной файл
    writeOutputFile(locationOutput, outputStrings);

    for (int i = 0; i < outputStrings.count(); i++)
    {
        qDebug() << outputStrings[i];
    }
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
        if (!idDatas[i].isDigit() || idDatas[i] == '0')  // Если символ не число
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

bool getAllContentFromXml(QFile& inputXml, department &rootDepartment)
{
    if (!inputXml.open(QIODevice::ReadOnly))
        {                                           // Проверяем, возможно ли открыть .xml файл для чтения
            qDebug() << "Error: can't read .xml file";
            inputXml.close();
        }           // Вывести в консоль ошибку, что файл открыть невозможно

    QByteArray buff = inputXml.readAll();
    QDomDocument doc;

    // Проверить, что .xml файл не пустой
    if (doc.setContent(buff) == false)
    {
        inputXml.close();
        qDebug() << "bad XML-file: setContent";
        return 0;
    }
    // Проверить, что на самом верхнем уровне находится подразделение
    QDomElement root = doc.documentElement();
    if (root.tagName() != "Department")
    {
        inputXml.close();
        qDebug() << "bad XML-file: tagname() != Department";
        return 0;
    }
    // Первая вложенная нода
    QDomNode record_node = root.firstChild();

    // Список подчиненных сотрудников
    QList<employee> childEmployees;

    // Список подчиненных подразделений
    QList<department> childDepartments;

    rootDepartment.idHead = QString::fromStdString(record_node.attributes().namedItem("head").nodeValue().toStdString()).toInt();
    rootDepartment.departmentName = QString::fromStdString(record_node.attributes().namedItem("name").nodeValue().toStdString());

    getInputXmlDatasToStructs(record_node, root, childEmployees, childDepartments);

    rootDepartment.childDepartments = childDepartments;
    rootDepartment.employeesOfDepartment = childEmployees;
}

void getInputXmlDatasToStructs(QDomNode record_node, QDomNode root, QList<struct employee> &employeeList, QList<struct department> &departmentList)
{
    // Пока текущая нода != Null
    while (record_node.isNull() == false)
    {
        if (record_node.toElement().tagName() == "Employee")
        {
            employee employeeInfo;

            // Получить ФИО
            employeeInfo.fioEmployee = QString::fromStdString(record_node.firstChild().nodeValue().toStdString());

            // Получить ID сотрудника
            employeeInfo.idEmployee = QString::fromStdString(record_node.attributes().namedItem("id").nodeValue().toStdString()).toInt();

            // Получить название отдела, чтобы определить принадлежность к отделу
            employeeInfo.departmentAffiliation = QString::fromStdString(root.attributes().namedItem("name").nodeValue().toStdString());

            // Записать полученные ФИО, ID, название отдела в структуру employeeList
            employeeList.append(employeeInfo);
        }
        else if(record_node.toElement().tagName() == "Department")
        {
            department departmentInfo;

            // Получить ID главы подразделения
            departmentInfo.idHead = QString::fromStdString(record_node.attributes().namedItem("head").nodeValue().toStdString()).toInt();

            // Получить название подразделения
            departmentInfo.departmentName = QString::fromStdString(record_node.attributes().namedItem("name").nodeValue().toStdString());

            QList<employee> childEmployees;
            QList<department> childDepartments;

            // Рекурсивный вызов функции для следующей ноды
            getInputXmlDatasToStructs(record_node.firstChild(), record_node, childEmployees, childDepartments);

            // Записать разделение в подразделенное
            departmentInfo.childDepartments = childDepartments;

            departmentInfo.employeesOfDepartment = childEmployees;
            departmentList.append(departmentInfo);
        }

        // Следующая итерация
        record_node = record_node.nextSibling();
    }
}


void getOutputStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings)
{
    if (rootDepartment.idHead == rootEmployeeId)
    {
        // Определить главу подразделения
        employee head;
        for (int i = 0; i < rootDepartment.employeesOfDepartment.count(); i++)
        {
            if (rootDepartment.employeesOfDepartment[i].idEmployee == rootEmployeeId)
            {
                head = rootDepartment.employeesOfDepartment[i];
                break;
            }
        }

        // Записать строку главы подразделения
        outputStrings.append("Руководитель " + rootDepartment.departmentName + ": " + head.fioEmployee);

        // Записать в список строк подразделение и его сотрудников
        outputStrings.append(rootDepartment.departmentName + ":");
        for (int i = 0; i < rootDepartment.employeesOfDepartment.count(); i++)
        {
            if (rootDepartment.employeesOfDepartment[i].idEmployee != rootEmployeeId)
            {
                outputStrings.append("    " + rootDepartment.employeesOfDepartment[i].fioEmployee);
            }
        }

        // Записать строки внутренних подразделений
        for (int i = 0; i < rootDepartment.childDepartments.count(); i++)
        {
            getDepartmentsStrings(rootEmployeeId, rootDepartment.childDepartments[i], outputStrings);
        }
    }
    else
    {
        // Записать строки для других подразделений того же уровня
        for (int i = 0; i < rootDepartment.employeesOfDepartment.count(); i++)
        {
            // Записать строки сотрудников подразделения
            if (rootDepartment.employeesOfDepartment[i].idEmployee == rootEmployeeId)
            {
                outputStrings.append(rootDepartment.departmentName + ":");
                for (int i = 0; i < rootDepartment.employeesOfDepartment.count(); i++)
                {
                    if (rootDepartment.employeesOfDepartment[i].idEmployee != rootEmployeeId)
                    {
                        outputStrings.append("    " + rootDepartment.employeesOfDepartment[i].fioEmployee);
                    }
                }

                // Записать строки внутренних подразделений
                for (int i = 0; i < rootDepartment.childDepartments.count(); i++)
                {
                    getDepartmentsStrings(rootEmployeeId, rootDepartment.childDepartments[i], outputStrings);
                }

                return;
            }
            else
            {
                // Записать строки подразделений
                for (int i = 0; i < rootDepartment.childDepartments.count(); i++)
                {
                    getOutputStrings(rootEmployeeId, rootDepartment.childDepartments[i], outputStrings);
                }
            }
        }
    }
}

void getDepartmentsStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings)
{
    // Записать строки подразделения
    outputStrings.append(rootDepartment.departmentName + ":");
    for (int i = 0; i < rootDepartment.employeesOfDepartment.count(); i++)
    {
        // Записать строки сотрудников подразделения
        if (rootDepartment.employeesOfDepartment[i].idEmployee != rootEmployeeId)
        {
            outputStrings.append("    " + rootDepartment.employeesOfDepartment[i].fioEmployee);
        }
    }

    // Записать строки внутренних подразделений
    for (int i = 0; i < rootDepartment.childDepartments.count(); i++)
    {
        getDepartmentsStrings(rootEmployeeId, rootDepartment.childDepartments[i], outputStrings);
    }
}

void writeOutputFile(QString filePath, QList<QString> &outputStrings)
{
    // Расположение файла
    QFile file(filePath);

    // Если можно записать данные в файл
    if (file.open(QIODevice::WriteOnly))
    {
        // Записать строки в файл
        QTextStream stream(&file);

        for (int i = 0; i < outputStrings.count(); i++)
        {
            stream << outputStrings[i] << "\n";
        }

        // Закрыть файл
        file.close();
    }
    // Вывести в консоль ошибку, что файл открыть невозможно
    else
    {
        qDebug() << "bad XML-file: cannot write output file";
    }
}
