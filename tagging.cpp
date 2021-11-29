#include "tagging.h"
#include "the_player.h"
#include "the_button.h"
#include <QStandardItem>
#include <QComboBox>
tagging::tagging()
{
    QWidget* window = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout();

    // add video
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

    layout->addWidget(filter);
    window->setLayout(layout);
    window->setWindowState(Qt::WindowMaximized);
    window->show();
}
