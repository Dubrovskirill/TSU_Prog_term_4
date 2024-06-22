#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->hashTable->resize(ui->spinBox_tableSize->value());

    ui->comboBoxHash->addItem("hi(K) = (hi-1(K) + c × i + d × i2) mod N");
    ui->comboBoxHash->addItem("hi(K) = [hi-1(K) × a × N] mod N;");
    ui->comboBoxHash->addItem("hi(K) = (K mod N) + i × (1+ K mod (N – 2)) mod N");
    connect(ui->comboBoxHash, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onHashFunctionChanged);

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

    connect(ui->hashTable, &HashTableWidget::isExists, this, [this](int key) {
        ui->statusbar->showMessage(QString("Ключ %1 уже существует в таблице.").arg(key));
    });
    connect(ui->hashTable, &HashTableWidget::isnotFound, this, [this](int key) {
        ui->statusbar->showMessage(QString("Ключ %1 не существует в таблице.").arg(key));
    });

    int size = 20;
    ui->hashTable->resize(size);
    ui->spinBox_tableSize->setValue(size);
   ui->hashTable->addRow(42, QString::number(17));
//    ui->hashTable->addRow(92, QString::number(24));
//    ui->hashTable->addRow(52, QString::number(52));

    for (int i = 0; i < size; ++i) {
        ui->hashTable->addRow(rand() % 100, QString::number(i));
    }


}

void MainWindow::onHashFunctionChanged(int index) {
    HashFunction* newHashFunction = nullptr;
    switch (index) {
    case 0:
        newHashFunction = new FirstHashFunction();
        break;
    case 1:
        newHashFunction = new SecondHashFunction();
        break;
    case 2:
        newHashFunction = new ThirdHashFunction();
        break;
    default:

        break;
    }

    if (newHashFunction != nullptr) {
        ui->hashTable->setHashFunction(newHashFunction);
       // ui->hashTable->updateTable();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
