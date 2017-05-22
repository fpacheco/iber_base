#include "vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(int id, QVector3D vertex)
{
  mId = id;
  this->setX(vertex.x());
  this->setY(vertex.y());
  this->setZ(vertex.z());
}

Vertex::Vertex(int id, float x, float y, float z)
{
  mId = id;
  this->setX(x);
  this->setY(y);
  this->setZ(z);
}
