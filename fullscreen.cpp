#include "fullscreen.h"
#include "the_player.h"
#include "the_button.h"

fullscreen::fullscreen(){
    QWidget* window = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout();

    // add video

    QVideoWidget *videoWidget = new QVideoWidget;
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);


    player->setMedia(*currentButton->url);
    player->play();

    layout->addWidget(videoWidget);
    window->setLayout(layout);
    window->setWindowState(Qt::WindowMaximized);
    window->show();

}
