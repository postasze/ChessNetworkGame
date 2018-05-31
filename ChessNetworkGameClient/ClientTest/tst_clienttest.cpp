#include <QString>
#include <QtTest>

class ClientTestTest : public QObject
{
    Q_OBJECT

public:
    ClientTestTest();

private Q_SLOTS:
    void testCase1();
};

ClientTestTest::ClientTestTest()
{
}

void ClientTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ClientTestTest)

#include "tst_clienttest.moc"
