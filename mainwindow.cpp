#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <random>
#include <algorithm>


static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};


static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::ApplyModel() {
    if (deque_model_.items.empty()) {
        ui->pop_back->setDisabled(true);
        ui->pop_front->setDisabled(true);
    } else {
        ui->pop_back->setDisabled(false);
        ui->pop_front->setDisabled(false);
    }
    ui->txt_size->setText(QString::fromStdString(std::to_string(deque_model_.items.size())));

    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();

    for (size_t i = 0; i < deque_model_.items.size(); ++i) {
        ui->list_widget->addItem(QString::fromStdString(std::to_string(i) + ": " + deque_model_.items[i]));
    }
    ui->list_widget->addItem("end");

    deque_model_.iterator = preserve_iter;
    ApplyIterator();
}


void MainWindow::ApplyIterator(){
    int offset = std::distance(deque_model_.items.begin(),deque_model_.iterator);

    ui->list_widget->setCurrentRow(offset);

    bool disabled = deque_model_.iterator == deque_model_.items.end();
    ui->edit->setDisabled(disabled);
    ui->erase->setDisabled(disabled);
    ui->btn_plus->setDisabled(disabled);
    ui->btn_minus->setDisabled(deque_model_.iterator == deque_model_.items.begin());


    if (deque_model_.iterator == deque_model_.items.end()){
        ui->txt_elem_content->setText("");
    } else {
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }
}


void MainWindow::on_pop_back_clicked()
{
    if (!deque_model_.items.empty())
    {
        deque_model_.items.pop_back();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_push_back_clicked()
{
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_tea_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_cakes_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_erase_clicked()
{
    if(deque_model_.iterator != deque_model_.items.end()){
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_insert_clicked()
{
    if(deque_model_.iterator != deque_model_.items.end()){
        deque_model_.items.insert(deque_model_.iterator,ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = deque_model_.items.begin();
    } else {
        deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = deque_model_.items.begin();
    }
    ApplyModel();
}


void MainWindow::on_edit_clicked()
{
    if(deque_model_.iterator != deque_model_.items.end()){
        *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
        ApplyModel();
    }
}


void MainWindow::on_btn_minus_clicked()
{
    if (deque_model_.iterator != deque_model_.items.begin()){
        --deque_model_.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_btn_plus_clicked()
{
    if (deque_model_.iterator != deque_model_.items.end()){
        ++deque_model_.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_end_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow < deque_model_.items.size()) {
        deque_model_.iterator = deque_model_.items.begin();
        std::advance(deque_model_.iterator, currentRow);
        ApplyIterator();
    } else if (currentRow == deque_model_.items.size()){
        deque_model_.iterator = deque_model_.items.end();
        ApplyIterator();
    }
}


void MainWindow::on_resize_clicked()
{
    deque_model_.items.resize(ui->txt_size->text().toInt());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_count_clicked()
{
    ui->lbl_count->setText(QString::number(std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toStdString())));
    ApplyModel();
}


void MainWindow::on_min_element_clicked()
{
    if (!deque_model_.items.empty()) {
        auto it = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.iterator = it;
    }
    ApplyModel();
}


void MainWindow::on_max_element_clicked()
{
    if (!deque_model_.items.empty()) {
        auto it = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.iterator = it;
    }
    ApplyModel();
}


void MainWindow::on_find_clicked()
{
    auto it = std::find(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}


void MainWindow::on_sort_clicked()
{
    deque_model_.items = MergeSort<std::string>(deque_model_.items);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_sOrT_clicked()
{
    class CaseInsensitiveStringCompare {
    public:
        bool operator()(const std::string& s1, const std::string& s2) const {
            return QString::compare(QString::fromStdString(s1), QString::fromStdString(s2), Qt::CaseInsensitive) < 0;
        }
    };
    deque_model_.items = MergeSort<std::string, CaseInsensitiveStringCompare>(deque_model_.items, CaseInsensitiveStringCompare());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_unique_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto to_del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(to_del, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_reverse_clicked()
{
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_shuffle_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel();
}


void MainWindow::SetRandomGen(const std::mt19937 &random_gen){
    random_gen_ = random_gen;
}


void MainWindow::on_pop_front_clicked()
{
    if (!deque_model_.items.empty())
    {
        deque_model_.items.pop_front();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_push_front_clicked()
{
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_lower_bound_clicked()
{
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    std::string searchString = ui->txt_elem_content->text().toStdString();


    auto it = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), searchString);

    if (it != deque_model_.items.end()) {
        deque_model_.iterator = it;
        ApplyIterator();
    }
}


void MainWindow::on_upper_bound_clicked()
{
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    std::string searchString = ui->txt_elem_content->text().toStdString();

    auto it = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), searchString);

    deque_model_.iterator = it;
    ApplyIterator();
}

