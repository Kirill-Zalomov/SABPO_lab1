#ifndef NOTE_H
#define NOTE_H


#include <QDateTime>


#define  DEFAULT_TITLE_OF_NOTE     ("Заголовок")
#define  DEFAULT_CONTENT_OF_NOTE   ("Заметка")
#define  MAX_TITLE_SIZE            (128u)
#define  MAX_CONTENT_SIZE          (2048u)


class Note final {
private:
    QDateTime _dateTime;
    QString _title;
    QString _content;

public:
    Note();

    QDateTime getDateTime() const;
    bool setDateTime(const QDateTime &newDateTime);
    QString getTitle() const;
    bool setTitle(const QString &newTitle);
    QString getContent() const;
    bool setContent(const QString &newContent);
};


#endif /* NOTE_H */
