#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void saveImage(const std::string& path, const cv::Mat& image) {
    if (cv::imwrite(path, image)) {
        std::cout << "图像已保存到: " << path << std::endl;
    } else {
        std::cerr << "保存图像失败！" << std::endl;
    }
}

std::vector<cv::Point> generateSeedPoints(int rows, int cols) {
    std::vector<cv::Point> seedPoints;

    // 生成四个角落的种子点
    seedPoints.emplace_back(0, 0);                   // 左上角
    seedPoints.emplace_back(cols - 1, 0);            // 右上角
    seedPoints.emplace_back(0, rows - 1);             // 左下角
    seedPoints.emplace_back(cols - 1, rows - 1);     // 右下角

    return seedPoints;
}

int main(int argc, char** argv) {
    // 获取图像的绝对路径
    if (argc < 2) {
        std::cerr << "请提供图像的绝对路径作为参数。" << std::endl;
        return -1;
    }
    std::string imagePath = argv[1];

    // 读取图像
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "无法读取图像！请检查路径是否正确。" << std::endl;
        return -1;
    }

    // 创建一个与原图像相同大小的副本用于填充
    cv::Mat filledImage = image.clone();

    // 生成四个角落的起点
    std::vector<cv::Point> seedPoints = generateSeedPoints(image.rows, image.cols);

    // 对每个种子点进行漫水填充
    for (const auto& seed : seedPoints) {
        cv::Scalar newColor(255, 0, 0); // 填充颜色（蓝色）
        cv::floodFill(filledImage, cv::Mat(), seed, newColor);
    }

    // 保存填充后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/output_image_filled.jpg";
    saveImage(outputPath, filledImage);

    // 显示填充后的图像
    cv::imshow("填充后的图像", filledImage);
    
    cv::waitKey(0); // 等待按键
    return 0;
}
