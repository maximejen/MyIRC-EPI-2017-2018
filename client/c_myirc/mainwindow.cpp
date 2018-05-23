#include <QInputDialog>
#include <QMessageBox>
#include <QString>
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
	MainWindow::connect(this->ui->refreshChannelBtn, SIGNAL(clicked()),
		this,
		SLOT(refreshChannelsList()));
	MainWindow::connect(this->ui->quitChannelBtn, SIGNAL(clicked()), this,
		SLOT(leaveChannel()));
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
		if (std::stoi(port) <= 65535 &&
			std::regex_match(ip, std::regex(REGEX))) {
			this->server.connectToServer(ip, std::stoi(port));
			if (!this->server.isConnected()) {
				QMessageBox::information(this, "Error",
					"Cannot connect to server");
				return;
			}
			QString nick = QInputDialog::getText(this, "Nickname",
				"what is your nickname?\n");
			if (nick != "") {
				this->server.sendCommand(
					std::string(
						"nick " + nick.toStdString()));
			}
		}
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void MainWindow::refreshChannelsList()
{
	if (!this->server.isConnected())
        return;
    auto res = this->server.sendCommand("LIST");
	if (res != "") {
		auto tab = this->explode(res);
		if (tab.size() == 0)
			return;
		this->ui->channelList->clear();
		for (const auto &i : tab) {
			this->ui->channelList->addItem(
				QString::fromStdString(i));
		}
	}
}

void MainWindow::leaveChannel()
{
	if (!this->server.isConnected())
		return;
	if (this->actualChannel != "") {
        this->server.sendCommand("PART " + this->actualChannel);
		this->ui->channelText->append(QString::fromStdString(
			"Leaved channel #" + this->actualChannel));
		this->actualChannel = "";
	}
}

void MainWindow::refreshPeopleList()
{
	if (!this->server.isConnected())
		return;
	std::string res = this->server.sendCommand("USERS");
	//this->ui->peopleList->append(QString::fromStdString(res));
}

std::vector<std::string> &MainWindow::explode(const std::string &str)
{
	//std::string str("abc:def:ghi:jkl"); -> exemple
	std::istringstream split(str); // flux d'exatraction sur un std::string
	std::vector<std::string> tokens;
	for (std::string each ; std::getline(split, each,
		':') ; tokens.push_back(each));
	return tokens;
}
