#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>

const int WIDTH = 8192;
const int HEIGHT = 8192;
const int MAX_ITERATIONS = 8000;
const int NUM_THREADS = std::thread::hardware_concurrency();

int mandelbrot(float real, float imag)
{
    float r = real;
    float i = imag;
    for (int iter = 0; iter < MAX_ITERATIONS; ++iter)
    {
        float r2 = r * r;
        float i2 = i * i;
        if (r2 + i2 > 4.0f)
        {
            return iter;
        }
        i = 2.0f * r * i + imag;
        r = r2 - i2 + real;
    }
    return MAX_ITERATIONS;
}

void generateMandelbrotSet(int *output)
{
    std::vector<std::thread> threads;

    auto thread_function = [&](int start_row, int end_row)
    {
        for (int y = start_row; y < end_row; ++y)
        {
            for (int x = 0; x < WIDTH; ++x)
            {
                float real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
                float imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;

                int value = mandelbrot(real, imag);

                output[y * WIDTH + x] = value;
            }
        }
    };

    int rows_per_thread = HEIGHT / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start_row = i * rows_per_thread;
        int end_row = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * rows_per_thread;

        threads.emplace_back(thread_function, start_row, end_row);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

int main()
{
    int *output = new int[WIDTH * HEIGHT];

    generateMandelbrotSet(output);

    std::ofstream image("mandelbrot_set_cpp.ppm");
    image << "P3\n"
          << WIDTH << " " << HEIGHT << "\n255\n";

    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        int value = output[i];
        int r = 0;
        int g = 0;
        int b = (value % 256);
        image << r << " " << g << " " << b << "\n";
    }

    delete[] output;

    return 0;
}
