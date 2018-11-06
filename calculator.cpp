#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i =0; i < 10; i++)
    {
        QString butName = "pushButton" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(clicked()),this,SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(clicked()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(clicked()),this,SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(clicked()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiplay,SIGNAL(clicked()),this,SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(clicked()),this,SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign,SIGNAL(clicked()),this,SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton * Button=(QPushButton *)sender();
    QString butval = Button->text();
    QString displayVal=ui->Display->text();
    if((displayVal.toDouble() == 0 )|| (displayVal.toDouble() == 0.0))
    {
        ui->Display->setText(butval);
    }
    else
    {
        QString newVal = displayVal +butval;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString butval = button->text();
    if(QString::compare(butval,"/",Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(butval,"*",Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    } else if (QString::compare(butval,"+",Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else {
        subTrigger =true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double  solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        }else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        }else {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDispayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDispayValSign));
    }
}


void Calculator::on_clear_clicked()
{
    ui->Display->setText("0");
}

void Calculator::on_MemGet_clicked()
{
    displayValBak = ui->Display->text();

}

void Calculator::on_MemAdd_clicked()
{

    double  solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dbldisplayValBak = displayValBak.toDouble();
    solution = dbldisplayValBak + dblDisplayVal;
    ui->Display->setText(QString::number(solution));
}

void Calculator::on_MemClear_clicked()
{
    double  solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dbldisplayValBak = displayValBak.toDouble();
    solution = dbldisplayValBak - dblDisplayVal;
    ui->Display->setText(QString::number(solution));
}
