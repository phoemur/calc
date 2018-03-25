#ifndef CALCULATOR_MAIN_HEADER
#define CALCULATOR_MAIN_HEADER

#include <QMainWindow>
#include <memory>

#include "ui_MainWindow.h"

namespace Ui {
    class MainWindow; // forward declaration
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    std::unique_ptr<Ui::MainWindow> ui;
    
public:
    MainWindow(QMainWindow* parent = nullptr);
    
private slots:
    void b1();
    void b2();
    void b3();
    void b4();
    void b5();
    void b6();
    void b7();
    void b8();
    void b9();
    void b0();
    void b_dot();
    void b_result();
    void b_l_bracket();
    void b_r_bracket();
    void b_power();
    void b_div();
    void b_mul();
    void b_plus();
    void b_min();
    void b_modulo();
    
private:
    void put_text(const char* t);
  
}; // class MainWindow

#endif // CALCULATOR_MAIN_HEADER