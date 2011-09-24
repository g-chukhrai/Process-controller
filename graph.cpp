#include "graph.h"
#include "math.h"
#include "resultwindow.h"

// конструктор обработчика
Graph::Graph(QList<QStringList> m ,QStringList names,QStringList values)
{
    // задание значений матрицы, имен и весов вершин
    matrix = m;
    vertexNames = names;   
    valueList = values;
}

// функция распараллеливания процессов
QList<QPair<QString,QString> > * Graph::startDealing(int countProc)
{
    // установка количества процессоров
    procCount = countProc;
    // выделение памяти для списка результатов
    QList<QPair<QString,QString> > *result = new QList<QPair<QString,QString> >[procCount];

    // пока матрица содержит значения
    while (matrix.count() != 0)
    {
        // найти все входы в матрицу
        QList<QPair<QString,QString> > enters;
        enters = findEnters();

        // для всех входов
        for (int i = 0 ; i < enters.count() ; i++)
        {
            int index = vertexNames.indexOf(enters[i].first);

            // удалить входы из матрицы
            for (int j = 0; j < matrix.count() ; j++)
                matrix[j].removeAt(index);
            matrix.removeAt(index);

            // удалить входы из списков имен и весов
            vertexNames.removeAt(index);
            valueList.removeAt(index);
        }

        int prC = procCount;
        int lastProc = procCount-1;
        // цикл нахождения распределения процессов
        for (int i = 0 ; i < procCount-1; i++)
        {
            // нахождение распределения входов на количество процессоров
            QList<QPair<QString,QString> > toProcessor = dealingProcess(enters,prC);

            // проосмотр найденного распределения
            for (int j = 0; j < toProcessor.count() ; j++)
            {
                // добавление процесса к процессору
                result[i] << toProcessor[j];
                // удаление процесса из списка входов
                enters.removeOne(toProcessor[j]);
            }
            prC--;
            // если список входов пуст
            if (enters.count() == 0)
            {
                // закончить цикл
                lastProc = i+1;
                break;
            }
        }
        // для оставшихся входов
        for (int j = 0 ; j < enters.count() ; j++)
        {
            // присвоить входы последнему процессору
            result[lastProc] << enters[j];
        }        
        // нахождение максимального времени выполнения процессов
        int max=-1;
        for (int i = 0 ; i < procCount; i++)
        {
            int summ = 0 ;
            for (int j = 0 ; j < result[i].count(); j++)
                summ += result[i][j].second.toInt();
            if(max < summ)
                max = summ;
        }

        // если время выполнения меньше максимального то добавить процесс простоя процессора
        for (int i = 0 ; i < procCount; i++)
        {
            int summ = 0 ;
            for (int j = 0 ; j < result[i].count(); j++)
                summ += result[i][j].second.toInt();
            if(summ < max)
            {
                QPair<QString,QString> pair;
                pair.first = "wait";
                pair.second = QString::number(max-summ);
                result[i] << pair;
            }
        }
    }
    // вернуть список результатов
    return result;
}

// функция нахождения входов матрицы
QList<QPair<QString,QString> > Graph::findEnters()
{
    QList<QPair<QString,QString> > enters;

    // нахождение размера матрицы
    int tableSize = matrix.count();

    // проход по столбцам матрицы
    for(int j = 0 ; j < tableSize ; j++)
    {
        bool isEnter = true;
        for (int i = 0 ; i < tableSize ; i++)
        {
            // если ячейка столбца содержит единицу значит процесс не является входом
            if (matrix[i][j] == "1")
            {
                isEnter = false;
                break;
            }
        }
        // если процесс является входом
        if (isEnter == true)
        {
            // добавить процесс к списку входов
            QPair<QString,QString> pair;
            pair.first = vertexNames[j];
            pair.second = valueList[j];
            enters << pair;
        }
    }
    // вернуть результаты
    return enters;
}

// функция распределения процессов на заданное количество процессоров
QList<QPair<QString,QString> > Graph::dealingProcess(QList<QPair<QString,QString> > procList, int prCount)
{
    // нахождение среднего времени выполнения всех процессов
    double t0 = 0;
    for (int i = 0; i < procList.count() ; i++)
        t0 += procList[i].second.toInt();
    t0 /= prCount;

    // сортировка процессов в порядке увеличения времени выпонения
    for (int i = 0 ; i < procList.count()-1 ; i++)
    {
        if (procList[i].second.toInt() > procList[i+1].second.toInt())
        {
            procList.swap(i,i+1);
            i=-1;
        }
    }

    double ds = 0;
    int index;    
    // нахождение позиции для начала поиска процессов
    for (int i = 0; i < procList.count() ; i++)
    {
        ds += procList[i].second.toInt();
        if (ds > t0)
        {
            index = i;
            break;
        }
    }  
    // создание двоичной строки
    QStringList mLine;
    for (int i = 0; i < procList.count() ; i++)
    {
        if (i == index)
            mLine << "1";
        else
            mLine << "0";
    }
    double min = t0+1;
    QStringList minMLine;
    bool cont = true;
    // выполнять увеличение строки пока не будет найдено время ближайшее к минимальному
    while(cont)
    {       
        // нахождение разницы среднего и текущего времени выполения процессов
        double sd=0;
        for (int i = 0; i < mLine.count() ; i++)
        {
            if (mLine[i] == "1")
                sd += procList[i].second.toInt();
        }
        sd -= t0;

        // если минимальное значение больше модуля разности
        if (min >= fabs(sd))
        {
            // присвоить минимальному значению новое значение
            min = fabs(sd);
            // установить новую минимаьлную двоичную строку
            minMLine = mLine;
        }        
        // если разница равна нулю значит было найдено наилучшее распределение процессов
        if (sd == 0)
        {
            cont = false;
            break;
        }
        // если разница больше нуля
        if (sd > 0)
        {
            // если в двоичной строке одна единица значит распределить этот процесс
            if (mLine.count("1") == 1)
            {
                cont = false;
                break;
            }
            // иначе если более одной единицы
            else if (mLine.count("1") > 1)
            {               
                // если последниий символ двоичной строки единица то поиск продолжать бессмысленно
                if (mLine.last() == "1")
                {
                    cont = false;
                    break;
                }
                // иначе произвести преобразование двоичной строки
                else
                {
                    // найти индекс второй единицы
                    int firInd = mLine.indexOf("1");
                    int secInd = mLine.indexOf("1",firInd+1);
                    int thInd = mLine.indexOf("0",secInd+1);
                    secInd = thInd-1;
                    // все значения строки до индекса занулить, а следующее установить равным единице
                    for (int i = 0 ; i <= secInd ; i++)
                    {
                        if (mLine[i] == "1")
                            mLine[i] = "0";
                    }
                    mLine[secInd+1] = "1";                    
                    continue;
                }
            }
        }        
        // произвести увеличение двоичной строки на единицу
        for (int i = 0 ; i < mLine.count() ; i++)
        {
            if( mLine[i] == "1")
            {
                mLine[i] = "0";
            }
            else
            {
                mLine[i] = "1";
                break;
            }
        }
        // если двоичная строка не содержит единицу прекратить поиск
        if (!mLine.contains("1"))
            cont = false;
    }

    // проанализировать минимальное значение и минимальную строку
    QList<QPair<QString,QString> > result;
    for (int i = 0 ; i < minMLine.count() ; i++)
    {
        // добавить к списку результатов процессы соответствующие единице в строке
        if (minMLine[i] == "1")
            result << procList[i];
    }
    // возвратить распределение
    return result;
}

// деструктор обработчика
Graph::~Graph()
{
    matrix.clear();
    vertexNames.clear();
    valueList.clear();
}


