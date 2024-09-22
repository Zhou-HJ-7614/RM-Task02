#include <opencv2/opencv.hpp>
#include <iostream>

std::string getOutputPath(const std::string& inputPath, const std::string& suffix) {
    size_t lastSlash = inputPath.find_last_of("/\\");
    if (lastSlash == std::string::npos) {
        return suffix + "_" + inputPath;
    }
    std::string directory = inputPath.substr(0, lastSlash);
    std::string filename = inputPath.substr(lastSlash + 1);
    return directory + "/" + suffix + "_" + filename;
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

    // 找到轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(redMask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 创建一个空白图像用于绘制轮廓
    cv::Mat contourImage = cv::Mat::zeros(colorImage.size(), CV_8UC3);

    // 绘制轮廓
    cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 0, 255), 2); // 红色轮廓

    // 保存结果
    std::string outputContoursPath = getOutputPath(inputImagePath, "contours");
    cv::imwrite(outputContoursPath, contourImage);
    std::cout << "轮廓已保存到: " << outputContoursPath << std::endl;

    return 0;
}