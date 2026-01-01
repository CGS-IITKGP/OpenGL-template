#include <iostream>
#include <bullet/btBulletDynamicsCommon.h>

int main() {
    std::cout << "Testing Bullet Physics..." << std::endl;
    
    btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
    
    std::cout << "Success! Bullet is working." << std::endl;
    
    delete dispatcher;
    delete collisionConfig;
    return 0;
}
