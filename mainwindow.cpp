#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <iostream>

using namespace std;
//Constructor
//Sets the initial conditions, connects buttons with slots
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton0,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton1,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton2,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton3,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton4,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton5,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton6,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton7,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton8,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton9,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));

    connect(ui->pushButton_Plus,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Min,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Mult,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Div,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_percent,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Clr,SIGNAL(clicked(bool)),this,SLOT(control_buttons()));
    connect(ui->pushButton_Eql,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
}
//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//When a digit button is pressed this method is called
void MainWindow::digit_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender(); //Button which is pressed
    QString number_displayed; //number which will be displayed on the screen (label)

    //If calculator mode is decimal and user presses hex numbers such as A,B etc. a warning appears on screen and calculations are cleared.

        //If previous value is invalid, clear the screen and display newly pressed button's digit
        if(ui->label->text() == "Invalid" ){
            number_displayed =pressed_button->text();
        //if the last operand is "=" then clear the screen and display newly pressed button's digit
        }else if(lastOperand=="="){
            lastOperand="";
            number_displayed =pressed_button->text();
            ui->label_3->setText(lastOperand);
        //If an operation button is pressed before, clear the screen and display newly pressed button's digit
        //also set isTypingSecondNum to true to get second input
        }else if(lastOperand!="" && !isTypingSecNum){
            isTypingSecNum=true;
            number_displayed=pressed_button->text();
        //If previous value is 0, clear the screen and display newly pressed button's digit
        }else if(ui->label->text() == "0"){
            number_displayed =pressed_button->text();
        //Else add the newly pressed button's digit next to the previous number on the screen
        }else{
            number_displayed =ui->label->text() + pressed_button->text();
        }
        ui->label->setText(number_displayed);//set the label



}

//When a operation button is pressed this method is called
void MainWindow::operator_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();//currently pressed button

    //If there is no number given before, store this number in stored_number
    if(!firstnum){
        stored_number=ui->label->text().toDouble();

        firstnum=true; //first num is stored
        //if an operation button is pressed make it last operand
        if(pressed_button->text()=="+" ||pressed_button->text()=="*" || pressed_button->text()=="/" ||pressed_button->text()=="-" ||pressed_button->text()=="%") lastOperand=pressed_button->text();
        //if "=" button is pressed clear
        else clear();
        ui->label_3->setText(lastOperand);
    }else{
    //        call calculate
        calculate(pressed_button->text(), ui->label->text().toDouble());

    }

}
//When hex, dec or clr button is pressed this method is called
void MainWindow::control_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();

    //if clr button is pressed, call clear method
    if(pressed_button->text() == "Clr"){
        clear();
    }

}
//this method does operations
//operation: currently pressed buttons operation
//secondNum: current num on the screen, right operand
void MainWindow::calculate(QString operation, double secondNum){

    //if division button is pressed before, do division and store the output value in stored_number
    if(lastOperand=="/" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number = (double) stored_number / secondNum;
        lastOperand="";

    //if subtraction button is pressed before, do subtraction and store the output value in stored_number
    }else if(lastOperand=="-" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number= (double) stored_number - secondNum;
       lastOperand="";

    //if addition button is pressed before, do addition and store the output value in stored_number
    }else if(lastOperand=="+" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number=(double)stored_number+secondNum;
        lastOperand="";

    //if multiplication button is pressed before, do multiplication and store the output value in stored_number
    }else if(lastOperand=="*" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number= (double)stored_number*secondNum;
        lastOperand="";
    }
    else if(lastOperand=="%" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number= (double)(stored_number/secondNum)*100;
        lastOperand="";
    }
    //Display the result in the label
    if(isDec)
        ui->label->setText(QString::number(stored_number));


    //If the operation is "=", reset the variables
    if(operation == "="){
        lastOperand="=";
        stored_number=0.0;
        firstnum=false;
        isTypingSecNum=false;
    //last operation is currently presssed button's operation
    }else{
        lastOperand=operation;
    }
    ui->label_3->setText(lastOperand);

}
//this method changes the calculator to its initial settings
void MainWindow::clear(){
    lastOperand="";
    stored_number=0.0;
    isTypingSecNum=false;
    firstnum=false;
    ui->label->setText("0");
    ui->label_3->setText(lastOperand);

}

//This method converts decimal number to hexadecimal
//dec: decimal value to be converted


