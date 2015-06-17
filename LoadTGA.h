#ifndef LOADTGA_H
#define LOADTGA_H
#include "stdio.h"
#include <iostream>
#include <GL/glut.h>

/*[Загрузка TGA текстур]*/
GLuint LoadTGATexture(const char* fileName)
{
    FILE *file;
    long size;
    GLint color;
    GLubyte header[18];
    file = fopen(fileName, "rb");
    if(!file){
        std::cerr << "File of Texture Not Exist" << std::endl;
        return 0;
    }
    fread(header,1,sizeof(header),file);


    if(header[2] != 2) {
        std::cerr << "Not RGB image!" << std::endl;
        return 0;
    }
    GLint width = header[13] * 256 + header[12];
    GLint height = header[15] * 256 + header[14];

    // Конвертирование данных в количество каналов, т.е. 3 или 4 канала (RGB или RGBA)
    color = header[16] / 8;

    // Вычисление размера массива необходимого для хранения текстуры width * height * ColorDepth(глубину цвета)
    size = width * height * color;

    // Собственно выделение памяти
    GLubyte *image = new GLubyte[sizeof(GLubyte) * size];

    // Загрузка данных изображения из файла
    fread(image,sizeof(GLubyte),size,file);

    // TGA хранит BGR(перевёрнутые) данные. Если вам нужны RGB. Нужно поменять каналы местами
    // Выглядит неплохо :D
    for(long i = 0; i < size; i += color)
    {
        GLubyte tmp = image[i];
        image[i] = image[i+2];
        image[i+2] = tmp;
    }

    fclose(file);

    // Объявляем переменную для хранения ID текстуры
    GLuint tex_id;

    // Генерация пустой текстуры получение её ID
    glGenTextures(1,&tex_id);

    // Задаёи "имя"(идентификатор) текстуре
    glBindTexture(GL_TEXTURE_2D,tex_id);


    // Оперируем только цветами текстуры, никакого смешивания
    // Можно установить GL_MODULATE, для смешивания цвета текстуры с желаемым цветом.
//    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    // Установка фильтров текстуры.
    /* GL_NEAREST               - Базовая. Без изменений.
     * GL_LINEAR                - Линейная фильтрация
     * GL_LINEAR_MIPMAP_NEAREST - Basic mipmapped texture
     * GL_LINEAR_MIPMAP_LINEAR  - BiLinear Mipmapped texture
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Повтор изображения
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    // Выбор количества каналов используемых в изображении 3 или 4 (RGB или RGBA)
    if(color == 3) {
        color = GL_RGB;
    }else if(color == 4){
        color = GL_RGBA;
    }else {
        std::cerr << "Color Depth Unsupported" << std::endl;
        return 0;
    }

//  gluBuild2DMipmaps(GL_TEXTURE_2D,color,width,height,color,GL_UNSIGNED_BYTE,image);
    glTexImage2D(GL_TEXTURE_2D, 0, color, width, height, 0, color, GL_UNSIGNED_BYTE, image);

    // Ну раз всё хорошо, возвращаем ID текстуры
    std::cerr << "Texture loaded" << std::endl;
    return tex_id;

}
/*[/Загрузка TGA текстур]*/

#endif // LOADTGA_H
