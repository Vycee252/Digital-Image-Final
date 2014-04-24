#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string Pvalue, Comment;
int size1, size2, grayscale;

int** readImage(string name);
void outputImage(int** image, string name);
int** edgeDetection(int** image);

int main()
{
    string fname;
    int choice;
    int **newImage;

    cout<<endl<<"Please enter your .PGM file name: ";
    cin>>fname;

    int** image = readImage(fname);



    do{

        cout<<"**********************************************************"<<endl;
        cout<<"*                                                        *"<<endl;
        cout<<"*  1: Option 1                                           *"<<endl;
        cout<<"*  2: Option 2                                           *"<<endl;
        cout<<"*  3: Option 3                                           *"<<endl;
        cout<<"*  4: Option 4                                           *"<<endl;
        cout<<"*  5: Exit                                               *"<<endl;
        cout<<"*                                                        *"<<endl;
        cout<<"**********************************************************"<<endl;
        cout<<"Choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
            case 1:
                cout<<"Case 1"<<endl;
                outputImage(image, fname);
                break;
            case 2:
                cout<<"Case 2"<<endl;
                newImage = edgeDetection(image);
                outputImage(newImage, fname);
                break;
            case 3:
                cout<<"Case 3"<<endl;
                break;
            case 4:
                cout<<"Case 4"<<endl;
                break;
            case 5:
                break;
            default:
                cout<<"Invalid Choice"<<endl;
                break;
        }
    }while(choice != 5);

    return 0;
}


int** readImage(string name)
{

    ifstream  inputFile(name.c_str());

    getline(inputFile, Pvalue);
    getline(inputFile, Comment);

    inputFile>>size1;
    inputFile>>size2;
    inputFile>>grayscale;

    int **image = new int*[size1];
    for(int i = 0; i < size1; i++)
        image[i] = new int[size2];

    for(int i = 0; i < size1; i++)
        for(int j = 0; j < size2; j++)
            inputFile>>image[i][j];

    return image;

}

void outputImage(int** image, string name)
{

    ofstream outputFile("NewFile.pgm");

    outputFile<<Pvalue<<endl;
    outputFile<<Comment<<endl;
    outputFile<<size1<<" ";
    outputFile<<size2<<endl;
    outputFile<<grayscale<<endl;

    for(int i = 0; i < size1; i ++)
        for(int j = 0; j < size2; j++)
            outputFile<<image[i][j]<<endl;
}

int** edgeDetection(int** image)
{
    int **newImage = new int*[size1];

    for(int i = 0; i < size1; i++)
        newImage[i] = new int[size2];

    for(int i = 0; i < size1; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            if(i == 0 || j == 0)
                newImage[i][j] = 0;
            else if(i == 255 || j == 255)
                newImage[i][j] = 0;
            else
            {
                newImage[i][j] = (image[i-1][j] + image[i][j-1] + image[i][j+1] +
                image[i+1][j] - image[i][j] - image[i][j] - image[i][j] - image[i][j]);
                if(newImage[i][j] < 0)
                    newImage[i][j] = 0;
                if(newImage[i][j] > 255)
                    newImage[i][j] = 255;
            }
        }
    }

    return newImage;
}
