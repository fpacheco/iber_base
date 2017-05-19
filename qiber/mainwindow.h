#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *mPrePScene;
    QGraphicsScene *mPostPScene;
    QGraphicsEllipseItem *mEllipse;
    QGraphicsRectItem *mRectangle;
    QGraphicsTextItem *mText;

};

#endif // MAINWINDOW_H
