#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <string.h>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainimage->setScene(&scene);
/*    index = 0;
    for (int i = 0; i<100; i++)
    {
        labelarray[i] = 0;
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


//.............. 3 classifier buttons ....................//
void MainWindow::on_pushButton_clicked()
{
    //save "0" in array labeled to image
    labelarray[index] = 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    //save "1" in array labeled to image
    labelarray[index] = 1;
}

void MainWindow::on_pushButton_3_clicked()
{
    //save "2" in array labeled to image
    labelarray[index] = 2;
}

 //don't use key, please click button for the first image (don't know why but the keyboard is sleeping for the first event)
void MainWindow::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_0 )
    {
        labelarray[index] = 0;
    }
    if( event->key() == Qt::Key_1 )
    {
        labelarray[index] = 1;
    }
    if( event->key() == Qt::Key_2 )
    {
        labelarray[index] = 2;
    }
    if( event->key() == Qt::Key_Enter)  //== click "next"
    {
      //  on_pushButton_5_clicked();   //can't call button func (only via slot?)
        qDebug()<<"label = "<<labelarray[index];
        if (index > 398)
        {
            index = 0;
            QLabel label;
            label.setText("ALL SET");
            label.show();
        }
        else
        {
            index = index + 1;
        }
        RefreshFilename();
        loadimage();
    }
}

//.............. funcs to change images ....................//
void MainWindow::RefreshFilename()
{
    filename = "";
    //clear it every time refresh it, otherwise would be "filename1 + filename2 + ..."
    QString s = QString::number(index);
/*    while(s.length()<2)
        s.insert(0,"0");*/
    if (s.length()<2)
    {
        s.insert(0,"00");
    }
    else if (s.length()<3)
    {
        s.insert(0,"0");
    }

    filename.append("C:/BubbleNet/set7/ml_bubbles_2018-04-26-170248-0");
    filename.append(s);
    filename.append(".jpg");
//    qDebug()<<"filename = "<<filename;

    mylabel.setText(filename);
    mylabel.show();
//    mylabel.clear();  //only clear text, side window still there
    //for some reason, label.show won't show all the elements in string

}

void MainWindow::on_pushButton_4_clicked()   //previous image
{
    if (index < 1)
    {
        index = 399;
        QLabel label;
        label.setText("Go back");
        label.show();
    }
    else
    {
        index = index - 1;
    }
//    qDebug()<<"index_new_p = "<<index;
    RefreshFilename();
    loadimage();
}

void MainWindow::on_pushButton_5_clicked()   //next image
{
    qDebug()<<"label = "<<labelarray[index];
    if (index > 398)
    {
        index = 0;
        QLabel label;
        label.setText("ALL SET");
        label.show();
    }
    else
    {
        index = index + 1;
    }
//    qDebug()<<"index_new_n = "<<index;
    RefreshFilename();
    loadimage();
}


//........................load new image...........................//
//void MainWindow::loadimage()
void MainWindow::loadimage()
{
    image = QImage(filename);
//     qDebug()<<"image = "<<image;
    im = image.scaled(500,500,Qt::KeepAspectRatio);

    scene.clear();
    ImageItem = scene.addPixmap(QPixmap::fromImage(im));
    scene.update();

}


//....................save label data to txt file.......................//
void MainWindow::on_pushButton_6_clicked()  //save button
{
    QString filename = "C:/BubbleNet/set7/set7Data.txt";
//    QString filename = "C:/BubbleNet/keyevent_test.txt";
    QFile file(filename);
    QString aa;
/*    if (file.exists() == true)
    {
        file.flush();
        file.resize(0);
    }*/
    if (file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        QTextStream stream(&file);
        int i = 0;
        while (i<index+1)
        {
            aa = QString::number(labelarray[i]);
            i++;
            la.append(aa);
        }
   //       stream << labelarray[i] << "\n"<<endl;
        stream << la <<endl;
          //this "\n" has to be here, otherwise the output would be wrong format when index>=50
          //probably because of QTextStream internal formatting limit
     }
}


//....................set up everything before labelling.......................//
void MainWindow::on_pushButton_7_clicked()   //set up button
{
    index = 0;
    for (int i = 0; i<400; i++)
    {
        labelarray[i] = 0;
    }
    RefreshFilename();
    loadimage();
}
