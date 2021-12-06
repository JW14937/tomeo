#ifndef ADD_TIMESTAMP_H
#define ADD_TIMESTAMP_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class AddTimestamp : public QHBoxLayout {

Q_OBJECT

public:
    AddTimestamp();
    QLineEdit* new_stamp_time;
    QLineEdit* new_stamp_comment;

public slots:
};


#endif // ADD_TIMESTAMP_H
