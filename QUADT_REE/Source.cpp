#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#define _CRT_SECURE_NO_WARNINGS
#define __STDC_LIB_EXT1__

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "quadtree.h"

QuadTree<std::vector<int>>* GenerateNWQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart);
QuadTree<std::vector<int>>* GenerateNEQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart);
QuadTree<std::vector<int>>* GenerateSWQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart);
QuadTree<std::vector<int>>* GenerateSEQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart);

int fac = 5;

QuadTree<std::vector<int>>* GenerateNWQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart) {

    int currentWidth = width / pow(2, depth);
    int currentHeight = height / pow(2, depth);
    bool difColor = false;
    unsigned char* currentRgbPointer = (*p + channels * width * ydepart + channels * xdepart);
    int RValue = (uint8_t)*currentRgbPointer;
    int GValue = (uint8_t) * (currentRgbPointer + 1);
    int BValue = (uint8_t) * (currentRgbPointer + 2);
    int i = 0;
    int j = 0;
    if (currentWidth > 1) {
        while (i < currentWidth) {
            while (!difColor && j < currentHeight) {
                int nextRvalue = (uint8_t) * (currentRgbPointer + i * channels + channels * width * j);
                int nextGvalue = (uint8_t) * (currentRgbPointer + i * channels + 1 + channels * width * j);
                int nextBvalue = (uint8_t) * (currentRgbPointer + i * channels + 2 + channels * width * j);

                if ((RValue <= nextRvalue - fac || RValue >= nextRvalue + fac) || (GValue <= nextGvalue - fac || GValue >= nextGvalue + fac) || (BValue <= nextBvalue - fac || BValue >= nextBvalue + fac)) {
                    difColor = true;
                }
                j++;
            }
            i++;
            j = 0;
        }

        if (difColor) {
            QuadNode<std::vector<int>>* ImgTree = new QuadNode<std::vector<int>>();
            ImgTree->son(0) = GenerateNWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart);
            ImgTree->son(1) = GenerateNEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart);
            ImgTree->son(2) = GenerateSWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart + (int)currentHeight / 2);
            ImgTree->son(3) = GenerateSEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart + (int)currentHeight / 2);
            return ImgTree;
        }
        else {
            std::vector<int> rgb;
            rgb.push_back(RValue);
            rgb.push_back(GValue);
            rgb.push_back(BValue);
            rgb.push_back(xdepart);
            rgb.push_back(ydepart);
            rgb.push_back(depth);
            QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
            return ImgTree;
        }
    }
    else {
        std::vector<int> rgb;
        rgb.push_back(RValue);
        rgb.push_back(GValue);
        rgb.push_back(BValue);
        rgb.push_back(xdepart);
        rgb.push_back(ydepart);
        rgb.push_back(depth);
        QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
        return ImgTree;
    }
}

QuadTree<std::vector<int>>* GenerateNEQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart) {


    int currentWidth = width / pow(2, depth);
    int currentHeight = height / pow(2, depth);
    bool difColor = false;
    unsigned char* currentRgbPointer = (*p + channels * width * ydepart + channels * xdepart);
    int RValue = (uint8_t)*currentRgbPointer;
    int GValue = (uint8_t) * (currentRgbPointer + 1);
    int BValue = (uint8_t) * (currentRgbPointer + 2);
    int i = 0;
    int j = 0;
    if (currentWidth > 1) {
        while (i < currentWidth) {
            while (!difColor && j < currentHeight) {
                int nextRvalue = (uint8_t) * (currentRgbPointer + i * channels + channels * width * j);
                int nextGvalue = (uint8_t) * (currentRgbPointer + i * channels + 1 + channels * width * j);
                int nextBvalue = (uint8_t) * (currentRgbPointer + i * channels + 2 + channels * width * j);

                if ((RValue <= nextRvalue - fac || RValue >= nextRvalue + fac) || (GValue <= nextGvalue - fac || GValue >= nextGvalue + fac) || (BValue <= nextBvalue - fac || BValue >= nextBvalue + fac)) {
                    difColor = true;
                }
                j++;
            }
            i++;
            j = 0;
        }

        if (difColor) {
            QuadNode<std::vector<int>>* ImgTree = new QuadNode<std::vector<int>>();
            ImgTree->son(0) = GenerateNWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart);
            ImgTree->son(1) = GenerateNEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart);
            ImgTree->son(2) = GenerateSWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart + (int)currentHeight / 2);
            ImgTree->son(3) = GenerateSEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart + (int)currentHeight / 2);
            return ImgTree;
        }
        else {
            std::vector<int> rgb;
            rgb.push_back(RValue);
            rgb.push_back(GValue);
            rgb.push_back(BValue);
            rgb.push_back(xdepart);
            rgb.push_back(ydepart);
            rgb.push_back(depth);
            QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
            return ImgTree;
        }
    }
    else {
        std::vector<int> rgb;
        rgb.push_back(RValue);
        rgb.push_back(GValue);
        rgb.push_back(BValue);
        rgb.push_back(xdepart);
        rgb.push_back(ydepart);
        rgb.push_back(depth);
        QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
        return ImgTree;
    }
}

QuadTree<std::vector<int>>* GenerateSWQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart) {

    int currentWidth = width / pow(2, depth);
    int currentHeight = height / pow(2, depth);
    int nydepart = currentHeight;
    bool difColor = false;
    unsigned char* currentRgbPointer = (*p + channels * width * ydepart + channels * xdepart);
    int RValue = (uint8_t)*currentRgbPointer;
    int GValue = (uint8_t) * (currentRgbPointer + 1);
    int BValue = (uint8_t) * (currentRgbPointer + 2);
    int i = 0;
    int j = 0;
    if (currentWidth > 1) {
        while (i < currentWidth) {
            while (!difColor && j < currentHeight) {
                int nextRvalue = (uint8_t) * (currentRgbPointer + i * channels + channels * width * j);
                int nextGvalue = (uint8_t) * (currentRgbPointer + i * channels + 1 + channels * width * j);
                int nextBvalue = (uint8_t) * (currentRgbPointer + i * channels + 2 + channels * width * j);

                if ((RValue <= nextRvalue - fac || RValue >= nextRvalue + fac) || (GValue <= nextGvalue - fac || GValue >= nextGvalue + fac) || (BValue <= nextBvalue - fac || BValue >= nextBvalue + fac)) {
                    difColor = true;
                }
                difColor = true;
                j++;
            }
            i++;
            j = 0;
        }

        if (difColor) {
            QuadNode<std::vector<int>>* ImgTree = new QuadNode<std::vector<int>>();
            ImgTree->son(0) = GenerateNWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart);
            ImgTree->son(1) = GenerateNEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart);
            ImgTree->son(2) = GenerateSWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart + (int)currentHeight / 2);
            ImgTree->son(3) = GenerateSEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)currentWidth / 2, ydepart + (int)currentHeight / 2);
            return ImgTree;
        }
        else {
            std::vector<int> rgb;
            rgb.push_back(RValue);
            rgb.push_back(GValue);
            rgb.push_back(BValue);
            rgb.push_back(xdepart);
            rgb.push_back(ydepart);
            rgb.push_back(depth);
            QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
            return ImgTree;
        }
    }
    else {
        std::vector<int> rgb;
        rgb.push_back(RValue);
        rgb.push_back(GValue);
        rgb.push_back(BValue);
        rgb.push_back(xdepart);
        rgb.push_back(ydepart);
        rgb.push_back(depth);
        QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
        return ImgTree;
    }
}

QuadTree<std::vector<int>>* GenerateSEQuadNodes(unsigned char** p, int width, int height, int channels,
    int depth, int xdepart, int ydepart) {

    int currentWidth = width / pow(2, depth);
    int currentHeight = height / pow(2, depth);
    int nxdepart = currentWidth;
    int nydepart = currentHeight;
    bool difColor = false;
    unsigned char* currentRgbPointer = (*p + channels * width * ydepart + channels * xdepart);
    int RValue = (uint8_t)*currentRgbPointer;
    int GValue = (uint8_t) * (currentRgbPointer + 1);
    int BValue = (uint8_t) * (currentRgbPointer + 2);
    if (currentWidth > 1) {
        int i = 0;
        int j = 0;
        while (i < currentWidth) {
            while (!difColor && j < currentHeight) {
                int nextRvalue = (uint8_t) * (currentRgbPointer + i * channels + channels * width * j);
                int nextGvalue = (uint8_t) * (currentRgbPointer + i * channels + 1 + channels * width * j);
                int nextBvalue = (uint8_t) * (currentRgbPointer + i * channels + 2 + channels * width * j);

                if ((RValue <= nextRvalue - fac || RValue >= nextRvalue + fac) || (GValue <= nextGvalue - fac || GValue >= nextGvalue + fac) || (BValue <= nextBvalue - fac || BValue >= nextBvalue + fac)) {
                    difColor = true;
                }
                j++;
            }
            i++;
            j = 0;
        }

        if (difColor) {
            QuadNode<std::vector<int>>* ImgTree = new QuadNode<std::vector<int>>();
            ImgTree->son(0) = GenerateNWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart);
            ImgTree->son(1) = GenerateNEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)(currentWidth) / 2, ydepart);
            ImgTree->son(2) = GenerateSWQuadNodes(p, width, height, channels, depth + 1, xdepart, ydepart + (int)(currentHeight) / 2);
            ImgTree->son(3) = GenerateSEQuadNodes(p, width, height, channels, depth + 1, xdepart + (int)(currentWidth) / 2, ydepart + currentHeight / 2);
            return ImgTree;
        }
        else {
            std::vector<int> rgb;
            rgb.push_back(RValue);
            rgb.push_back(GValue);
            rgb.push_back(BValue);
            rgb.push_back(xdepart);
            rgb.push_back(ydepart);
            rgb.push_back(depth);
            QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
            return ImgTree;
        }
    }
    else {
        std::vector<int> rgb;
        rgb.push_back(RValue);
        rgb.push_back(GValue);
        rgb.push_back(BValue);
        rgb.push_back(xdepart);
        rgb.push_back(ydepart);
        rgb.push_back(depth);
        QuadLeaf<std::vector<int>>* ImgTree = new QuadLeaf<std::vector<int>>(rgb);
        return ImgTree;
    }
}

void Draw(QuadTree<std::vector<int>>* quadtree, unsigned char* ni, int channels, int width, int height) {
    if (quadtree->isNode()) {
        Draw(quadtree->son(0), ni, channels, width, height);
        Draw(quadtree->son(1), ni, channels, width, height);
        Draw(quadtree->son(2), ni, channels, width, height);
        Draw(quadtree->son(3), ni, channels, width, height);
    }
    else {
        int pxdepart = quadtree->value().at(3) * channels;
        int pydepart = quadtree->value().at(4) * channels * width;
        int currentWidth = width / pow(2, quadtree->value().at(5) - 1);
        int currentHeight = height / pow(2, quadtree->value().at(5) - 1);
        for (int i = 0; i < currentWidth; i++) {
            for (int j = 0; j < currentHeight; j++) {
                *(ni + i * channels + pxdepart + pydepart + channels * width * j) = quadtree->value().at(0);
                *(ni + i * channels + pxdepart + pydepart + channels * width * j + 1) = quadtree->value().at(1);
                *(ni + i * channels + pxdepart + pydepart + channels * width * j + 2) = quadtree->value().at(2);
            }

        }
    }

}

int QDdemo() {

    int width, height, channels;
    unsigned char* img = stbi_load("montgolfiere.png", &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    //Construction of quadtree
    QuadTree<std::vector<int>>* ImgTree = new QuadNode<std::vector<int>>();

    bool difColor = false;
    unsigned char* RgbPointer = img;
    int RValue = (uint8_t)*RgbPointer;
    int GValue = (uint8_t) * (RgbPointer + 1);
    int BValue = (uint8_t) * (RgbPointer + 2);
    int i = 1;
    while (!difColor && i < width * height) {
        int nextRvalue = (uint8_t) * (RgbPointer + i * channels);
        int nextGvalue = (uint8_t) * (RgbPointer + i * channels + 1);
        int nextBvalue = (uint8_t) * (RgbPointer + i * channels + 2);

        if ((RValue < nextRvalue - fac || RValue > nextRvalue + fac) && (GValue < nextGvalue - fac || GValue > nextGvalue + fac) && (BValue < nextBvalue - fac || BValue > nextBvalue + fac)) {
            difColor = true;
        }
        i++;
    }

    if (difColor) {
        ImgTree->son(0) = GenerateNWQuadNodes(&RgbPointer, width, height, channels, 1, 0, 0);
        ImgTree->son(1) = GenerateNEQuadNodes(&RgbPointer, width, height, channels, 1, width / 2, 0);
        ImgTree->son(2) = GenerateSWQuadNodes(&RgbPointer, width, height, channels, 1, 0, height / 2);
        ImgTree->son(3) = GenerateSEQuadNodes(&RgbPointer, width, height, channels, 1, width / 2, height / 2);
    }
    else {
        std::vector<int> rgb;
        rgb.push_back(RValue);
        rgb.push_back(GValue);
        rgb.push_back(BValue);
        rgb.push_back(0);
        rgb.push_back(0);
        rgb.push_back(1);
        *ImgTree = QuadLeaf<std::vector<int>>(rgb);
    }


    // Convert the input image to gray
    size_t new_img_size = (static_cast<size_t>(width) * height * channels) * 2;
    int new_img_channels = channels;


    unsigned char* new_img = (unsigned char*)malloc(new_img_size);
    if (new_img) memset(new_img, 0, new_img_size);

    //unsigned char * gray_img = malloc(gray_img_size);
    if (new_img == NULL) {
        std::cout << "Unable to allocate memory for the new image.\n" << std::endl;
        exit(1);
    }
    unsigned char* pg = new_img;

    std::cout << ImgTree->nLeaves() << std::endl;
    std::cout << ImgTree->nNodes() << std::endl;
    std::cout << ImgTree->son(2)->isLeaf() << std::endl;
    std::cout << ImgTree->son(3)->isLeaf() << std::endl;
    Draw(ImgTree, pg, channels, width, height);

    stbi_write_png("The_Test.png", width, height, new_img_channels, new_img, width * new_img_channels);

    stbi_image_free(img);
    free(new_img);

    return 0;
}
