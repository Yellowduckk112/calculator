#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mybutton.h"
#include "painter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double calculate(bool op=0);
    friend double painter::calculate(double a);

private slots:
    void on_Bu1_clicked();

    void on_Bu2_clicked();

    void on_Bu3_clicked();

    void on_Bu4_clicked();

    void on_Bu5_clicked();

    void on_Bu6_clicked();

    void on_Bu7_clicked();

    void on_Bu8_clicked();

    void on_Bu9_clicked();

    void on_Bu0_clicked();

    void on_Bu10_clicked();

    void on_Bu12_clicked();

    void on_Bu13_clicked();

    void on_Bu15_clicked();

    void on_Bu14_clicked();

    void on_Bu16_clicked();

    void on_pushButton_clicked();

    void on_Esc_clicked();

    void on_left_button_clicked();

    void on_right_button_clicked();

    void on_pushButton_2_clicked();

    void on_Save_1_clicked();

    void on_Save_2_clicked();

    void on_Save_3_clicked();

    void on_Save_4_clicked();

    void on_sin_button_clicked();

    void on_cos_button_clicked();

    void on_tan_button_clicked();

    void on_arcsin_button_clicked();

    void on_arccos_button_clicked();

    void on_arctan_button_clicked();

    void on_ln_button_clicked();

    void on_pi_button_clicked();

    void on_e_button_clicked();

    void on_drawbutton_clicked();

    void on_x_button_clicked();

    void on_pushButton_3_clicked();

    void on_mod_Button_clicked();

private:
    Ui::MainWindow *ui;
    QString lable;
    static QString lable2;
    long long ans;
    bool calculate_end,which;
};

#endif // MAINWINDOW_H
