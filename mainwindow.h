#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editplaylist.h"

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
    void addBtn();
    void addNewPlaylist();
    void clearBtn();
    void editBtn();
private:
    Ui::MainWindow *ui;

    EditPlaylist m_editPlaylist;

    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QStandardItemModel *m_playlistModel;
    QStandardItemModel *m_playlistListModel;
};

#endif
