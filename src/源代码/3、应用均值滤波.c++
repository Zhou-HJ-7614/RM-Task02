#include <opencv2/opencv.hpp>
#include <iostream>

std::string getOutputPath(const std::string& inputPath) {
    size_t lastSlash = inputPath.find_last_of("/\\");
    if (lastSlash == std::string::npos) {
        return "filtered_" + inputPath;  // 如果没有路径，直接返回文件名
    }
    std::string directory = inputPath.substr(0, lastSlash);
    std::string filename = inputPath.substr(lastSlash + 1);
    return directory + "/filtered_" + filename;
}

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

    // 应用均值滤波
    cv::Mat filteredImage;
    cv::blur(colorImage, filteredImage, cv::Size(5, 5));  // 5x5的均值滤波

    // 获取输出路径
    std::string outputImagePath = getOutputPath(inputImagePath);

    // 保存滤波后的图像
    cv::imwrite(outputImagePath, filteredImage);
    std::cout << "滤波后的图像已保存到: " << outputImagePath << std::endl;

    return 0;
}