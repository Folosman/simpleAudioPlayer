#ifndef EDITPLAYLIST_H
#define EDITPLAYLIST_H

#include <QDialog>
#include <QListView>
#include <QStandardItemModel>

namespace Ui {
class EditPlaylist;
}

class EditPlaylist : public QDialog
{
    Q_OBJECT

public:
    explicit EditPlaylist(QWidget *parent = nullptr);

    QStandardItemModel *m_musicListModel;
    ~EditPlaylist();
private slots:
    void addBtn();
    void removeBtn();
    void renameBtn();
private:
    Ui::EditPlaylist *ui;
};

#endif // EDITPLAYLIST_H
