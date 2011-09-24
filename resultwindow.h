#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H
#include "graphscene.h"

#include <QDialog>
#include <QTableWidget>

namespace Ui {
    class ResultWindow;
}

class ResultWindow : public QDialog {
    Q_OBJECT
public:
    ResultWindow(QTableWidget*, QTableWidget*, GraphScene* scn, QWidget *parent = 0);
    ~ResultWindow();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *e);
private:
    Ui::ResultWindow *ui;
    QTableWidget* matrixTable;
    QTableWidget* valueTable;
    GraphScene* scene;
    QGraphicsScene* gra;
    QPoint endX,endY;

    void paint();
    int newProcCount;

private slots:
    void on_saveExcel_clicked();
    void on_makeScreen_clicked();
    void on_backButton_clicked();
    void on_startDeal_clicked();
};

#endif // RESULTWINDOW_H
