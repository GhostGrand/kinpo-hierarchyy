#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class tests : public QObject
{
    Q_OBJECT
public:
    explicit tests(QObject *parent = nullptr);

private slots:
    void getInputID_test_success();
    void getInputID_test_zero();
    void getInputID_test_space();
    void getInputID_test_empty();
    void getInputID_test_word();
    void getInputID_test_two_value();
    void getInputID_test_word_and_value();
    void getInputID_test_complex();

    void getAllContentFromXml_success();
    void getAllContentFromXml_zero();
    void getAllContentFromXml_person();
//    void getInputXmlDatasToStructs_success();
};

#endif // TESTS_H
