// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        // width / 2 worths learning!
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sumR = 0, sumG = 0, sumB = 0, counter = 0;
            // check the around pixels in two directions
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if(j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    sumR += image[i + k][j + l].rgbtRed;
                    sumG += image[i + k][j + l].rgbtGreen;
                    sumB += image[i + k][j + l].rgbtBlue;
                    counter++;
                }
            }
            tmp[i][j].rgbtRed = round(sumR / counter);
            tmp[i][j].rgbtGreen = round(sumG / counter);
            tmp[i][j].rgbtBlue = round(sumB / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}, gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE tmp[height][width];
    // to deal with the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each loop, these values should return to zero!
            int Gx_red = 0, Gx_green = 0, Gx_blue = 0, Gy_red = 0, Gy_green = 0, Gy_blue = 0;
            // multiply corresponding number
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i + k < 1 || i + k > height)
                    {
                        continue;
                    }
                    if (j + l < 1 || j + l > width)
                    {
                        continue;
                    }
                    Gx_red += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                    Gx_green += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                    Gx_blue += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                    Gy_red += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                    Gy_green += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                    Gy_blue += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                }
            }
            // use question marks and colons
            tmp[i][j].rgbtRed = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red)) > 255 ? 255 : round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            tmp[i][j].rgbtGreen = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green)) > 255 ? 255 : round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            tmp[i][j].rgbtBlue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue)) > 255 ? 255 : round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
