#include "HashTableCellWidget.h"
#include "ui_HashTableCellWidget.h"

HashTableCellWidget::HashTableCellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HashTableCellWidget)
{
    ui->setupUi(this);
    ui->lineEdit_value->setReadOnly(true);
    connect(ui->lineEdit_value, &QLineEdit::editingFinished, this, [this]() {
        emit valueChanged(this);
    });
    setFixedSize(QSize(250, 40));
}

HashTableCellWidget::~HashTableCellWidget()
{
    delete ui;
}

int HashTableCellWidget::key() const
{
    return ui->label_keyValue->text().toInt();
}

QString HashTableCellWidget::value() const
{
    return ui->lineEdit_value->text();
}

void HashTableCellWidget::setKey(int key)
{
    ui->label_keyValue->setText(QString::number(key));
}

void HashTableCellWidget::setValue(const QString &value)
{
    ui->lineEdit_value->setText(value);
}

void HashTableCellWidget::emptyKey()
{
    ui->label_keyValue->setText("");
}
