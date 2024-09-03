#include "controller.h"
#include "ui_mainwindow.h"


NoterController::NoterController(QWidget *parent) : QMainWindow(parent) {
    this->ui = new Ui::MainWindow;
    this->ui->setupUi(this);

    this->ui->label_NumberOfSymbols->setText("0 / " + QString::number(MAX_CONTENT_SIZE));
    this->ui->label_NumberOfNotes->setText("0 / " + QString::number(MAX_NOTE_NUMBER));
    this->ui->statusbar->showMessage("Строка состояния: Приложение запущено");
}


NoterController::~NoterController() {
    delete ui;
}


void NoterController::on_button_Create_clicked() {
    quint32 currentNotesNumber = this->ui->listWidget_Notes->count();
    if(currentNotesNumber == MAX_NOTE_NUMBER) {
        this->ui->statusbar->showMessage("Строка состояния: Заметка не создана, достигнуто максимальное число заметок.");
        return;
    }

    Note newNote = Note();
    this->model.addNote(newNote);
    this->ui->listWidget_Notes->addItem(newNote.getDateTime().toString("[dd.MM.yyyy HH:mm:ss]  ") + newNote.getTitle());
    this->ui->statusbar->showMessage("Строка состояния: Приложение запущено");
    this->ui->label_NumberOfNotes->setText(QString::number(currentNotesNumber + 1) + " / " + QString::number(MAX_NOTE_NUMBER));
}


void NoterController::on_button_Delete_clicked() {
    quint32 indexOfSelectedNote = this->ui->listWidget_Notes->currentRow();
    if(indexOfSelectedNote > MAX_NOTE_NUMBER) {
        this->ui->statusbar->showMessage("Строка состояния: Удаление не выполнено, нет выбранной заметки для удаления.");
        return;
    }

    QListWidgetItem *item = this->ui->listWidget_Notes->takeItem(indexOfSelectedNote);
    delete item;

    this->model.deleteNote(indexOfSelectedNote);
    this->ui->statusbar->showMessage("Строка состояния: Удаление заметки успешно выполнено.");
    this->ui->label_NumberOfNotes->setText(QString::number(this->ui->listWidget_Notes->count()) + " / " + QString::number(MAX_NOTE_NUMBER));

    if(indexOfSelectedNote == this->model.getCurrentEditedNoteIndex()) {
        this->clearEditingElements();
        this->enableEditingElements(false);
        this->model.setCurrentEditedNoteIndex(UNDEFINED_NOTE_INDEX);
    }
    else if(indexOfSelectedNote < this->model.getCurrentEditedNoteIndex()) {
        this->model.decrementCurrentEditedNoteIndex();
    }
}


void NoterController::on_button_Edit_clicked() {
    quint32 indexOfSelectedNote = this->ui->listWidget_Notes->currentRow();
    if(indexOfSelectedNote > MAX_NOTE_NUMBER) {
        this->ui->statusbar->showMessage("Строка состояния: Редактирование невозможно, нет выбранной заметки для редактирования.");
        return;
    }

    QPair<bool, Note> selectedNote = this->model.getNoteByIndex(indexOfSelectedNote);
    if(!static_cast<bool>(selectedNote.first)) {
        this->ui->statusbar->showMessage("Строка состояния: Редактирование невозможно, заметка не найдена.");
        return;
    }

    Note note = static_cast<Note>(selectedNote.second);
    this->ui->lineEdit_Title->setText(note.getTitle());
    this->ui->textEdit_NoteContent->setText(note.getContent());

    this->enableEditingElements(true);
    this->ui->label_NumberOfSymbols->setText(QString::number(note.getContent().size()) + " / " + QString::number(MAX_CONTENT_SIZE));
    this->model.setCurrentEditedNoteIndex(indexOfSelectedNote);
}


void NoterController::on_button_Save_clicked() {
    Note editedNote = Note();
    editedNote.setTitle(this->ui->lineEdit_Title->text());
    editedNote.setContent(this->ui->textEdit_NoteContent->toPlainText());
    editedNote.setDateTime(QDateTime::currentDateTime());
    if(this->model.editNote(this->model.getCurrentEditedNoteIndex(), editedNote)) {
        this->ui->statusbar->showMessage("Строка состояния: Отредактированная заметка успешно сохранена.");
        this->ui->listWidget_Notes->takeItem(this->model.getCurrentEditedNoteIndex());
        this->ui->listWidget_Notes->insertItem(this->model.getCurrentEditedNoteIndex(), editedNote.getDateTime().toString("[dd.MM.yyyy HH:mm:ss]  ") + editedNote.getTitle());
        this->ui->listWidget_Notes->setCurrentRow(this->model.getCurrentEditedNoteIndex());
    }
    else {
        this->ui->statusbar->showMessage("Строка состояния: Возникла ошибка при сохранении отредактированной заметки.");
    }
}


void NoterController::enableEditingElements(const bool &enable) {
    this->ui->lineEdit_Title->setEnabled(enable);
    this->ui->textEdit_NoteContent->setEnabled(enable);
    this->ui->button_Save->setEnabled(enable);
}


void NoterController::clearEditingElements() {
    this->ui->lineEdit_Title->clear();
    this->ui->textEdit_NoteContent->clear();
}


void NoterController::on_textEdit_NoteContent_textChanged() {
    static QString lastNoteContentState;
    static quint32 lastNumberOfSymbols;

    QTextCursor savedCursor = this->ui->textEdit_NoteContent->textCursor();
    quint32 savedCursorPosition = savedCursor.position();
    quint32 numberOfSymbolsInNote = this->ui->textEdit_NoteContent->toPlainText().size();
    if(numberOfSymbolsInNote <= MAX_CONTENT_SIZE) {
        this->ui->label_NumberOfSymbols->setText(QString::number(numberOfSymbolsInNote) + " / " + QString::number(MAX_CONTENT_SIZE));
        lastNoteContentState = this->ui->textEdit_NoteContent->toPlainText();
        lastNumberOfSymbols = numberOfSymbolsInNote;
    }
    else {
        if(lastNumberOfSymbols < MAX_CONTENT_SIZE)  {
            this->ui->textEdit_NoteContent->setText(this->ui->textEdit_NoteContent->toPlainText().mid(0, MAX_CONTENT_SIZE));
        }
        else {
            this->ui->textEdit_NoteContent->setText(lastNoteContentState);
            savedCursor.setPosition(savedCursorPosition - 1);
        }
        this->ui->label_NumberOfSymbols->setText(QString::number(MAX_CONTENT_SIZE) + " / " + QString::number(MAX_CONTENT_SIZE));
        this->ui->textEdit_NoteContent->setTextCursor(savedCursor);
    }
}

