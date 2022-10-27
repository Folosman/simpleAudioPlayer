#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "style.h"
#include "resizefilter.h"

#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QGraphicsDropShadowEffect>
#include <QSlider>

#include <QFile>
#include <QTextStream>
#include <QFileInfo>

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
    ui->playlistView->hideColumn(1);//                                      this doesn't work
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);





    QTableView *playlistList = new QTableView();
    m_playlistListModel = new QStandardItemModel(this);
    ui->playlistList->setModel(m_playlistListModel);

    /*     Playlist table setting   */
    ui->playlistList->hideColumn(1);//                                      this doesn't work
    ui->playlistList->verticalHeader()->setVisible(false);
    ui->playlistList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistList->horizontalHeader()->setStretchLastSection(true);





    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);



    /*      Volume Slider setting       */
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setFixedWidth(100);
    ui->volumeSlider->setValue(100);



    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->backBtn, &QPushButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->skipBtn, &QPushButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->playBtn, &QPushButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->pauseBtn, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->stopBtn, &QPushButton::clicked, m_player, &QMediaPlayer::stop);

    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), m_player, SLOT(setVolume(int)));
    /* DoubleClicked set current track*/

    connect(playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){m_playlist->setCurrentIndex(index.row());});


    QFile file("../SimpleAudioPlayer/conf.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString item;
        while(!file.atEnd())
        {
            QList <QStandardItem *> items;
            item = file.readLine();
            item.resize(item.size()-1);
            items.append(new QStandardItem(QDir(item).dirName()));
            items.append(new QStandardItem(item));
            m_playlistModel->appendRow(items);
            m_playlist->addMedia(QUrl::fromLocalFile(item));
        }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
    delete m_playlistModel;
    delete m_playlist;
    delete m_player;
    delete m_playlistListModel;
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
}

void MainWindow::on_addNewPlaylist_clicked()
{
    QDir file;
    if(!file.cd("../SimpleAudioPlayer/Music/playlist"))
    {
        file.mkdir("../SimpleAudioPlayer/Music/playlist");
    };

}

void MainWindow::on_clearBtn_clicked()
{
    m_playlist->clear();
    m_playlistModel->clear();
}
