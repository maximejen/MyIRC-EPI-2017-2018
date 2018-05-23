#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTimer>
#include "ApiConnection.hpp"

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
    ApiConnection server;
    QTimer timer;
    std::string actualChannel;
    std::vector<std::string>& explode(const std::string& str);

private slots:
    void clickConnectBtn();
    void refreshChannelsList();
    void leaveChannel();
    void refreshPeopleList();
};

#endif // MAINWINDOW_HPP
