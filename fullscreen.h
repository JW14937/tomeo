#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QUrl>
#include <the_button.h>
#include <the_player.h>

extern TheButtonInfo* currVid;
class Fullscreen: public QDialog{
public:
    Fullscreen();
};

#endif // FULLSCREEN_H
