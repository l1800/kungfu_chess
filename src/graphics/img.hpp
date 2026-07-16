#pragma once

#include <opencv2/opencv.hpp>

#include <string>
#include <utility>

class Img
{
public:
    /**
     * Creates an empty image object.
     */
    Img();

    /**
     * Loads an image from a file.
     *
     * @param path Path to the image file.
     * @param size Optional target size: width and height.
     * @param keepAspect Whether to preserve the original aspect ratio.
     * @param interpolation OpenCV resize interpolation method.
     * @return Reference to the current Img object.
     */
    Img& read(
        const std::string& path,
        const std::pair<int, int>& size = {},
        bool keepAspect = false,
        int interpolation = cv::INTER_AREA
    );

    /**
     * Draws this image on another image.
     *
     * @param otherImg Destination image.
     * @param x Horizontal position of the upper-left corner.
     * @param y Vertical position of the upper-left corner.
     */
    void draw_on(
        Img& otherImg,
        int x,
        int y
    );

    /**
     * Draws text on the image.
     *
     * @param text Text to draw.
     * @param x Horizontal text position.
     * @param y Text baseline position.
     * @param fontSize OpenCV font scale.
     * @param color Text color in BGR/BGRA format.
     * @param thickness Text line thickness.
     */
    void put_text(
        const std::string& text,
        int x,
        int y,
        double fontSize,
        const cv::Scalar& color =
            cv::Scalar(255, 255, 255, 255),
        int thickness = 1
    );

    /**
     * Displays the image and waits until a key is pressed.
     */
    void show();

    /**
     * Displays one frame without permanently blocking the program.
     *
     * @param windowName Window title.
     * @param delayMilliseconds Keyboard wait duration.
     * @return Pressed key code, or -1 if no key was pressed.
     */
    int show_frame(
        const std::string& windowName = "Kung Fu Chess",
        int delayMilliseconds = 16
    );

    /**
     * Returns the underlying OpenCV image.
     */
    const cv::Mat& get_mat() const;

    /**
     * Returns whether an image is currently loaded.
     */
    bool is_loaded() const;

private:
    cv::Mat img;
};