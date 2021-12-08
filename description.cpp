#include "description.h"

Description::Description() {

}

void Description::set_player(ThePlayer* player_input) {

    player = player_input;
}

void Description::set_vid_location(QString vid_loc_input) {

    vid_location = new QString(vid_loc_input);
}

void Description::load_from_file() {

    // if video reloaded, remove all previous descriptions
    QLayoutItem *old_item;
    while ((old_item = takeAt(0)) != nullptr) {
        delete old_item->widget();
        delete old_item;
    }

    QString video_path = *player->currently_playing;
    int name_start = video_path.lastIndexOf("/");
    if(name_start == -1) name_start = video_path.lastIndexOf("\\");
    if(name_start == -1) name_start = 0;
    QString video_name = video_path.right(video_path.length() - (name_start+1));

    title = new QString(video_name);

    QString desc_path = *vid_location + "\\" + video_name.left(video_name.length()-4) + "_desc.txt";
    QFile file(desc_path);

    description = new QString("");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            description->append(line);
            description->append("\n");
        }
    }

    QLabel* title_label = new QLabel();
    title_label->setText(*title);

    QTextEdit* desc = new QTextEdit();
    if(description->length() == 0) desc->setPlaceholderText("Video description");
    else desc->setText(*description);
    desc->setFixedHeight(50);

    this->addWidget(title_label);
    this->addWidget(desc);
}

