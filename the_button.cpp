//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
TheButtonInfo* currentButton;
void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void TheButton::clicked() {
    currentButton = info;
    emit jumpTo(info);
}
