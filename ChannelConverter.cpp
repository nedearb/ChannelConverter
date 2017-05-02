
#include <string>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


char rgbOrHsv(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'r':
            case 'R':
                option = 'r';
                choosing = false;
                break;
            case 'h':
            case 'H':
                option = 'h';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}

char chooseRGBN(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'r':
            case 'R':
                option = 'x';
                choosing = false;
                break;
            case 'g':
            case 'G':
                option = 'y';
                choosing = false;
                break;
            case 'b':
            case 'B':
                option = 'z';
                choosing = false;
                break;
            case '0':
                option = '0';
                choosing = false;
                break;
            case '1':
                option = '1';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}

char chooseHSVN(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'h':
            case 'H':
                option = 'x';
                choosing = false;
                break;
            case 's':
            case 'S':
                option = 'y';
                choosing = false;
                break;
            case 'v':
            case 'V':
                option = 'z';
                choosing = false;
                break;
            case '0':
                option = '0';
                choosing = false;
                break;
            case '1':
                option = '1';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}


int main(int argc, const char * argv[]){
    
    string imagePath;
    
    if(argc == 2){
        imagePath = argv[1];
    }else{
        cout << "Enter filename: ";
        getline(cin, imagePath);
    }
    
    Mat inputImage;
    inputImage = imread(imagePath.c_str(), CV_LOAD_IMAGE_COLOR);
    
    if(!inputImage.data){
        cout << "No image data." << endl;
        return -1;
    }
    
    cout << "Loaded Image: " << imagePath << endl;
    
    imshow("Input", inputImage);
    
    waitKey(10);
    
    destroyWindow("Input");
    
    char fromOption = rgbOrHsv("From RGB or HSV? (r,h)");
    char toOption = rgbOrHsv("To RGB or HSV? (r,h)");
    
    char fromToX, fromToY, fromToZ;
    
    string fromStr;
    
    Mat fromImage;
    
    if(fromOption == 'r'){
        fromStr = "RGB";
        cvtColor(inputImage, fromImage, COLOR_BGR2RGB);
    }else{
        fromStr = "HSV";
        cvtColor(inputImage, fromImage, COLOR_BGR2HSV);
    }
    
    if(toOption == 'r'){
        fromToX = chooseRGBN("From "+fromStr.substr(0,1)+" to (r,g,b,0,1)");
        fromToY = chooseRGBN("From "+fromStr.substr(1,1)+" to (r,g,b,0,1)");
        fromToZ = chooseRGBN("From "+fromStr.substr(2,1)+" to (r,g,b,0,1)");
    }else{
        fromToX = chooseHSVN("From "+fromStr.substr(0,1)+" to (h,s,v,0,1)");
        fromToY = chooseHSVN("From "+fromStr.substr(1,1)+" to (h,s,v,0,1)");
        fromToZ = chooseHSVN("From "+fromStr.substr(2,1)+" to (h,s,v,0,1)");
    }
    
    cout << "Processing..." << endl;
    
    Mat result(fromImage.rows, fromImage.cols, CV_8UC3);
    
    for(int i = 0; i < fromImage.rows; i++){
        for(int j = 0; j < fromImage.cols; j++){
            Vec3b fromXYZ = fromImage.at<Vec3b>(i, j);
            Vec3b toXYZ(0, 0, 0);
            if(fromOption == 'h'){
                fromXYZ[0] = (unsigned char)(fromXYZ[0] * (255/180));
            }
            switch (fromToX) {
                case 'x': toXYZ[0] = fromXYZ[0]; break;
                case 'y': toXYZ[0] = fromXYZ[1]; break;
                case 'z': toXYZ[0] = fromXYZ[2]; break;
                case '0': toXYZ[0] = 0; break;
                case '1': toXYZ[0] = 255; break;
                default: break;
            }
            switch (fromToY) {
                case 'x': toXYZ[1] = fromXYZ[0]; break;
                case 'y': toXYZ[1] = fromXYZ[1]; break;
                case 'z': toXYZ[1] = fromXYZ[2]; break;
                case '0': toXYZ[1] = 0; break;
                case '1': toXYZ[1] = 255; break;
                default: break;
            }
            switch (fromToZ) {
                case 'x': toXYZ[2] = fromXYZ[0]; break;
                case 'y': toXYZ[2] = fromXYZ[1]; break;
                case 'z': toXYZ[2] = fromXYZ[2]; break;
                case '0': toXYZ[2] = 0; break;
                case '1': toXYZ[2] = 255; break;
                default: break;
            }
            if(toOption == 'h'){
                fromXYZ[0] = (unsigned char)(toXYZ[0] * (180/255));
            }
            result.at<Vec3b>(i, j) = toXYZ;
        }
    }
    
    Mat outputImage;
    
    if(toOption == 'r'){
        cvtColor(result, outputImage, COLOR_RGB2BGR);
    }else{
        cvtColor(result, outputImage, COLOR_HSV2BGR);
    }
    
    imwrite("converted.png", outputImage);
    
}