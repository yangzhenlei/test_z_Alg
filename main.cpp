#include <QCoreApplication>
#include <QDebug>

typedef struct DataStruct
{
    quint16  StepNumber;
    quint16 stepCycle;
    float Channel1[96];
    float Channel2[96];
    float Channel3[96];
    float Channel4[96];
    float Channel5[96];
    float Channel6[96];
    DataStruct()
    {
        for(int i=0;i<96;i++)
        {
            Channel1[i]=0;
            Channel2[i]=0;
            Channel3[i]=0;
            Channel4[i]=0;
            Channel5[i]=0;
            Channel6[i]=0;
        }
    }
}Data;

typedef struct Data2FileStruct
{
//    QPCRProgramProcess::Program Program;
    QList<QList<Data>> AllStepsData;
//    QList<MeltingData> AllMeltingData;
    QList<QList<Data>> RawAmpData;
 }Data2File;

Data2File *_Data2File = new Data2File;

void _BumpyPlateauFix(int step, int wellPos, int channel, int cycles, int totalCycles, float slopeThreshold, float dampCoeff)
{
    for (int cycle =0;cycle <3; cycle ++)
    {
        switch(channel)
        {
        case 0:
            _Data2File->AllStepsData[step][cycle].Channel1[wellPos]=_Data2File->RawAmpData[step][cycle].Channel1[wellPos];
            break;
        case 1:
            _Data2File->AllStepsData[step][cycle].Channel2[wellPos]=_Data2File->RawAmpData[step][cycle].Channel2[wellPos];
            break;
        case 2:
            _Data2File->AllStepsData[step][cycle].Channel3[wellPos]=_Data2File->RawAmpData[step][cycle].Channel3[wellPos];
            break;
        case 3:
            _Data2File->AllStepsData[step][cycle].Channel4[wellPos]=_Data2File->RawAmpData[step][cycle].Channel4[wellPos];
            break;
        case 4:
            _Data2File->AllStepsData[step][cycle].Channel5[wellPos]=_Data2File->RawAmpData[step][cycle].Channel5[wellPos];
            break;
        case 5:
            _Data2File->AllStepsData[step][cycle].Channel6[wellPos]=_Data2File->RawAmpData[step][cycle].Channel6[wellPos];
            break;
        }
        if(cycle==cycles-1)
        {
            return;
        }
    }
    if (cycles < 4)
    {
        return;
    }

    float slopeMax, crntSlope, lastSlope;
    int slopeMaxIndex;
    for (int cycle = 3; cycle < cycles+1; cycle++)
    {
        // determine the slopeMax
        slopeMax = 0;
        slopeMaxIndex = 0;
        for (int loop = 2; loop < cycle; loop++)
        {
            switch(channel)
            {
            case 0:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel1[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel1[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel1[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel1[wellPos];
                break;
            case 1:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel2[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel2[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel2[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel2[wellPos];
                break;
            case 2:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel3[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel3[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel3[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel3[wellPos];
                break;
            case 3:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel4[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel4[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel4[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel4[wellPos];
                break;
            case 4:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel5[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel5[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel5[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel5[wellPos];
                break;
            case 5:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel6[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel6[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel6[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel6[wellPos];
                break;
            default:
                crntSlope = _Data2File->AllStepsData[step][loop].Channel1[wellPos] - _Data2File->AllStepsData[step][loop - 1].Channel1[wellPos];
                lastSlope = _Data2File->AllStepsData[step][loop-1].Channel1[wellPos] - _Data2File->AllStepsData[step][loop - 2].Channel1[wellPos];
                break;
            }

            if (crntSlope > 0 && lastSlope > 0 && crntSlope > slopeMax)
            {
                if (crntSlope > slopeThreshold)
                {
                    slopeMax = crntSlope;
                    slopeMaxIndex = loop;
                }
            }
        }
        if (slopeMax == 0)
        {
            switch(channel)
            {
            case 0:
                _Data2File->AllStepsData[step][cycle].Channel1[wellPos] = _Data2File->RawAmpData[step][cycle].Channel1[wellPos];
                break;
            case 1:
                _Data2File->AllStepsData[step][cycle].Channel2[wellPos] = _Data2File->RawAmpData[step][cycle].Channel2[wellPos];
                break;
            case 2:
                _Data2File->AllStepsData[step][cycle].Channel3[wellPos] = _Data2File->RawAmpData[step][cycle].Channel3[wellPos];
                break;
            case 3:
                _Data2File->AllStepsData[step][cycle].Channel4[wellPos] = _Data2File->RawAmpData[step][cycle].Channel4[wellPos];
                break;
            case 4:
                _Data2File->AllStepsData[step][cycle].Channel5[wellPos] = _Data2File->RawAmpData[step][cycle].Channel5[wellPos];
                break;
            case 5:
                _Data2File->AllStepsData[step][cycle].Channel6[wellPos] = _Data2File->RawAmpData[step][cycle].Channel6[wellPos];
                break;
            }
            continue;
        }
        switch(channel)
        {
        case 0:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel1[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel1[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel1[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel1[wellPos];
            break;
        case 1:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel2[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel2[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel2[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel2[wellPos];
            break;
        case 2:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel3[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel3[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel3[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel3[wellPos];
            break;
        case 3:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel4[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel4[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel4[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel4[wellPos];
            break;
        case 4:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel5[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel5[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel5[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel5[wellPos];
            break;
        case 5:
            crntSlope = _Data2File->RawAmpData[step][cycle].Channel6[wellPos] - _Data2File->AllStepsData[step][cycle - 1].Channel6[wellPos];
            lastSlope = _Data2File->AllStepsData[step][cycle-1].Channel6[wellPos] - _Data2File->AllStepsData[step][cycle - 2].Channel6[wellPos];
            break;
        }
        bool fix=false;
        if (crntSlope > lastSlope)
        {
            if (slopeMaxIndex == cycle - 1)
            {
                // data is saturated, make it smoothly
                if (crntSlope==0)
                {
                    fix=true;
                }
            }
            else
            {
                fix=true;
            }
        }
        else
        {
            if (crntSlope < 0)
            {
                fix=true;
            }
            else
            {
                // data is saturated, make it smoothly
                if (crntSlope == 0)
                {
                    fix=true;
                }
            }
        }

        if(fix)
        {
            switch(channel)
            {
            case 0:
                _Data2File->AllStepsData[step][cycle].Channel1[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel1[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            case 1:
                _Data2File->AllStepsData[step][cycle].Channel2[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel2[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            case 2:
                _Data2File->AllStepsData[step][cycle].Channel3[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel3[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            case 3:
                _Data2File->AllStepsData[step][cycle].Channel4[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel4[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            case 4:
                _Data2File->AllStepsData[step][cycle].Channel5[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel5[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            case 5:
                _Data2File->AllStepsData[step][cycle].Channel6[wellPos] = _Data2File->AllStepsData[step][cycle - 1].Channel6[wellPos] + lastSlope * (totalCycles  - cycle * dampCoeff) / totalCycles;
                break;
            }
        }
        else
        {
            switch(channel)
            {
            case 0:
                _Data2File->AllStepsData[step][cycle].Channel1[wellPos] = _Data2File->RawAmpData[step][cycle].Channel1[wellPos];
                break;
            case 1:
                _Data2File->AllStepsData[step][cycle].Channel2[wellPos] = _Data2File->RawAmpData[step][cycle].Channel2[wellPos];
                break;
            case 2:
                _Data2File->AllStepsData[step][cycle].Channel3[wellPos] = _Data2File->RawAmpData[step][cycle].Channel3[wellPos];
                break;
            case 3:
                _Data2File->AllStepsData[step][cycle].Channel4[wellPos] = _Data2File->RawAmpData[step][cycle].Channel4[wellPos];
                break;
            case 4:
                _Data2File->AllStepsData[step][cycle].Channel5[wellPos] = _Data2File->RawAmpData[step][cycle].Channel5[wellPos];
                break;
            case 5:
                _Data2File->AllStepsData[step][cycle].Channel6[wellPos] = _Data2File->RawAmpData[step][cycle].Channel6[wellPos];
                break;
            }
        }
    }


}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    float srcy[40] = { 1.119964,1.101604,1.103899,1.108489,1.102752,1.106194,1.108489,1.110784,1.129144,1.157832,1.215207,1.335695,1.568638,2.0001,2.757453,4.008233,5.701949,7.49894,8.769228,9.611497,10.17951,10.60179,10.89785,11.07915,11.21456,11.34652,11.40046,11.44521,11.4743,11.49284,11.50443,11.51153,11.51579,11.51829,11.51973,11.52054,11.52099,11.52123,11.52135,11.52142 };

    DataStruct data1,data2;
    QList<Data> Listdata1,Listdata2;

    for (int i = 0;i<40;i++) {
        data1.Channel1[0] = srcy[i];
        Listdata1.append(data1);
        data2.Channel1[0] = 0;
        Listdata2.append(data2);
    }

    _Data2File->RawAmpData.append(Listdata1);
    _Data2File->AllStepsData.append(Listdata2);

    int step = 0;
    int channel = 0;
    int wellpos = 0;
    int totalCycles = 40;

    for (int my_clcles = 0;my_clcles<40;my_clcles++) {
        _BumpyPlateauFix(step,wellpos,channel,my_clcles,totalCycles,0.5,0.5);
    }

    for (int i=0;i<40;i++) {
        qDebug() << i << ":  "<< "AllStepsData:" << _Data2File->AllStepsData[0][i].Channel1[0]
                    << "  ;  RawAmpData:" << _Data2File->RawAmpData[0][i].Channel1[0]<<endl;
    }

    return a.exec();
}
