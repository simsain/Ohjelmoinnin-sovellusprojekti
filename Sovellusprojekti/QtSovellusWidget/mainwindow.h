#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;

    void onReply(QNetworkReply *reply);
    void loadCars();
    void addCar();
    void updateCar();
    void deleteCar();
    void clearInputs();

    int selectedId = -1;
};
#endif // MAINWINDOW_H
