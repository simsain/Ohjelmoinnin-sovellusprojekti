#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::onReply);

    loadCars();

    connect(ui->tableWidget, &QTableWidget::cellClicked,
            this, [&](int row, int) {
                selectedId = ui->tableWidget->item(row, 0)->text().toInt();
            });

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &MainWindow::addCar);

    connect(ui->btnUpdate, &QPushButton::clicked,
            this, &MainWindow::updateCar);

    connect(ui->btnDelete, &QPushButton::clicked,
            this, &MainWindow::deleteCar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCars()
{
    qDebug() << "Ladataan autolista";
    manager->get(QNetworkRequest(QUrl("http://localhost:3000/car")));
}

void MainWindow::addCar()
{
    qDebug() << "ADD BUTTON CLICKED";
    QJsonObject obj;
    obj["branch"] = ui->lineEditBranch->text();
    obj["model"] = ui->lineEditModel->text();

    QNetworkRequest request(QUrl("http://localhost:3000/car"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, QJsonDocument(obj).toJson());

    connect(reply, &QNetworkReply::finished,
            this, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "ADD error:" << reply->errorString();
        } else {
            qDebug() << "ADD success";
        }

                reply->deleteLater();
                loadCars();
                clearInputs();
            });
}

void MainWindow::onReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }
    QByteArray data = reply->readAll();
    //qDebug() <<data;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Branch", "Model"});
    ui->tableWidget->setRowCount(array.size());

    int row = 0;

    for (auto item : array) {
        QJsonObject obj = item.toObject();
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(obj["id"].toInt())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(obj["branch"].toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(obj["model"].toString()));
        row++;
    }

    reply->deleteLater();
}

void MainWindow::updateCar()
{
    qDebug() << "UPDATE BUTTON CLICKED";
    if (selectedId == -1){
        qDebug() << "Valitse päivitettävä rivi";
        return;
    }
    qDebug() << "Updating car with id: "<<selectedId;

    QJsonObject obj;
    obj["branch"] = ui->lineEditBranch->text();
    obj["model"] = ui->lineEditModel->text();
    //qDebug() <<obj;

    QString url = "http://localhost:3000/car/" + QString::number(selectedId);
    //qDebug() <<url;

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->put(request, QJsonDocument(obj).toJson());

    connect(reply, &QNetworkReply::finished,
            this, [=]() {
                qDebug() << "UPDATE success";
            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "UPDATE error:" << reply->errorString();
            }

                reply->deleteLater();
                loadCars();
                clearInputs();
            });

}
void MainWindow::deleteCar()
{
    qDebug() << "DELETE CLICKED";
    if (selectedId == -1) {
        qDebug() << "Valitse poistettava rivi";
        return;
    }

    QString url = "http://localhost:3000/car/" + QString::number(selectedId);
    qDebug() << "Rivi poistettu";
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->deleteResource(request);

    connect(reply, &QNetworkReply::finished,
            this, [=]() {
                if (reply->error() != QNetworkReply::NoError) {
                    qDebug() << "DELETE error:" << reply->errorString();
                } else {
                    qDebug() << "DELETE success";
                }

                reply->deleteLater();
                loadCars();
                clearInputs();
            });
}

void MainWindow::clearInputs()
{
    ui->lineEditBranch->clear();
    ui->lineEditModel->clear();
    selectedId = -1;
}