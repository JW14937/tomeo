#include "fullscreen.h"

fullscreen::fullscreen(){
    QWidget* window = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* label = new QLabel();
    label->setText("test");
    layout->addWidget(label);


    window->setLayout(layout);
    window->setMinimumSize(500,500);
    window->show();

}
