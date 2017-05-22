#ifndef VERTEX_H
#define VERTEX_H
#include <QObject>
#include <QVector3D>

class Vertex : public QVector3D
{
  // Q_OBJECT
  // id = 1 to setId id to getId
  // Q_PROPERTY(int id READ id WRITE setId)

public:
  Vertex();
  Vertex(int id, QVector3D vertex);
  Vertex(int id, float x, float y, float z);

  int id () { return mId; }
  void setId (int id) { mId = id; }

private:
  int mId;
};

#endif // VERTEX_H
