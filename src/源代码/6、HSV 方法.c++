#include <opencv2/opencv.hpp>
#include <iostream>

std::string getOutputPath(const std::string& inputPath) {
    size_t lastSlash = inputPath.find_last_of("/\\");
    if (lastSlash == std::string::npos) {
        return "red_extracted_" + inputPath;
    }
    std::string directory = inputPath.substr(0, lastSlash);
    std::string filename = inputPath.substr(lastSlash + 1);
    return directory + "/red_extracted_" + filename;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "用法: " << argv[0] << " <图片路径>" << std::endl;
        return -1;
    }

    std::string inputImagePath = argv[1];
    cv::Mat colorImage = cv::imread(inputImagePath);
    if (colorImage.empty()) {
        std::cerr << "无法打开或找到图像: " << inputImagePath << std::endl;
        return -1;
    }

    // 转换为 HSV 颜色空间
    cv::Mat hsvImage;
    cv::cvtColor(colorImage, hsvImage, cv::COLOR_BGR2HSV);

    // 定义红色的 HSV 范围
    cv::Scalar lowerRed1(0, 100, 100);
    cv::Scalar upperRed1(10, 255, 255);
    cv::Scalar lowerRed2(160, 100, 100);
    cv::Scalar upperRed2(180, 255, 255);

    // 创建掩膜
    cv::Mat mask1, mask2, redMask;
    cv::inRange(hsvImage, lowerRed1, upperRed1, mask1);
    cv::inRange(hsvImage, lowerRed2, upperRed2, mask2);
    redMask = mask1 | mask2;

    // 提取红色区域
    cv::Mat redExtracted;
    cv::bitwise_and(colorImage, colorImage, redExtracted, redMask);

    // 保存结果
    std::string outputImagePath = getOutputPath(inputImagePath);
    cv::imwrite(outputImagePath, redExtracted);
    std::cout << "提取的红色区域已保存到: " << outputImagePath << std::endl;

    return 0;
}