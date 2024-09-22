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

    // 计算裁剪区域的大小
    int width = image.cols / 2;   // 原图宽度的一半
    int height = image.rows / 2;  // 原图高度的一半

    // 裁剪左上角区域
    cv::Rect roi(0, 0, width, height); // 裁剪区域的左上角坐标和大小
    cv::Mat croppedImage = image(roi);

    // 保存裁剪后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/output_image_cropped.jpg";
    saveImage(outputPath, croppedImage);

    // 显示裁剪后的图像
    cv::imshow("裁剪后的图像", croppedImage);
    
    cv::waitKey(0); // 等待按键
    return 0;
}