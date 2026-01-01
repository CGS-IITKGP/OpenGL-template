#include <iostream>
#include <bullet/btBulletDynamicsCommon.h>

int main() {
    std::cout << "Testing Bullet Physics Installation..." << std::endl;
    
    // Just create a simple collision configuration to test
    btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
    
    std::cout << "✓ Bullet Physics initialized successfully!" << std::endl;
    std::cout << "✓ Collision configuration created" << std::endl;
    std::cout << "✓ Collision dispatcher created" << std::endl;
    
    // Cleanup
    delete dispatcher;
    delete collisionConfig;
    
    std::cout << "Test passed! Bullet is working." << std::endl;
    return 0;
}
