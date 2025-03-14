#ifndef STEGANOGRAPHY_IMAGE_H
#define STEGANOGRAPHY_IMAGE_H
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include "PixelColor.h"
#include "BmpImageStuff.h"
#include "PpmImageStuff.h"
#include "PngImageStuff.h"

using namespace std;

class Image {
public:
    int getWidth() {
        return _width;
    }

    int getHeight() {
        return _height;
    }

    long getFileSize() {
        return _fileSize;
    }

    std::filesystem::file_time_type getLastWriteTime() {
        return _lastWriteTime;
    }

    void open(const string& filename) {
        _lastWriteTime = std::filesystem::last_write_time(filename);
        _fileSize = std::filesystem::file_size(filename);

        auto extension = std::filesystem::path(filename).extension();

        if (extension == ".bmp") {
            openBmp(filename);
        }
        else if (extension == ".ppm") {
            openPpm(filename);
        }
        else if (extension == ".png") {
            openPng(filename);
        }
        else throw std::logic_error("Not supported format");
    }

    void save(const string& filename) {
        auto extension = std::filesystem::path(filename).extension();
        if (extension == ".bmp") {
            saveBmp(filename);
        }
        else if (extension == ".ppm") {
            savePpm(filename);
        }
        else if (extension == ".png") {
            savePng(filename);
        }
        else throw std::logic_error("Not supported format");
    }



    PixelColor* getPixel(int row, int col) {
        return &_pixels[row][col];
    }
private:
    vector<vector<PixelColor>> _pixels;
    long _width, _height, _fileSize;
    std::filesystem::file_time_type _lastWriteTime;

    void openBmp(const string& filename){
        ifstream bmpStream(filename, ios::in | ios::binary); // inputfilestream open binary filestream to reading

        bmpFileMark bm_chars; // first 2 char where first b and m, if not b and m -> exp
        bmpStream.read((char*)(&bm_chars), sizeof(bm_chars)); // 2 bytes from file stream and write it to the bm_chars

        bmpFileHeader header; //structure
        bmpStream.read((char*)(&header), sizeof(header));

        bmpFileDibInfo dibInfo;
        bmpStream.read((char*)(&dibInfo), sizeof(dibInfo));

        // normally BMP stored from bottom to top
        bool flip = true;

        // but in case when height is negative - BMP stored from top to bottom
        if (dibInfo.height < 0)
        {
            flip = false;
            dibInfo.height = -dibInfo.height;
        }

        // Only supporting 24-bit images
        if (dibInfo.bitsPerPixel != 24) //3 options, 1 bit monochrom(1 bit for pixel, 1 light, 1 dark), 8 bit color(1byte, 256 colors), 16 bit per pixel cannot be only 24xpixel
        {
            std::cerr<<filename<<" uses "<<dibInfo.bitsPerPixel
                     <<"bits per pixel (bit depth). Bitmap only supports 24bit.\n";
            throw std::logic_error("Unsupported image depth!");
        }

        // No support for compressed images
        if (dibInfo.compression != 0) // cannot modify compressed images
        {
            std::cerr<<filename<<" is compressed. "
                     <<"Bitmap only supports uncompressed images.\n";
            throw std::logic_error("Unsupported compression of BMP image!");
        }

        bmpStream.seekg(header.bmpOffset); //position on the file stream for jump throw some bytes
        _width = dibInfo.width;
        _height = dibInfo.height;

        // Read the pixels for each row and column of Pixels in the image.
        for (int row = 0; row < _height; row++)
        {
            vector <PixelColor> row_data;

            for (auto col = 0; col < _width; col++)
            {
                unsigned char blue = bmpStream.get();
                unsigned char green = bmpStream.get();
                unsigned char red = bmpStream.get();

                row_data.push_back( PixelColor(red, green, blue, 0) );
            }

            // Rows are padded so that they're always a multiple of 4
            // bytes. This line skips the padding at the end of each row.
            bmpStream.seekg(_width % 4, ios::cur); // each next stroke must be start from position%4, for jump if we have not 8 or 12 or 16 bytes if we have 9 for example

            if (flip)
            {
                _pixels.insert(_pixels.begin(), row_data); //add to the top
            }
            else
            {
                _pixels.push_back(row_data); // add to the bottom
            }
        }

        bmpStream.close();
    }

    void openPpm(const string& filename){
        ifstream ppmStream(filename, ios::in); // ios::in open file in reading state
        if (ppmStream.fail()) {
            throw std::logic_error("File failed to open");
        }

        auto ppmHeader = read<string>(ppmStream);
        _width = read<int>(ppmStream);
        _height = read<int>(ppmStream);
        auto maxColor = read<int>(ppmStream); //
        if (ppmHeader != "P3") {
            throw std::logic_error("Unsupported file type");
        }
        for(auto row=0; row<_height; row++) {
            vector<PixelColor> rowData;

            for(auto col=0; col<_width; col++) {
                auto blue = read<int>(ppmStream);
                auto red = read<int>(ppmStream);
                auto green = read<int>(ppmStream);
                rowData.push_back( PixelColor(red, green, blue, 0) );
            }
            _pixels.push_back(rowData);
        }
    }

    void openPng(const string& filename) {
        int width, height, channels;
        auto img = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        _width = width;
        _height = height;
        for(auto row=0; row<height; row++) {
            vector<PixelColor> rowData;
            for(auto col=0; col<width; col++) {
                auto index=(row*width+col)*4;
                auto red = img[index];
                auto green = img[index + 1];
                auto blue = img[index + 2];
                auto alpha = img[index + 3];
                rowData.push_back( PixelColor(red, green, blue, alpha) );
            }
            _pixels.emplace_back(rowData);
        }
        stbi_image_free(img);

    }

    void saveBmp(const string& filename){
        ofstream file(filename, ios::out | ios::binary);

        if (file.fail())
        {
            std::cerr<<filename<<" could not be opened for editing. "
                     <<"Is it already open by another program or is it read-only?\n";

        }
        else
        {
            // Write all the header information that the BMP file format requires.
            file.write("BM", BmpMarkLength);
            bmpFileHeader header = { 0 };
            header.bmpOffset = 2 //
                               + sizeof(bmpFileHeader)
                               + sizeof(bmpFileDibInfo);
            auto width = _pixels[0].size();
            auto originalRowSize = width*3;
            auto adjustedRowSize = originalRowSize % 4 == 0
                                   ? originalRowSize
                                   : originalRowSize + 4- originalRowSize%4; // each row started from offset, divided by 4
            auto height = _pixels.size();
            header.fileSize = header.bmpOffset
                              + height * adjustedRowSize;
            file.write((char*)(&header), sizeof(header));
            bmpFileDibInfo dib_info = { 0 };
            dib_info.header_size = sizeof(bmpFileDibInfo);
            dib_info.width = width;
            dib_info.height = height;
            dib_info.numPlanes = 1;
            dib_info.bitsPerPixel = 24;
            dib_info.compression = 0;
            dib_info.bmpByteSize = 0;
            dib_info.hres = 0;
            dib_info.vres = 0;
            dib_info.numColors = 0;
            dib_info.numImportantColors = 0;
            file.write((char*)(&dib_info), sizeof(dib_info));

            // Write pixels info line by line
            for (int row = _pixels.size() - 1; row >= 0; row--)
            {
                auto row_data = _pixels[row];

                for (auto pixel : row_data)
                {
                    file.put(pixel.blue);
                    file.put(pixel.green);
                    file.put(pixel.red);
                }

                // Rows are padded so that they're always a multiple of 4
                // bytes. This line skips the padding at the end of each row.
                for (int i = 0; i < row_data.size() % 4; i++)
                {
                    file.put(0);
                }
            }

            file.close();
        }
    }

    void savePpm(const string& filename){
        ofstream file(filename, ios::out);
        file<<"P3"<<endl; // header
        file<<_pixels[0].size()<<" "<<_pixels.size()<<endl; // width height
        file<<255<<endl; // max amount of colors in pixel
        auto pixelsInRow=0;
        for(auto &_pixelRow : _pixels){
            for(auto &colNum : _pixelRow) {
                file<<(int)colNum.blue
                    <<" "<<(int)colNum.red
                    <<" "<<(int)colNum.green
                    <<" ";

                if(++pixelsInRow==4) {
                    file<<endl; // to fit the row limit of 70 chars we're writing only 6 pixels per line
                    pixelsInRow=0;
                }
            }
            if (pixelsInRow>0) {
                file<<endl; // each row of pixels also starts from new line
                pixelsInRow=0;
            }
        }
    }

    void savePng(const string& filename) {
        std::vector<unsigned char> data;
        data.reserve(_width * _height * 4);
        for (const auto& row : _pixels) {
            for (const auto& pixel : row) {
                data.push_back(pixel.red);
                data.push_back(pixel.green);
                data.push_back(pixel.blue);
                data.push_back(pixel.alpha);
            }
        }
        int result = stbi_write_png(filename.c_str(), _width, _height, 4, data.data(), _width * 4);
        if (result == 0) {
            throw logic_error("Failed to save Png file");
        }
    }

};


#endif //STEGANOGRAPHY_IMAGE_H
