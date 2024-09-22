#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem> // C++17 标准库

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    // 检查参数数量
    if (argc != 2) {
        std::cerr << "用法: " << argv[0] << " <图片路径>" << std::endl;
        return -1;
    }

    // 获取图片路径
    std::string inputImagePath = argv[1];

    // 读取原始图像
    cv::Mat colorImage = cv::imread(inputImagePath);
    if (colorImage.empty()) {
        std::cerr << "无法打开或找到图像: " << inputImagePath << std::endl;
        return -1;
    }

    // 转换为 HSV 图像
    cv::Mat hsvImage;
    cv::cvtColor(colorImage, hsvImage, cv::COLOR_BGR2HSV);

    // 获取输出路径
    fs::path inputPath(inputImagePath);
    std::string outputImagePath = inputPath.parent_path().string() + "/hsv_" + inputPath.filename().string();

    // 保存 HSV 图像
    cv::imwrite(outputImagePath, hsvImage);
    std::cout << "HSV 图像已保存到: " << outputImagePath << std::endl;

    return 0;
}