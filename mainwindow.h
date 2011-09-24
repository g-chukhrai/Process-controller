#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "graphscene.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void createMenus();
    QMenu *itemMenu;
    GraphScene *scene;

    QAction *deleteAction;
    QAction *viewMatrixAction;
    QAction *addArcAction;

    QString programmTitle;

    void setCurrentFileName(const QString &fileName);
    bool maybeSave();
    virtual void closeEvent(QCloseEvent *e);
    void centerScrollBar();
public slots:
    void addArc_clicked();
    void deleteButton_clicked();
    void newFile();
    bool save();
    bool saveAs();
    bool load();
    void setMoveMode();
    void viewMatrix_clicked();
    void exit();
    void infoExec();
    void about();
    void deleteAll();

};

#endif // MAINWINDOW_H
