#include <add_timestamp.h>

AddTimestamp::AddTimestamp() {

    new_stamp_time = new QLineEdit();
    new_stamp_time->setPlaceholderText("00:00:00");

    new_stamp_comment = new QLineEdit();
    new_stamp_comment->setPlaceholderText("Timestamp comment");

    new_stamp_time->setFixedWidth(100);
    new_stamp_comment->setFixedWidth(450);
    addWidget(new_stamp_time);
    addWidget(new_stamp_comment);

}
