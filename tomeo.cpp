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
#include <QComboBox>
#include <QStandardItem>
#include <QLineEdit>
#include <QScrollArea>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "fullscreen.h"
#include <QProgressBar>
#include "tagging.h"

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



    // create the main window and layout
    QWidget window;
    QGridLayout *top = new QGridLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);



    // LEFT HAND SIDE

    // Creating a Vertical Layout for the left hand side
    QGridLayout *left_layout = new QGridLayout;
    QWidget* left = new QWidget();
    left->setLayout(left_layout);

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;
    videoWidget->setFixedHeight(350);

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    //Progress Bar
    QLabel* temp = new QLabel();
    temp->setText("progress bar");
    QProgressBar* progressBar = new QProgressBar();
    // video buttons
    QWidget* video_butts = new QWidget();
    QHBoxLayout* video_butts_layout = new QHBoxLayout;

    QPushButton *prev = new QPushButton("<<");
    QPushButton *pause = new QPushButton("||");
    QPushButton *play = new QPushButton(">");
    QPushButton *speed = new QPushButton("x1");
    QPushButton *next = new QPushButton(">>");
    QPushButton *zoom = new QPushButton("🔍");
    QPushButton *fullscr = new QPushButton("⛶");
    QPushButton *add_tag = new QPushButton("add tags");

    video_butts_layout->addWidget(prev);
    video_butts_layout->addWidget(pause);
    video_butts_layout->addWidget(play);
    video_butts_layout->addWidget(speed);
    video_butts_layout->addWidget(next);
    video_butts_layout->addStretch();
    video_butts_layout->addWidget(zoom);
    video_butts_layout->addWidget(fullscr);
    video_butts_layout->addWidget(add_tag);

    video_butts->setLayout(video_butts_layout);

    // Adding functions to buttons above
    pause->connect(pause, SIGNAL(clicked()), player, SLOT(pause()));
    play->connect(play, SIGNAL(clicked()), player, SLOT(play()));
    fullscr->connect(fullscr, SIGNAL(clicked()),player,SLOT(fullscreen()));
    add_tag->connect(add_tag, SIGNAL(clicked()), player, SLOT(tagging()));

    // title and description
    QLineEdit* title = new QLineEdit();
    title->setPlaceholderText("Video title");

    QTextEdit* desc = new QTextEdit();
    desc->setPlaceholderText("Video description");
    desc->setFixedHeight(70);

    // timestamps
    QScrollArea* timestamps_scroll = new QScrollArea();
    QWidget* timestamps = new QWidget();
    QGridLayout* timestamps_layout = new QGridLayout();

    for(int i=0; i<10; i++) {

        QPushButton* time = new QPushButton();
        time->setText("00:00");
        QLineEdit* comment = new QLineEdit();
        comment->setPlaceholderText("Timestamp comment");

        timestamps_layout->addWidget(time, i, 0);
        timestamps_layout->addWidget(comment, i, 1, 1, 3);
    }

    timestamps->setLayout(timestamps_layout);
    timestamps_scroll->setWidget(timestamps);

    left_layout->setHorizontalSpacing(20);
    left_layout->setVerticalSpacing(10);
    left_layout->addWidget(videoWidget, 0,0,1,3);
    left_layout->addWidget(temp, 1,0,1,1);
    left_layout->addWidget(progressBar, 1,1,1,2);
    left_layout->addWidget(video_butts, 2,0,1,3);
    left_layout->addWidget(title, 3,0,1,3);
    left_layout->addWidget(desc, 4,0,1,3);
    left_layout->addWidget(timestamps_scroll, 5,0,1,3);


    // RIGHT HAND SIDE
    QVBoxLayout *right_layout = new QVBoxLayout;
    QWidget* right = new QWidget();
    right->setMinimumWidth(300);
    right->setMaximumWidth(300);
    right->setLayout(right_layout);


    // add filter by tags dropdown

    // tags checkboxes
    QStandardItemModel tags_checkboxes(5, 1); // 5 rows for 5 tags, 1 column

    QStandardItem* select_tag_prompt = new QStandardItem(QString("-- Select tags --").arg(0));
    tags_checkboxes.setItem(0, 0, select_tag_prompt);

    for (int i=1; i<=5; i++) {
        QStandardItem* tag = new QStandardItem(QString("Tag %0").arg(i));

        tag->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        tag->setData(Qt::Unchecked, Qt::CheckStateRole);

        tags_checkboxes.setItem(i, 0, tag);
    }

    // filter dropdown
    QComboBox* filter = new QComboBox();
    filter->setModel(&tags_checkboxes);

    // video thumbnails

    // a column of thumbnails
    QWidget *thumbnails_widget = new QWidget();
    // a list of the thumbnails
    std::vector<TheButton*> thumbnails;
    // the thumbnails are arranged vertically
    QVBoxLayout *thumbnails_layout = new QVBoxLayout();
    thumbnails_widget->setLayout(thumbnails_layout);

    // create the thumbnails
    for ( int i = 0; i < 6; i++ ) {
        TheButton *thumbnail = new TheButton(thumbnails_widget);
        thumbnail->connect(thumbnail, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        thumbnails.push_back(thumbnail);
        thumbnails_layout->addWidget(thumbnail);
        // title
        QLineEdit *title = new QLineEdit();
        title->setPlaceholderText("Video title");
        title->setReadOnly(true);
        thumbnails_layout->addWidget(title);
        thumbnail->init(&videos.at(i));
    }

    // tell the player what thumbnails and videos are available
    player->setContent(&thumbnails, & videos);
    // add thumbnails to scroll area
    QScrollArea *thumbnails_scroll = new QScrollArea;
    thumbnails_scroll->setWidget(thumbnails_widget);

    // add widgets to RHS
    right_layout->addWidget(filter);
    right_layout->addWidget(thumbnails_scroll);



    // TOP LEVEL

    // add to the top level widget
    top->addWidget(left,0,0,1,2);
    top->addWidget(right,0,2,1,1);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}

