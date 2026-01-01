#include <iostream>
#include <btBulletDynamicsCommon.h>

int main() {
    std::cout << "Testing Bullet Physics..." << std::endl;
    
    // Simple test
    btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    
    std::cout << "✓ Bullet collision configuration created successfully!" << std::endl;
    std::cout << "Bullet Physics is working!" << std::endl;
    
    delete collisionConfig;
    return 0;
}
