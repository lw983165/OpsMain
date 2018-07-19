#include "Canvas.hpp"
#include "Group.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include "SelectionTool.hpp"
#include "DrawCircleTool.hpp"
#include "DrawRectangleTool.hpp"
#include "DrawLineTool.hpp"
#include "PropertyColorButton.hpp"
#include "PropertySpinBox.hpp"
#include "GlobalDrawProperties.hpp"
#include "MainCommandStack.hpp"
#include "ActiveSelection.hpp"
#include "DrawCommand.hpp"
#include "DeleteSelectedCommand.hpp"
#include "SendBackwardCommand.hpp"
#include "BringForwardCommand.hpp"
#include "BringToFrontCommand.hpp"
#include "SendToBackCommand.hpp"
#include "FileReaderFactory.hpp"
#include "FileWriterFactory.hpp"
#include "ValueChangeTool.h"
#include "ValueChangeEvent.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QFileInfo>
#include <cassert>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMenu>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_canvas = new Canvas(ui->container);
    m_canvas->setGeometry(ui->container->geometry());

    m_selectionTool = std::unique_ptr<SelectionTool>
            (new SelectionTool(m_canvas));
    m_canvas->setActiveTool(m_selectionTool.get());

    QMenu *menu=new QMenu();
    menu->addAction(tr("1"));
    menu->addAction(tr("2"));
    menu->addAction(tr("3"));
    ui->toolButton_22->setMenu(menu);
    ui->toolButton_20->setMenu(menu);
    ui->toolButton_23->setMenu(menu);
    ui->toolButton_24->setMenu(menu);
    ui->toolButton_25->setMenu(menu);
    ui->toolButton_26->setMenu(menu);
    ui->toolButton_27->setMenu(menu);
    ui->toolButton_28->setMenu(menu);
    ui->toolButton_31->setMenu(menu);
    ui->toolButton_32->setMenu(menu);
    ui->toolButton_34->setMenu(menu);
    ui->toolButton_35->setMenu(menu);
    ui->pushButton->setStyleSheet("background-color: rgb(255, 0, 0);color: black;");
    ui->pushButton_2->setStyleSheet("background-color: rgb(0, 255, 0);color: black;");
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    ui->redlineEdit->setStyleSheet("background-color: rgb(0, 255, 0);color: white;border:0px;");
    ui->bluelineEdit->setStyleSheet("background-color: rgb(0, 0, 255);border:0px;");
    ui->redlineEdit_2->setStyleSheet("background-color: rgb(0, 255, 0);color: white;border:0px;");
    ui->bluelineEdit_2->setStyleSheet("background-color: rgb(0, 0, 255);border:0px;");
    ui->redlineEdit_3->setStyleSheet("background-color: rgb(0, 255, 0);color: white;border:0px;");
    ui->bluelineEdit_3->setStyleSheet("background-color: rgb(0, 0, 255);border:0px;");
    ui->redlineEdit_4->setStyleSheet("background-color: rgb(0, 255, 0);color: white;border:0px;");
    ui->bluelineEdit_4->setStyleSheet("background-color: rgb(0, 0, 255);border:0px;");
    ui->redlineEdit_5->setStyleSheet("background-color: rgb(0, 255, 0);color: white;border:0px;");
    ui->bluelineEdit_5->setStyleSheet("background-color: rgb(0, 0, 255);border:0px;");
    ui->pushButton_3->setFlat(true);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timerUpdate(void)
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->timelabel->setText(str);
}
void MainWindow::on_toolButton_20_triggered()
{
   // if (!promptUnsavedWork()) return;

    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Canvas"),QDir::currentPath(),tr("Json (*.json);;All File Types (*.*)"));

    if (fileName.isEmpty()) return;

    QString ext = QFileInfo(fileName).suffix();
    IFileReader *reader = FileReaderFactory::create(ext.toStdString());

    if (reader == nullptr) {
        QMessageBox::critical(this,"Unsupported file type",QString("I can't read *.%1 files.").arg(ext));
        return;
    }

    Group *readCanvas = new Group();
    reader->setup(readCanvas);


    bool canRead = reader->read(fileName.toStdString());
    //delete reader;
    if (canRead) {
        m_canvas->setMainGroup(readCanvas);
        ui->statusBar->showMessage(QString("Opened file: \"%1\"").arg(fileName));
    } else {
        delete readCanvas;
        QMessageBox::critical(this,
                              "File Read Error",
                              "I can't read this file ):");
        return;
    }


//    setCanvasFile(fileName);

    //resetCommandStack();

    m_canvas->repaint();
}
