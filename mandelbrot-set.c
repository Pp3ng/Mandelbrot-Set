#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 8192
#define HEIGHT 8192
#define MAX_ITERATIONS 8000

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
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            float real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            float imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;

            int value = mandelbrot(real, imag);

            output[y * WIDTH + x] = value;
        }
    }
}

int main()
{
    int *output = (int *)malloc(WIDTH * HEIGHT * sizeof(int));

    generateMandelbrotSet(output);

    FILE *image = fopen("mandelbrot_set_c.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        int value = output[i];
        int r = 0;
        int g = 0;
        int b = (value % 256);
        fprintf(image, "%d %d %d\n", r, g, b);
    }

    fclose(image);
    free(output);

    return 0;
}
