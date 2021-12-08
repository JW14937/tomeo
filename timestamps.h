#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <QGridLayout>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include "the_player.h"
#include "add_timestamp.h"


class Timestamps : public QGridLayout {

Q_OBJECT

public:
    Timestamps();
    ~Timestamps();
    ThePlayer* player;
    QString* vid_location;
    AddTimestamp* stamp_adder;
    void set_player(ThePlayer* player_input);
    void set_vid_location(QString vid_loc_input);
    void set_stamp_adder(AddTimestamp* stamp_adder_input);

private:
    int nr_timestamps;

public slots:
    void add_timestamp();
    void load_from_file();
};

#endif // TIMESTAMPS_H
