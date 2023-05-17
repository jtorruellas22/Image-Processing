#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "TGA.h"
using namespace std;

int main()
{
    string files[11] = { "input/car.tga", 
        "input/circles.tga",
        "input/layer_blue.tga",
        "input/layer_green.tga",
        "input/layer_red.tga",
        "input/layer1.tga",
        "input/layer2.tga",
        "input/pattern1.tga",
        "input/pattern2.tga",
        "input/text.tga",
        "input/text2.tga"};

    string examples[12] = { "examples/EXAMPLE_part1.tga",
        "examples/EXAMPLE_part2.tga",
        "examples/EXAMPLE_part3.tga",
        "examples/EXAMPLE_part4.tga",
        "examples/EXAMPLE_part5.tga",
        "examples/EXAMPLE_part6.tga",
        "examples/EXAMPLE_part7.tga",
        "examples/EXAMPLE_part8_r.tga",
        "examples/EXAMPLE_part8_g.tga",
        "examples/EXAMPLE_part8_b.tga",
        "examples/EXAMPLE_part9.tga",
        "examples/EXAMPLE_part10.tga" };

    vector<Tfile> imageFile;
    vector<Tfile> exampleFile;
    int size = 0;

    for (int i = 0; i < 11; i++) {
		ifstream inFile(files[i], ios_base::binary);
        Tfile newFile = Tfile();
        newFile.unPackHeader(inFile);
        newFile.unPackPixel(inFile);
        imageFile.push_back(newFile);
        size += 1;
    }
    for (int i = 0; i < 12; i++) {
        ifstream inFile(examples[i], ios_base::binary);
        Tfile newFile = Tfile();
        newFile.unPackHeader(inFile);
        newFile.unPackPixel(inFile);
        exampleFile.push_back(newFile);
    }
    // Task 1 Multiply "layer1.tga" and "pattern1.tga"
    Tfile file1 = Tfile();
    file1.Multiply(imageFile[5], imageFile[7]);
    file1.writeFile("output/part1.tga");
    if (file1 == exampleFile[0]) {
        cout << "Task 1 Pass" << endl;
    }
    else
        cout << "Task 1 Fail" << endl;
    
    //Task 2 Subtract "layer2.tga" (top) with "car.tga" (bottom)
    Tfile file2 = Tfile();
    file2.Subtract(imageFile[0], imageFile[6]);
    file2.writeFile("output/part2.tga");
    if (file2 == exampleFile[1]) {
        cout << "Task 2 Pass" << endl;
    }
    else
        cout << "Task 2 Fail" << endl;

    //Task 3 Multiply layer1 pattern2, then combine with text using Screen
    Tfile temp1 = Tfile();
    temp1.Multiply(imageFile[5], imageFile[8]);
    Tfile file3 = Tfile();
    file3.Screen(imageFile[9], temp1);
    file3.writeFile("output/part3.tga");
    if (file3 == exampleFile[2]) {
        cout << "Task 3 Pass" << endl;
    }
    else
        cout << "Task 3 Fail" << endl;

    // Task 4: Mulitply layer 2.tga with circles.tga. Subtract pattern 2.
    Tfile temp2 = Tfile();
    temp2.Multiply(imageFile[6], imageFile[1]);
    Tfile file4 = Tfile();
    file4.Subtract(temp2, imageFile[8]);
    file4.writeFile("output/part4.tga");
    if (file4 == exampleFile[3]) {
        cout << "Task 4 Pass" << endl;
    }
    else
        cout << "Task 4 Fail" << endl;

    //Task 5: Overlay layer 1 and pattern 1
    Tfile file5 = Tfile();
    file5.Overlay(imageFile[5], imageFile[7]);
    file5.writeFile("output/part5.tga");
    if (file5 == exampleFile[4]) {
        cout << "Task 5 Pass" << endl;
    }
    else
        cout << "Task 5 Fail" << endl;

    //Task 6: Load car and add 200 to green
    Tfile file6 = Tfile(imageFile[0]);
    file6.Add(200, "green");
    file6.writeFile("output/part6.tga");
    if (file6 == exampleFile[5]) {
        cout << "Task 6 Pass" << endl;
    }
    else
        cout << "Task 6 Fail" << endl;

    //Task 7: Load car, multiply red by 4, blue by 0
    Tfile file7= Tfile(imageFile[0]);
    file7.Multiply(4, "red");
    file7.Multiply(0, "blue");
    file7.writeFile("output/part7.tga");
    if (file7 == exampleFile[6]) {
        cout << "Task 7 Pass" << endl;
    }
    else
        cout << "Task 7 Fail" << endl;

    //Task 8: Load car, each color seperate file
    imageFile[0].writeFileSeperate("output/part8_r.tga", "output/part8_g.tga", "output/part8_b.tga");
    ifstream create("output/part8_r.tga", ios_base::binary);
    Tfile made = Tfile();
    made.unPackHeader(create);
    made.unPackPixel(create);
    if (made == exampleFile[7]) {
        cout << "Task 8 Pass" << endl;
    }
    else
        cout << "Task 8 Fail" << endl;

    //Task 9: Load red, green, blue and combine
    Tfile file9 = Tfile();
    file9.Combine(imageFile[4], imageFile[3], imageFile[2]);
    file9.writeFile("output/part9.tga");
    if (file9 == exampleFile[10]) {
        cout << "Task 9 Pass" << endl;
    }
    else
        cout << "Task 9 Fail" << endl;

    //Task 10: Write text 2 in reverse
    imageFile[10].writeFileReverse("output/part10.tga");
    ifstream created("output/part10.tga", ios_base::binary);
    Tfile made2 = Tfile();
    made2.unPackHeader(created);
    made2.unPackPixel(created);
    if (made2 == exampleFile[11]) {
        cout << "Task 10 Pass" << endl;
    }
    else
        cout << "Task 10 Fail" << endl;
}
