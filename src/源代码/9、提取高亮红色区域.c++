#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // 使用示例图像，如果没有提供路径，则使用默认图像
    std::string imagePath = (argc > 1) ? argv[1] : "images/your_image.jpg";

    // 读取图像
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "无法读取图像！请检查路径是否正确。" << std::endl;
        return -1;
    }

    // 缩小图像（例如，缩放到原始尺寸的 50%）
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(), 0.5, 0.5); // 50% 缩放

    // 转换为 HSV 色彩空间
    cv::Mat hsvImage;
    cv::cvtColor(resizedImage, hsvImage, cv::COLOR_BGR2HSV);

    // 定义高亮红色的 HSV 范围
    cv::Scalar lowerBrightRed(0, 150, 150);
    cv::Scalar upperBrightRed(10, 255, 255);
    cv::Scalar lowerBrightRed2(160, 150, 150);
    cv::Scalar upperBrightRed2(180, 255, 255);

    // 创建掩膜
    cv::Mat mask1, mask2;
    cv::inRange(hsvImage, lowerBrightRed, upperBrightRed, mask1);
    cv::inRange(hsvImage, lowerBrightRed2, upperBrightRed2, mask2);
    
    // 合并掩膜
    cv::Mat mask;
    cv::bitwise_or(mask1, mask2, mask);

    // 通过掩膜提取高亮红色区域
    cv::Mat result;
    cv::bitwise_and(resizedImage, resizedImage, result, mask);

    // 保存提取的高亮红色区域到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/extracted_red_area.jpg";
    cv::imwrite(outputPath, result);

    // 显示提取的高亮红色区域
    cv::imshow("提取的高亮红色区域", result);
    
    cv::waitKey(0); // 等待按键
    return 0;
}