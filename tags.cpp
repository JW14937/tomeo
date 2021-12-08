#include "tags.h"

Tags::Tags() {

}

void Tags::add_tag() {

    QString tag_input = new_tag->text();

    QPushButton* tag = new QPushButton();
    tag->setText(tag_input + "  X");
    insertWidget(count()-3, tag);
}


void Tags::set_player(ThePlayer* player_input) {
    player = player_input;
}

void Tags::set_vid_location(QString vid_loc_input) {
    vid_location = new QString(vid_loc_input);
}

void Tags::set_thumbnails(QVBoxLayout *thumbnails_input) {
    thumbnails_layout = thumbnails_input;
}

void Tags::load_from_file() {

    // if video reloaded, remove all previous tags
    QLayoutItem *old_item;
    while ((old_item = takeAt(0)) != nullptr) {
        delete old_item->widget();
        delete old_item;
    }

    // load the tags file

    QString video_path = *player->currently_playing;
    int name_start = video_path.lastIndexOf("/");
    if(name_start == -1) name_start = video_path.lastIndexOf("\\");
    if(name_start == -1) name_start = 0;
    QString video_name = video_path.right(video_path.length() - (name_start));
    QString stamp_path = *vid_location + video_name.left(video_name.length()-4) + "_tags.txt";
    QFile file(stamp_path);

    addStretch();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // display the times and comments from the file
        while (!in.atEnd()) {
            QString line = in.readLine();
            QPushButton* tag = new QPushButton();
            tag->setText(line + "  X");
            insertWidget(count()-1, tag);
        }
    }

    new_tag = new QLineEdit();
    new_tag->setPlaceholderText("new tag");
    new_tag->setMaximumWidth(70);
    insertWidget(count()-1, new_tag);
    QPushButton* new_tag_button = new QPushButton();
    new_tag_button->setText("add");
    new_tag_button->setMaximumWidth(30);
    insertWidget(count()-1, new_tag_button);
    new_tag_button->connect(new_tag_button, SIGNAL(clicked()), this, SLOT(add_tag()));
}

void Tags::filter() {
    for(int i=0; i<10; i++) {
        QLayoutItem *old_item;
        old_item = thumbnails_layout->takeAt(0);
        delete old_item->widget();
        delete old_item;
    }
}
