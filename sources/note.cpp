#include "note.h"


Note::Note() {
    this->_dateTime  = QDateTime::currentDateTime();
    this->_title     = DEFAULT_TITLE_OF_NOTE;
    this->_content   = DEFAULT_CONTENT_OF_NOTE;
}


QDateTime Note::getDateTime() const {
    return this->_dateTime;
}
bool Note::setDateTime(const QDateTime &newDateTime) {
    if(newDateTime.isNull()) return false;
    this->_dateTime = newDateTime;
    return true;
}


QString Note::getTitle() const {
    return this->_title;
}
bool Note::setTitle(const QString &newTitle) {
    if(newTitle.isEmpty()) return false;
    this->_title = newTitle;
    return true;
}


QString Note::getContent() const {
    return this->_content;
}
bool Note::setContent(const QString &newContent) {
    if(newContent.isEmpty()) return false;
    this->_content = newContent;
    return true;
}
