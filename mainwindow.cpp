#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "style.h"
#include "resizefilter.h"

#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(Style::backgroundStyle());

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9);
    shadowEffect->setOffset(0);
    shadowEffect->setColor("Red");
    ui->centralwidget->setGraphicsEffect(shadowEffect);
    ui->centralwidget->layout()->setMargin(0);
    ui->centralwidget->layout()->setSpacing(0);



    /*         Style setting        */
    ui->playlistView->setStyleSheet(Style::playlistViewStyle());
    ui->audioHeader->setStyleSheet(Style::backgroundStyle());
    ui->audioHeader->setStyleSheet(Style::horizontalHeaderStyle());
    ui->PlayerNavigation->setStyleSheet(Style::navigationStyle());
    ui->PlayerNavigation->installEventFilter(new ResizeFilter(ui->PlayerNavigation));




    QTableView *playlistView = new QTableView();
    m_playlistModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playlistModel);

    /*     Playlist table setting   */
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(40);
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
