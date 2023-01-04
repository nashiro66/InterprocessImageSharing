#include <Spout.h>

class Sender {
public:
    Sender(int width, int height);
    ~Sender();
    void Connect(GLuint fbo);

private:
    Spout _spout;
    int _width;
    int _height;
};