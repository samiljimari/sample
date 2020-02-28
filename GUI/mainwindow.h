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
    void on_treeView_activated(const QModelIndex &index);

    void on_listView_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_listView_2_activated(const QModelIndex &index);

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_listView_2_doubleClicked(const QModelIndex &index);

    void on_listView_2_clicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

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

};

#endif // MAINWINDOW_H
