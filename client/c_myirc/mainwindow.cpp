#include <QInputDialog>
#include <QMessageBox>
#include <cstring>
#include <regex>
#include <iostream>
#include <exception>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ApiConnection.hpp"

static const std::string REGEX = "((25[0-5]|2[0-4][0-9]|[01]?[0-9]{1,2})\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]{1,2})";

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    server(), timer(this)
{
	ui->setupUi(this);
	this->setWindowTitle("My IRC");
	this->setFixedSize(QSize(1280, 720));
	MainWindow::connect(ui->connectBtn, SIGNAL(clicked()), this,
		SLOT(clickConnectBtn()));
    //connect(&this->timer, SIGNAL(timeout()), this, SLOT(fillResultText()));
    this->timer.start(1000);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::clickConnectBtn()
{
	try {
		QString connect = QInputDialog::getText(this, "Connection",
			"Please, provide an address IP and a PORT for "
   "connection\nsyntax :\n\t127.0.0.1:6667");
		std::string connectString = connect.toStdString();
		auto pos = strstr(connectString.c_str(), ":");
		std::string ip = connectString.substr(0,
			pos - connectString.c_str());
		std::string port = connectString.substr(
			pos + 1 - connectString.c_str(), connectString.size());
		QMessageBox::information(this, "args",
			QString::fromStdString(ip + "\n" + port));
		if (std::stoi(port) <= 65535 &&
			std::regex_match(ip, std::regex(REGEX))) {
			QMessageBox::information(this, "args",
				"The IP address and the PORT are Valid.");
            this->server.connectToServer(ip, std::stoi(port));
			QString nick = QInputDialog::getText(this, "Nickname",
				"what is your nickname?\n");
            this->server.sendCommand(std::string("nick " + nick.toStdString()));
			//todo : demander le nick a l'utilisateur puis l'envoyer au serveur
			//todo : check le retour du serveur, si il y en a un.
		}
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
