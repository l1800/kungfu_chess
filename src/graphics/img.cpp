#include "img.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

Img::Img() = default;

Img& Img::read(
    const std::string& path,
    const std::pair<int, int>& size,
    bool keepAspect,
    int interpolation
)
{
    img = cv::imread(
        path,
        cv::IMREAD_UNCHANGED
    );

    if (img.empty())
    {
        throw std::runtime_error(
            "Cannot load image: " + path
        );
    }

    if (size.first > 0 && size.second > 0)
    {
        const int targetWidth = size.first;
        const int targetHeight = size.second;

        if (keepAspect)
        {
            const double scale = std::min(
                static_cast<double>(targetWidth) /
                    static_cast<double>(img.cols),
                static_cast<double>(targetHeight) /
                    static_cast<double>(img.rows)
            );

            const int newWidth =
                std::max(
                    1,
                    static_cast<int>(img.cols * scale)
                );

            const int newHeight =
                std::max(
                    1,
                    static_cast<int>(img.rows * scale)
                );

            cv::resize(
                img,
                img,
                cv::Size(newWidth, newHeight),
                0.0,
                0.0,
                interpolation
            );
        }
        else
        {
            cv::resize(
                img,
                img,
                cv::Size(targetWidth, targetHeight),
                0.0,
                0.0,
                interpolation
            );
        }
    }

    return *this;
}

void Img::draw_on(
    Img& otherImg,
    int x,
    int y
)
{
    if (img.empty() || otherImg.img.empty())
    {
        throw std::runtime_error(
            "Both images must be loaded before drawing."
        );
    }

    if (x < 0 || y < 0)
    {
        throw std::out_of_range(
            "Drawing coordinates must be non-negative."
        );
    }

    if (x + img.cols > otherImg.img.cols ||
        y + img.rows > otherImg.img.rows)
    {
        throw std::out_of_range(
            "Image does not fit at the specified position."
        );
    }

    cv::Mat destinationRegion =
        otherImg.img(
            cv::Rect(
                x,
                y,
                img.cols,
                img.rows
            )
        );

    if (img.channels() == 4)
    {
        cv::Mat sourceBgr;

        cv::cvtColor(
            img,
            sourceBgr,
            cv::COLOR_BGRA2BGR
        );

        std::vector<cv::Mat> sourceChannels;
        cv::split(img, sourceChannels);

        cv::Mat alpha;

        sourceChannels[3].convertTo(
            alpha,
            CV_32FC1,
            1.0 / 255.0
        );

        cv::Mat alphaBgr;

        cv::cvtColor(
            alpha,
            alphaBgr,
            cv::COLOR_GRAY2BGR
        );

        cv::Mat destinationBgr;

        if (destinationRegion.channels() == 4)
        {
            cv::cvtColor(
                destinationRegion,
                destinationBgr,
                cv::COLOR_BGRA2BGR
            );
        }
        else if (destinationRegion.channels() == 3)
        {
            destinationBgr = destinationRegion;
        }
        else
        {
            throw std::runtime_error(
                "Unsupported destination image format."
            );
        }

        cv::Mat sourceFloat;
        cv::Mat destinationFloat;

        sourceBgr.convertTo(
            sourceFloat,
            CV_32FC3
        );

        destinationBgr.convertTo(
            destinationFloat,
            CV_32FC3
        );

        cv::Mat inverseAlpha =
            cv::Scalar::all(1.0) - alphaBgr;

        cv::Mat blended =
            sourceFloat.mul(alphaBgr) +
            destinationFloat.mul(inverseAlpha);

        cv::Mat blended8;

        blended.convertTo(
            blended8,
            CV_8UC3
        );

        if (destinationRegion.channels() == 4)
        {
            cv::cvtColor(
                blended8,
                destinationRegion,
                cv::COLOR_BGR2BGRA
            );
        }
        else
        {
            blended8.copyTo(
                destinationRegion
            );
        }

        return;
    }

    if (img.channels() == destinationRegion.channels())
    {
        img.copyTo(destinationRegion);
        return;
    }

    if (img.channels() == 3 &&
        destinationRegion.channels() == 4)
    {
        cv::Mat converted;

        cv::cvtColor(
            img,
            converted,
            cv::COLOR_BGR2BGRA
        );

        converted.copyTo(destinationRegion);
        return;
    }

    if (img.channels() == 4 &&
        destinationRegion.channels() == 3)
    {
        cv::Mat converted;

        cv::cvtColor(
            img,
            converted,
            cv::COLOR_BGRA2BGR
        );

        converted.copyTo(destinationRegion);
        return;
    }

    throw std::runtime_error(
        "Unsupported source and destination image formats."
    );
}

void Img::put_text(
    const std::string& text,
    int x,
    int y,
    double fontSize,
    const cv::Scalar& color,
    int thickness
)
{
    if (img.empty())
    {
        throw std::runtime_error(
            "Image not loaded."
        );
    }

    cv::putText(
        img,
        text,
        cv::Point(x, y),
        cv::FONT_HERSHEY_SIMPLEX,
        fontSize,
        color,
        thickness,
        cv::LINE_AA
    );
}

void Img::show()
{
    if (img.empty())
    {
        throw std::runtime_error(
            "Image not loaded."
        );
    }

    cv::imshow(
        "Kung Fu Chess",
        img
    );

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int Img::show_frame(
    const std::string& windowName,
    int delayMilliseconds
)
{
    if (img.empty())
    {
        throw std::runtime_error(
            "Image not loaded."
        );
    }

    if (delayMilliseconds < 1)
    {
        throw std::invalid_argument(
            "Frame delay must be positive."
        );
    }

    cv::imshow(
        windowName,
        img
    );

    return cv::waitKey(
        delayMilliseconds
    );
}

const cv::Mat& Img::get_mat() const
{
    return img;
}

bool Img::is_loaded() const
{
    return !img.empty();
}