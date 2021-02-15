#include "Image.h"

Image::Image() {
    this->aspect_ratio_ = 16.0 / 9.0;
    this->width_ = 500;
    this->height_ = static_cast<int>(this->width_ / this->aspect_ratio_);
}

Image::Image(double aspect_ratio, int width) {
    this->aspect_ratio_ = aspect_ratio;
    this->width_ = width;
    this->height_ = static_cast<int>(this->width_ / this->aspect_ratio_);
}

double Image::aspect_ratio() const {
    return this->aspect_ratio_;
}

int Image::width() const {
    return this->width_;
}

int Image::height() const {
    return this->height_;
}
