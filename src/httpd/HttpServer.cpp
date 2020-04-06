#include "HttpServer.hpp"

void HTTPServer::onData(int fd, G::event_type_t event_type)
{

}

HTTPServer::HTTPServer()
{

}

HTTPServer::~HTTPServer()
{

}

int HTTPServer::service(int max)
{
    return this->_service(this, max);
}
