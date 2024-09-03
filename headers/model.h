#ifndef MODEL_H
#define MODEL_H


#include <QList>
#include <QPair>
#include "note.h"


#define  MAX_NOTE_NUMBER        (256u)
#define  UNDEFINED_NOTE_INDEX   (4294967295u)


class NoterModel {
private:
    QList<Note> _notes;
    quint32 _currentEditedNode;

public:
    NoterModel();

    QPair<bool, Note> getNoteByIndex(const quint32 &index);
    bool addNote(const Note &newValue);
    bool editNote(const quint32 &index, const Note &newValue);
    bool deleteNote(const quint32 &index);

    bool setCurrentEditedNoteIndex(const quint32 &index);
    quint32 getCurrentEditedNoteIndex();
    bool incrementCurrentEditedNoteIndex();
    bool decrementCurrentEditedNoteIndex();
};


#endif // MODEL_H
