#include "tests.h"
#include <QtTest/QTest>
#include "header.h"

tests::tests(QObject *parent)
    : QObject(parent)
{

}

void tests::getInputID_test_success()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_correct.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(1 == result, "Success");
}

void tests::getInputID_test_zero()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_zero.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_space()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_space.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getInputID_test_word()
{
    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_incorrect_word.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    int result = getInputID(inputTxt);

    QVERIFY2(0 == result, "Success");
}

void tests::getAllContentFromXml_success()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_correct.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(1 == result, "Success");
}

void tests::getAllContentFromXml_zero()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_zero.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(0 == result, "Success");
}

void tests::getAllContentFromXml_person()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_person.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    department rootDepartment;
    int result = getAllContentFromXml(inputXml, rootDepartment);

    QVERIFY2(0 == result, "Success");
}
