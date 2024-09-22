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

    // 在图像上绘制矩形
    cv::rectangle(image, cv::Rect(50, 50, 200, 100), cv::Scalar(0, 255, 0), 2); // 绿色矩形

    // 在图像上绘制圆
    cv::circle(image, cv::Point(300, 200), 50, cv::Scalar(255, 0, 0), 2); // 蓝色圆

    // 在图像上绘制文本
    cv::putText(image, "Hello OpenCV!", cv::Point(50, 300), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2); // 红色文本

    // 保存绘制后的图像到原目录
    std::string outputPath = imagePath.substr(0, imagePath.find_last_of('/')) + "/output_image.jpg";
    saveImage(outputPath, image);

    // 显示绘制后的图像
    cv::imshow("绘制后的图像", image);
    
    cv::waitKey(0); // 等待按键
    return 0;
}