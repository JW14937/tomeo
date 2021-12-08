//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include "fullscreen.h"
#include "the_button.h"
#include <iostream>
#include "tagging.h"
#include <fstream>
#include <QDebug>
#include <QFile>

// all buttons have been setup, store pointers here
TheButtonInfo* currVid;
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}


void ThePlayer::jumpTo (TheButtonInfo* button) {
    currVid = button;
    setMedia( * button -> url);
    QString video_name = button->url->toString();
    currently_playing = new QString(video_name);
    updated_video();
    play();
}
void ThePlayer::fullscreen(){
    class Fullscreen* test = new class Fullscreen();
    test->setModal(true);
}
void ThePlayer::nextVid(){
    TheButtonInfo* button = currVid;
    currVid = (currVid + 1);
    setMedia( *(button+1) -> url);
    play();
}
void ThePlayer::prevVid(){
    TheButtonInfo* button = currVid;
    currVid = (currVid - 1);
    setMedia( *(button-1) -> url);
    play();
}
void ThePlayer::slow(){
    setMedia( *(infos->at(6)). url);
    play();
}
void ThePlayer::zoom(){
    setMedia( *(infos->back()). url);
    play();
}
void ThePlayer::tagging(){
    class tagging* test = new class tagging();
    test->setModal(true);
}
void ThePlayer::writeToFile(QString timeInput, QString commentInput){
//    QString filename = "abc.txt";
//    QFile file(filename);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
//        QTextStream stream(&file);
        qDebug() << qPrintable(timeInput);
        qDebug() << qPrintable(commentInput);
        qDebug() << "tedst";

//        stream << timeLine << endl;
//        stream << cmt << endl;
//    }
//    file.close();
}

void updated_video() {

}

