#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QGraphicsScene>

class Scene : public QGraphicsScene {
public:
  Scene(QObject *parent = Q_NULLPTR, QString epsg="epsg:3221");

private:
  QString mEPSG;

};

#endif // SCENE_H
