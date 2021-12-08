#include "timestamps.h"

Timestamps::Timestamps()
{

}

Timestamps::~Timestamps() {

}

void Timestamps::add_timestamp() {

    QString time_input = (stamp_adder->new_stamp_time)->text();
    QString comment_input = (stamp_adder->new_stamp_comment)->text();

    QPushButton* time = new QPushButton();
    time->setText(time_input);
    QLabel* comment = new QLabel();
    comment->setText(comment_input);

    QPushButton* delete_stamp = new QPushButton();
    delete_stamp->setText("X");
    delete_stamp->setMaximumWidth(20);
    addWidget(delete_stamp, nr_timestamps, 0);
    addWidget(time, nr_timestamps, 1, 1, 1);
    addWidget(comment, nr_timestamps, 2, 1, 5);

    nr_timestamps++;
}


void Timestamps::set_player(ThePlayer* player_input) {
    player = player_input;
}

void Timestamps::set_vid_location(QString vid_loc_input) {
    vid_location = new QString(vid_loc_input);
}

void Timestamps::set_stamp_adder(AddTimestamp *stamp_adder_input) {
    stamp_adder = stamp_adder_input;
}

void Timestamps::load_from_file() {

    // if video reloaded, remove all previous timestamps
    QLayoutItem *old_item;
    while ((old_item = takeAt(0)) != nullptr) {
        delete old_item->widget();
        delete old_item;
    }

    // load the timestamps file

    QString video_path = *player->currently_playing;
    int name_start = video_path.lastIndexOf("/");
    if(name_start == -1) name_start = video_path.lastIndexOf("\\");
    if(name_start == -1) name_start = 0;
    QString video_name = video_path.right(video_path.length() - (name_start+1));
    QString stamp_path = *vid_location + "\\" + video_name.left(video_name.length()-4) + "_stamp.txt";
    QFile file(stamp_path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int i=0;

        // display the times and comments from the file
        while (!in.atEnd()) {
            QString line = in.readLine();
            QPushButton* time = new QPushButton();
            time->setText(line);
            time->setFixedWidth(100);
            line = in.readLine();
            QLabel* comment = new QLabel();
            comment->setText(line);
            QPushButton* delete_stamp = new QPushButton();
            delete_stamp->setText("X");
            delete_stamp->setMaximumWidth(20);
            addWidget(delete_stamp, i, 0);
            addWidget(time, i, 1, 1, 1);
            addWidget(comment, i, 2, 1, 5);
            i++;
        }

        nr_timestamps = i;
    }
}
