#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QDebug>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "the_player.h"

class Description: public QVBoxLayout {

    Q_OBJECT

    public:
        Description();
        QString* description;
        QString* title;
        ThePlayer* player;
        QString* vid_location;
        void set_player(ThePlayer* player_input);
        void set_vid_location(QString vid_loc_input);

    public slots:
        void load_from_file();
};

#endif // DESCRIPTION_H
