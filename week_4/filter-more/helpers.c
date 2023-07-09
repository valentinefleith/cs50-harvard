#include "helpers.h"
#include "math.h"
#include <stdbool.h>

static void copy_image(int height, int width, RGBTRIPLE source[height][width], RGBTRIPLE destination[height][width]);

static RGBTRIPLE average_around(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

static bool is_valid_position(int i, int j, int height, int width);

static RGBTRIPLE sobel_edge(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

static int combination(int value_gx, int value_gy);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int max_swap;

    if (width % 2 == 1)
    {
        max_swap = (width - 1) / 2;
    }
    else
    {
        max_swap = width / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, mirror = width - 1; j < max_swap; j++, mirror--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][mirror];
            image[i][mirror] = temp;
        }
    }
    return;
}



// Blur image


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copied_image[height][width];
    copy_image(height, width, image, copied_image);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = average_around(i, j, height, width, copied_image);
        }
    }

    return;
}

static void copy_image(int height, int width, RGBTRIPLE source[height][width], RGBTRIPLE destination[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            destination[i][j] = source[i][j];
        }
    }
    return;
}

static RGBTRIPLE average_around(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed = 0, sumBlue = 0, sumGreen = 0;
    int count = 0;

    for (int m = (i - 1); m <= i + 1; m++)
    {
        for (int n = (j - 1); n <= j + 1; n++)
        {
            if (!is_valid_position(m, n, height, width))
            {
                continue;
            }

            sumRed += image[m][n].rgbtRed;
            sumBlue += image[m][n].rgbtBlue;
            sumGreen += image[m][n].rgbtGreen;
            count++;
        }
    }

    RGBTRIPLE average;

    average.rgbtRed = round((float)sumRed / count);
    average.rgbtBlue = round((float)sumBlue / count);
    average.rgbtGreen = round((float)sumGreen / count);

    return average;
}

static bool is_valid_position(int i, int j, int height, int width)
{
    bool i_is_valid = ((i >= 0) && (i < height));
    bool j_is_valid = ((j >= 0) && (j < width));

    return (i_is_valid && j_is_valid);

}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copied_image[height][width];
    copy_image(height, width, image, copied_image);


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = sobel_edge(i, j, height, width, copied_image);
        }
    }

    return;
}


static RGBTRIPLE sobel_edge(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int sum_gx_red = 0;
    int sum_gx_green = 0;
    int sum_gx_blue = 0;

    int sum_gy_red = 0;
    int sum_gy_green = 0;
    int sum_gy_blue = 0;

    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int count = 0;

    for (int m = (i - 1); m <= i + 1; m++)
    {
        for (int n = (j - 1); n <= (j + 1); n++, count++)
        {
            if (!is_valid_position(m, n, height, width))
            {
                continue;
            }

            sum_gx_red += image[m][n].rgbtRed * Gx[count];
            sum_gx_green += image[m][n].rgbtGreen * Gx[count];
            sum_gx_blue += image[m][n].rgbtBlue * Gx[count];

            sum_gy_red += image[m][n].rgbtRed * Gy[count];
            sum_gy_green += image[m][n].rgbtGreen * Gy[count];
            sum_gy_blue += image[m][n].rgbtBlue * Gy[count];

        }
    }

    RGBTRIPLE edged_pixel;
    edged_pixel.rgbtRed = combination(sum_gx_red, sum_gy_red);
    edged_pixel.rgbtGreen = combination(sum_gx_green, sum_gy_green);
    edged_pixel.rgbtBlue = combination(sum_gx_blue, sum_gy_blue);

    return edged_pixel;
}

static int combination(int value_gx, int value_gy)
{
    int result;

    result = round(sqrt(pow(value_gx, 2) + pow(value_gy, 2)));

    if (result > 255)
    {
        result = 255;
    }

    return result;
}
