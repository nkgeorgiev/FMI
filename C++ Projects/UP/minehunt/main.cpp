#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>

#include "button.h"
#include "grid.h"
#include "DialogDifficulty.h"


vector<vector<int> > generateMines(int x, int y,int numMines, vector<vector<int> > grid){
    int a, b;
    grid[x][y]=0;
    srand(time(NULL));
    while (numMines>0){
        a=rand() % grid.size();
        b=rand() % grid[0].size();
        if(!grid[a][b]&& (a!=x||b!=y)) {
            grid[a][b]=1;
            //cout<<"MINE "<<a<<' ' << b<<endl;
            numMines--;
        }
    }
    return grid;
}


int main(int argc, char *argv[])
{
    int m=8;
    int n=8;
    int x=10;

    std::vector<std::vector<int> > grid(20,std::vector<int>(40,0));
    //grid=generateMines(0,0,x,grid);
    QApplication a(argc, argv);
    MainWindow *w=new MainWindow();
    QWidget *centralWidget=new QWidget();
    centralWidget->setWindowIcon(QIcon("mine_logo.gif"));
    Button *button[20][40];
    //QButtonGroup *buttons=new QButtonGroup();
    //QGridLayout *gridLayout=new QGridLayout();
   //gridLayout->setHorizontalSpacing(0);
    //gridLayout->setVerticalSpacing(0);
    Grid *minefield=new Grid(m,n,x,&grid,button,centralWidget);

    QDialog *diff=new QDialog();
    Ui_Dialog *dialog=new Ui_Dialog();
    dialog->setupUi(diff);
    diff->show();
    QObject::connect(dialog->buttonGroup,SIGNAL(buttonClicked(int)),minefield,SLOT(chooseDifficulty(int)));
    QObject::connect(dialog->buttonBox,SIGNAL(accepted()),minefield,SLOT(setGrid()));

    minefield->setGrid();

    //w->setCentralWidget(centralWidget);
    //w->show();
    
    return a.exec();
}
