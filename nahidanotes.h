#ifndef NAHIDANOTES_H
#define NAHIDANOTES_H

#include <QMainWindow>

// custom:
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class NahidaNotes; }
QT_END_NAMESPACE

class NahidaNotes : public QMainWindow
{
    Q_OBJECT

public:
    NahidaNotes(QWidget *parent = nullptr);
    ~NahidaNotes();

private slots:
    void on_actionNew_triggered();

private:
    Ui::NahidaNotes *ui;
    QTextEdit currentFile;
};
#endif // NAHIDANOTES_H
