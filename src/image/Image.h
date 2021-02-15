#ifndef IMAGE_H
#define IMAGE_H

class Image {

    private:
        double aspect_ratio_;
        int width_, height_;

    public:
        Image();
        Image(double aspect_ratio, int width);
        double aspect_ratio() const;
        int width() const;
        int height() const;

};

#endif
