#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QString>
namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();
    QString displayValBak="";

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
   void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void on_clear_clicked();
    void on_MemGet_clicked();
    void on_MemAdd_clicked();
    void on_MemClear_clicked();
};

#endif // CALCULATOR_H
