#ifndef MATRIXWINDOW_H
#define MATRIXWINDOW_H
#include "graphscene.h"
#include <QDialog>

namespace Ui {
    class MatrixWindow;
}

class MatrixWindow : public QDialog {
    Q_OBJECT
public:
    MatrixWindow(GraphScene* scn, QWidget *parent = 0);
    ~MatrixWindow();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *e);
private:
    Ui::MatrixWindow *ui;
    GraphScene *scene;
    void createTables();
    void createTimeTable();

    QStringList tableLabels;
    QList<QStringList> getInputPath(Vertex* vertex);

private slots:
    void on_valueTable_cellChanged(int row, int column);
    void on_backButton_clicked();
    void on_manageProcess_clicked();
};

#endif // MATRIXWINDOW_H
