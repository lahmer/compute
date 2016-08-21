//
// Created by lahmer on 8/16/16.
//
#include "common.h"

 int main(){
     Compute::Init();
     for (int i = 0; i < 10; ++i) {
         if(!DiskImagesManager::CreateVolume("ilyas"+std::to_string(i),5000000)){
             if(DiskImagesManager::DeleteVolume("ilyas"+std::to_string(i))){
                 std::cout<<"ilyas"+std::to_string(i)<<"is deleted"<<std::endl;
             }
         }else{
             std::cout<<"ilyas"+std::to_string(i)<<"is created"<<std::endl;

         }

     }

     while(true);
     return 0;
}
