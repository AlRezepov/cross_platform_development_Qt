#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_clearResult->setCheckable(true);

    chartWindow = new QMainWindow(this);
    chart = new QChart();
    chartView = new QChartView(chart);
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    // Инициализация осей
    axisX->setTitleText("Время, мс");
    axisY->setTitleText("Значение");

    // Добавление осей на виджет графика
    chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    chartView->chart()->addAxis(axisY, Qt::AlignLeft);

    // Подключаем сигнал dataReadyForChart к слоту displayChart
    connect(this, &MainWindow::dataReadyForChart, this, &MainWindow::displayChart);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView;
    delete chartWindow;
}

void MainWindow::displayChart(QVector<double> data)
{
    chartWindow->setWindowTitle("График данных");

    // Проверяем наличие серий в графике
    if (!chart->series().isEmpty()) {
        // Удаляем все текущие серии из графика и освобождаем память
        foreach (QAbstractSeries *series, chart->series()) {
            chart->removeSeries(series);
            delete series;
        }
    }

    // Создаем новую серию для данных
    QLineSeries *newSeries = new QLineSeries();

    // Устанавливаем данные для новой серии
    for (int i = 0; i < data.size(); ++i) {
        newSeries->append(i, data[i]);
    }

    // Привязка новой серии к осям
    chartView->chart()->addSeries(newSeries);
    newSeries->attachAxis(axisX);
    newSeries->attachAxis(axisY);

    // Устанавливаем текущую серию в окне графика
    chartView->setChart(chartView->chart());

    // Помечаем новую серию для удаления при следующем вызове displayChart()
    QObject::connect(chartView, &QChartView::destroyed, newSeries, &QObject::deleteLater);

    // Масштабирование оси Y
    double maxElem = *std::max_element(data.begin(), data.end());
    double minElem = *std::min_element(data.begin(), data.end());
    axisY->setRange(minElem, maxElem);

    // Установка графика в виджет и его отображение
    chartWindow->setCentralWidget(chartView);
    chartWindow->resize(800, 600);
    chartWindow->show();
}



/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel)
{

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }
    else{

        //продумать как выйти из функции
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;

        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;

            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;

                if(sizeFrame > 1500){
                    continue;
                }

                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;

                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);

                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(const QVector<uint32_t> dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }

        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);

    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }

    //Поиск 2го максимума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> resultData)
{

    double min = 0, sMin = 0;
    QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
    QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;

}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked()
{
    pathToFile = "";
    ui->le_path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                              tr("Открыть файл"), "/home/", tr("ADC Files (*.adc)"));

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked()
{
    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){
        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);

    int selectIndex = ui->cmB_numCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEF;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xED;
    }

    auto read = [&]{ return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return ProcessFile(res);};
    auto findMax = [&](QVector<double> res){
        maxs = FindMax(res);
        mins = FindMin(res);
        DisplayResult(mins, maxs);

        QVector<double> firstSecondData = res.mid(0, 1000);
        emit dataReadyForChart(firstSecondData);
    };

    QtConcurrent::run(read)
                 .then(process)
                 .then(findMax);
}
