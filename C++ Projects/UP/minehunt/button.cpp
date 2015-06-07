#include "button.h"
#include <iostream>
#include <QMouseEvent>
#include <QMessageBox>
using namespace std;
Button::Button(int id, QWidget *parent) :
    QPushButton(parent)
{
    this->id=id;
}


void Button::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClick(id);
    else if(e->button()==Qt::LeftButton)
        emit leftClick(id);
}

void Button::onLeftClick(int x){
    std::cout<<x<<" Left Click"<<std::endl;
}

void Button::onRightClick(int x){
    std::cout<<"Right click"<<std::endl;
}



