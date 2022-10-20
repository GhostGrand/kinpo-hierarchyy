#ifndef HEADER_H
#define HEADER_H

#endif // HEADER_H
#include <QString>
#include <QList>
#include <QFile>
#include <QDomDocument>


/*!
 * Структура сотрудника
 */
struct employee
{
   QString fioEmployee;             /*! ФИО сотрудника */
   int idEmployee;                  /*! ID сотрудника */
   QString departmentAffiliation;   /*! Принадлежность сотрудника к подразделению */
};

/*!
 * Структура подразделения (отдела)
 */
struct department
{
    int idHead;                             /*! ID директора подразделения */
    QString departmentName;                 /*! Название подразделения */
    QList<employee> employeesOfDepartment;  /*! Список сотрудников подразделения */
    QList<department> childDepartments;     /*! Список нижестоящих подразделений */
};

/*!
 * Проверка входных данных (.xml и .txt файлов)
 *
 * @param[in] locationXml   расположение входного .xml файла
 * @param[in] inputXml      входной .xml файл
 * @param[in] locationTxt   расположение входного .txt файла
 * @param[in] inputTxt      входной .txt файл
 * @return                  true - входные данные корректные, false - входные данные некорректные
 */
bool testInputDatas(QString& locationXml, QFile& inputXml, QString& locationTxt, QFile& inputTxt);

/*!
 * Вывод ошибок входных данных
 *
 * @param[in] error номер ошибки
 */
void outputError(int error);

/*!
 * Получение входного ID сотрудника
 *
 * @param[in] inputTxt входной .txt файл
 * @return             ID сотрудника
 */
int getInputID(QFile& inputTxt);

/*!
 * Получение .xml файла и запись данных в массивы структур
 *
 * @param[in] record_node       текущая рассматриваемая нода
 * @param[in] root              вышестоящая нода
 * @param[in] employeeList      массив структур employeeList
 * @param[in] departmentList    массив структур departmentList
 */
void getInputXmlDatasToStructs(QDomNode record_node, QDomNode root, QList<struct employee> &employeeList, QList<struct department> &departmentList);    // сюда заносить ноду

/*!
 * Получить все данные из .xml файла
 *
 * @param[in] inputXml          входной .xml файл
 * @param[in] rootDepartment    самое вышестоящее подразделение
 * @return                      true - .xml файл корректный, false -.xml файл некорректный
 */
bool getAllContentFromXml(QFile& inputXml, department &rootDepartment);

/*!
 * Закрыть входные .xml и .txt файлы
 *
 * @brief closeInputDatas
 * @param[in] inputXml      входной .xml файл
 * @param[in] inputTxt      входной .txt файл
 */
void closeInputDatas(QFile& inputXml, QFile& inputTxt);

/*!
 * Получить результат и записать его в список строк
 *
 * @param[in] rootEmployeeId    ID сотрудника рассматриваемого подразделения
 * @param[in] rootDepartment    текущее рассматриваемое подразделение
 * @param[out] outputStrings    список получившихся строк
 */
void getOutputStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings);

/*!
 * Получить данные о внутренних подразделениях строками
 *
 * @param[in] rootEmployeeId    текущий сотрудник
 * @param[in] rootDepartment    текущее рассматриваемое подразделение
 * @param[out] outputStrings    список получившихся строк
 */
void getDepartmentsStrings(int rootEmployeeId, department &rootDepartment, QList<QString> &outputStrings);

/*!
 * Записать получившиеся строки в выходной .txt файл
 *
 * @param[in] filePath      расположение .txt файла
 * @param[in] outputStrings получившиеся строки
 */
void writeOutputFile(QString filePath, QList<QString> &outputStrings);
