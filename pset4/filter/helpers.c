#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of RGB values
            int gv = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            // Make pixel grayscale
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = gv;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia value
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Set cap to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Make pixel sepia
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Create temporary copy of image
            RGBTRIPLE temp = image[i][(width - 1) - j];

            // Flip and copy left half to right half
            image[i][(width - 1) - j] = image[i][j];

            // Flip and copy right half to left half using copy as base
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int averageRed[height][width];
    int averageGreen[height][width];
    int averageBlue[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If top edge and not corner
            if (i == 0 && j > 0 && j < (width - 1))
            {
                averageRed[i][j] = round((float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j -
                                                 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);
                averageGreen[i][j] = round((float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j -
                                                   1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);
                averageBlue[i][j] = round((float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j -
                                                  1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
            }
            // If top left corner
            if (i == 0 && j == 0)
            {
                averageRed[i][j] = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j +
                                                 1].rgbtRed) / 4);
                averageGreen[i][j] = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j +
                                                   1].rgbtGreen) / 4);
                averageBlue[i][j] = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j +
                                                  1].rgbtBlue) / 4);
            }
            // If top right corner
            if (i == 0 && j == (width - 1))
            {
                averageRed[i][j] = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j -
                                                 1].rgbtRed) / 4);
                averageGreen[i][j] = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j -
                                                   1].rgbtGreen) / 4);
                averageBlue[i][j] = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j -
                                                  1].rgbtBlue) / 4);
            }
            // If left edge and not corner
            if (i > 0 && i < (height - 1) && j == 0)
            {
                averageRed[i][j] = round((float)(image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j +
                                                 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);
                averageGreen[i][j] = round((float)(image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j +
                                                   1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);
                averageBlue[i][j] = round((float)(image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j +
                                                  1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
            }
            // If bottom left corner
            if (i == (height - 1) && j == 0)
            {
                averageRed[i][j] = round((float)(image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j +
                                                 1].rgbtRed) / 4);
                averageGreen[i][j] = round((float)(image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j +
                                                   1].rgbtGreen) / 4);
                averageBlue[i][j] = round((float)(image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j +
                                                  1].rgbtBlue) / 4);
            }
            // If bottom right corner
            if (i == (height - 1) && j == (width - 1))
            {
                averageRed[i][j] = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                 image[i][j].rgbtRed) / 4);
                averageGreen[i][j] = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                   image[i][j].rgbtGreen) / 4);
                averageBlue[i][j] = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                  image[i][j].rgbtBlue) / 4);
            }
            // If right edge and not corner
            if (i > 0 && i < (height - 1) && j == (width - 1))
            {
                averageRed[i][j] = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                 image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6);
                averageGreen[i][j] = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                   image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6);
                averageBlue[i][j] = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                  image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6);
            }
            // If bottom edge and not corner
            if (i == (height - 1) && j > 0 && j < (width - 1))
            {
                averageRed[i][j] = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j -
                                                 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6);
                averageGreen[i][j] = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                   image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6);
                averageBlue[i][j] = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6);
            }
            // All other cases
            if (i > 0 && i < (height - 1) && j > 0 && j < (width - 1))
            {
                averageRed[i][j] = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j -
                                                 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j
                                                         + 1].rgbtRed) / 9);
                averageGreen[i][j] = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                   image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i +
                                                           1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);
                averageBlue[i][j] = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue
                                                  + image[i + 1][j + 1].rgbtBlue) / 9);
            }
        }
    }

    // Make each pixel blurred
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = averageRed[i][j];
            image[i][j].rgbtGreen = averageGreen[i][j];
            image[i][j].rgbtBlue = averageBlue[i][j];
        }
    }
    return;
}