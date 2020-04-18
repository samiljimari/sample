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
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class QPushButton;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsItem;

class SizeGripItem : public QGraphicsItem
{
    private:
        enum
        {
            Top         = 0x1,
            Bottom      = 0x2,
            Left        = 0x4,
            TopLeft     = Top | Left,
            BottomLeft  = Bottom | Left,
            Right       = 0x8,
            TopRight    = Top | Right,
            BottomRight = Bottom | Right
        };

        class HandleItem : public QGraphicsRectItem
        {
            public:
                HandleItem(int positionFlags, SizeGripItem* parent);
                int positionFlags() const;

            protected:
                virtual QVariant itemChange(GraphicsItemChange change,
                                            const QVariant &value);

            private:
                QPointF restrictPosition(const QPointF& newPos);

                int positionFlags_;
                SizeGripItem* parent_;
        };

    public:
        class Resizer
        {
            public:
                virtual void operator()(QGraphicsItem* item,
                                        const QRectF& rect) = 0;
        };

        SizeGripItem(Resizer* resizer = 0, QGraphicsItem* parent = 0);
        virtual ~SizeGripItem();
        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter,
                           const QStyleOptionGraphicsItem* option,
                           QWidget* widget = 0);
        void setTopLeft(const QPointF& pos);
        void setTop(qreal y);
        void setTopRight(const QPointF& pos);
        void setRight(qreal x);
        void setBottomRight(const QPointF& pos);
        void setBottom(qreal y);
        void setBottomLeft(const QPointF& pos);
        void setLeft(qreal x);

    private:
        void doResize();
        void updateHandleItemPositions();

        QList<HandleItem*> handleItems_;
        QRectF rect_;
        Resizer* resizer_;
};

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

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_label_2_linkActivated(const QString &link);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsPolygonItem *triangle;
    QGraphicsRectItem *rectangle;
    QGraphicsPolygonItem *pentagon;
    QGraphicsPolygonItem *hexagon;
    QGraphicsPolygonItem *heptagon;
    QGraphicsPolygonItem *octagon;
    QPixmap image;
    QImage  *imageObject;
    QObject sender;
    QStringList *model;
    QStringListModel *stringmodel;

};

#endif // MAINWINDOW_H
