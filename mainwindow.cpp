#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <QTextEdit>
#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>

#pragma execution_character_set("utf-8")

using namespace std;
namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
}

list <string> file(string files, string _files)
{
	list <string> listFiles;
		for (const auto & f1 : fs::directory_iterator(files))
	{
		for (const auto & f2 : fs::directory_iterator(_files))
		{
			auto name = f1.path();
			auto _name = f2.path();

			ifstream fin1(f1.path(), ios::binary);
			ifstream fin2(f2.path(), ios::binary);
			if (fin1&&fin2)
			{
				char ch1, ch2;
				bool result = true;
				while (fin1.get(ch1) && fin2.get(ch2))
				{
					if (ch1 != ch2)
					{
						result = false;
						break;
					}
				}
				if (result)
				{
					string file = name.filename().string() + "  и  " + _name.filename().string();
					listFiles.push_back(file);
				}
			}
		}
	}
	return listFiles;
}

void MainWindow::on_pushButton_clicked()
{
   	QString str = QFileDialog::getExistingDirectory(0, "Выбор папки", "");
	ui->lineEdit->setText(str);
}
void MainWindow::on_pushButton_2_clicked()
{
	QString _str = QFileDialog::getExistingDirectory(0,"Выбор папки", "");
	ui->lineEdit_2->setText(_str);
}
void MainWindow::on_pushButton_3_clicked()
{
	
	ui->resultText->clear();
	string dir, _dir;
	dir = ui->lineEdit->text().toStdString();
	_dir = ui->lineEdit_2->text().toStdString();
	if (dir.empty() || _dir.empty())
		ui->resultText->setText("Папка не выбрана");
	else
	{
		auto listFiles = file(dir, _dir);
		QList <QString> _listFiles;
		for (const std::string& s : listFiles)
		{
			_listFiles.append(QString::fromStdString(s));
		}
		if (listFiles.empty()) ui->resultText->append("Индентичные файлы не обнаружены");
		else {
			ui->resultText->append("Индентичные файлы:");
			foreach(QString value, _listFiles)
			{
				ui->resultText->append(value);
			}
		}
	}
}
MainWindow::~MainWindow()
{
	delete ui;
}

