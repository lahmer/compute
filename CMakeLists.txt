cmake_minimum_required(VERSION 3.5)
project(ClioTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#***********************************************************************************************************************
#This part we add the header files directories for the libraries used in this project
#***********************************************************************************************************************
        #add libssh header directories
                INCLUDE_DIRECTORIES(/usr/include)
#***********************************************************************************************************************
#This part is didecated to add the directories of the libraries shared files
#***********************************************************************************************************************
                link_directories(/usr/lib)
                link_directories(/usr/local/lib)


set(SOURCE_FILES
        main.cpp common.h Compute.cpp Compute.h RequestServer/ResquestServer.cpp RequestServer/ResquestServer.h RequestServer/ConnectionManager.cpp RequestServer/ConnectionManager.h RequestServer/RequestThread.cpp RequestServer/RequestThread.h RequestServer/RequestThreadPoolManager.cpp RequestServer/RequestThreadPoolManager.h RequestServer/Semaphore.cpp RequestServer/Semaphore.h TaskEngine/TaskQueueManager.cpp TaskEngine/TaskQueueManager.h TaskEngine/TaskThread.cpp TaskEngine/TaskThread.h TaskEngine/Message.cpp TaskEngine/Message.h "Disk Images MAnager/Volume.cpp" "Disk Images MAnager/Volume.h" "Disk Images MAnager/DiskImagesManager.cpp" "Disk Images MAnager/DiskImagesManager.h" VmManager/VmComponents/VirtualMachine.cpp VmManager/VmComponents/VirtualMachine.h VmManager/VmComponents/AbstractVmFactory.h VmManager/VmComponents/DeviceFactory.cpp VmManager/VmComponents/DeviceFactory.h VmManager/VmComponents/Booter.cpp VmManager/VmComponents/Booter.h)


add_executable(compute ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES(compute config++ boost_system boost_thread virt pthread crypto ssl ticpp guestfs)