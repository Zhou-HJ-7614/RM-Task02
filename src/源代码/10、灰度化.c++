#include <opencv2/opencv.hpp>
#include <iostream>

void saveImage(const std::string& path, const cv::Mat& image) {
    if (cv::imwrite(path, image)) {
        std::cout << "图像已保存到: " << path << std::endl;
    } else {
        std::cerr << "保存图像失败！" << std::endl;
    }
}

int main(int argc, char** argv) {
    // 使用示例图像，如果没有提供路径，则使用默认图像
    std::string imagePath = (argc > 1) ? argv[1] : "images/your_image.jpg";

    // 读取图像
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "无法读取图像！请检查路径是否正确。" << std::endl;
        return -1;
    }

    // 灰度化图像
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 保存灰度化后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/gray_image.jpg";
    saveImage(outputPath, grayImage);

    // 显示灰度化后的图像
    cv::imshow("灰度化图像", grayImage);
    
    cv::waitKey(0); // 等待按键
    return 0;
}