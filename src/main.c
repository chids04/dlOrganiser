#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLEN 256

bool inArr(char *extension, int size, const char **array);
void createFolders(const char **array, int size, const char*path);
char *createDirName(const char *name);

int main(){

    const char *folderPath = "/Users/chids/Downloads/";
    const char *fileExts[] = {"archive", "image", "program", "document"};
    char srcPath[MAXLEN];
    char destPath[MAXLEN];
    int arrSize = sizeof(fileExts) / sizeof(fileExts[0]);

    createFolders(fileExts, arrSize, folderPath);
    
    DIR *dir;
    struct dirent *entry;

    while(true){
        if((dir = opendir(folderPath)) != NULL) {
            sleep(1);
            while((entry = readdir(dir)) != NULL){

                if(entry->d_type == DT_REG){
                    char *extension = strrchr(entry->d_name, '.') + 1;
                        
                    if(strcmp(extension, "pdf") == 0 || 
                    strcmp(extension, "docx") == 0 || 
                    strcmp(extension, "doc") == 0 || 
                    strcmp(extension, "ppt") == 0 ||
                    strcmp(extension, "pptx") == 0) {

                        memset(destPath, 0, sizeof(destPath));
                        strcpy(destPath, folderPath);
                        strcat(destPath, createDirName("document"));
                        strcat(destPath, "/");
                        strcat(destPath, entry->d_name);

                        memset(srcPath, 0, sizeof(srcPath));
                        strcpy(srcPath, folderPath);
                        strcat(srcPath, entry->d_name);

                        rename(srcPath, destPath);
                    }
                    else if(strcmp(extension, "zip") == 0 || strcmp(extension, "7zip") == 0 || strcmp(extension, "rar") == 0){

                        memset(destPath, 0, sizeof(destPath));
                        strcpy(destPath, folderPath);
                        strcat(destPath, createDirName("archive"));
                        strcat(destPath, "/");
                        strcat(destPath, entry->d_name);

                        memset(srcPath, 0, sizeof(srcPath));
                        strcpy(srcPath, folderPath);
                        strcat(srcPath, entry->d_name);

                        rename(srcPath, destPath);
                    }
                    else if(strcmp(extension, "app") == 0 || strcmp(extension, "dmg") == 0 || strcmp(extension, "exe") == 0 || strcmp(extension, "pkg") == 0){

                        memset(destPath, 0, sizeof(destPath));
                        strcpy(destPath, folderPath);
                        strcat(destPath, createDirName("program"));
                        strcat(destPath, "/");
                        strcat(destPath, entry->d_name);

                        memset(srcPath, 0, sizeof(srcPath));
                        strcpy(srcPath, folderPath);
                        strcat(srcPath, entry->d_name);

                        rename(srcPath, destPath);
                    }
                    else if(strcmp(extension, "png") == 0 || strcmp(extension, "jpg") == 0|| strcmp(extension, "bmp") == 0 || strcmp(extension, "webmp") == 0){
                        
                        memset(destPath, 0, sizeof(destPath));
                        strcpy(destPath, folderPath);
                        strcat(destPath, createDirName("image"));
                        strcat(destPath, "/");
                        strcat(destPath, entry->d_name);

                        memset(srcPath, 0, sizeof(srcPath));
                        strcpy(srcPath, folderPath);
                        strcat(srcPath, entry->d_name);

                        rename(srcPath, destPath);
                    }
                }            
            }
            closedir(dir);
        } 
    }
    return 0;
}

bool inArr(char *extension, int size, const char **array){
    
    for(int i=0; i<size; i++){
        if(strcmp(extension, array[i]) == 0){
            return true;
        }
    }

    return false;
}

char *createDirName(const char *name){

    size_t length = strlen(name);
    char *folderName = malloc(length+2);

    for(int i=0; i<length; i++){
        if(islower(name[i])){
            folderName[i] = toupper(name[i]);
        }
    }

    //folderName[length-1] = 's';
    folderName[length] = 'S';
    folderName[length+1] = '\0';
    
    return folderName;
}

void createFolders(const char **array, int size, const char *path){

    char *folderName;
    char filePath[MAXLEN];
    DIR *tempDir;

    for(int i=0; i<size; i++){
        folderName = createDirName(array[i]);
        if((tempDir = opendir(folderName)) == NULL){
            strcpy(filePath, path);
            strcat(filePath, folderName);
            free(folderName);
            mkdir(filePath, 0777);
            
        }
        else{
            closedir(tempDir);
            free(folderName);
            printf("already exists\n");
        }
    }

}