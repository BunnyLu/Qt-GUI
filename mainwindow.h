#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsView>
#include <string>
#include <QString>
#include <QSaveFile>
#include <QLabel>
#include <QImage>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void RefreshFilename();
    Ui::MainWindow *ui;
    QGraphicsScene scene;

    void loadimage();

    QString filename;
    QString pathvariant;
    int index;
    int labelarray[400];  //set1 = 100; set7 = 400; other set = 500
    QString la;

    QLabel mylabel;
    QLabel *imagelabel;

    QImage image;
    QImage im;
    QGraphicsPixmapItem *ImageItem;

    QKeyEvent *event;
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();  //0
    void on_pushButton_2_clicked(); //1
    void on_pushButton_3_clicked();  //2 or more

    void on_pushButton_4_clicked();  //previous
    void on_pushButton_5_clicked();  //next

    void on_pushButton_6_clicked();  //save label in file
    void on_pushButton_7_clicked();//set up

private:

};

#endif // MAINWINDOW_H
