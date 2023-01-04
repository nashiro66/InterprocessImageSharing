#include <GL/glew.h>
#include <Spout.h>
#include "texture.hpp"

class Receiver {
public:
    Receiver();
    ~Receiver();
    void ShowLog();
    bool Connect();

private:
    Spout spout;
    Texture texture;
};