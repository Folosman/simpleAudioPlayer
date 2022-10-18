#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addBtn_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QStandardItemModel *m_playlistModel;
};

#endif
