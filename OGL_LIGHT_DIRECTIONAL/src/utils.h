#include "includes.h"

struct ImgParams{
    int width, height, nrChannels;
};

unsigned char* getImageData(const char* path, ImgParams* params){
    unsigned char * data;
    int width, height, nrChannels;

    data = stbi_load(path, &width, &height, &nrChannels, 0);

    params->height = height;
    params->width = width;
    params->nrChannels = nrChannels;

    return data;
}