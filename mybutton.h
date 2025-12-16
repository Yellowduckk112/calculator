#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton: public QPushButton{
    Q_OBJECT
private:
    bool Clicked;
public:
    MyButton(QWidget* parent = nullptr)
        : QPushButton(parent) {
        Clicked= 0;
    }
    void Set_Clicked(bool a);
    bool Get_Clicked();
};

#endif // MYBUTTOM_H
