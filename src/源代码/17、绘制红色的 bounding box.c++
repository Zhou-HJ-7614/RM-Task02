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

    // 转换为灰度图像
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 使用边缘检测找到轮廓
    cv::Mat edges;
    cv::Canny(grayImage, edges, 100, 200);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 在原图上绘制红色的 bounding box
    for (const auto& contour : contours) {
        cv::Rect boundingBox = cv::boundingRect(contour);
        cv::rectangle(image, boundingBox, cv::Scalar(0, 0, 255), 2); // 红色边界框
    }

    // 保存绘制后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/output_image_with_bboxes.jpg";
    saveImage(outputPath, image);

    // 显示绘制后的图像
    cv::imshow("绘制后的图像", image);
    
    cv::waitKey(0); // 等待按键
    return 0;
}