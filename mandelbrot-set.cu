#include <iostream>
#include <fstream>
#include <cmath>
#include <cuda_runtime.h>

const int width = 8192;
const int height = 8192;
const int max_iterations = 8000;

__device__ int mandelbrot(float real, float imag)
{
    float r = real;
    float i = imag;
    for (int iter = 0; iter < max_iterations; ++iter)
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
    return max_iterations;
}

__global__ void generateMandelbrotSet(int *output)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    float real = (x - width / 2.0) * 4.0 / width;
    float imag = (y - height / 2.0) * 4.0 / height;

    int value = mandelbrot(real, imag);

    output[y * width + x] = value;
}

int main()
{
    int *host_output = new int[width * height];
    int *device_output;

    cudaMalloc((void **)&device_output, width * height * sizeof(int));

    dim3 blockDim(32, 32);
    dim3 gridDim((width + blockDim.x - 1) / blockDim.x, (height + blockDim.y - 1) / blockDim.y);

    generateMandelbrotSet<<<gridDim, blockDim>>>(device_output);

    cudaMemcpy(host_output, device_output, width * height * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(device_output);

    std::ofstream image("mandelbrot_set_cuda.ppm");
    image << "P3\n"
          << width << " " << height << "\n255\n";

    for (int i = 0; i < width * height; ++i)
    {
        int value = host_output[i];
        int r = 0;
        int g = 0;
        int b = (value % 256);
        image << r << " " << g << " " << b << "\n";
    }

    delete[] host_output;

    return 0;
}
