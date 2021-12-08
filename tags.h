#ifndef TAGS_H
#define TAGS_H

#include <QDebug>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "the_player.h"

class Tags: public QHBoxLayout {

    Q_OBJECT

    public:
        Tags();
        QLineEdit* new_tag;
        ThePlayer* player;
        QString* vid_location;
        QVBoxLayout *thumbnails_layout;
        void set_player(ThePlayer* player_input);
        void set_vid_location(QString vid_loc_input);
        void set_thumbnails(QVBoxLayout *thumbnails_input);

    public slots:
        void load_from_file();
        void add_tag();
        void filter();
};

#endif // TAGS_H
