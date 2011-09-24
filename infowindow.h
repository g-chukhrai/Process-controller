#ifndef INFOWINDOW_H
#define INFOWINDOW_H
#include <QDialog>

class GraphScene;
namespace Ui {
    class InfoWindow;
}

class InfoWindow : public QDialog {
    Q_OBJECT
public:
    InfoWindow( GraphScene  *inScene ,QWidget *parent = 0);
    ~InfoWindow();

    void setName(QString);
    QString getName()
    {return name;}

    void setValue(QString);
    QString getValue()
    {return value;}

public slots:
    void nameChanged(QString newName);

signals:
    void infoUpdate(QString, QString);

protected:
    void changeEvent(QEvent *e);

private:
    const GraphScene *scene;
    QString name;
    QString value;
    Ui::InfoWindow *ui;

private slots:
    void on_canselButton_clicked();
    void on_addVertexButton_clicked();
};

#endif // INFOWINDOW_H
