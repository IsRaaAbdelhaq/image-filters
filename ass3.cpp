//Name:  Israa Abdelhaq Mohammed          20230053        filter:1 & 4 & 7 & 10 & 13 & 14
//       seif allah ahmed sayed hassan    20230185               3 & 6 & 9 & 12 & 15 &
//       ziad el sayed mohamed            20230152               2 & 5 & 8 & 11 & 16 & 17
//Section : 21 & 22
//this project convert the image to any filter in this code
//github link:https://github.com/IsRaaAbdelhaq/image-filters
//system diagram link:https://drive.google.com/file/d/1EYT7On4w21nk3hY5sG2T_fFG8Wr6qPWy/view?usp=drivesdk
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "image_class.h"
#include <string>
#include <vector>
#include <limits> 
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
void resizeByDimensions(Image& image, int W, int H) {
    unsigned char* temp = new unsigned char[W * H * 3];
    float R_W1 = (float)image.width / W;
    float R_H1 = (float)image.height / H;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            int x = static_cast<int>(R_W1 * j);
            int y = static_cast<int>(R_H1 * i);
            for (int k = 0; k < 3; ++k) {
                temp[(i * W + j) * 3 + k] = image(x, y, k);
            }
        }
    }
    delete[] image.imageData;
    image.imageData = temp;
    image.width = W;
    image.height = H;
}

void resizeByRatio(Image& image, double ratio) {
    int newWidth = static_cast<int>(image.width * ratio);
    int newHeight = static_cast<int>(image.height * ratio);
    resizeByDimensions(image, newWidth, newHeight);
}

void resizeImage(Image& image) {
    int choice;
    cout << "Pls Choose the resize option:\n"
         << "1- Enter the new dimensions\n"
         << "2- Enter a ratio\n";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 2) {//if choice isn’t valid 
        cout << "Invalid input. Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// delete end line 
        cin >> choice;
    }

    if (choice == 1) {
        int newWidth, newHeight;
        cout << "Enter new width: ";
        cin >> newWidth;
        cout << "Enter new height: ";
        cin >> newHeight;
        resizeByDimensions(image, newWidth, newHeight);
    } else {
        double ratio;
        cout << "Enter a ratio: ";
        cin >> ratio;
        resizeByRatio(image, ratio);
    }
}
// Function for resizing an image
void resizeImage(Image& img, int targetWidth, int targetHeight) {

    unsigned char* resizedData = new unsigned char[targetWidth * targetHeight * 3];

  
    for (int x = 0; x < targetWidth; ++x) {
        for (int y = 0; y < targetHeight; ++y) {
  
            double srcX = x * static_cast<double>(img.width) / targetWidth;
            double srcY = y * static_cast<double>(img.height) / targetHeight;


            int x1 = static_cast<int>(srcX);
            int y1 = static_cast<int>(srcY);
            int x2 = min(static_cast<int>(srcX) + 1, img.width - 1);
            int y2 = min(static_cast<int>(srcY) + 1, img.height - 1);

            // Loop over each color channel
            for (int channel = 0; channel < 3; ++channel) {
                double q11 = img(x1, y1, channel);
                double q12 = img(x1, y2, channel);
                double q21 = img(x2, y1, channel);
                double q22 = img(x2, y2, channel);

                double r1 = ((x2 - srcX) * q11 + (srcX - x1) * q21) / (x2 - x1);
                double r2 = ((x2 - srcX) * q12 + (srcX - x1) * q22) / (x2 - x1);

                resizedData[(y * targetWidth + x) * 3 + channel] = (y2 - srcY) * r1 + (srcY - y1) * r2;
            }
        }
    }

    
    delete[] img.imageData;

    img.imageData = resizedData;
    img.width = targetWidth;
    img.height = targetHeight;
}

// Function for merging two images
void mergeTwoImages(Image& img1, Image& img2, int mergeOption) {
    // Ask the user to choose the merge option
    cout << "Choose the merge option:\n"
         << "1- Resize the smaller image or both images to the biggest height and width and then merge\n"
         << "2- Merge the common area of the smaller width and the smaller height\n";
    while (true) {
        cin >> mergeOption;
        // Check if the user's input is valid
        if (!cin.fail() && (mergeOption == 1 || mergeOption == 2)) {
            break; // Exit the loop if the input is valid
        }
        cout << "Invalid input. Please enter 1 or 2.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }

    if (mergeOption == 1) {
        // Determine the dimensions of the new image
        int maxWidth = max(img1.width, img2.width);
        int maxHeight = max(img1.height, img2.height);

        // Resize the images
        resizeImage(img1, maxWidth, maxHeight); // Resize the first image
        resizeImage(img2, maxWidth, maxHeight); // Resize the second image

        // Loop over each pixel in the new image
        for (int x = 0; x < maxWidth; ++x) {
            for (int y = 0; y < maxHeight; ++y) {
                // For each pixel, if it is within the dimensions of the original images,
                // calculate the average of the corresponding pixels in the input images
                for (int channel = 0; channel < 3; ++channel) {
                    if (x < img1.width && y < img1.height && x < img2.width && y < img2.height) {
                        img1(x, y, channel) = (img1(x, y, channel) + img2(x, y, channel)) / 2;
                    } else if (x < img1.width && y < img1.height) {
                        img1(x, y, channel) = img1(x, y, channel);
                    } else if (x < img2.width && y < img2.height) {
                        img1(x, y, channel) = img2(x, y, channel);
                    } else {
                        img1(x, y, channel) = 0; // Fill the rest of the image with black
                    }
                }
            }
        }
    } else if (mergeOption == 2) {
        // Determine the dimensions of the common area
        int minWidth = min(img1.width, img2.width);
        int minHeight = min(img1.height, img2.height);

        // Resize the images
        resizeImage(img1, minWidth, minHeight); // Resize the first image
        resizeImage(img2, minWidth, minHeight); // Resize the second image

        // Loop over each pixel in the new image
        for (int x = 0; x < minWidth; ++x) {
            for (int y = 0; y < minHeight; ++y) {
                // For each pixel, calculate the average of the corresponding pixels in the input images
                for (int channel = 0; channel < 3; ++channel) {
                    img1(x, y, channel) = (img1(x, y, channel) + img2(x, y, channel)) / 2;
                }
            }
        }
    } else {
        cout << "Invalid option. Please enter 1 or 2.\n";
    }
}
void rotateImage(Image& image) {
    int rotation;
    cout << "Choose the type of rotation:\n1. 90\n2. 180\n3. 270\n";
    cin >> rotation;

    int newWidth = (rotation == 1 || rotation == 3) ? image.height : image.width;
    int newHeight = (rotation == 1 || rotation == 3) ? image.width : image.height;

    unsigned char* tempData = new unsigned char[newWidth * newHeight * 3];

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int new_i, new_j;
                switch (rotation) {
                    case 1: 
                        new_i = image.height - 1 - j;
                        new_j = i;
                        break;
                    case 2: 
                        new_i = image.width - 1 - i;
                        new_j = image.height - 1 - j;
                        break;
                    case 3: 
                        new_i = j;
                        new_j = image.width - 1 - i;
                        break;
                    default:
                        cout << "ERROR: Choose a valid rotation: ";
                        delete[] tempData;
                        return;
                }
                tempData[(new_j * newWidth + new_i) * 3 + k] = image(i, j, k);
            }
        }
    }

    delete[] image.imageData;
    image.imageData = tempData;
    image.width = newWidth;
    image.height = newHeight;
}
void darken_lighten_filter(Image &image){
    string choice;
    while (true)
    {
        cout << "Do you want to lighten (1) or darken (2) the image ? \n";
        cin >> choice;
        if(choice=="1"){
            double n;
            cout << "Enter the level of darkening or lighting from 0 to 100%: ";
            cin >> n;
            for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                double x = (n / 100);
                for (int k = 0; k < 3; ++k) {
                        // Lighten the pixel by level
                        int newValue = image(i, j, k) + x * (255 - image(i, j, k));
                        image(i, j, k) = (newValue > 255) ? 255 : newValue;
                    }
            }}
            break;
        }
        else if(choice=="2"){
            double n;
            cout << "Enter the level of darkening or lighting from 0 to 100%: ";
            cin >> n;
            for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                double y = (n / 100);
                    for (int k = 0; k < 3; ++k) {
                        // Darken the pixel by level
                        image(i, j, k) *=  y;
            }}
        }
        break;
    }
    else{
        cout << "Invalid choice. Please enter 'l' to lighten or 'd' to darken the image." << endl;
        continue;
    }
    
}
}
void cropImage(Image& img) {
    int X, Y, W, H;
    bool isInputValid = false;

    while (!isInputValid) {
        cout << "Please enter center point (x, y):\n";
        cin >> X >> Y; // center point (x, y)
        cout << "Please enter the dimensions of the area to cut (W, H):\n";
        cin >> W >> H; // the dimensions of the area to cut (W, H)
        if (X < 0 || Y < 0 || X >= img.width || Y >= img.height) {
            cout << "Invalid starting point. Try again.\n";
        }
        else if (W <= 0 || H <= 0 || X + W > img.width || Y + H > img.height) {
            cout << "Invalid dimensions, Pls Try again.\n";
        }
        else {
            isInputValid = true;
        }
    }
    unsigned char* croppedImageData = new unsigned char[W * H * 3];

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < 3; ++k) {
                croppedImageData[(j * W + i) * 3 + k] = img(X + i, Y + j, k);
            }
        }
    }
    delete[] img.imageData;

    img.imageData = croppedImageData;
    img.width = W;
    img.height = H;
}
void white_simple_frame(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if(i<20||j<20||i>(image.width-20)||j>(image.height-20)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=255;
            }
            }
        }
    }
}
void grey_simple_frame(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if(i<20||j<20||i>(image.width-20)||j>(image.height-20)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=150;
            }
            }
        }
    }
}
void white_fancy_frame(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if(i<20||j<20||i>(image.width-20)||j>(image.height-20)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=255;
                }
            }
            if((i>30&&i<40)||(i>50&&i<60)||(j>30&&j<40)||(j>50&&j<60)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=255;
                }
            }
            if((i<(image.width-30)&&i>(image.width-40))||(i<(image.width-50)&&i>(image.width-60))){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=255;
                }
            }
            if((j<(image.height-30)&&j>(image.height-40))||(j<(image.height-50)&&j>(image.height-60))){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=255;
                }
            }
        }
    }
}
void grey_fancy_frame(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if(i<20||j<20||i>(image.width-20)||j>(image.height-20)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=150;
                }
            }
            if((i>30&&i<40)||(i>50&&i<60)||(j>30&&j<40)||(j>50&&j<60)){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=150;
                }
            }
            if((i<(image.width-30)&&i>(image.width-40))||(i<(image.width-50)&&i>(image.width-60))){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=150;
                }
            }
            if((j<(image.height-30)&&j>(image.height-40))||(j<(image.height-50)&&j>(image.height-60))){
                for(int k = 0; k < 3; k++) {
                image(i, j, k)=150;
                }
            }
        }
    }
}
void frames(Image &image){
    string choose;
    bool x=true;
    while (x)
    {
        cout<<"choose the type of frame\n1.Simple\n2.Fancy\n";
        cin>>choose;
        if(choose=="1"){
            string ch;
            while (true)
            {
                cout<<"choose the color of frame\n1.white\n2.grey\n";
                cin>>ch;
                if(ch=="1"){
                    white_simple_frame(image);
                    x = false;
                    break;
                }
                else if(ch=="2"){
                    grey_simple_frame(image);
                    x = false;
                    break;
                    
                }
                else{
                    cout<<"choose 1 or 2 !\n";
                    continue;
                }
            }
            
        }
        else if(choose=="2"){
            string ch;
            while (true)
            {
            cout<<"choose the color of frame\n1.white\n2.grey\n";
            cin>>ch;
                if(ch=="1"){
                    white_fancy_frame(image);
                    x = false;
                    break;
                    
                }
                else if(ch=="2"){
                    grey_fancy_frame(image);
                    x = false;
                    break;
                    
                }
                else{
                    cout<<"choose 1 or 2 !\n";
                    continue;
                }
            }
        }
        else{
            cout<<"choose 1 or 2 !\n";
            continue;
        }
    }
}
void edgeDetection(Image& img) {
    gray_filter(img);
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    std::vector<std::vector<int>> gradMagnitudes(img.width, std::vector<int>(img.height));
    int minGrad = std::numeric_limits<int>::max();
    int maxGrad = std::numeric_limits<int>::min();
    for (int x = 1; x < img.width - 1; ++x) {
        for (int y = 1; y < img.height - 1; ++y) {
            int gradX = 0, gradY = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    gradX += sobelX[i + 1][j + 1] * img(x + i, y + j, 0);
                    gradY += sobelY[i + 1][j + 1] * img(x + i, y + j, 0);
                }}
            int magnitude = sqrt(gradX * gradX + gradY * gradY);
            gradMagnitudes[x][y] = magnitude;
            minGrad = std::min(minGrad, magnitude);
            maxGrad = std::max(maxGrad, magnitude);
        }}
    if (minGrad == maxGrad) {
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                for (int k = 0; k < 3; ++k) {
                    img(x, y, k) = 0;
                }}}
    } else {
        for (int x = 1; x < img.width - 1; ++x) {
            for (int y = 1; y < img.height - 1; ++y) {
                int normalizedMagnitude = 255 * (gradMagnitudes[x][y] - minGrad) / (maxGrad - minGrad);
                for (int k = 0; k < 3; ++k) {
                    img(x, y, k) = normalizedMagnitude;
                }}}}
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int k = 0; k < 3; ++k) {
                img(x, y, k) = 255 - img(x, y, k);
            }
        }}}
void blur(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            for(int k = 0; k < 3; k++) {
                int sum=0;
                int count =0;
                for(int x=i;x<i+20;x++){
                    for(int y=j;y<j+20;y++){
                        if(x<image.width&&y<image.height){
                            sum+=image(x,y,k);
                            count++;
                        }
                    }
                }
                image(i,j,k)=sum/count;
                }
            }
        }
        cout << "it will take some minutes...";
}
void warm_filter(Image &image){
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Increase the intensity of warm colors (red and orange)
            image(x, y, 0) = min(255, image(x, y, 0) + 50); // Red channel
            image(x, y, 1) = max(0, image(x, y, 1) - 20);    // Green channel
            image(x, y, 2) = max(0, image(x, y, 2) - 20);    // Blue channel
        }
    }
}
void oil_filter(Image &image){
    const int rad = 5; // rad = radius
    const int intlevel = 2; //  intlevel = intensityLevels

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int intensityCount[intlevel] = {0};
            int sumR[intlevel] = {0};
            int sumG[intlevel] = {0};
            int sumB[intlevel] = {0};


            for (int x = i - rad; x <= i + rad; ++x) {
                for (int y = j - rad; y <= j + rad; ++y) {

                    if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                        int r = image(x, y, 0);
                        int g = image(x, y, 1);
                        int b = image(x, y, 2);

                        int intensity = int((r + g + b) / 3.0 * intlevel / 255.0);
                        intensityCount[intensity]++;
                        sumR[intensity] += r;
                        sumG[intensity] += g;
                        sumB[intensity] += b;
                    }
                }
            }
            int maxIndex = 0;
            int curMax = 0;
            for (int k = 0; k < intlevel; ++k) {
                if (intensityCount[k] > curMax) {
                    curMax = intensityCount[k];
                    maxIndex = k;
                }
            }
            image(i, j, 0) = sumR[maxIndex] / curMax;
            image(i, j, 1) = sumG[maxIndex] / curMax;
            image(i, j, 2) = sumB[maxIndex] / curMax;
        }
    }
}
void old_tv(Image &image){
    srand(time(0));
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            for(int k = 0; k < 3; ++k) {
                if (j % 2 == 0) {
                    image(i, j, k) -= rand() % 31;
                    if (image(i, j, k) < 0)
                        image(i, j, k) = 0;
                }
            }
        } 
    }
}
void purple(Image &image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
               image(i,j,1)*=.9;//green * 0.90 for pruple filter
               
                
        }
    }}
}
void infared(Image &image){
     for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i,j,0)=255;
                image(i,j,1)=255-image(i,j,1);//change Green to infrared 
                image(i,j,2)=255-image(i,j,2);//change Blue to infrared 

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
        cout << " 7 / Darken and Lighten Image     8 / Crop image \n";
        cout << "9 / Frame image                   10 / Sobel_edge_detection   \n";
        cout << "11 /Resize image                  12 / Blur image \n";
        cout << "13 / Sunshine Image               14 / Oil painting \n";
        cout << "15 / Old Tv                       16 / Purple image  \n";
        cout<<"                        17 / Infared image               \n ";
        string choose1;
        cin >> choose1;
        cout << "_______________________________________________________________________________________________________" << endl ;
        if(choose1=="1"){
            gray_filter(image);
            save_image(image,filename1);
            back = true;
        }
        else if (choose1=="2"){
            black_white_filter(image);
            save_image(image,filename1);
                back = true;
        }
        else if (choose1=="3"){
            invert(image);
            save_image(image,filename1);
                back = true;
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
        int option;
        mergeTwoImages(image,image2,option);
        save_image(image,filename1);
                back = true;
        }
        else if (choose1=="5"){
            flip_filter(image);
            save_image(image,filename1);
                back = true;
        }
        else if (choose1=="6"){
            rotateImage(image);
            save_image(image,filename1);
            back = true;
        }
        else if (choose1=="7"){
            darken_lighten_filter(image);
            save_image(image,filename1);
                back = true;
        }
        else if (choose1=="8"){
             cropImage(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="9"){
             frames(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="10"){
            edgeDetection(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="11"){
            int w,h;
            double x;
            resizeImage(image);
            save_image(image,filename1);
            back = true;
        } 
        else if (choose1=="12"){
             blur(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="13"){
             warm_filter(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="14"){
             oil_filter(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="15"){
             old_tv(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="16"){
             purple(image);
             save_image(image,filename1);
                back = true;
        }
        else if (choose1=="17"){
             infared(image);
             save_image(image,filename1);
                back = true;
        }
        else{
            cout << "Invalid input. Please enter a number from 1 to 17.\n";
            continue;
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







