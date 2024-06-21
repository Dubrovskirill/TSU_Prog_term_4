#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->hashTable->resize(ui->spinBox_tableSize->value());

    connect(ui->pushButton_add, &QPushButton::clicked, this, [this]() {
        ui->hashTable->addRow(ui->spinBox_key->value(), ui->lineEdit_value->text());
    });
    connect(ui->pushButton_remove, &QPushButton::clicked, this, [this]() {
        ui->hashTable->removeRow(ui->spinBox_key->value());
    });
    connect(ui->pushButton_find, &QPushButton::clicked, this, [this]() {
        ui->hashTable->findRow(ui->spinBox_key->value());
    });
    connect(ui->pushButton_setTableSize, &QPushButton::clicked, this, [this]() {
        ui->hashTable->resize(ui->spinBox_tableSize->value());
    });
    int size = 20;
    ui->hashTable->resize(size);
//    ui->hashTable->addRow(42, QString::number(17));
//    ui->hashTable->addRow(92, QString::number(24));
//    ui->hashTable->addRow(52, QString::number(52));

    for (int i = 0; i < size; ++i) {
        ui->hashTable->addRow(rand() % 100, QString::number(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
