#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::mt19937 engine(time(nullptr));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->selected_door_text->setVisible(false);
    ui->selected_door_value->setVisible(false);

    ui->open_next_door->setVisible(false);

    ui->change_mind_text->setVisible(false);
    ui->change_mind_yes->setVisible(false);
    ui->change_mind_no->setVisible(false);

    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 326);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::open_next_door(QString win_door) {

    std::uniform_int_distribution<int> dist(1, 3);

    int next_door = dist(engine);

    if (QString::number(next_door) == win_door) {
        return open_next_door(win_door);
    } else {
        return QString::number(next_door);
    }
}

void MainWindow::generate_door_state() {

    std::uniform_int_distribution<int> dist(1, 3);

    int winning_door = dist(engine);

    m_win_door = QString::number(winning_door);

    m_next_door = open_next_door(QString::number(winning_door));

    ui->open_next_door->setText(ui->open_next_door->text().replace("#", m_next_door));
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Checked: " + m_next_door + ", ");
}

void MainWindow::form_state_selected() {
    ui->selected_door_text->setVisible(true);
    ui->selected_door_value->setVisible(true);
    ui->selected_door_clear->setVisible(false);

    ui->door1->setEnabled(false);
    ui->door2->setEnabled(false);
    ui->door3->setEnabled(false);

    ui->open_next_door->setVisible(true);
    ui->change_mind_text->setVisible(true);
    ui->change_mind_yes->setVisible(true);
    ui->change_mind_no->setVisible(true);
}

void MainWindow::on_door1_clicked()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 390);

    m_selected_door = "1";

    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Selected: " + m_selected_door + ", ");

    generate_door_state();

    ui->selected_door_value->setText(m_selected_door);

    form_state_selected();
}

void MainWindow::on_door2_clicked()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 390);

    m_selected_door = "2";

    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Selected: " + m_selected_door + ", ");

    generate_door_state();

    ui->selected_door_value->setText(m_selected_door);

    form_state_selected();
}

void MainWindow::on_door3_clicked()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 390);

    m_selected_door = "3";

    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Selected: " + m_selected_door + ", ");

    generate_door_state();

    ui->selected_door_value->setText(m_selected_door);

    form_state_selected();
}

void MainWindow::form_state_after() {
    ui->door1->setEnabled(true);
    ui->door2->setEnabled(true);
    ui->door3->setEnabled(true);

    ui->open_next_door->setVisible(false);
    ui->change_mind_text->setVisible(false);
    ui->change_mind_yes->setVisible(false);
    ui->change_mind_no->setVisible(false);

    ui->selected_door_text->setVisible(false);
    ui->selected_door_value->setVisible(false);
    ui->selected_door_clear->setVisible(true);
}

void MainWindow::on_change_mind_no_clicked()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 326);

    ui->open_next_door->setText(ui->open_next_door->text().replace(m_next_door, "#"));

    form_state_after();

    ui->selected_door_value->setText("0");

    game_counter_not_changed += 1.0;

    if (m_selected_door == m_win_door) {
        won_not_changed += 1.0;
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Won!" + "\n");
    } else {
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Lost!" + "\n");
    }

    ui->w_no_change_value->setText(QString::number( (won_not_changed/game_counter_not_changed)*100.0, 'f', 2 ));
}


void MainWindow::on_change_mind_yes_clicked()
{
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 326);

    ui->open_next_door->setText(ui->open_next_door->text().replace(m_next_door, "#"));

    form_state_after();

    ui->selected_door_value->setText("0");

    if (m_selected_door == "1" && m_next_door == "2") {
        m_selected_door = "3";
    } else if (m_selected_door == "1" && m_next_door == "3") {
        m_selected_door = "2";
    } else if (m_selected_door == "2" && m_next_door == "1") {
        m_selected_door = "3";
    } else if (m_selected_door == "2" && m_next_door == "3") {
        m_selected_door = "1";
    } else if (m_selected_door == "3" && m_next_door == "1") {
        m_selected_door = "2";
    } else if (m_selected_door == "3" && m_next_door == "2") {
        m_selected_door = "1";
    }

    game_counter_changed += 1.0;

    if (m_selected_door == m_win_door) {
        won_changed += 1.0;
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Won!" + "\n");
    } else {
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Lost!" + "\n");
    }

    ui->w_changed_value->setText(QString::number( (won_changed/game_counter_changed)*100.0, 'f', 2 ));
}

