#include "grid.h"
#include "button.h"
#include "DialogWin.h"
#include "DialogLose.h"
#include "DialogDifficulty.h"


#include <vector>

#include <QMessageBox>
#include <stdio.h>
#include <QIcon>
#include <QSize>
#include <QMouseEvent>
#include <QGridLayout>
#include <QAbstractButton>
#include <QButtonGroup>

Grid::Grid(int m, int n, int x, vector<vector<int> > *grid,Button *button[20][40],QWidget *centralWidget, QObject *parent) :
    QObject(parent)
{
    this->m=m;
    this->n=n;
    this->x=x;
    this->grid=grid;
    this->button=button;
    this->centralWidget=centralWidget;
}

//QWidget *centralWidget=new QWidget();
QGridLayout *gridLayout=new QGridLayout();
QButtonGroup *buttons=new QButtonGroup();
int arr[20][40];
int cnt=0;
int id=0;


void Grid::flag(int id){
    int i=id/n;
    int j=id%n;
    if(arr[i][j]!=1){
        QAbstractButton *current=button[i][j];

        if(arr[i][j]!=2){
            arr[i][j]=2;
            current->setIcon(QIcon("flag.png"));
            current->setIconSize(QSize(40,40));

        }
        else {
            arr[i][j]=0;
            current->setIcon(QIcon());

        }
    }


}

void Grid::openMine(int id){
    int i=id/n;
    int j=id%n;
    if(cnt==0){
       *grid=generateMines(i,j,x,*grid);
    }
    QAbstractButton *current=button[i][j];
    QString text=QString::number(numberOfMines(i,j,grid));
    if(arr[i][j]==0){
        if(grid->at(i)[j]==0){
            if(text=="0"){
                 openZeroes(i,j,grid);

            } else {
                arr[i][j]=1;
                cnt++;
                current->setText(text);
                setColor(i,j,text);

                //current->setDisabled(true);
            }
        }
        else{
            //Lose

            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    if(arr[i][j]!=1){
                        if(grid->at(i)[j]==0){
                            arr[i][j]=1;                          
                            button[i][j]->setText(QString::number(numberOfMines(i,j,grid)));
                            setColor(i,j,QString::number(numberOfMines(i,j,grid)));

                            //button[i][j]->setDisabled(true);
                       } else
                        button[i][j]->setIcon(QIcon("mine_logo.gif"));
}
                }
            }
            QDialog *Qlose=new QDialog();
            Ui_DialogLose *lose=new Ui_DialogLose();
            lose->setupUi(Qlose);
            Qlose->show();
            QObject::connect(Qlose,SIGNAL(accepted()),this,SLOT(setGame()));

        }
        //Win
        if(cnt==m*n-x){
            QDialog *Qwin=new QDialog();
            Ui_DialogWin *win=new Ui_DialogWin();
            win->setupUi(Qwin);
            Qwin->show();

            QObject::connect(Qwin,SIGNAL(accepted()),this,SLOT(setGame()));
        }
    }
    else if(arr[i][j]==1){
        int count=0;
        for(int a=i-1;a<=i+1;a++){
            for(int b=j-1;b<=j+1;b++){
                if(!(a<0 || a>=m || b<0 || b>=n) && arr[a][b]==2){
                    count++;
                }
            }
        }
        /*
        std::cout<<count<<endl;
        for(int p=0;p<m;p++){
            for(int q=0;q<n;q++)
                cout<<arr[p][q]<<" ";
            cout<<endl;
        }
        */

        if(QString::number(count)==button[i][j]->text()){
            for(int a=i-1;a<=i+1;a++)
                for(int b=j-1;b<=j+1;b++)
                    if(!(a<0 || a>=m || b<0 || b>=n) && arr[a][b]==0)
                        openMine(a*n+b);
        }
    }

}

vector<vector<int> > Grid::generateMines(int x, int y,int numMines, vector<vector<int> > grid){
    int a, b;
    grid[x][y]=0;
    srand(time(NULL));
    while (numMines>0){
        a=rand() % m;
        b=rand() % n;
        if(!grid[a][b]&& (a!=x||b!=y)) {
            grid[a][b]=1;
            numMines--;
        }
    }
    return grid;
}

int Grid::numberOfMines(int x, int y,std::vector<std::vector<int> > *grid){
    int count=0;
    for(int i=x-1;i<=x+1;i++){
        for(int j=y-1;j<=y+1;j++){
            if(!(i<0 || i>=m || j<0 || j>=n))
            if(grid->at(i)[j]==1){
                count++;
            }
        }
    }
    return count;

}

void Grid::openZeroes(int i,int j,std::vector<std::vector<int> >  *grid){

    for(int a=i-1;a<=i+1;a++){
        for(int b=j-1;b<=j+1;b++){
            if(!(a<0 || a>=m || b<0 || b>=n) && arr[a][b]==0 ){
                QAbstractButton *current=button[a][b];
                QString text=QString::number(numberOfMines(a,b,grid));
                arr[a][b]=1;
                cnt++;
                if(text=="0"){
                    current->setText("");
                    current->setDisabled(true);
                }
                else
                    current->setText(text);
                setColor(a,b,text);
                    //current->setDisabled(true);
                if(numberOfMines(a,b,grid)==0)
                    openZeroes(a,b,grid);

            }
        }

    }

}



void Grid::setGame(){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            arr[i][j]=0;
            grid->at(i)[j]=0;
            gridLayout->removeWidget(button[i][j]);
            buttons->removeButton(button[i][j]);

        }
    }


    QDialog *diff=new QDialog();
    Ui_Dialog *dialog=new Ui_Dialog();
    dialog->setupUi(diff);
    diff->show();

    QObject::connect(dialog->buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(chooseDifficulty(int)));

    QObject::connect(dialog->buttonBox,SIGNAL(accepted()),this,SLOT(setGrid()));


    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            QAbstractButton *current=button[i][j];
            current->setText("");
            current->setIcon(QIcon());
            current->setEnabled(true);
        }
    }
    cnt=0;



}

void Grid::chooseDifficulty(int a){
    switch (a){
    case 1:
        m=8;
        n=8;
        x=10;

        break;
    case 2:
        m=16;
        n=16;
        x=40;
        break;
    case 3:
        m=16;
        n=30;
        x=99;
        break;
    }
}

void Grid::setGrid(){
    centralWidget->deleteLater();
    centralWidget=new QWidget();
    centralWidget->setMinimumSize(n*42,m*42);
    centralWidget->setMaximumSize(n*42, m*42);

    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            button[i][j]=new Button(i*n+j);
            button[i][j]->setMaximumHeight(40);
            button[i][j]->setMaximumWidth(40);
            button[i][j]->setMinimumHeight(40);
            button[i][j]->setMinimumWidth(40);
            //button[i][j]->setStyleSheet("font-size: 18pt;"
            //                            "font-weight: bold;"
            //                            "color: #0000ff;");
            button[i][j]->setCheckable("True");
            buttons->addButton(button[i][j],j+i*n);
            gridLayout->addWidget(button[i][j],i,j);
            QObject::connect(button[i][j], SIGNAL(rightClick(int)), this, SLOT(flag(int)));
            QObject::connect(button[i][j],SIGNAL(leftClick(int)),this,SLOT(openMine(int)));
        }
    }

   centralWidget->setLayout(gridLayout);
   centralWidget->show();


}

void Grid::setColor(int i,int j,QString text){
    if(text=="0"){
        button[i][j]->setText("");
        button[i][j]->setDisabled(true);
    }
    else if(text=="1")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #0000ff;");
    else if(text=="2")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #0BB502;");
    else if(text=="3")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #ff0000;");
    else if(text=="4")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #16048A;");
    else if(text=="5")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #753408;");
    else if(text=="6")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #009DBD;");
    else if(text=="7")
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #000000;");
    else
        button[i][j]->setStyleSheet("font-size: 18pt; font-weight: bold; color: #6E6E6E;");


}
