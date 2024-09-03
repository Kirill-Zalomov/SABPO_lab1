#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QMainWindow>
#include "model.h"
#include "note.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class NoterController : public QMainWindow {
    Q_OBJECT

public:
    NoterController(QWidget *parent = nullptr);
    ~NoterController();

private slots:
    void on_button_Create_clicked();
    void on_button_Delete_clicked();
    void on_button_Edit_clicked();
    void on_button_Save_clicked();

    void enableEditingElements(const bool &enable);
    void clearEditingElements();

    void on_textEdit_NoteContent_textChanged();

private:
    NoterModel model;
    Ui::MainWindow *ui;
};


#endif // CONTROLLER_H
