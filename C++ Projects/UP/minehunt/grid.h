#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <ctime>
#include <iostream>
#include <QMessageBox>
#include <stdio.h>
#include <QIcon>
#include <QSize>
#include <QStyle>
#include <QMouseEvent>
#include <QSignalMapper>
#include <QGridLayout>
#include <QAbstractButton>
#include <QDebug>
#include <QGridLayout>
#include <vector>
#include "button.h"
using namespace std;

class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(int m, int n, int x, vector<vector<int> > *grid, Button *buttons[20][40], QWidget *centralWidget, QObject *parent = 0);
    
signals:
    
public slots:
    void openMine(int id);
    vector<vector<int> > generateMines(int x, int y,int numMines, vector<vector<int> > grid);
    int numberOfMines(int x, int y,std::vector<std::vector<int> > *grid);
    void openZeroes(int i,int j,std::vector<std::vector<int> >  *grid);
    void setGame();
    void flag(int id);
    void chooseDifficulty(int);
    void setGrid();
    void setColor(int i,int j,QString text);


    
private:
    int m,n,x;
    vector<vector<int> > *grid;
    Button *(*button)[40];
    QWidget *centralWidget;
};

#endif // GRID_H
