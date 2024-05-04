/*
This Program allows you to apply a filter on any photo with any extension
Authors: Nada Samir Hanfy: 20230441: S5 >> Filters : 1 , 4 , 7 ,10
         Ammar Sayed Mansour: 20230561: S6 >> Filters : 3 , 6 , 9 ,12 + main menu
         Youssef Yasser Ahmed: 20230518: S5 >> Filters : 2 , 5 , 8 ,11 + main menu

github link: https://github.com/Ammarrx/Assignment3
*/
#include "Image_Class.h"
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;
// Grayscale filter
void grayscale(const string& filename, string e_filename) {
    Image image(filename);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int average = 0;
            for (int k = 0; k < image.channels; k++) {
                average += image(i, j, k);
            }
            average /= 3;
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = average;
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Black and white function
void black_white(const string& filename, string e_filename) {
    Image image(filename);
    const unsigned int compare = 128;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            unsigned char pxl_value = (avg > compare) ? 255 : 0;
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = pxl_value;
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Horizontal flip function
void horizontalflip(const string& filename, string e_filename) {
    Image image(filename);
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned char h_f_pxl = image(i, j, k);
                image(i, j, k) = image(image.width - 1 - i, j, k);
                image(image.width - 1 - i, j, k) = h_f_pxl;
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Vertical flip function
void verticalflip(const string& filename, string e_filename) {
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            // Swap pixels
            for (int k = 0; k < 3; ++k) {
                unsigned char v_f_pxl = image(i, j, k);
                image(i, j, k) = image(i, image.height - 1 - j, k);
                image(i, image.height - 1 - j, k) = v_f_pxl;
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Invert filter
void invert_image(const string& filename, string e_filename) {
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {

                // invert all channels colors
                image(i, j, 0) = 255 - image(i, j, 0);
                image(i, j, 1) = 255 - image(i, j, 1);
                image(i, j, 2) = 255 - image(i, j, 2);
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Merge filter
void merge_image(const string& filename1, const string& e_filename1) {
    string filename2, e_filename2;

    cout << "Please enter the second image name and extenstion: ";
    cin >> filename2;
    Image image1(filename1);
    Image image2(filename2);
    // Check if the images have the same dimensions
    if (image1.width != image2.width || image1.height != image2.height) {
        cout << "Error: Images must have the same dimensions for merging." << endl;
        return;
    }

    // Create a new image to store the result
    Image merged_image(image1.width, image1.height);

    // Algorithm
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                merged_image(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }

    merged_image.saveImage(e_filename1);
    system(e_filename1.c_str());
}

// Rotate_90 filter
void rotate_image90(const string& filename, string e_filename) {
    Image image(filename);
    Image degrees_90(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            degrees_90(image.height - j - 1, i, 0) = image(i, j, 0);
            degrees_90(image.height - j - 1, i, 1) = image(i, j, 1);
            degrees_90(image.height - j - 1, i, 2) = image(i, j, 2);
        }
    }
    degrees_90.saveImage(e_filename);
    system(e_filename.c_str());
}

// Rotate_180 filter
void rotate_image180(const string& filename, string e_filename) {
    Image image(filename);
    Image degrees_90(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            degrees_90(image.height - j - 1, i, 0) = image(i, j, 0);
            degrees_90(image.height - j - 1, i, 1) = image(i, j, 1);
            degrees_90(image.height - j - 1, i, 2) = image(i, j, 2);
        }
    }
    Image degrees_180(image.width, image.height);
    for (int i = 0; i < degrees_90.width; ++i) {
        for (int j = 0; j < degrees_90.height; ++j) {
            degrees_180(degrees_90.height - j - 1, i, 0) = degrees_90(i, j, 0);
            degrees_180(degrees_90.height - j - 1, i, 1) = degrees_90(i, j, 1);
            degrees_180(degrees_90.height - j - 1, i, 2) = degrees_90(i, j, 2);
        }
    }
    degrees_180.saveImage(e_filename);
    system(e_filename.c_str());
}

// Rotate_270 filter
void rotate_image270(const string& filename, string e_filename) {
    Image image(filename);
    Image degrees_90(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            degrees_90(image.height - j - 1, i, 0) = image(i, j, 0);
            degrees_90(image.height - j - 1, i, 1) = image(i, j, 1);
            degrees_90(image.height - j - 1, i, 2) = image(i, j, 2);
        }
    }
    Image degrees_180(image.width, image.height);
    for (int i = 0; i < degrees_90.width; ++i) {
        for (int j = 0; j < degrees_90.height; ++j) {
            degrees_180(degrees_90.height - j - 1, i, 0) = degrees_90(i, j, 0);
            degrees_180(degrees_90.height - j - 1, i, 1) = degrees_90(i, j, 1);
            degrees_180(degrees_90.height - j - 1, i, 2) = degrees_90(i, j, 2);
        }
    }
    Image degrees_270(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            degrees_270(degrees_180.height - j - 1, i, 0) = degrees_180(i, j, 0);
            degrees_270(degrees_180.height - j - 1, i, 1) = degrees_180(i, j, 1);
            degrees_270(degrees_180.height - j - 1, i, 2) = degrees_180(i, j, 2);
        }
    }
    degrees_270.saveImage(e_filename);
    system(e_filename.c_str());
}

// Crop filter
void crop_image(const string& filename, string e_filename) {
    Image image(filename);

    int x, y, width, height;

    // input
    cout << "Enter the starting postion (x, y) separated by a space: ";
    cin >> x >> y;
    cout << "Enter the width: ";

    while (!(cin >> width) || width < 0) {
        cout << "Invalid input. Please enter a valid number for width: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter the height: ";
    while (!(cin >> height) || width < 0) {
        cout << "Invalid input. Please enter a valid number for height: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

        Image cropped_image(width, height);

        // algorithm
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    cropped_image(i, j, k) = image(x + i, y + j, k);
                }
            }
        }
        cropped_image.saveImage(e_filename);
        system(e_filename.c_str());
    }


// Resize filter
void resize_image(const string& filename, string e_filename, int new_width , int new_height ) {
    Image image(filename);


    Image resized_image(new_width, new_height);

    // Algorithm
    double x_ratio = static_cast<double>(image.width) / new_width;
    double y_ratio = static_cast<double>(image.height) / new_height;

    for (int i = 0; i < new_width; ++i) {
        for (int j = 0; j < new_height; ++j) {
            int nearest_x = static_cast<int>(i * x_ratio);
            int nearest_y = static_cast<int>(j * y_ratio);

            for (int k = 0; k < image.channels; ++k) {
                resized_image(i, j, k) = image(nearest_x, nearest_y, k);
            }
        }
    }

    resized_image.saveImage(e_filename);
    system(e_filename.c_str());
}
#include <algorithm>

// Darken and Lighten filter
void darken_lighten(const string& filename, string e_filename) {
    Image image(filename);
    string choice;

    // Ask the user if they want to darken or lighten 
    while (true) {
        cout << "I)darken\n";
        cout << "II)lighten\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "I" || choice == "i") {
            // Darken 
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        image(i, j, k) = image(i, j, k) / 2;
                    }
                }
            }
            break;
        }
        else if (choice == "II" || choice == "ii") {
            // Lighten 
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {

                        image(i, j, k) = std::min(255, static_cast<int>(image(i, j, k) * 1.5));
                    }
                }
            }
            break;
        }
        else {
            cout << "Invalid choice. Please enter 'darken' or 'lighten'." << endl;
            continue;
        }
    }

    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// Detect image edges 
void detect_edges(const string& filename, string e_filename) {
    Image image(filename);
    Image edges_image(image.width, image.height);

    // Convert image to grayscale
    Image grayscale_image(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int gray_value = 0;
            for (int k = 0; k < image.channels; ++k) {
                gray_value += image(i, j, k);
            }
            gray_value /= 3;
            grayscale_image(i, j, 0) = gray_value;
            grayscale_image(i, j, 1) = gray_value;
            grayscale_image(i, j, 2) = gray_value;
        }
    }

    // Apply edge detection
    for (int x = 1; x < image.width - 1; ++x) {
        for (int y = 1; y < image.height - 1; ++y) {
            // Calculate gradient magnitude
            double dx = grayscale_image(x + 1, y, 0) - grayscale_image(x - 1, y, 0);
            double dy = grayscale_image(x, y + 1, 0) - grayscale_image(x, y - 1, 0);
            double magnitude = sqrt(dx * dx + dy * dy);

            // Ensure the magnitude does not exceed 255
            if (magnitude > 255) magnitude = 255;

            // Set pixel values in the edges image
            edges_image(x, y, 0) = static_cast<unsigned char>(magnitude);
            edges_image(x, y, 1) = static_cast<unsigned char>(magnitude);
            edges_image(x, y, 2) = static_cast<unsigned char>(magnitude);
        }
    }

    edges_image.saveImage(e_filename);
    system(e_filename.c_str());
}

void blur(const string& filename, string e_filename) {

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int counter = 0;
                int total = 0;
                for (int w = -20; w <= 20; w++) {
                    for (int h = -20; h <= 20; h++) {
                        if ((i + w >= 0 && i + w < image.width) && (j + h >= 0 && j + h < image.height)) {
                            counter++;
                            total += image.getPixel(i + w, j + h, k);
                        }
                    }
                }
                image.setPixel(i, j, k, total / counter);
            }
        }
    }
    image.saveImage(e_filename);
    system(e_filename.c_str());
}

// red frame function
void red_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);


    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 255;
                Frame(i, j, 1) = 0;
                Frame(i, j, 2) = 0;
            }
        }
    }

    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}


// green frame function
void green_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);


    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 0;
                Frame(i, j, 1) = 255;
                Frame(i, j, 2) = 0;
            }
        }
    }

    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}


// blue frame function
void blue_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);


    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 0;
                Frame(i, j, 1) = 0;
                Frame(i, j, 2) = 255;
            }
        }
    }

    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}


// white frame function
void white_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);


    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, k) = 255;

            }
        }
    }

    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}


// black frame function
void black_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);


    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, k) = 0;

            }
        }
    }

    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}

//fancy frame function
void fancy_frame(const string& filename, string e_filename, int framewidth, int frameheight) {

    Image image(filename);

    int biggerwidth = image.width + 2 * framewidth;
    int biggerheight = image.height + 2 * frameheight;


    Image Frame(biggerwidth, biggerheight);

    for (int i = 0; i < Frame.width; ++i) {
        for (int j = 0; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 146;
                Frame(i, j, 1) = 84;
                Frame(i, j, 2) = 46;
            }
        }
    }

    for (int i = 0; i < Frame.width / 2; ++i) {
        for (int j = 0; j < Frame.height / 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 254;
                Frame(i, j, 1) = 225;
                Frame(i, j, 2) = 147;

            }
        }
    }

    for (int i = Frame.width / 2; i < Frame.width; ++i) {
        for (int j = Frame.height / 2; j < Frame.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                Frame(i, j, 0) = 255;
                Frame(i, j, 1) = 215;
                Frame(i, j, 2) = 0;
            }
        }
    }


    for (int i = framewidth; i < biggerwidth - framewidth; ++i) {
        for (int j = frameheight; j < biggerheight - frameheight; ++j) {

            for (int k = 0; k < 3; ++k) {

                Frame(i, j, k) = image(i - framewidth, j - frameheight, k);

            }
        }
    }

    Frame.saveImage(e_filename);
    system(e_filename.c_str());
}

//Main function
int main() {
    int framewidth, frameheight , new_width , new_height;
    string choice, filename, e_filename, filter_choice, flip_choice, rotate_choice, frame_color;

    // Main Menu
    while (true) {
        cout << "Welcome to photos filters program\n";
        cout << "A)Insert a new photo\n";
        cout << "B)Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);
        // Program
        if (choice == "A" || choice == "a") {
            // Filters
            while (true) {
                cout << "\nFilters\n";
                cout << "-------\n";
                cout << "A)Grayscale\n";
                cout << "B)Black and white\n";
                cout << "C)Invert\n";
                cout << "D)Merge\n";
                cout << "E)Flip\n";
                cout << "F)Rotate\n";
                cout << "G)Darken and Lighten\n";
                cout << "H)Crop\n";
                cout << "I)Adding a frame\n";
                cout << "J)Detect image edges\n";
                cout << "K)Resize\n";
                cout << "L)Blur (Takes 5 minutes to process)\n";
                cout << "Choose a filter: ";
                cin >> filter_choice;

                // File names and extensions
                // Before filter
                cout << "Please enter an image name and extenstion: ";
                cin >> filename;
                Image image(filename);
                // After filter
                cout << "Enter an Image name and extenstion to store a new image: ";
                cin >> e_filename;

                // Grayscale 
                if (filter_choice == "A" || filter_choice == "a") {
                    grayscale(filename, e_filename);
                    break;
                }

                // Black and white
                else if (filter_choice == "B" || filter_choice == "b") {
                    black_white(filename, e_filename);
                    break;
                }

                // Invert
                else if (filter_choice == "C" || filter_choice == "c") {
                    invert_image(filename, e_filename);
                    break;
                }
                // Merge
                else if (filter_choice == "D" || filter_choice == "d") {
                    merge_image(filename, e_filename);
                    break;
                }

                // Flip
                else if (filter_choice == "E" || filter_choice == "e") {
                    while (true) {
                        cout << "I)Horizontal flip\n";
                        cout << "II)Vertical flip\n";
                        cout << "Enter your choice: ";
                        cin >> flip_choice;

                        // Horizontal flip
                        if (flip_choice == "I" || flip_choice == "i") {
                            horizontalflip(filename, e_filename);
                            break;
                        }

                        // Vertical flip
                        else if (flip_choice == "II" || flip_choice == "ii") {
                            verticalflip(filename, e_filename);
                            break;
                        }

                        // Invalid Input
                        else {
                            cout << "Invalid Input, Please choose either (I) or (II)" << endl;
                            continue;
                        }
                    }
                    break;
                }

                //Rotate
                else if (filter_choice == "F" || filter_choice == "f") {
                    while (true) {
                        cout << "90\n";
                        cout << "180\n";
                        cout << "270\n";
                        cout << "Enter your choice: ";
                        cin >> rotate_choice;

                        //90 degrees
                        if (rotate_choice == "90") {
                            rotate_image90(filename, e_filename);
                            break;
                        }

                        //180 degrees
                        else if (rotate_choice == "180") {
                            rotate_image180(filename, e_filename);
                            break;
                        }

                        //270 degrees
                        else if (rotate_choice == "270") {
                            rotate_image270(filename, e_filename);
                            break;
                        }

                        // Invalid Input
                        else {
                            cout << "Invalid Input, Please enter one of the following numbers: " << endl;
                            continue;
                        }
                    }
                    break;
                }

                // Darken and Lighten
                else if (filter_choice == "G" || filter_choice == "g") {
                    darken_lighten(filename, e_filename);
                    break;
                }

                // Crop 
                else if (filter_choice == "H" || filter_choice == "h") {
                    crop_image(filename, e_filename);
                    break;
                }

                // Adding a frame 
                else if (filter_choice == "I" || filter_choice == "i") {

                    cout << "Enter frame width: ";
                    while (!(cin >> framewidth) || framewidth <= 0) {
                        cout << "Invalid input. Please enter a positive integer for frame width: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    cout << "Enter frame height: ";
                    while (!(cin >> frameheight) || frameheight <= 0) {
                        cout << "Invalid input. Please enter a positive integer for frame height: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (true) {
                        cout << "1) RED\n";
                        cout << "2) GREEN\n";
                        cout << "3) BLUE\n";
                        cout << "4) WHITE\n";
                        cout << "5) BLACK\n";
                        cout << "6) Fancy(Cream & Brown & Gold)\n";
                        cout << "Enter your choice: ";
                        cin >> frame_color;

                        //red frame
                        if (frame_color == "1") {
                            red_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }

                        //green frame
                        else if (frame_color == "2") {
                            green_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }

                        //blue frame
                        else if (frame_color == "3") {
                            blue_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }

                        //white fame
                        else if (frame_color == "4") {
                            white_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }

                        //black frame
                        else if (frame_color == "5") {
                            black_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }

                        //fancy fame
                        else if (frame_color == "6") {
                            fancy_frame(filename, e_filename, framewidth, frameheight);
                            break;
                        }
                        // Invalid Input
                        else {
                            cout << "Invalid Input. Please enter one of the following numbers: " << endl;
                        }

                    }
                    break;
                }
                
                // Detect image edges 
                else if (filter_choice == "J" || filter_choice == "j") {
                    detect_edges(filename, e_filename);
                    break;
                }

                // Resize
                else if (filter_choice == "K" || filter_choice == "k") {

                    cout << "Enter new width: ";
                    while (!(cin >> new_width) || new_width <= 0) {
                        cout << "Invalid input. Please enter a positive integer for new width: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    cout << "Enter new height: ";
                    while (!(cin >> new_height) || new_height <= 0) {
                        cout << "Invalid input. Please enter a positive integer for new height: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    resize_image(filename, e_filename , new_width , new_height);
                    break;
                }

                // Blur
                else if (filter_choice == "L" || filter_choice == "l") {
                    blur(filename, e_filename);
                    break;
                }

                // Invalid Input
                else {
                    cout << "Invalid Input, Please choose a letter between(A,L)" << endl;
                    continue;
                }
                // Clear Output
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        // Exit
        else if (choice == "B" || choice == "b") {
            cout << "Exiting the program..." << endl;
            break;
        }
        // Invalid Input
        else {
            cout << "Invalid Input, Please choose between A or B.\n" << endl;
            continue;
        }
        // Clear Output
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0;
}
