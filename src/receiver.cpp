#include "receiver.hpp"

Receiver::Receiver():texture("../img/texture2.png", false)
{
    spoututils::OpenSpoutConsole();
    spoututils::EnableSpoutLog();
	// chose specific application
    const char* receiverName = "sender";
    spout.SetReceiverName(receiverName);
}

Receiver::~Receiver()
{
    spout.ReleaseReceiver();
}

void Receiver::ShowLog()
{
	std::string str;

	if (spout.IsConnected()) {
		str = spout.GetSenderName();
		str += " (";

		if (spout.GetSenderCPU())
		{
			str += "CPU share : ";
		}

		str += std::to_string(spout.GetSenderWidth());
		str += "x";
		str += std::to_string(spout.GetSenderHeight());

		if (spout.GetSenderFrame() > 0) {
			str += " : fps ";
			str += std::to_string((int)(round(spout.GetSenderFps())));
			str += " : frame ";
			str += std::to_string(spout.GetSenderFrame());
		}
		str += ") ";
		std::cout << str << std::endl;
	}
	else {
		str = "No sender detected";
		std::cout << str << std::endl;
	}

	if (!spout.IsGLDXready()) {
		if (spout.GetAutoShare()) {
			str = "CPU share receiver";
		}
		else {
			str = "Graphics not texture share compatible";
		}
		std::cout << str << std::endl;

		str = "Graphics adapter ";
		str += std::to_string(spout.GetAdapter());
		str += " : ";
		str += spout.AdapterName();
		std::cout << str << std::endl;
	}
}

bool Receiver::Connect()
{
    //if (spout.ReceiveTexture()) {
    //    if (spout.BindSharedTexture()) {
    //        GLuint texID = spout.GetSharedTextureID();
    //        if ((int)texture.GetTexWidth() == spout.GetSenderWidth() && (int)texture.GetTexHeight() == spout.GetSenderHeight()) {
    //            spout.CopyTexture(texID, GL_TEXTURE_2D,
    //                texture.GetTexId(),
    //                GL_TEXTURE_2D,
    //                spout.GetSenderWidth(), spout.GetSenderHeight());
    //        }
    //        //spout.UnBindSharedTexture();
    //    }
    //}

    if (spout.ReceiveTexture(texture.GetTexId(), GL_TEXTURE_2D, false)) {
		if (spout.IsUpdated())
		{
			texture.Resize(spout.GetSenderWidth(), spout.GetSenderHeight());
		}
    }

	spout.BindSharedTexture();
    if(!spout.IsConnected())
    {
        return false;
    }

	ShowLog();

    return true;
}
