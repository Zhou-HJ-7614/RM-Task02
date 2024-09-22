#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    // 检查命令行参数
    if (argc != 3) {
        std::cerr << "用法: " << argv[0] << " <输入图像> <输出图像>" << std::endl;
        return -1;
    }

    // 读取输入图像
    cv::Mat colorImage = cv::imread(argv[1]);
    if (colorImage.empty()) {
        std::cerr << "无法读取图像: " << argv[1] << std::endl;
        return -1;
    }

    // 转换为灰度图
    cv::Mat grayImage;
    cv::cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);

    // 保存输出图像
    cv::imwrite(argv[2], grayImage);

    std::cout << "图像转换完成: " << argv[2] << std::endl;
    return 0;
}