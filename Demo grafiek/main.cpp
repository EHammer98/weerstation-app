/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);                                                     //Create application

    QLineSeries *series = new QLineSeries();                                        //Create line

    for(int n = 0; n < 11; n++){                                                    //Add coordinates for line
        int r = rand() % 11;
        series->append(n, r);
    }

    QChart *chart = new QChart();                                                   //Create chart
    chart->legend()->hide();                                                        //Hide legenda
    chart->addSeries(series);                                                       //Add line to chart
    chart->createDefaultAxes();                                                     //Create grid

    QFont font;
    font.setPixelSize(18);                                                          //Size of title
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));                                        //Color of title
    chart->setTitle("Lijn grafiek");                                                //Set title for chart

    QPen pen(QRgb(0xD51301));                                                       //Color of line
    pen.setWidth(3);                                                                //Width of line
    series->setPen(pen);                                                            //Set pen (Color and width) in series

    QLinearGradient backgroundGradient;                                             //Background of chart
    backgroundGradient.setColorAt(0.0, QRgb(0x00daff));
    chart->setBackgroundBrush(backgroundGradient);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);                               //Smoothing line

    QMainWindow window;                                                             //Create window
    window.setCentralWidget(chartView);                                             //Fill window
    window.resize(400, 300);                                                        //Resize window
    window.show();                                                                  //Show window

    return a.exec();
}
