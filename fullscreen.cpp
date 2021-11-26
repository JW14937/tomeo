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


    player->setMedia(QUrl::fromLocalFile("/Users/abelfurhad/Desktop/University of Leeds/Year 2/User Interface/tomeo/videos/f.mp4"));
    player->play();

    layout->addWidget(videoWidget);
    window->setLayout(layout);
    window->setMinimumSize(500,500);
    window->show();

}
