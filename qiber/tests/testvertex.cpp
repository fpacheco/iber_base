#include <QtTest>
#include <QObject>
#include "../vertex.h"

class TestVertex : public QObject
{
  Q_OBJECT
public:
  explicit TestVertex(QObject *parent = 0);
signals:
  //Nada
public slots:
  //Nada
private slots:
  void initTestCase();
  void cleanupTestCase();
  void create();
};

TestVertex::TestVertex(QObject *parent) : QObject(parent)
{

}

void TestVertex::initTestCase()
{

}

void TestVertex::cleanupTestCase()
{

}

void TestVertex::create()
{
  Vertex *ver1 = new Vertex();
  ver1->setId(1);
  QVERIFY(ver1->id() == 1);

  ver1->setId(2);
  QVERIFY(ver1->id() == 2);

  Vertex *ver2 = new Vertex(3,100.001,200.001,300.001);
  QVERIFY(ver2->id() == 3);
  QCOMPARE(ver2->x(), 100.001);
  QCOMPARE(ver2->y(), 200.001);
  QCOMPARE(ver2->z(), 300.001);
}

QTEST_MAIN(TestVertex)
#include "testvertex.moc"
