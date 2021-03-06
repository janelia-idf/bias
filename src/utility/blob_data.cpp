#include "blob_data.hpp"
#include "json.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

namespace bias
{

    // Centroid 
    // ----------------------------------------------------------------------------
    Centroid::Centroid()
    {
        x = 0;
        y = 0;
    }


    Centroid::Centroid(cv::Moments moments)
    {
        setFromMoments(moments);
    }


    void Centroid::setFromMoments(cv::Moments moments)
    {
        x = moments.m10/moments.m00;
        y = moments.m01/moments.m00;
    }


    std::string Centroid::toStdString(unsigned int indent)
    {
        std::stringstream ss;
        std::string indentStr0 = getIndentString(indent);
        std::string indentStr1 = getIndentString(indent+1);
        ss << indentStr0 << "centroid:" << std::endl;
        ss << indentStr1 << "x: " << x << std::endl;
        ss << indentStr1 << "y: " << y << std::endl;
        return ss.str();
    }


    void Centroid::print(unsigned int indent)
    {
        std::cout << toStdString(indent);
    }


    // Ellipse
    // ----------------------------------------------------------------------------

    Ellipse::Ellipse()
    {
        centerX = 0;
        centerY = 0;
        semiMajor = 0;
        semiMinor = 0;
        angle = 0;
    }


    Ellipse::Ellipse(std::vector<cv::Point> contour)
    {
        setFromContour(contour);
    }


    void Ellipse::setFromContour(std::vector<cv::Point> contour)
    {
        cv::Mat pointsf;
        cv::Mat(contour).convertTo(pointsf,CV_32F);
        cv::RotatedRect rotRect = cv::fitEllipse(pointsf);
        centerX = rotRect.center.x;
        centerY = rotRect.center.y;
        if (rotRect.size.width > rotRect.size.height)
        {
            semiMajor = 0.5*rotRect.size.width;
            semiMinor = 0.5*rotRect.size.height;
            angle = rotRect.angle;
        }
        else
        {
            semiMajor = 0.5*rotRect.size.height;
            semiMinor = 0.5*rotRect.size.width;
            angle = rotRect.angle + 90.0;
        }
        if (angle > 180.0)
        {
            angle -= 180.0;
        }
    }


    std::string Ellipse::toStdString(unsigned int indent)
    {
        std::stringstream ss;
        std::string indentStr0 = getIndentString(indent);
        std::string indentStr1 = getIndentString(indent+1);
        ss << indentStr0 << "ellipse:" << std::endl;
        ss << indentStr1 << "centerX: " << centerX << std::endl;
        ss << indentStr1 << "centerY: " << centerY << std::endl;
        ss << indentStr1 << "semiMajor: " << semiMajor << std::endl;
        ss << indentStr1 << "semiMinor: " << semiMinor << std::endl;
        ss << indentStr1 << "angle: " << angle << std::endl;
        return ss.str();
    }


    void Ellipse::print(unsigned int indent)
    {
        std::cout << toStdString(indent);
    }


    void Ellipse::draw(cv::Mat &img)
    { 
        cv::Point lineStart; 
        cv::Point lineStop;

        // Plot major axis
        lineStart.x = centerX - semiMajor*std::cos(M_PI*angle/180.0);
        lineStart.y = centerY - semiMajor*std::sin(M_PI*angle/180.0);
        lineStop.x = centerX + semiMajor*std::cos(M_PI*angle/180.0);
        lineStop.y = centerY + semiMajor*std::sin(M_PI*angle/180.0);
        cv::line(img,lineStart,lineStop,cv::Scalar(0,255,0),2,8);

        // Plot limor axis
        double anglePlus90 = angle + 90.0;
        lineStart.x = centerX - semiMinor*std::cos(M_PI*anglePlus90/180.0);
        lineStart.y = centerY - semiMinor*std::sin(M_PI*anglePlus90/180.0);
        lineStop.x = centerX + semiMinor*std::cos(M_PI*anglePlus90/180.0);
        lineStop.y = centerY + semiMinor*std::sin(M_PI*anglePlus90/180.0);
        cv::line(img,lineStart,lineStop,cv::Scalar(0,255,0),2,8);

        // Plot ellipse
        cv::Point centerPt = cv::Point(centerX, centerY);
        cv::Size size = cv::Size(semiMajor, semiMinor);
        cv::ellipse(img,centerPt,size,angle,0,360,cv::Scalar(0,255,0),2,8);
    }


    // Blob Data
    // ----------------------------------------------------------------------------
    const long BlobData::ID_NOT_ASSIGNED = -1;

    BlobData::BlobData()
    {
        id = ID_NOT_ASSIGNED;
        old = false;
        onBorderX = false;
        onBorderY = false;
        area = 0;
    }


    BlobData::BlobData(
            std::vector<cv::Point> contour, 
            cv::Mat image, 
            unsigned int numPad
            ) : BlobData()
    {
        setFromContour(contour,image, numPad);

    }


    void BlobData::setFromContour(
            std::vector<cv::Point> contour, 
            cv::Mat image, 
            unsigned int numPad
            )
    {
        contourVector = contour;

        // Calculate moments
        cv::Moments moments = cv::moments(contour);
        area = moments.m00;
        centroid = Centroid(moments);

        // Determine bounding rectangle
        cv::Rect contourRect = cv::boundingRect(cv::Mat(contour));
        int x = std::max(0, contourRect.x-int(numPad));
        int y = std::max(0, contourRect.y-int(numPad));
        int w = contourRect.width + 2*numPad;
        int h = contourRect.height + 2*numPad;
        if ((x+w) > image.cols)
        {
            w = image.cols-x; 
        }
        if ((y+h) > image.rows)
        {
            h = image.rows-y;
        }
        boundingRect = cv::Rect(x,y,w,h);
        cv::Mat subImage = image(boundingRect);
        subImage.copyTo(boundingImage);

        // Check for data on x and y borders
        if ((x <= 0) || ((x+w) >= (image.cols-1)))
        {
            onBorderX = true;
        }
        else
        {
            onBorderX = false;
        }
        if ((y <= 0) || ((y+h) >= (image.rows-1)))
        {
            onBorderY = true;
        }
        else
        {
            onBorderY = false;
        }

        // Fit ellipse
        if (contour.size() >= 5)
        {
            ellipse = Ellipse(contour);
        }

    }


    std::string BlobData::toStdString(unsigned int indent)
    {
        std::stringstream ss;
        std::string indentStr0 = getIndentString(indent);
        std::string indentStr1 = getIndentString(indent+1);
        std::string indentStr2 = getIndentString(indent+2);
        ss << indentStr0 << "blobData:" << std::endl;
        ss << indentStr1 << "id: " << id << std::endl;
        ss << indentStr1 << "old: " << old << std::endl;
        ss << indentStr1 << "area: " << area << std::endl;
        ss << indentStr1 << "onBorderX: " << onBorderX << std::endl;
        ss << indentStr1 << "onBorderY: " << onBorderY << std::endl;
        ss << centroid.toStdString(indent+1);
        ss << ellipse.toStdString(indent+1);
        ss << indentStr1 << "boudningRect: " << std::endl;
        ss << indentStr2 << "x: " << boundingRect.x << std::endl;
        ss << indentStr2 << "y: " << boundingRect.y << std::endl;
        ss << indentStr2 << "width: " << boundingRect.width << std::endl;
        ss << indentStr2 << "height: " << boundingRect.height << std::endl;
        ss << indentStr1 << "boundingImage: (not shown) " << std::endl;
        ss << indentStr1 << "contourVector: (not shown) " << std::endl;
        return ss.str();
    }


    void BlobData::print(unsigned int indent)
    {
        std::cout << toStdString(indent);
    }


    void BlobData::draw(cv::Mat &img)
    { 
        std::vector<std::vector<cv::Point>> contourArray;
        contourArray.push_back(contourVector);
        //cv::drawContours(img, contourArray, 0, cv::Scalar(0,0,255),2,8);
        //ellipse.draw(img);
        cv::rectangle(img, boundingRect, cv::Scalar(0,0,255),2,8);
    }


    bool BlobData::isOnBorder()
    {
        return onBorderX || onBorderY;
    }


    // Utility functions
    // ----------------------------------------------------------------------------


    std::string getIndentString(unsigned int indent, unsigned indentStep)
    {
        std::string indentString;
        for (unsigned int i=0; i<indent; i++)
        {
            for (unsigned int j=0; j<indentStep; j++)
            {
                indentString.append(" ");
            }
        }
        return indentString;
    }


    int getNumBlobsExcludeXBorder(BlobDataList blobDataList)
    {
        int num = 0;
        BlobDataList::iterator it;
        for (it = blobDataList.begin(); it != blobDataList.end(); it++)
        {
            BlobData blobData = *it;
            if (!blobData.onBorderX)
            {
                num++;
            }
        }
        return num;
    }


    int getNumBlobsExcludeYBorder(BlobDataList blobDataList)
    {
        int num = 0;
        BlobDataList::iterator it;
        for (it = blobDataList.begin(); it != blobDataList.end(); it++)
        {
            BlobData blobData = *it;
            if (!blobData.onBorderY)
            {
                num++;
            }
        }
        return num;
    }


} // namespace bias
