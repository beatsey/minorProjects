/*
В файле pic.bmp задано изображение в формате True Color 32 бита на пиксел. Написать программу на языке C++, которая загружает это изображение в программу, масштабирует изображение таким образом, чтобы его ширина и высота уменьшились бы втрое и выводит в файл pic2.bmp.
В каждой точке создаваемого изображения каждая компонента цвета должна быть выбрана в виде среднего значения из девяти значений из квадрата 3х3 вокруг соответствующей точки на исходном изображении. В граничных точках размер области вокруг соответствующей точки на исходном изображении может быть меньше.
Вся отведенная память в программе должна быть очищена. Все открытые файлы должны быть закрыты.
*/

#include<iostream>
#include<fstream>
#include <string>
using namespace std;

struct header
{
    int16_t header;
    int32_t filesize;
    int16_t reser;
    int16_t reser1;
    int32_t dataoffset;
};

struct infoheader
{
    int32_t headersize;
    int32_t width;
    int32_t height;
    int16_t plans;
    int16_t bpp;
    int32_t compression;
    int32_t datasize;
    int32_t re;
    int32_t ve;
    int32_t color;
    int32_t importantcolor;
};

struct Pixel {
    uint32_t R=0, G=0, B=0, A=0, counter=0;
};


int main()
{
    header h;
    infoheader info;
    string name;
    getline(cin, name);

    ifstream file(name, ios::binary);

    if (file.is_open())
    {
        file.read((char*)&h, sizeof(h));
        if (h.header == 0x4D42)
        {
            file.read((char*)&info, sizeof(info));
            cout << info.width << " " << info.height << " " << h.filesize << " " << info.bpp << " " << info.datasize << endl;

            if (info.bpp != 32)
                return -1;

            const int size = info.width * info.height;
            uint32_t* image = new uint32_t[size];

            const int newWidth = info.width / 3, newHeight = info.height / 3, newSize = newWidth*newHeight;

            Pixel* newImage = new Pixel[(newWidth+1)*(newHeight+1)];

            file.read((char *)image, size*4);

            char somebuffer[100];
            file.read(somebuffer, 68);
            file.close();
            for (int i = 0; i < info.height; i++)
            {
                for (int j = 0; j < info.width; j++)
                {
                    int index = i * info.width + j;
                    uint32_t pixel=image[index];

                    uint8_t A = pixel >> 24; // alpha mask
                    uint8_t R = pixel >> 16; // red mask
                    uint8_t G = pixel >> 8; // green mask
                    uint8_t B = pixel; // blue mask

                    Pixel& pix = newImage[(i / 3) * newWidth + (j / 3)];
                    pix.A += A;
                    pix.R += R;
                    pix.G += G;
                    pix.B += B;
                    pix.counter++;
                }
            }

            // Собираем уменьшенную картинку

            for (int i = 0; i < newHeight; i++)
            {
                for (int j = 0; j < newWidth; j++)
                {
                    Pixel& pix = newImage[i * newWidth + j];
                    
                    pix.A /= pix.counter;
                    pix.R /= pix.counter;
                    pix.G /= pix.counter;
                    pix.B /= pix.counter;
                    

                    // redraw the previous image buffer
                    image[i * newWidth + j] = (pix.A << 24) + (pix.R << 16) + (pix.G << 8) + pix.B;
                }
            }

            info.width = newWidth;
            info.height = newHeight;
            info.datasize = h.filesize = h.filesize - size * 4 + newSize * 4;
            

            // save the result to a file
            // Неясно как его корректно сохранить

            ofstream newFile("resized.bmp", ios::binary);
            newFile.write((char*)&h,sizeof(h));
            newFile.write((char*)&info, sizeof(info));
            newFile.write((char*)image, newSize*4);
            newFile.write(somebuffer, 68);
            newFile.close();

            delete[] image;
            delete[] newImage;

        }
        else
        {
            return -2;
        }
    }
}