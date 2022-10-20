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

void tests::getInputXmlDatasToStructs_success()
{
    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_correct2.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    department rootDepartment;
    getAllContentFromXml(inputXml, rootDepartment);
    inputXml.close();
    if (!inputXml.open(QIODevice::ReadOnly))    // Проверяем, возможно ли открыть .xml файл для чтения
        qDebug() << "Error: can't read .xml file";  // Вывести в консоль ошибку, что файл открыть невозможно

    QByteArray buff = inputXml.readAll();
    QDomDocument doc;

    // Проверить, что .xml файл не пустой
    if (doc.setContent(buff) == false)
    {
        qDebug() << "bad XML-file: setContent";
    }
    // Проверить, что на самом верхнем уровне находится подразделение
    QDomElement root = doc.documentElement();
    if (root.tagName() != "Department")
    {
        qDebug() << "bad XML-file: tagname() != Department";
    }

    // Первая вложенная нода
    QDomNode record_node = root.firstChild();

    // Список подчиненных сотрудников
    QList<employee> childEmployees;

    // Список подчиненных подразделений
    QList<department> childDepartments;

    QList<employee> expected_childEmployees;
    expected_childEmployees.append((employee){"Директор", 1111, "ООО TechLab"});

    QList<department> expected_childDepartment;
    expected_childDepartment.append((department){1, "ТП", QList<employee>({
                                                     (employee){"Александров А. Г.", 1, "ТП"},
                                                     (employee){"Гончаров Л. Г.", 2, "ТП"},
                                                     (employee){"Понасенков Г. В.", 3, "ТП"}
                                                 }),
                                     QList<department>({
                                                     (department){8, "Группа тестировщиков", QList<employee>({
                                                        (employee){"Григорьев С. М.", 8, "Группа тестировщиков"},
                                                        (employee){"Павлова А. А.", 9, "Группа тестировщиков"},
                                                        (employee){"Григорьева. В. В.", 10, "Группа тестировщиков"},
                                                 }), QList<department>()}
                                                     })
                                    });
    expected_childDepartment.append((department){5, "Разработка", QList<employee>({
                                                     (employee){"Буров П. Г.", 4, "Разработка"},
                                                     (employee){"Исаков В. В.", 5, "Разработка"},
                                                     (employee){"Шарапов Е. П.", 6, "Разработка"}
                                                 }),
                                                 QList<department>()});
    expected_childDepartment.append((department){7, "Бухгалтерия", QList<employee>({
                                                     (employee){"Антонов Е. В.", 7, "Бухгалтерия"}
                                                 }),
                                                 QList<department>()});

    getInputXmlDatasToStructs(record_node, root, childEmployees, childDepartments);

    for (int i = 0; i < expected_childEmployees.size(); i++)
    {
        QVERIFY2(expected_childEmployees[i].departmentAffiliation == childEmployees[i].departmentAffiliation, "Success");
        QVERIFY2(expected_childEmployees[i].fioEmployee == childEmployees[i].fioEmployee, "Success");
        QVERIFY2(expected_childEmployees[i].idEmployee == childEmployees[i].idEmployee, "Success");
    }

    for (int i = 0; i < expected_childDepartment.size(); i++)
    {
        QVERIFY2(expected_childDepartment[i].idHead == childDepartments[i].idHead, "Success");
        QVERIFY2(expected_childDepartment[i].departmentName == childDepartments[i].departmentName, "Success");

        for (int j = 0; j < expected_childDepartment[i].employeesOfDepartment.size(); j++)
        {
            QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].departmentAffiliation == childDepartments[i].employeesOfDepartment[j].departmentAffiliation, "Success");
            QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].fioEmployee == childDepartments[i].employeesOfDepartment[j].fioEmployee, "Success");
            QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].idEmployee == childDepartments[i].employeesOfDepartment[j].idEmployee, "Success");
        }

        for (int j = 0; j < expected_childDepartment[i].childDepartments.size(); j++)
        {
            QVERIFY2(expected_childDepartment[i].childDepartments[j].idHead == childDepartments[i].childDepartments[j].idHead, "Success");
            QVERIFY2(expected_childDepartment[i].childDepartments[j].departmentName == childDepartments[i].childDepartments[j].departmentName, "Success");

            for (int j = 0; j < expected_childDepartment[i].employeesOfDepartment.size(); j++)
            {
                QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].departmentAffiliation == childDepartments[i].employeesOfDepartment[j].departmentAffiliation, "Success");
                QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].fioEmployee == childDepartments[i].employeesOfDepartment[j].fioEmployee, "Success");
                QVERIFY2(expected_childDepartment[i].employeesOfDepartment[j].idEmployee == childDepartments[i].employeesOfDepartment[j].idEmployee, "Success");
            }
        }
    }

//    QVERIFY2(0 == result, "Success");
}

void tests::getOutputStrings_success()
{
    department rootDepartment;

    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_correct.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_correct.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    getAllContentFromXml(inputXml, rootDepartment);

    // Получить подразделения, подчиняющиеся данному сотруднику
    QList<QString> outputStrings;

    int rootEmployeeId = getInputID(inputTxt);

    getOutputStrings(rootEmployeeId, rootDepartment, outputStrings);

    QList<QString> expected_output;
    expected_output.append("Руководитель ТП: Александров А. Г.");
    expected_output.append("ТП:");
    expected_output.append("    Гончаров Л. Г.");
    expected_output.append("    Понасенков Г. В.");
    expected_output.append("Группа тестировщиков:");
    expected_output.append("    Григорьев С. М.");
    expected_output.append("    Павлова А. А.");
    expected_output.append("    Григорьева. В. В.");

    QVERIFY2(expected_output == outputStrings, "Success");
}

void tests::getDepartmentsStrings_success()
{
    department rootDepartment;

    QString locationTxt = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\id_correct.txt";  // Расположение входного .txt файла
    QFile inputTxt(locationTxt);

    QString locationXml = QDir::currentPath() + "..\\..\\kinpo-hierarchyy\\tests\\xml_correct.xml";  // Расположение входного .xml файла
    QFile inputXml(locationXml);

    getAllContentFromXml(inputXml, rootDepartment);

    // Получить подразделения, подчиняющиеся данному сотруднику
    QList<QString> outputStrings;

    int rootEmployeeId = getInputID(inputTxt);

    for (int i = 0; i < rootDepartment.childDepartments.count(); i++)
    {
        getDepartmentsStrings(rootEmployeeId, rootDepartment.childDepartments[i], outputStrings);
    }

    QList<QString> expected_output;
    expected_output.append("ТП:");
    expected_output.append("    Гончаров Л. Г.");
    expected_output.append("    Понасенков Г. В.");
    expected_output.append("Группа тестировщиков:");
    expected_output.append("    Григорьев С. М.");
    expected_output.append("    Павлова А. А.");
    expected_output.append("    Григорьева. В. В.");
    expected_output.append("Разработка:");
    expected_output.append("    Буров П. Г.");
    expected_output.append("    Исаков В. В.");
    expected_output.append("    Шарапов Е. П.");
    expected_output.append("Бухгалтерия:");
    expected_output.append("    Антонов Е. В.");

    QVERIFY2(expected_output == outputStrings, "Success");
}
