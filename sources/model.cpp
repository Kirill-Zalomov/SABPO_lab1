#include "model.h"


NoterModel::NoterModel() {
    this->_notes = QList<Note>();
    this->_currentEditedNode = UNDEFINED_NOTE_INDEX;
}


QPair<bool, Note> NoterModel::getNoteByIndex(const quint32 &index) {
    QPair<bool, Note> result;
    if(index + 1 > this->_notes.size()) {
        result.first  = false;
        result.second = Note();
        return result;
    }
    else {
        result.first  = true;
        result.second = this->_notes.at(index);
        return result;
    }
}


bool NoterModel::addNote(const Note &newValue) {
    this->_notes.append(newValue);
    return true;
}


bool NoterModel::editNote(const quint32 &index, const Note &newValue) {
    if(index + 1 > this->_notes.size()) return false;
    this->_notes.replace(index, newValue);
    return true;
}


bool NoterModel::deleteNote(const quint32 &index) {
    if(index + 1 > this->_notes.size()) return false;
    this->_notes.removeAt(index);
    return true;
}


bool NoterModel::setCurrentEditedNoteIndex(const quint32 &index) {
    if(index + 1 >= MAX_NOTE_NUMBER) return false;
    this->_currentEditedNode = index;
    return true;
}


quint32 NoterModel::getCurrentEditedNoteIndex() {
    return this->_currentEditedNode;
}


bool NoterModel::incrementCurrentEditedNoteIndex() {
    if(this->_currentEditedNode + 1 >= MAX_NOTE_NUMBER) return false;
    this->_currentEditedNode++;
    return true;
}


bool NoterModel::decrementCurrentEditedNoteIndex() {
    if(!(this->_currentEditedNode > 0)) return false;
    this->_currentEditedNode--;
    if(this->_currentEditedNode > MAX_NOTE_NUMBER) {
        this->_currentEditedNode = 0;
        return false;
    }
    return true;
}
