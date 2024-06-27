#pragma once

#include <QWidget>

namespace Ui {
class HashTableCellWidget;
}

class HashTableCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableCellWidget(QWidget *parent = nullptr);
    ~HashTableCellWidget();

    int key() const;
    QString value() const;
    void setEditable(bool editable);

public slots:
    void setKey(int key);
    void setValue(const QString &value);
    void emptyKey();
signals:
    void valueChanged(HashTableCellWidget *item);

private:
    Ui::HashTableCellWidget *ui;
};

