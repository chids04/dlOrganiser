#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

bool inArr(char *extension, int size, const char *array);
    
int main(){

    char *folderPath = "/Users/chids/Downloads";
    const char *fileExts[] = {"pdf", "zip", "dmg", "png", "jpg"};
    int arrSize = sizeof(fileExts) / sizeof(fileExts[0]);
    
    DIR *dir;
    struct dirent *entry;

    while(true){
        if((dir = opendir(folderPath)) != NULL) {
            while((entry = readdir(dir)) != NULL){

                if(entry->d_type == DT_REG){
                    char *extension = strrchr(entry->d_name, '.') + 1;
                    
                    if(inArr(extension, arrSize, fileExts) == true){
                        //check if folder for file path exists
                        //add file name to current path and move file to folder
                        //add support for zip and rar files
        
                    }

                }
            }
        }
        closedir(dir);
    }
    return 0;
    
}

bool inArr(char *extension, int size, const char *array){

    for(int i=0; i<size; i++){
        if(strcmp(extension, array[i]) == 0){
            return true;
        }
    }

    return false;
}