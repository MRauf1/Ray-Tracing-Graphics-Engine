#ifndef IMAGE_H
#define IMAGE_H

class Image {

    private:

        double aspect_ratio_;
        int width_, height_;


    public:

        /**
         * Default Image constructor
         */
        Image();

        /**
         * Parameterized Image constructor
         * Height of the image is calculated automatically using
         * given aspect ratio and width
         * @param aspect_ratio Aspect ratio of the image
         * @param width        Width of the image
         */
        Image(double aspect_ratio, int width);

        /**
         * Getter for aspect_ratio
         * @return Aspect ratio of the image
         */
        double aspect_ratio() const;

        /**
         * Getter for width
         * @return Width of the image
         */
        int width() const;

        /**
         * Getter for height
         * @return Height of the image
         */
        int height() const;

};

#endif
