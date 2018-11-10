#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QTimer>
#include <QStatusBar>

#include <QMessageBox>

#define IP "192.168.4.1"

#define HEIGHT 8
#define WIDTH 32

QString toString(const Model model){
    QString s;
    for (int i = 0; i < HEIGHT; ++i){
        for (int j = 0; j < WIDTH; ++j){
            s += ((model[i][j] != 0) ? "1" : "0");
        }
    }
    return s;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->show();

    this->setWindowTitle("Controller");

    ui->runButton->setEnabled(true);

    m_model = ui->canvas->getModel();

    connect(ui->clearButton, &QPushButton::pressed, ui->canvas, &PaletteEditor::clear);
    connect(ui->runButton, &QPushButton::pressed, this, [this](){sendRequest(Image);});
    connect(ui->playSnake, &QPushButton::pressed, this, [this](){sendRequest(Snake);});
    connect(ui->runnerButton, &QPushButton::pressed, this, [this](){sendRequest(Runner);});
    connect(ui->autoSnake, &QPushButton::pressed, this, [this](){sendRequest(SnakeAuto);});
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sendRequest(RequestType t)
{
    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

    QString request;

    switch(t){
    case Image:
    {
        m_model = ui->canvas->getModel();
        QString img1 = toString(m_model);
        request = QString("http://")+IP+"/?img=" + img1;
        break;
    }
    case Snake:
    {
        request = QString("http://")+IP+"/?snakestart=0";
        break;
    }
    case SnakeAuto:
    {
        request = QString("http://")+IP+"/?snakeauto=0";
        break;
    }
    case Speed:
    {
        request = QString("http://")+IP+"/?speed=100";
        break;
    }
    case Text:
    {
        request = QString("http://")+IP+"/?text=Hello%20";
        break;
    }
    case Runner:
    {
        request = QString("http://")+IP+"/?runner=0";
        break;
    }
    }

    mgr->get(QNetworkRequest(QUrl(request)));
    qDebug() << request;
}

void MainWindow::onFinish(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();
    QString str(bts);
    qDebug() << "received" << str;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    int i = 0;
    switch(event->key())
    {
    case 83:
        i = 0;
        break;
    case 87:
        i=1;
        break;
    case 65:
        i=2;
        break;
    case 68:
        i=3;
        break;
    }

    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

    QString request = QString("http://")+IP+"/?button=" + QString::number(i);

    mgr->get(QNetworkRequest(QUrl(request)));
    qDebug() << request;
}
