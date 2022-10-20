#include "tests.h"
#include <QtTest/QTest>
#include "header.h"

tests::tests(QObject *parent)
    : QObject(parent)
{

}

void tests::getInputID_test_success()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_correct.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(1 == result, "Success");
}

void tests::getInputID_test_zero()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_zero.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_space()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_space.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_empty()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_empty.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_word()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_word.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_two_value()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_two_value.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_word_and_value()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_word_and_value.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_complex()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_complex.txt";
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getAllContentFromXml_success()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_correct.xml";
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(1 == result, "Success");
}

void tests::getAllContentFromXml_zero()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_zero.xml";
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(0 == result, "Success");
}

void tests::getAllContentFromXml_person()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_person.xml";
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(0 == result, "Success");
}

//void tests::getInputXmlDatasToStructs_success()
//{
//    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_person.xml";  // Расположение входного .xml файла
//    QFile inputXml(locationXml);

//    department rootDepartment;
//    getAllContentFromXml(inputXml, rootDepartment);

//    if (!inputXml.open(QIODevice::ReadOnly))    // Проверяем, возможно ли открыть .xml файл для чтения
//        qDebug() << "Error: can't read .xml file";  // Вывести в консоль ошибку, что файл открыть невозможно

//    QByteArray buff = inputXml.readAll();
//    QDomDocument doc;


//    QDomElement root = doc.documentElement();

//    // Первая вложенная нода
//    QDomNode record_node = root.firstChild();

//    // Список подчиненных сотрудников
//    QList<employee> childEmployees;

//    // Список подчиненных подразделений
//    QList<department> childDepartments;

//    QList<employee> expected_childEmployees({1111, "Директор", "ООО TechLab"});
//    getInputXmlDatasToStructs(record_node, root, childEmployees, childDepartments);

////    QVERIFY2(0 == result, "Success");
//}

