#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

int main() {
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        std::cerr << "Ошибка: не удалось открыть камеру!" << std::endl;
        return -1;
    }

    cv::Mat frame, transformedFrame;
    int frameCount = 0;
    int fpsCount = 0;
    double totalTime = 0.0;

    auto fpsTimer = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        // Захват кадра
        auto st3 = std::chrono::high_resolution_clock::now();
        capture.read(frame);
        auto ed3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> t3 = ed3 - st3;
        std::cout << t3.count() * 1000 << std::endl;
        
        if (frame.empty()) break;

        auto st1 = std::chrono::high_resolution_clock::now();
        // Произвольное преобразование (например, перевод в оттенки серого)
        cv::cvtColor(frame, transformedFrame, cv::COLOR_BGR2GRAY);
        auto ed1 = std::chrono::high_resolution_clock::now();


        // Показ измененного кадраd
        auto st2 = std::chrono::high_resolution_clock::now();
        cv::imshow("Camera", transformedFrame);
        auto ed2 = std::chrono::high_resolution_clock::now();

        // Измерение времени обработки
        frameCount++;
        fpsCount++;

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeSinceLastFPS = currentTime - fpsTimer;

        if (timeSinceLastFPS.count() >= 1.0) {
            std::cout << "FPS за последнюю секунду: " << fpsCount << std::endl;
            fpsCount = 0;
            fpsTimer = currentTime;

            std::chrono::duration<double> t1 = ed1 - st1;
            std::chrono::duration<double> t2 = ed2 - st2;
            std::chrono::duration<double> t3 = ed3 - st3;
            std::cout << t1.count() * 1000 << std::endl;
            std::cout << t2.count() * 1000 << std::endl;
            std::cout << t3.count() * 1000 << std::endl;
        }

        // Завершение по нажатию 'q'
        if (cv::waitKey(15) == 'q') break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    totalTime = elapsed.count();

    // Вычисление FPS и среднего времени обработки кадра
    double fps = frameCount / totalTime;
    double avgProcessingTime = (totalTime / frameCount) * 1000.0;

    std::cout << "Среднее FPS: " << fps << std::endl;
    std::cout << "Среднее время обработки кадра: " << avgProcessingTime << " мс" << std::endl;

    capture.release();
    cv::destroyAllWindows();

    return 0;
}
