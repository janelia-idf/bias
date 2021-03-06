#include "gender_sorter.hpp"
#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>

// GenderData
// ----------------------------------------------------------------------------
GenderData::GenderData()
{
    gender = GenderData::UNKNOWN;
    havePredictorData = false;
};


std::string GenderData::toStdString(unsigned int indent)
{
    std::stringstream ss;
    std::string indentStr0 = getIndentString(indent);
    std::string indentStr1 = getIndentString(indent+1);
    std::string indentStr2 = getIndentString(indent+2);
    std::string genderStr = GenderSorter::GenderToString(gender);
    ss << indentStr0 << "GenderData: " << std::endl;
    ss << indentStr1 << "gender: " << genderStr << std::endl; 
    ss << indentStr1 << "havePredictorData: " << havePredictorData << std::endl;
    ss << indentStr1 << "predictorData: "; 
    if (havePredictorData)
    {
        ss << std::endl;
        ss << indentStr2 << "label: " << predictorData.label << std::endl;
        ss << indentStr2 << "fit: " << predictorData.fit << std::endl;
    }
    else
    {
        ss << " none" << std::endl;
    }
    ss << positionData.toStdString(indent+1);
    return ss.str();
}


void GenderData::print(unsigned int indent)
{
    std::cout << toStdString(indent);
}


// GenderSorter
// ----------------------------------------------------------------------------
GenderSorter::GenderSorter() {};


GenderSorter::GenderSorter(GenderSorterParam param) : GenderSorter()
{
    setParam(param);
}


void GenderSorter::setParam(GenderSorterParam param)
{
    param_ = param;
}

GenderSorterData GenderSorter::sort(HogPositionFitterData hogData)
{
    GenderSorterData sorterData;
    PositionDataList::iterator it;
    int cnt = 0;
    for (it=hogData.positionDataList.begin(); it!=hogData.positionDataList.end(); it++)
    {
        GenderData genderData;
        genderData.gender = GenderData::UNKNOWN;
        genderData.havePredictorData = false;
        genderData.positionData = *it;

        if (genderData.positionData.success)
        {
            FastBinaryPredictor genderPred = FastBinaryPredictor(param_.classifier);
            genderData.predictorData = genderPred.predict(genderData.positionData.pixelFeatureVector);
            genderData.havePredictorData = true;
            if (genderData.predictorData.fit >= param_.minConfidence)
            {
                genderData.gender = GenderData::FEMALE;
            }
            if (genderData.predictorData.fit <= -param_.minConfidence)
            {
                genderData.gender = GenderData::MALE;
            }

            // DEBUG -- print gender info
            // ---------------------------------------------------------------------------
            std::cout << "GenderSorter: ";
            std::cout << "frame: " << genderData.positionData.frameCount << ", "; 
            std::cout << "fit: " << genderData.predictorData.fit << ",  "; 
            std::cout << GenderSorter::GenderToString(genderData.gender);
            std::cout << std::endl;
            // ----------------------------------------------------------------------------
            
            // DEBUG -- write pvec and fitness
            // ----------------------------------------------------------------------------
            //QString fileName = QString("pVec_frm_%1_cnt_%2.txt").arg(genderData.positionData.frameCount+1).arg(cnt+1);
            //std::cout << fileName.toStdString() << std::endl;
            //std::ofstream outStream;
            //outStream.open(fileName.toStdString());
            //outStream << genderData.predictorData.fit << std::endl;
            //for (int i=0; i<genderData.positionData.pixelFeatureVector.size();i++)
            //{
            //    outStream << genderData.positionData.pixelFeatureVector[i] << std::endl;
            //}
            //outStream.close();
            // -----------------------------------------------------------------------------

            cnt++;
        }
        sorterData.genderDataList.push_back(genderData);
    }
    return sorterData;
}

std::string GenderSorter::GenderToString(GenderData::Gender gender)
{
    std::string genderString;

    switch (gender)
    {
        case GenderData::FEMALE:
            genderString = std::string("female");
            break;

        case GenderData::MALE:
            genderString = std::string("male");
            break;

        default:
            genderString = std::string("unknown");
            break;

    }
    return genderString;
}


std::string GenderSorter::GenderToLetter(GenderData::Gender gender)
{
    std::string letterString;
    switch (gender)
    {
        case GenderData::FEMALE:
            letterString = std::string("F");
            break;

        case GenderData::MALE:
            letterString = std::string("M");
            break;

        default:
            letterString = std::string("U");
            break;

    }
    return letterString;
}
