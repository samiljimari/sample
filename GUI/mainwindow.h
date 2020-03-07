#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QtGui>
#include <QtCore>
#include <QFileSystemModel>
#include <QStandardItem>
#include <QGraphicsScene>
#include <QFileInfo>

class QPushButton;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_11_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void populateScene();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;
    QStringListModel *stringmodel;

};

#endif // MAINWINDOW_H
