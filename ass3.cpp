//Name:  Israa Abdelhaq Mohammed          20230053        filter:1 & 7
//       seif allah ahmed sayed hassan    20230185               2 & 5
//       ziad el sayed mohamed            20230152               3 & 6
//Section : 21 & 22
//this project convert the image to any filter in this code

/*
#include <iostream>
#include "Image_Class.h"
#include <string>
using namespace std;
namespace filter1 {
    void gray_filter() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
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
        image.saveImage(new_image);
        system(new_image.c_str());
    }
}
namespace filter4 {
    void merge_images(const string& filename1, const string& filename2, const string& new_image) {
        // Load the two images
        Image image1(filename1);
        Image image2(filename2);

        // Get dimensions of both images
        int width1 = image1.width;
        int height1 = image1.height;
        int width2 = image2.width;
        int height2 = image2.height;

        // Calculate the region of overlap (common area)
        int overlapWidth = min(width1, width2);
        int overlapHeight = min(height1, height2);

        // Create a new image to store the merged result
        Image merged_image(overlapWidth, overlapHeight);

        // Blend the pixels from the common area
        double opacity = 0.5; // Opacity for blending (adjust as needed)
        for (int y = 0; y < overlapHeight; ++y) {
            for (int x = 0; x < overlapWidth; ++x) {
                unsigned char r1 = image1.getPixel(x, y, 0);
                unsigned char g1 = image1.getPixel(x, y, 1);
                unsigned char b1 = image1.getPixel(x, y, 2);

                unsigned char r2 = image2.getPixel(x, y, 0);
                unsigned char g2 = image2.getPixel(x, y, 1);
                unsigned char b2 = image2.getPixel(x, y, 2);

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

        // Save the merged image
        merged_image.saveImage(new_image);
        cout << "Merged image saved as: " << new_image << endl;
        system(new_image.c_str());

    }
    void merge() {
        string filename1, filename2, new_image;

        cout << "Enter the first image name and its extension: ";
        getline(cin, filename1);

        cout << "Enter the second image name and its extension: ";
        getline(cin, filename2);

        cout << "Enter the new image name to store the merged image (extension: jpg, bmp, png, tga): ";
        getline(cin, new_image);

        merge_images(filename1, filename2, new_image);


    }

}
namespace filter7 {
    void darken_lighten_filter(bool lighten, Image &image) {
        double n;
        cout << "Enter the level of darkening or lighting from 0 to 100%: ";
        cin >> n;

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {



                if (lighten) {
                    double x = (n / 100);
                    for (int k = 0; k < 3; ++k) {
                        // Lighten the pixel by level
                        int newValue = image(i, j, k) + x * (255 - image(i, j, k));
                        image(i, j, k) = (newValue > 255) ? 255 : newValue;
                    }
                } else {
                    double y = (n / 100);
                    for (int k = 0; k < 3; ++k) {
                        // Darken the pixel by level
                        image(i, j, k) *=  y;

                    }

                }
            }
        }

    }

    void dr_filter() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        string choice;
        cout << "Do you want to lighten (l) or darken (d) the image ? \n";
        cin >> choice;
        int n , m;
        if (choice == "l" || choice == "L") {
            darken_lighten_filter(true, image); // Lighten the image
        } else if (choice == "d" || choice == "D") {
            darken_lighten_filter(false, image); // Darken the image
        } else {
            cout << "Invalid choice. Please enter 'l' to lighten or 'd' to darken the image." << endl;

        }
        image.saveImage(new_image);
        system(new_image.c_str());
    }
}
namespace filter2 {
    void black_white_filter() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);

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

        image.saveImage(new_image);
        system(new_image.c_str());

    }
}
namespace filter5 {
    void horizontally() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        for (int i = 0; i < image.width / 2; ++i) {//take half of weidth t avoid repeated pixels
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);
                    image(i, j, k) = image(image.width - i - 1, j, k);
                    image(image.width - i - 1, j, k) = pixel_points;
                }
            }
        }
        image.saveImage(new_image);
        system(new_image.c_str());
    }

    void vertical() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {//take half of height t avoid repeated pixels
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);//take a copy from colour pixel of point
                    image(i, j, k) = image(i, image.height - j - 1, k);
                    image(i, image.height - j - 1, k) = pixel_points;
                }
            }
        }
        image.saveImage(new_image);
        system(new_image.c_str());
    }

    void flip_filter() {
        cout << "please enter flip type\n1)horizontal\n2)vertical\n3)exit\n";
        while (true) {
            string choose;
            cin >> choose;
            if (choose == "1") {
                horizontally();
                break;
            } else if (choose == "2") {
                vertical();
                break;
            } else if (choose == "3") {
                break;
            } else {
                cout << "please enter a valid choice\n";
                continue;
            }
        }

    }
}
namespace filter3 {
    void invert() {
        string name,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,name);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(name);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(name);
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
        image.saveImage(new_image);
        system(new_image.c_str());

    }
}
namespace filter6 {
    string filename;

// Function to rotate the image by 90 degrees
    void rotation_90() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        // Create a new Image object with dimensions swapped for 90-degree rotation
        Image image2(image.height, image.width);
        // Nested loops to iterate through each pixel of the original image
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                // Loop through each color channel (RGB)
                for (int k = 0; k < 3; k++) {
                    // Perform rotation operation
                    image2(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        // Save the rotated image
        image2.saveImage(new_image);
        system(new_image.c_str());
    }

// Function to rotate the image by 180 degrees
    void rotation_180() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        // Nested loops to iterate through each pixel of the original image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                // Loop through each color channel (RGB)
                for (int k = 0; k < 3; ++k) {
                    // Swap pixels to perform rotation
                    int location = image(i, j, k);
                    image(i, j, k) = image(i, image.height - j - 1, k);
                    image(i, image.width - j - 1, k) = location;
                }
            }
        }
        // Save the rotated image
        image.saveImage(new_image);
        system(new_image.c_str());
    }

// Function to rotate the image by 270 degrees
    void rotation_270() {
        string filename,new_image;
        bool loaded_img=false;
        cin.ignore();
        while (!loaded_img)
        {
            try
            {
                cout << "Enter the image name and it's extension: ";
                getline(cin,filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): " ;
                getline(cin,new_image);
                Image image(filename);
                loaded_img=true;
            }
            catch(const std::exception& e)
            {
                cout<<"Error: "<< e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        // Create a new Image object with dimensions swapped for 270-degree rotation
        Image image2(image.height, image.width);
        // Nested loops to iterate through each pixel of the original image
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                // Loop through each color channel (RGB)
                for (int k = 0; k < 3; k++) {
                    // Perform rotation operation
                    image2(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        // Save the rotated image
        image2.saveImage(new_image);
        system(new_image.c_str());
    }

    void rotate_filter() {
        string rotation;
        cout << "Choose the type of rotation:\n1. 90\n2. 180\n3. 270\n";
        while (true) {
            cin >> rotation;
            // Perform rotation based on user input
            if (rotation == "1") {
                rotation_90();
                break;
            } else if (rotation == "2") {
                rotation_180();
                break;
            } else if (rotation == "3") {
                rotation_270();
                break;
            } else {
                // Handle invalid input
                cout << "ERROR: Choose a valid rotation: ";
                continue;
            }
        }

    }
}
namespace filter10{
    void sobel_edge_detection() {
        string filename, new_image;
        bool loaded_img = false;
        cin.ignore();
        while (!loaded_img) {
            try {
                cout << "Enter the image name and it's extension: ";
                getline(cin, filename);
                cout << "Enter image name to store new image.extension(jpg , bmp , png , tga): ";
                getline(cin, new_image);
                Image image(filename);
                loaded_img = true;
            }
            catch (const std::exception &e) {
                cout << "Error: " << e.what() << endl;
                continue;
            }
        }
        Image image(filename);
        int width = image.width;
        int height = image.height;

        Image edge_image (width , height);


        int kernel_x[3][3] = {{-1, 0, 1},
                              {-2, 0, 2},
                              {-1, 0, 1}};
        int kernel_y[3][3] = {{-1, -2, -1},
                              {0,  0,  0},
                              {1,  2,  1}};

        while (true) {
            string x;
            cout << "what do you want ? \n 1 to black edge \n 2 to white edge \n 3 to exit\n";
            cin >> x;
            //each pixel in the image
            if (x == "1") {
                for (int y = 1; y < height - 1; ++y) {
                    for (int x = 1; x < width - 1; ++x) {
                        int sum_x = 0;
                        int sum_y = 0;
                        for (int ky = 0; ky < 3; ++ky) {
                            for (int kx = 0; kx < 3; ++kx) {
                                int pixel_value = image.getPixel(x + ky - 1, y + ky - 1, 0); // Accumulate pixel values
                                sum_x += pixel_value * kernel_x[ky][kx];
                                sum_y += pixel_value * kernel_y[ky][kx];
                            }
                        }

                        int magnitude = sqrt(sum_x * sum_x + sum_y * sum_y);

                        unsigned char edge_value = (magnitude > 128) ? 225 : 0;
                        edge_image.setPixel(x, y, 0, 225 - edge_value);
                        edge_image.setPixel(x, y, 1, 225 - edge_value);
                        edge_image.setPixel(x, y, 2, 225 - edge_value);


                    }

                }
                edge_image.saveImage(new_image);
                system(new_image.c_str());
            }

            else if (x == "2"){
                for (int y = 1; y < height - 1; ++y) {
                    for (int x = 1; x < width - 1; ++x) {
                        int sum_x = 0;
                        int sum_y = 0;
                        for (int ky = 0; ky < 3; ++ky) {
                            for (int kx = 0; kx < 3; ++kx) {
                                int pixel_value = image.getPixel(x + ky - 1, y + ky - 1, 0); // Accumulate pixel values
                                sum_x += pixel_value * kernel_x[ky][kx];
                                sum_y += pixel_value * kernel_y[ky][kx];
                            }
                        }

                        int magnitude = sqrt(sum_x * sum_x + sum_y * sum_y);

                        unsigned char edge_value = (magnitude > 128) ? 225 : 0;
                        edge_image.setPixel(x, y, 0, edge_value);
                        edge_image.setPixel(x, y, 1, edge_value);
                        edge_image.setPixel(x, y, 2, edge_value);


                    }

                }
                edge_image.saveImage(new_image);
                system(new_image.c_str());

            }

            else if (x == "3"){
                break;
            }

            else {
                cout << "invalid input\n";
                continue;
            }
        }


    }
}
namespace filter13{
    // Function to apply the warm lighting effect to an image
    void apply_warm_lighting(Image& image) {
        // Iterate over each pixel in the image
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                // Increase the intensity of warm colors (red and orange)
                image(x, y, 0) = min(255, image(x, y, 0) + 50); // Red channel
                image(x, y, 1) = max(0, image(x, y, 1) - 20);    // Green channel
                image(x, y, 2) = max(0, image(x, y, 2) - 20);    // Blue channel
            }
        }
    }

// Function to apply the warm filter to an image
    void warm_filter(const string& filename, const string& new_image) {
        // Load the image
        Image image(filename);

        // Apply warm lighting effect
        apply_warm_lighting(image);

        // Save the warm-filtered image
        image.saveImage(new_image);
        cout << "Warm-filtered image saved as: " << new_image << endl;
    }

    void warm() {
        string filename, new_image;

        cout << "Enter the image name and its extension: ";
        getline(cin, filename);

        cout << "Enter the new image name to store the warm-filtered image (extension: jpg, bmp, png, tga): ";
        getline(cin, new_image);

        warm_filter(filename, new_image);


    }
}


int main (){
    while (true){
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
        string choose;
        cin >> choose;
        cout << "_______________________________________________________________________________________________________" << endl ;
        if (choose == "1"){
            filter1::gray_filter();
            break;
        }
        else if (choose == "2"){
            filter2::black_white_filter();
            break;
        }
        else if (choose == "3"){
            filter3::invert();
            break;
        }
        else if (choose == "4"){
            filter4::merge();
            break;
        }
        else if (choose == "5"){
            filter5::flip_filter();
            break;
        }
        else if (choose == "6"){
            filter6::rotate_filter();
            break;
        }
        else if (choose == "7"){
            filter7::dr_filter();
        }
        else if (choose == "10"){
            filter10::sobel_edge_detection();
        }
        else if (choose == "13"){
            filter13::warm();
        }

        else {
            cout << "Enter valid input from 1 to 7: "<<endl;
            continue;
        }

    }

}
*/


#include <iostream>
#include <string>
#include <stdexcept>
#include "Image_Class.h"
using namespace std;
string filename, new_image,filename2;
void invalid0(string &filename, string &new_image) {
    bool loaded_img = false;
    cin.ignore();
    while (!loaded_img) {
        try {
            cout << "Enter the first image name and its extension: ";
            getline(cin, filename);
            Image image(filename);
            loaded_img = true;
        } catch(const std::exception& e) {
            cout << "Error: " << e.what() << endl;
            continue;
        } catch(...) {
            cout << "Unknown error occurred." << endl;
        }
    }
}
void invalid(string &filename, string &filename2, string &new_image) {
    bool loaded_img = false;
    cin.ignore();
    while (!loaded_img) {
        try {
            cout << "Enter the first image name and its extension: ";
            getline(cin, filename);
            cout << "Enter the second image name and its extension: ";
            getline(cin, filename2);
            // Attempt to load the images
            Image image(filename);
            Image image2(filename2);
            // If no exception occurred, set loaded_img to true to exit the loop
            loaded_img = true;
        } catch(const std::exception& e) {
            // If an exception occurred, print the error message and continue the loop to ask for input again
            cout << "Error: " << e.what() << endl;
            continue;

        } catch(...) {
            // Handle any other exceptions
            cout << "Unknown error occurred." << endl;
        }
    }
}

// Function to apply grayscale filter to an image
Image gray_filter(Image &image){
    Image image2(image.width, image.height); // Create a new image to store the filtered result
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            // Set all RGB channels to the average value to convert to grayscale
            image2(i, j, 0) = avg;
            image2(i, j, 1) = avg;
            image2(i, j, 2) = avg;
        }
    }
    return image2;
}
Image black_white_filter(Image &image){
    Image image2(image.width, image.height);
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
            image2(i, j, 0) = avg;
            image2(i, j, 1) = avg;
            image2(i, j, 2) = avg;
        }
    }
    return image2;
}
Image invert(Image &image){
    Image image2(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                image(i, j, k);
            }
            image2(i, j, 0) = 255 - image(i, j, 0);
            image2(i, j, 1) = 255 - image(i, j, 1);
            image2(i, j, 2) = 255 - image(i, j, 2);
        }
    }
    return image2;
}
Image Merge_images(Image &image,Image &image0 , string& option){

    Image image1(filename);
    Image image2(filename2);
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
    if (option == ""){

    int width1 = image1.width;
    int height1 = image1.height;
    int width2 = image2.width;
    int height2 = image2.height;

    // Calculate the region of overlap (common area)
    int overlapWidth = min(width1, width2);
    int overlapHeight = min(height1, height2);

    // Create a new image to store the merged result
    Image merged_image(overlapWidth, overlapHeight);

    // Blend the pixels from the common area
    double opacity = 0.5; // Opacity for blending (adjust as needed)
    for (int y = 0; y < overlapHeight; ++y) {
        for (int x = 0; x < overlapWidth; ++x) {
            unsigned char r1 = image1.getPixel(x, y, 0);
            unsigned char g1 = image1.getPixel(x, y, 1);
            unsigned char b1 = image1.getPixel(x, y, 2);

            unsigned char r2 = image2.getPixel(x, y, 0);
            unsigned char g2 = image2.getPixel(x, y, 1);
            unsigned char b2 = image2.getPixel(x, y, 2);

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
    return merged_image;
}
Image Flip(Image &image) {
    cout << "please enter flip type\n1)horizontal\n2)vertical\n3)exit\n";
    string choose;
    cin >> choose;
    if (choose == "1") {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);
                    image(i, j, k) = image(image.width - i - 1, j, k);
                    image(image.width - i - 1, j, k) = pixel_points;
                }
            }
        }
    } else if (choose == "2") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    int pixel_points = image(i, j, k);
                    image(i, j, k) = image(i, image.height - j - 1, k);
                    image(i, image.height - j - 1, k) = pixel_points;
                }
            }
        }
    }
    return image;
}
Image rotate(Image &image){
    Image image0;
    string rotation;
    cout << "Choose the type of rotation:\n1. 90\n2. 180\n3. 270\n";
    while (true) {
        cin >> rotation;
        // Perform rotation based on user input
        if (rotation == "1") {
            Image image0(image.height, image.width);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    // Loop through each color channel (RGB)
                    for (int k = 0; k < 3; k++) {
                        // Perform rotation operation
                        image0(image.height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            break;
        }
        else if (rotation == "2") {
            Image image0(image.width,image.height);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    // Loop through each color channel (RGB)
                    for (int k = 0; k < 3; ++k) {
                        // Swap pixels to perform rotation
                        int location = image(i, j, k);
                        image(i, j, k) = image0(i, image.height - j - 1, k);
                        image0(i, image.height - j - 1, k) = location;
                    }
                }
            }
            break;
        }
        else if (rotation == "3") {
            Image image0(image.height, image.width);
            // Nested loops to iterate through each pixel of the original image
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    // Loop through each color channel (RGB)
                    for (int k = 0; k < 3; k++) {
                        // Perform rotation operation
                        image0(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            break;
        }
        else {
            cout << "ERROR: Choose a valid rotation: ";
            continue;
        }
    }
    return image0;
}
Image darken_lighten_filter(Image &image){
    Image image0(image.width,image.height);
    double n;
    cout << "Enter the level of darkening or lighting from 0 to 100%: ";
    cin >> n;
    string choice;
    cout << "Do you want to lighten (l) or darken (d) the image ? \n";
    cin >> choice;
    if (choice == "l" || choice == "L"){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                double x = (n / 100);
                for (int k = 0; k < 3; ++k) {
                    // Lighten the pixel by level
                    int newValue = image(i, j, k) + x * (255 - image(i, j, k));
                    image0(i, j, k) = (newValue > 255) ? 255 : newValue;
                }
            }}
    }
    else if (choice == "d" || choice == "D") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                double y = (n / 100);
                for (int k = 0; k < 3; ++k) {
                    // Darken the pixel by level
                    image0(i, j, k) *=  y;

                }
            }}
    }
    else {
        cout << "Invalid choice. Please enter 'l' to lighten or 'd' to darken the image." << endl;

    }
    return image0;
}
int main() {
    string ch;
    while (true)
    {
        cout<<"How many images do you want to enter ?\n1.one image\n2.two images\n";
        cin>>ch;
        if(ch=="1"){
            invalid0(filename,new_image);
            break;
        }
        else if(ch=="2"){
            invalid(filename,filename2,new_image);
            break;
        }
        else{
            continue;
        }
    }

    while (true) {
        Image image;
        Image image2;
        cout << "_" << endl ;
        cout << "                                    welcome to our program!                  \n";
        cout << "Choose the Filter you Want\n";
        cout << " 1 / Grayscale conversion          2 / Black and White \n";
        cout << " 3 / Invert Image                  4 / Merge Images \n";
        cout << " 5 / Flip Image                    6 / Rotate Image \n";
        cout << " 7 / Darken and Lighten Image     10 / Edge Image \n";
        cout << "11 /                              12 /  \n";
        cout << "13 / Sunshine Image               14 /  \n";
        cout << "                      16 / Exit                    \n";
        string choose, ch;
        cin >> choose;
        cout << "_" << endl ;
        if (choose == "1") {
            Image filtered_image = gray_filter(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {

                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="2"){
            Image filtered_image = black_white_filter(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="3"){
            Image filtered_image = invert(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="4"){
            Image filtered_image = Merge_images(image,image2); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="5"){
            Image filtered_image =Flip(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="6"){
            Image filtered_image =rotate(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }
        else if(choose=="7"){
            Image filtered_image =darken_lighten_filter(image); // Apply grayscale filter
            while (true) {
                cout << "Save the image :\n1.same file\n2.new file\n";
                cin >> ch;
                if (ch == "1") {
                    filtered_image.saveImage(filename); // Save the filtered image with the same filename
                    system(filename.c_str());
                    break;
                } else if (ch == "2") {
                    filtered_image.saveImage(new_image); // Save the filtered image with the new filename
                    system(new_image.c_str());
                    break;
                } else {
                    cout << "choose correct..!\n";
                    continue;
                }
            }
            break;
        }

    }
    return 0;
}