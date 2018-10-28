#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QResizeEvent>


#include <vector>

//DONT DO IT, KIDS LIKE THIS
using namespace std;
using Model = vector<vector<bool>>;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum RequestType{
        Image,
        Snake,
        SnakeAuto,
        Text,
        Speed
    };

    void saveCurrent();
    void read();

    Q_SLOT void sendRequest(RequestType t);

    Q_SLOT void onFinish(QNetworkReply *rep);
protected:

    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:

    Ui::MainWindow *ui;

    Model m_model;
};

#endif // MAINWINDOW_H
