#include "lzz_Factory.h"




lzz_Factory::lzz_Factory()
{
//	lzz_out << "lzz_Factory¹¹Ôì" << lzz_endline;
}


lzz_Factory::~lzz_Factory()
{
	lzz_Deletes(request);
	lzz_Deletes(respone);

}

void lzz_Factory::onLoad()
{
}

void lzz_Factory::init(lzz_SocketInterface* lzz_socket_interface, lzz_ClientList* p_lzz_client_list,char* p_str,SOCKADDR* p_sockaddr)
{
	this->sk = lzz_socket_interface;
	this->cl = p_lzz_client_list;
	this->request = p_str;
	if(p_sockaddr != lzz_nullptr)
		lzz_Memcpy(&address_sockaddr_, p_sockaddr, sizeof(SOCKADDR));
}

void lzz_Factory::BindView()
{
	
}

void lzz_Factory::backFunction(int actionType)
{
}