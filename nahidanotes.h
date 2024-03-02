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

private:
    Ui::NahidaNotes *ui;
    QString currentFile;
};
#endif // NAHIDANOTES_H
