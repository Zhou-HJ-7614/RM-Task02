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

    // 获取图像中心
    cv::Point2f center(image.cols / 2.0f, image.rows / 2.0f);

    // 计算旋转矩阵
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, 35, 1.0); // 旋转 35 度

    // 进行仿射变换
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());

    // 保存旋转后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/output_image_rotated.jpg";
    saveImage(outputPath, rotatedImage);

    // 显示旋转后的图像
    cv::imshow("旋转后的图像", rotatedImage);
    
    cv::waitKey(0); // 等待按键
    return 0;
}