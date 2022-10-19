#include "style.h"


QString Style::backgroundStyle()
{
    return "QMainWindow { "
           "background-color: #1f2021;"
           "border: 1px solid #000;}"

           "QTabWidget {"
           "background-color: #1f2021;"
           "border: none;}";
}

QString Style::playlistViewStyle()
{
    return "QTableView { "
           "background-color: 1f2021; "
           "color: white; "
           "border: 1px solid #black;"
           "}"
           "QTableView::item:selected {"
           "background-color: #000;"
           "}"
           "QHeaderView::section:horizintal {"
           "background-color: 1f2021;"
           "border-style: none;"
           "color: white; "
           "border: 1px solid #black; "
           "padding: 6px; "
           "}";
}

QString Style::horizontalHeaderStyle()
{
    return "QLabel {"
           "color: 000;"
           "padding: 0;"
           "padding-bottom: 10px;"
           "padding-top: 10px;"
           "margin: 0;"
           "background-color: #1f2021;}";
}

QString Style::navigationStyle()
{
    return "QTabBar::audioPage {"
           "width: 100%;"
           "height: 100%;}";
}
