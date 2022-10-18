#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QVBoxLayout *vbox = new QVBoxLayout(this);
    QTableView *playlistView = new QTableView();
    m_playlistModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playlistModel);
    m_playlistModel->setHorizontalHeaderLabels(QStringList() << tr("Audio Track") << tr("File Path"));

    /*     Playlist table setting   */
    ui->playlistView->hideColumn(1);
//    playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    playlistView->horizontalHeader()

    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(100);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->backBtn, &QPushButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->skipBtn, &QPushButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->playBtn, &QPushButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->pauseBtn, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->stopBtn, &QPushButton::clicked, m_player, &QMediaPlayer::stop);

    /* DoubleClicked set current track*/

    connect(playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){m_playlist->setCurrentIndex(index.row());});


}



MainWindow::~MainWindow()
{
    delete ui;
    delete m_playlistModel;
    delete m_playlist;
    delete m_player;
}

void MainWindow::on_addBtn_clicked(){
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open Files"), QString(), tr("Audio Files (*.mp3)"));

    foreach (QString filePath, files) {
        QList <QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playlistModel->appendRow(items);
        m_playlist->addMedia(QUrl("file://" + filePath));
    }
};
