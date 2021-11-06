#include <iostream>
#include <fstream>
#include<cstdio>

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render
    FILE* fp = fopen("binary.ppm", "wb");
    fprintf(fp, "P3\n%d %d\n255\n", image_width, image_height);
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            fprintf(fp, "%d %d %d\n", ir, ig, ib);
        }
    }
    fclose(fp);
}