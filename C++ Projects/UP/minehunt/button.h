#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(int id, QWidget *parent = 0);
    
signals:
    void rightClick(int);
    void leftClick(int);

public slots:

private slots:
    void onRightClick(int);
    void onLeftClick(int);
    void mousePressEvent(QMouseEvent *e);


private:
    int id;


    
};

#endif // BUTTON_H
