#include <opencv2/opencv.hpp>
#include <iostream>

void calculateContourAreas(const std::vector<std::vector<cv::Point>>& contours) {
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        std::cout << "轮廓 " << i << " 的面积: " << area << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "请提供图像路径！" << std::endl;
        return -1;
    }

    // 读取图像
    std::string imagePath = argv[1];
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "无法读取图像！" << std::endl;
        return -1;
    }

    // 转换为 HSV
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    // 阈值处理（根据需要调整阈值）
    cv::Mat mask;
    cv::inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 计算轮廓面积
    calculateContourAreas(contours);

    return 0;
}