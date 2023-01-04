#include "sender.hpp"

Sender::Sender(int width, int height)
{
    spoututils::OpenSpoutConsole();
    spoututils::EnableSpoutLog();
    _width = width;
    _height = height;
    // setup spout
    const char* senderName = "sender";
    _spout.SetSenderName(senderName);
}

Sender::~Sender()
{
    _spout.ReleaseSender();
}


void Sender::Connect(GLuint fbo)
{
    _spout.SendFbo(fbo, _width, _height);
}
