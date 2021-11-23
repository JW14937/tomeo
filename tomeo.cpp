//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QVBoxLayout *layout = new QVBoxLayout();
    buttonWidget->setLayout(layout);

    // create the four buttons
    for ( int i = 0; i < 4; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QWidget window;
    QGridLayout *top = new QGridLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // ADD CODE BELOW FOR LEFT HAND SIDE

    //Creating a Vertical Layout for the left hand side
    QGridLayout *left_layout = new QGridLayout;
    QWidget* left = new QWidget();
    left->setLayout(left_layout);

    QTextEdit* desc = new QTextEdit();
    videoWidget->setFixedHeight(350);
    desc->setFixedHeight(70);

    //hard coding timestamps
    QPushButton* time1 = new QPushButton();
    QPushButton* time2 = new QPushButton();
    QPushButton* time3 = new QPushButton();
    time1->setText("timestamp");
    time2->setText("timestamp");
    time3->setText("timestamp");
    QTextEdit* comment1 = new QTextEdit();
    QTextEdit* comment2 = new QTextEdit();
    QTextEdit* comment3 = new QTextEdit();
    comment1->setFixedHeight(30);
    comment2->setFixedHeight(30);
    comment3->setFixedHeight(30);
    //


    left_layout->setHorizontalSpacing(20);
    left_layout->setVerticalSpacing(10);
    left_layout->addWidget(videoWidget,0,0,1,3);
    left_layout->addWidget(desc,1,0,1,3);
    left_layout->addWidget(time1,2,0);
    left_layout->addWidget(time2,3,0);
    left_layout->addWidget(time3,4,0);
    left_layout->addWidget(comment1,2,1,1,2);
    left_layout->addWidget(comment2,3,1,1,2);
    left_layout->addWidget(comment3,4,1,1,2);

    //

    // ADD CODE BELOW FOR RIGHT HAND SIDE
    QVBoxLayout *right_layout = new QVBoxLayout;
    QWidget* right = new QWidget();
    right->setLayout(right_layout);

    right_layout->addWidget(buttonWidget);
    //


    // add the video and the buttons to the top level widget
    top->addWidget(left,0,0,1,2);
    top->addWidget(right,0,2,1,1);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
