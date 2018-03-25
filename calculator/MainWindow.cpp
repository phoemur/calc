#include <QString>
#include <QDebug>
#include <sstream>

#include "MainWindow.h"
#include "parser.h"

MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent), ui{std::make_unique<Ui::MainWindow>()}
{
    ui->setupUi(this);
}

void MainWindow::put_text(const char* t)
{
    QString text = ui->lineEdit->text();
    text.push_back(t);
    ui->lineEdit->setText(text);
}

void MainWindow::b0()          {put_text("0");}
void MainWindow::b1()          {put_text("1");}
void MainWindow::b2()          {put_text("2");}
void MainWindow::b3()          {put_text("3");}
void MainWindow::b4()          {put_text("4");}
void MainWindow::b5()          {put_text("5");}
void MainWindow::b6()          {put_text("6");}
void MainWindow::b7()          {put_text("7");}
void MainWindow::b8()          {put_text("8");}
void MainWindow::b9()          {put_text("9");}
void MainWindow::b_dot()       {put_text(".");}
void MainWindow::b_l_bracket() {put_text("(");}
void MainWindow::b_r_bracket() {put_text(")");}
void MainWindow::b_power()     {put_text("^");}
void MainWindow::b_div()       {put_text("/");}
void MainWindow::b_mul()       {put_text("*");}
void MainWindow::b_plus()      {put_text("+");}
void MainWindow::b_min()       {put_text("-");}
void MainWindow::b_modulo()    {put_text("%");}

void MainWindow::b_result() 
{
    auto text = ui->lineEdit->text().toStdString();
    std::istringstream ss {text};
    try {
        Parser::Expression expr(ss);
        double result = expr.getValue();
        //qDebug() << result << "\n";
        ui->lineEdit->setText(QString::number(result, 'g', 15));
    }
    catch (std::exception& e) {
        text = e.what();
        ui->lineEdit->setText(QString().fromStdString(text));
    }
}