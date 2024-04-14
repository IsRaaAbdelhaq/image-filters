//Name:  Israa Abdelhaq Mohammed          20230053        filter:1 & 7
//       seif allah ahmed sayed hassan    20230185               2 & 5
//       ziad el sayed mohamed            20230152               3 & 6
//Section : 21 & 22
//this project convert the image to any filter in this code

/*
#include <iostream>
#include <vector>
#include "image_class.h"
#include <string>
#include <cmath>
#include <limits> // For numeric_limits
#include <algorithm> 
using namespace std;
string filename1,filename2,new_image;
void gray_filter(Image &image){
    for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                unsigned int avg = 0;
                for (int k = 0; k < 3; ++k) {
                    avg += image(i, j, k);

                }
                avg /= 3;

                image(i, j, 0) = avg;
                image(i, j, 1) = avg;
                image(i, j, 2) = avg;
            }
        }
}
void black_white_filter(Image &image){
    for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned  int avg = 0; // Initialize average value
                for (int k = 0; k < 3; ++k) {
                    avg += image(i, j, k); // Accumulate pixel values
                }
                avg /= 3; // Calculate average
                if(avg<128)//check pixels colour is bigger than gray colour or not
                    avg=0;//make colour avg black
                else
                    avg=255;//make colour avg white
                image(i, j, 0) = avg;
                image(i, j, 1) = avg;
                image(i, j, 2) = avg;
            }
        }
}
void invert(Image &image){
    for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    image(i, j, k);
                }
                image(i, j, 0) = 255 - image(i, j, 0);
                image(i, j, 1) = 255 - image(i, j, 1);
                image(i, j, 2) = 255 - image(i, j, 2);
            }
        }
}
void flip_filter(Image &image){
    cout << "please enter flip type\n1)horizontal\n2)vertical\n3)exit\n";
    while (true)
    {
        string choose;
        cin >> choose;
        if(choose=="1"){
            for (int i = 0; i < image.width / 2; ++i) {//take half of weidth t avoid repeated pixels
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);
                    image(i, j, k) = image(image.width - i - 1, j, k);
                    image(image.width - i - 1, j, k) = pixel_points;
                }
            }
        }
        break;
        }
        else if(choose=="2"){
            for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {//take half of height t avoid repeated pixels
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);//take a copy from colour pixel of point
                    image(i, j, k) = image(i, image.height - j - 1, k);
                    image(i, image.height - j - 1, k) = pixel_points;
                }
            }
        }
        break;
        }
        else{
            cout << "please enter a valid choice\n";
                continue;
        }
    } 
} 
void resize(Image &image , int &W , int &H){
    Image org_image(filename1);
    cout<<"please enter a new dimensions (W,H)\n";
    cin>>W>>H;
    float R_W1=(float)org_image.width/W,R_H1=(float)org_image.height/H;// make casting to R_W1 and R_H1
    Image resize(W,H);//make a new image to store resized image
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            for (int k = 0; k < 3; ++k) {
                resize(i,j,k)=org_image(round(i*R_W1),round(j*R_H1),k);
            }
        }
    }
}
void Merge_images(Image &image,Image &image0 , string& option){
    cout << "Choose the merge option:\n"
         << "1- Resize the smaller image or both images to the biggest height and width and then merge\n"
         << "2- Merge the common area of the smaller width and the smaller height\n";
    while (true) {
        cin >> option;
        // Check if the user's input is valid
        if (!cin.fail() && (option == "1" || option == "2")) {
            break; // Exit the loop if the input is valid
        }
        cout << "Invalid input. Please enter 1 or 2.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }
    if (option == "1"){
        int newWidth = max(image.width, image0.width);
        int newHeight = max(image.height, image0.height);
        // Resize the images
        resize(image, newWidth, newHeight); // Resize the first image
        resize(image0, newWidth, newHeight); // Resize the second image
        // Loop over each pixel in the new image
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                // For each pixel, if it is within the dimensions of the original images,
                // calculate the average of the corresponding pixels in the input images
                for (int k = 0; k < 3; ++k) {
                    if (i < image.width && j < image.height && i < image0.width && j < image0.height) {
                        (image)(i, j, k) = (image(i, j, k) + image0(i, j, k)) / 2;
                    } else if (i < image.width && j < image.height) {
                        (image)(i, j, k) = image(i, j, k);
                    } else if (i < image0.width && j < image0.height) {
                        (image)(i, j, k) = image0(i, j, k);
                    } else {
                        (image)(i, j, k) = 0; // Fill the rest of the image with black
                    }}}}
    }

    if (option == "2") {

        int width1 = image.width;
        int height1 = image.height;
        int width2 = image0.width;
        int height2 = image0.height;

        // Calculate the region of overlap (common area)
        int overlapWidth = min(width1, width2);
        int overlapHeight = min(height1, height2);

        // Create a new image to store the merged result
        Image merged_image(overlapWidth, overlapHeight);

        // Blend the pixels from the common area
        double opacity = 0.5; // Opacity for blending (adjust as needed)
        for (int y = 0; y < overlapHeight; ++y) {
            for (int x = 0; x < overlapWidth; ++x) {
                unsigned char r1 = image.getPixel(x, y, 0);
                unsigned char g1 = image.getPixel(x, y, 1);
                unsigned char b1 = image.getPixel(x, y, 2);

                unsigned char r2 = image0.getPixel(x, y, 0);
                unsigned char g2 = image0.getPixel(x, y, 1);
                unsigned char b2 = image0.getPixel(x, y, 2);

                // Blend the pixel values using opacity
                unsigned char r = static_cast<unsigned char>((1.0 - opacity) * r1 + opacity * r2);
                unsigned char g = static_cast<unsigned char>((1.0 - opacity) * g1 + opacity * g2);
                unsigned char b = static_cast<unsigned char>((1.0 - opacity) * b1 + opacity * b2);

                // Set the blended pixel values in the merged image
                merged_image.setPixel(x, y, 0, r);
                merged_image.setPixel(x, y, 1, g);
                merged_image.setPixel(x, y, 2, b);
            }
        }
    }
}
void save_image(Image &image,string &filename1){
    string ch,name;
    while (true)
    {
        cout<<"Save the image\n1-new file\n2-same file\n";
        cin>>ch;
        if(ch=="1"){
            cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
            cin>>new_image;
             name = new_image;
        }
        else if(ch=="2"){
            name = filename1;
        }
        else{
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }
        try
        {
            image.saveImage(name);
            system(name.c_str());
            break;
        }
        catch(const std::exception& e)
        {
            std::cerr <<"Failed to save image: "<< e.what() << '\n';
            continue;
        }
        
    }
}
int main() {
    string choose;
    while (true) {
        cout << "What do you want to do?\n"
        << "1-Edit an image\n"
        << "2-Exit the program\n";
        cin>>choose;
        if(choose=="1"){
            bool loaded_img = false;
            cin.ignore();
            while (!loaded_img) {
                cout << "Enter the image name and it's extension: ";
                getline(cin, filename1);
                try {
                    Image image(filename1);
                    loaded_img = true; 
                } catch (const std::exception& e) { 
                    cout << "Invalid image name or path. Please try again.\n";
                }
            }
        Image image(filename1);
        bool back = false;
        while (back == false){
        cout << "_______________________________________________________________________________________________________" << endl ;
        cout << "                                    welcome to our program!                  \n";
        cout << "Choose the Filter you Want\n";
        cout << " 1 / Grayscale conversion          2 / Black and White \n";
        cout << " 3 / Invert Image                  4 / Merge Images \n";
        cout << " 5 / Flip Image                    6 / Rotate Image \n";
        cout << " 7 / Darken and Lighten Image     10 / Edge Image \n";
        cout << "11 /                              12 /  \n";
        cout << "13 / Sunshine Image               14 /  \n";
        cout << "                      16 / Exit                    \n";
        string choose1;
        cin >> choose1;
        cout << "_______________________________________________________________________________________________________" << endl ;
        if(choose1=="1"){
            gray_filter(image);
        }
        else if (choose1=="2"){
            black_white_filter(image);
        }
        else if (choose1=="3"){
            invert(image);
        }
        else if (choose1=="4"){
            bool loaded_img2 = false;
            cin.ignore();
            while (!loaded_img2) {
                cout << "Enter the second image name and it's extension: ";
                getline(cin, filename2);
                try {
                    Image image2(filename2);
                    loaded_img2 = true; 
                } catch (const std::exception& e) { 
                    cout << "Invalid image name or path. Please try again.\n";
                }
            }
        Image image2(filename2);
        string option;
        Merge_images(image,image2,option);
        }
        else if (choose1=="5"){
            flip_filter(image);
        }
        else if (choose1=="11"){
            int w,h;
            resize(image,w,h);
        }
        while (true)
        {
            string chh;
            cout << "Do you want to add another filter or save the image?\n"
            << "1- Add another filter\n"
            << "2- Save the image\n";
            cin>>chh;
            if(chh=="1"){
                break;
            }
            else if(chh=="2"){
                save_image(image,filename1);
                back = true;
                break;
            }
        }
        
        }
        }
        else if(choose=="2"){
            cout << "Thanks for using the program. Goodbye!\n";
            break;
        }
    }
    return 0;
}
