#ifndef BIAS_BACKGROUND_DATA_UFMF_HPP
#define BIAS_BACKGROUND_DATA_UFMF_HPP
#include <memory>

namespace bias
{
    class StampedImage;

    class BackgroundData_ufmf
    {
        public:
            BackgroundData_ufmf();
            BackgroundData_ufmf( 
                    StampedImage stampedImg, 
                    unsigned int numBins, 
                    unsigned int binSize
                    );
            void addImage(StampedImage stampedImg);
            std::shared_ptr<float> getMedians();
            void clear();

        private:
            std::shared_ptr<unsigned int>  binPtr_;
            std::shared_ptr<unsigned long> cntPtr_;
            unsigned int numRows_;
            unsigned int numCols_;
            unsigned int numBins_;
            unsigned int binSize_;
            bool isFirst_;

    };
}

#endif // #ifndeff BIAS_BACKGROUND_DATA_UFMF_HPP
